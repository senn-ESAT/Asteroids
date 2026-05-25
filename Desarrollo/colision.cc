float crossCalculator(mm::Vec2 A, mm::Vec2 B){
  return (A.x * B.y) - (A.y * B.x);
}

float PointInTriangle(mm::Vec2 p, mm::Vec2 a, mm::Vec2 b){

    mm::Vec2 ab = mm::subVec2(b, a);
    mm::Vec2 ap = mm::subVec2(p, a);

    //  P
    //  |
    //  |
    //  A------>B

    // si mismo signo del cross product entonces adentro

    float cross = crossCalculator(ab, ap);

    return cross;
}

bool ChechProximity(mm::Vec2 pos1, mm::Vec2 pos2, float offset){
  mm::Vec2 p2 = mm::subVec2(pos1, pos2);

  if((p2.x < offset && p2.x > - offset) && (p2.y < offset && p2.y > - offset)){ // Are they in the same space
    return true;
  }
  return false;
}

bool colisionDetector(esat::Vec2 point, esat::Mat3 matPoint, colisionArea *colsion, int nAreas){
  int j = 0;
  while(j < nAreas){
    
    int nPoints = colsion[j].nPoints;
    esat::Vec2 *areaPoints = (esat::Vec2*)malloc(nPoints * sizeof(esat::Vec2));
    for (int i = 0; i < nPoints; ++i) {
      esat::Vec3 tmp = esat::Mat3TransformVec3(matPoint, colsion[j].area[i]);    
      areaPoints[i] = {tmp.x, tmp.y};
    }
    
    int i = 0;
    bool stillSame = true;
    float previousCross = 0.0f;
    while(stillSame && i < nPoints){
      mm::Vec2 A = {areaPoints[i].x, areaPoints[i].y};
      mm::Vec2 B = {areaPoints[(i + 1) % nPoints].x, areaPoints[(i + 1) % nPoints].y};
      mm::Vec2 p = {point.x, point.y};

      float newCross = PointInTriangle(p, A, B);

      if(i != 0){
        if((newCross < 0 && previousCross < 0) || (newCross > 0 && previousCross > 0)){
          stillSame = true;
        }else{
          stillSame = false;
        }
      }
      previousCross = newCross;
      i++;
    }
    
    free(areaPoints);
    if(stillSame){
      return true;
    }

    j++;
  }
  return false;
}

void PlayerBulletCollisions(Bullet **bullets, Asteroids **aste, UFO **enemy, int *points){
  if(BulletAmount((*bullets))){ // if there are bullets
    Bullet *b;
    bool isBcompromized = false;
    // i use the b to navigate so if i delete a bullet it mess up the search and crashes so isBcompromized enter the scene to save the day

    for(b = *bullets; !isBcompromized && b != nullptr; b = b->prox){ // loop every bullet

      ////////////// ASTYEROIDS COLLISIONS /////////////////
      for(int i = 0; i < nAste; i++){   // loop every asteroid
        if(ChechProximity((*aste)[i].pos, b->p1, (*aste)[i].size)){ // if they are close enough to colision
          esat::Vec2 p = {b->p1.x, b->p1.y};
          esat::Mat3 matAs = MatAsteroid((*aste)[i].pos, (*aste)[i].size);
          if(colisionDetector(p, matAs, (*aste)[i].areas, (*aste)[i].nAreas)){ // if they are actually colisioning
            isBcompromized = true;
            int lasone = SplitAste(&(*aste), i);
            if(lasone){
              lvl++;
              initAsteroids(&(*aste), 5+lvl);
            }
            DellBulletOnHit(b, &*bullets);
            if((*aste)[i].size > 30){
              *points += 20;
            }else if((*aste)[i].size > 20){
              *points += 50;
            }else{
              *points += 100;
            }
          }
        }
      }
      ////////////// UFO COLLISIONS /////////////////
      if((*enemy)->alive){
        if(ChechProximity((*enemy)->pos, b->p1, (*enemy)->size * 3)){ // if they are close enough to colision
          esat::Vec2 p = {b->p1.x, b->p1.y};  // change from mm to esat
  
          esat::Mat3 matUf = MatAsteroid((*enemy)->pos, (*enemy)->size);
          if(colisionDetector(p, matUf, (*enemy)->areas, (*enemy)->nAreas)){
            (*enemy)->alive = false;
            (*enemy)->TimeDeath = esat::Time();
            DellBulletOnHit(b, &*bullets);
            if((*enemy)->size > 3){
              *points += 200;
            }else{
              *points += 1000;
            }
            isBcompromized = true;
          }
        }
      }
    }
  }  
}

