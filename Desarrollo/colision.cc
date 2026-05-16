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
  printf(" PROXIMITY ");
  mm::Vec2 p2 = mm::subVec2(pos1, pos2);

  printf(" CHeckProximity ");
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

    esat::DrawSetFillColor(rand()%255,rand()%255,rand()%255);
    esat::DrawSolidPath(&areaPoints[0].x, nPoints);
    
    int i = 0;
    bool stillSame = true;
    float previousCross = 0.0f;
    printf("\n");
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

void PlayerBulletCollisions(Bullet **bullets, Asteroids **aste, UFO **enemy, esat::Mat3 *mat){
  if(BulletAmount((*bullets))){ // if there are bullets
    Bullet *b;
    for(b = *bullets; b != nullptr; b = b->prox){ // loop every bullet
      printf("Bucle bullets: [%f]\n", b->p1.x);

      ////////////// ASTYEROIDS COLLISIONS /////////////////
      for(int i = 0; i < nAste; i++){   // loop every asteroid
        printf(" Bucle ASTE->");
        if(ChechProximity((*aste)[i].pos, b->p1, (*aste)[i].size)){ // if they are close enough to colision
          esat::Vec2 p = {b->p1.x, b->p1.y};
          if(colisionDetector(p, mat[0], (*aste)[i].areas, (*aste)[i].nAreas)){ // if they are actually colisioning

            SplitAste(&(*aste), i);
            DellBulletOnHit(b, &*bullets);
          }
        }
      }

      ////////////// UFO COLLISIONS /////////////////
      if((*enemy)->alive){
        if(ChechProximity((*enemy)->pos, b->p1, (*enemy)->size)){ // if they are close enough to colision
          esat::Vec2 p = {b->p1.x, b->p1.y};  // change from mm to esat

          if(colisionDetector(p, mat[1], (*enemy)->areas, (*enemy)->nAreas)){
            (*enemy)->alive = false;
            // delete bullet
          }
        }
      }
    }
  }

  // UFO COLLISIONS
}

void EnemyBulletCollisions(Bullet **bullets, Asteroids **aste, Ship *player, esat::Mat3 *mat){

  printf("\n\n INICIO ");
  if(BulletAmount((*bullets))){
    Bullet *b;
    for(b = *bullets; b != nullptr; b = b->prox){
      printf("Bucle bullets: [%f]\n", b->p1.x);
      for(int i = 0; i < nAste; i++){
        printf(" Bucle ASTE->");
        if(ChechProximity((*aste)[i].pos, b->p1, (*aste)[i].size)){
        
          printf("--------------[FoundProximity]-------------------");

          esat::Vec2 p = {b->p1.x, b->p1.y};
          if(colisionDetector(p, mat[0], (*aste)[i].areas, (*aste)[i].nAreas)){
            printf("[COLISION]");

            SplitAste(&(*aste), i);
            // delete bullet
          }
        }
      }
      // if(ChechProximity(player->pos)){

      // }
    }
  }


  // UFO COLLISIONS
}