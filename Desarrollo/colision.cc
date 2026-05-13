
struct colisionArea{
  int nPoints;
  esat::Vec3 *area;   // puntos area
};

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

bool ChechProximity(mm::Vec2 pos1, esat::Vec2 pos2, float offset){

  mm::Vec2 p2 = {pos2.x, pos2.y};
  p2 = mm::subVec2(pos1, p2);

  if((p2.x < offset && p2.x > - offset) && (p2.y < offset && p2.y > - offset)){ // Are they in the same space
    return true;
  }
  return false;
}

bool colisionDetector(esat::Vec2 point, esat::Mat3 matPoint, colisionArea *colsion, int nAreas){
  int j = 0;
  while(j < nAreas){
    
    esat::Vec2 *areaPoints = nullptr;
    areaPoints = (esat::Vec2*)malloc(colsion[j].nPoints * sizeof(esat::Vec2));
    for (int i = 0; i < colsion[j].nPoints; ++i) {
      esat::Vec3 tmp = esat::Mat3TransformVec3(matPoint, colsion[j].area[i]);    
      areaPoints[i] = {tmp.x, tmp.y};
    }
    
    int i = 0;
    bool stillSame = true;
    float previusCross = 0.0f;
    printf("\n");
    while(stillSame && i < colsion[j].nPoints){

      mm::Vec2 A = {areaPoints[i].x,areaPoints[i].y};       // 0 -> 1 -> 2 etc...
      mm::Vec2 B = {areaPoints[i+1].x, areaPoints[i+1].y};  // 1 -> 2 -> 3 etc...
      mm::Vec2 p = {point.x, point.y};      // p

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
      return true;
    }

    j++;
    free(areaPoints);
  }
  return false;
}