bool IsInsidePlayer(Ship *ship, mm::Vec2 pointPos){
  esat::Vec2 ShipPos = {ship->pos.x, ship->pos.y};

    bool stillInside = true;
    float previusCross; // guarda el resultado de crossproduct del bucle precedente
    
    int nPoints = 3, i = 0;
    while(stillInside && i < nPoints * 2){
                      // x                  // y
      mm::Vec2 A = {ship->puntosNave[i], ship->puntosNave[i + 1]};     // 0 -> 1 -> 2 etc...
      mm::Vec2 B = {ship->puntosNave[i + 2], ship->puntosNave[i + 3]}; // 1 -> 2 -> 3 etc...
      mm::Vec2 p = {pointPos.x, pointPos.y};               // p
      float newCross = PointInTriangle(p, A, B);

      if(i != 0){
        if((newCross < 0 && previusCross < 0) || (newCross > 0 && previusCross > 0)){
          stillInside = true;
        }else{
          stillInside = false;
        }
      }
      previusCross = newCross;
      i+=2;
    }

    if(stillInside){
      return true;
    }
    return false;
  }
  
void EnemyBulletCollisions(Bullet **bullets, Asteroids **aste, Ship **player){
  if(BulletAmount((*bullets))){
    Bullet *b;
    bool isBcompromized = false;
    for(b = *bullets; !isBcompromized && b != nullptr; b = b->prox){
      
      // PLAYER COLISION
      //if player dead or invulnerable then skip
      if((*player)->deathTime+1000 < esat::Time() && (*player)->noHit + 2000 < esat::Time()){
        // if close then check solison
        if(ChechProximity((*player)->pos, b->p1, 50)){
          if(IsInsidePlayer(*player, b->p1)){
            DellBulletOnHit(b, &*bullets);
            (*player)->health--;
            (*player)->dying = true;
            (*player)->deathTime = esat::Time();
            isBcompromized = true;
          }
        }
      }
      
      for(int i = 0; i < nAste; i++){   // loop every asteroid
        if(ChechProximity((*aste)[i].pos, b->p1, (*aste)[i].size)){ // if they are close enough to colision
          esat::Vec2 p = {b->p1.x, b->p1.y};
          esat::Mat3 matAs = MatAsteroid((*aste)[i].pos, (*aste)[i].size);
          if(colisionDetector(p, matAs, (*aste)[i].areas, (*aste)[i].nAreas)){ // if they are actually colisioning
            isBcompromized = true;
            int lasone = SplitAste(&(*aste), i);
            if(lasone){
              lvl++;
              initAsteroids(&(*aste), 5+lvl);
            }
            DellBulletOnHit(b, &*bullets);
          }
        }
      }
    }
  }
}

void BodyCollisionWithPlayer(Asteroids **aste, UFO **enemy, Ship **player){
  // is player unkillable
  if((*player)->deathTime+1000 < esat::Time() && (*player)->noHit + 2000 < esat::Time()){
    ////////////// ASTYEROIDS COLLISIONS /////////////////
    for(int i = 0; i < nAste && !((*player)->dying); i++){   // loop every asteroid
      if(ChechProximity((*aste)[i].pos, (*player)->pos, (*aste)[i].size)){ // if they are close enough to colision
        esat::Mat3 mat = MatAsteroid((*aste)[i].pos, (*aste)[i].size);

        for(int j = 0; j < ((*aste)[i].nPoints) && !((*player)->dying); j++){     

          esat::Vec2 p = {(*aste)[i].points[j].x, (*aste)[i].points[j].y};
          esat::Vec2 tmp = esat::Mat3TransformVec2(mat, p);    

          mm::Vec2 pnt = {tmp.x, tmp.y};

          if(IsInsidePlayer(*player, pnt)){
            (*player)->health--;
            (*player)->dying = true;
            (*player)->deathTime = esat::Time();
          }
        }
      }
    }

      //////////// UFO COLLISIONS /////////////////
    if((*enemy)->alive){
      if(ChechProximity((*enemy)->pos, (*player)->pos, 20)){ // if they are close enough to colision
        esat::Mat3 mat = MatAsteroid((*enemy)->pos, (*enemy)->size);

        for(int j = 0; j < 12 && !((*player)->dying); j++){     

          esat::Vec2 p = {(*enemy)->UFOPoints[j].x, (*enemy)->UFOPoints[j].y};
          esat::Vec2 tmp = esat::Mat3TransformVec2(mat, p);    

          mm::Vec2 pnt = {tmp.x, tmp.y};

          if(IsInsidePlayer(*player, pnt)){
            (*player)->health--;
            (*player)->dying = true;
            (*player)->deathTime = esat::Time();
          }
        }
      }
    }
  }
}