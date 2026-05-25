struct UFO{
  mm::Vec2 pos, speed;
  esat::Vec3 *UFOPoints = nullptr;
  colisionArea *areas;
  Bullet *enemyBullets = nullptr;
  float size;       // There are 4 sizes that also represent the health
  bool alive, type; // If the ufo is alive or not, what type of ufo is it
  double TimeDeath, newDirection, fireTime; // the time the the ufo has been killed
  int rate = 8, nAreas;     // At the first level the spawn rate will be 80% the dumb UFO
};

void initUFO(UFO *enemy){
  enemy->TimeDeath = esat::Time();
  enemy->alive = false;
}

void SpawnUFO(UFO *enemy){
  if(enemy->alive == false && enemy->TimeDeath + 5000 < esat::Time()){ //10 sec after death it respawn
    enemy->alive = true;
    enemy->fireTime = esat::Time();
    enemy->newDirection = esat::Time();

    if(rand()%2){ // RIGHT
      enemy->pos = {0.0f, 50 + ((float)(rand()) / (float)(ScreenY - 100))}; // 0,50-550
      enemy->speed = { 2.0f, 0.0f};
    }else{  // LEFT
      enemy->pos = {ScreenX, 50 + ((float)(rand()) / (float)(ScreenY - 100))}; // 0,50-550
      enemy->speed = { -2.0f, 0.0f};
    }
    
    int randomType = rand()%10;
    if(randomType < enemy->rate){
      enemy->type = 0;
      enemy->size = 4.0f;
    }else{
      enemy->type = 1;
      enemy->size = 2.0f;
    }

    enemy->UFOPoints = (esat::Vec3*)malloc(12*sizeof(esat::Vec3));

    enemy->UFOPoints[0] = { 2.0f, -1.0f,  1.0f};
    enemy->UFOPoints[1] = { -2.0f, -1.0f,   1.0f};
    enemy->UFOPoints[2] = { -5.0f, 1.0f,  1.0f};
    enemy->UFOPoints[3] = { 5.0f, 1.0f, 1.0f};
    enemy->UFOPoints[4] = { 2.0f, 3.0f, 1.0f};
    enemy->UFOPoints[5] = { -2.0f, 3.0f,  1.0f};
    enemy->UFOPoints[6] = { -5.0f, 1.0f,  1.0f};
    enemy->UFOPoints[7] = { -2.0f, -1.0f,   1.0f};
    enemy->UFOPoints[8] = { -1.0f, -3.0f,   1.0f};
    enemy->UFOPoints[9] = { 1.0f, -3.0f,  1.0f};
    enemy->UFOPoints[10]= { 2.0f, -1.0f,  1.0f};
    enemy->UFOPoints[11]= { 5.0f, 1.0f, 1.0f};

    enemy->nAreas = 2;
    enemy->areas = (colisionArea*)malloc(2 * sizeof(colisionArea));

    enemy->areas[0].nPoints = 4; // cockpit
    enemy->areas[0].area = (esat::Vec3*)malloc(5 * sizeof(esat::Vec3));

    enemy->areas[0].area[0]= { -2.0f, -1.0f,   1.0f};  // 7  - 0
    enemy->areas[0].area[1]= { -1.0f, -3.0f,   1.0f};  // 8  - 1
    enemy->areas[0].area[2]= { 1.0f, -3.0f,  1.0f};    // 9  - 2
    enemy->areas[0].area[3]= { 2.0f, -1.0f,  1.0f};    // 10 - 3
    enemy->areas[0].area[4]= { -2.0f, -1.0f,   1.0f};  // 7  - 4

    enemy->areas[1].nPoints = 6;  // body
    enemy->areas[1].area = (esat::Vec3*)malloc(7 * sizeof(esat::Vec3));

    enemy->areas[1].area[0] = { 2.0f, -1.0f,  1.0f};    // 0 - 0
    enemy->areas[1].area[1] = { -2.0f, -1.0f,   1.0f};  // 1 - 1
    enemy->areas[1].area[2] = { -5.0f, 1.0f,  1.0f};    // 2 - 2
    enemy->areas[1].area[3] = { -2.0f, 3.0f,  1.0f};    // 5 - 3
    enemy->areas[1].area[4] = { 2.0f, 3.0f, 1.0f};      // 4 - 4
    enemy->areas[1].area[5] = { 5.0f, 1.0f, 1.0f};      // 3 - 5
    enemy->areas[1].area[6] = { 2.0f, -1.0f,  1.0f};    // 0 - 6
  }
}

void MoveUFO(mm::Vec2 *velo, mm::Vec2 *pos){
  mm::Vec2Print(*pos);
  mm::Vec2Print(*velo);
  
  *pos = mm::sumVec2(*pos, *velo);
}

void UFOChageDir(mm::Vec2 *velo){
  if(velo->y != 0){
    velo->y = 0;
  }else if(rand()%2 == 0){
    velo->y = 1.0f;
  }else{
    velo->y = -1.0f;
  }
}

void ManageUFO(UFO *enemy, mm::Vec2 playerPos){
  switch (enemy->type){
    case 0:
      if(enemy->fireTime + 500 < esat::Time()){
        mm::Vec2 dir;

        // random dir of the bullet
        switch(rand()%8){
          case 0: dir = {1.0f,0.0f};    break;
          case 1: dir = {0.0f,1.0f};    break;
          case 2: dir = {-1.0f,0.0f};   break;
          case 3: dir = {0.0f,-1.0f};   break;
          case 4: dir = {0.5f,0.5f};    break;
          case 5: dir = {-0.5f,0.5f};   break;
          case 6: dir = {0.5f,-0.5f};   break;
          case 7: dir = {-0.5f,-0.5f};  break;
        }
        
        dir = normalize(dir);
        
        mm::Vec2 bspeed = mm::scaleV2(dir, 7.5f);
        
        InsertBullet(&enemy->enemyBullets, enemy->pos, bspeed, 1);
        enemy->fireTime = esat::Time();
      }
    break;
    
    case 1:
      if(enemy->fireTime + 500 < esat::Time()){
        mm::Vec2 dir;

        dir = mm::subVec2(playerPos, enemy->pos);
        dir = normalize(dir);
        
        mm::Vec2 bspeed = mm::scaleV2(dir, 7.5f);
        
        InsertBullet(&enemy->enemyBullets, enemy->pos, bspeed, 1);
        enemy->fireTime = esat::Time();
      }
    break;
  }
  if(enemy->newDirection + 1500 < esat::Time()){
    UFOChageDir(&enemy->speed);

    enemy->newDirection = esat::Time();
  }

  if(BulletAmount(enemy->enemyBullets) != 0){
    ElimBullet(&enemy->enemyBullets);
  }
}
