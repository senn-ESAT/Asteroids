


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
  printf("\nCOlision start: \n");
  int j = 0;
  while(j < nAreas){
    printf("  Area start\n");
    
    esat::Vec2 *areaPoints = nullptr;
    areaPoints = (esat::Vec2*)malloc(colsion[j].nPoints * sizeof(esat::Vec2));
    for (int i = 0; i < colsion[j].nPoints; ++i) {
      esat::Vec3 tmp = esat::Mat3TransformVec3(matPoint, colsion[j].area[i]);
      areaPoints[i] = {tmp.x, tmp.y};
    }
    printf("    Pre while");
    
    int i = 0;
    bool stillSame = true;
    float previusCross = 0.0f;
    printf("\n");
    while(stillSame && i < colsion[j].nPoints){

      mm::Vec2 A = {areaPoints[i].x,areaPoints[i].y};       // 0 -> 1 -> 2 etc...
      mm::Vec2 B = {areaPoints[i+1].x, areaPoints[i+1].y};  // 1 -> 2 -> 3 etc...
      mm::Vec2 p = {point.x, point.y};      // p

      printf("  CROSS");
      float newCross = PointInTriangle(p, A, B);

      if(i != 0){
        if((newCross < 0 && previusCross < 0) || (newCross > 0 && previusCross > 0)){
          stillSame = true;
        }else{
          stillSame = false;
        }
      }
      previusCross = newCross;
      i++;
    }
      
    if(stillSame){
      printf("  YES COLISION DETECTED WOWOWOWOWOOWOW");
      return true;
    }
      printf("  FREE AND RESTART");

    j++;
    free(areaPoints);

  }
  return false;
}

void CheckCollisions(Ship *ship, Bullet **bullets, Asteroids **aste, UFO **enemy, esat::Mat3 *mat){

  // if(ship->noHit + 2000 < esat::Time()){

  // }
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
          }
        }
      }
    }
  }
}