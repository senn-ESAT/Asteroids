struct UFO{
  mm::Vec2 pos, speed;
  esat::Vec3 *UFOPoints;
  Bullet *enemyBullets;
  float size;       // There are 4 sizes that also represent the health
  bool alive, type; // If the ufo is alive or not, what type of ufo is it
  double TimeDeath, newDirection, fireTime; // the time the the ufo has been killed
  int rate = 7;     // At the first level the spawn rate will be 70% the easy UFO
};

void initUFO(UFO *enemy){
  enemy->TimeDeath = esat::Time();
  enemy->alive = false;
}

void SpawnUFO(UFO *enemy){
  if(!enemy->alive && enemy->TimeDeath + 10000 < esat::Time()){ //10 sec after death it respawn
    
    enemy->alive = true;
    enemy->fireTime = esat::Time();

    if(rand()%2){ // RIGHT
      enemy->pos = {0.0f, 50 + ((float)(rand()) / (float)(ScreenY - 100))}; // 0,50-550
      enemy->speed = { 1.0f, 0.0f};
    }else{  // LEFT
      enemy->pos = {ScreenX, 50 + ((float)(rand()) / (float)(ScreenY - 100))}; // 0,50-550
      enemy->speed = { -1.0f, 0.0f};
    }
    enemy->size = 5.0f;

    //int randomType = rand()%10;
    //if(randomType < enemy->rate){
      enemy->type = 1;
    // }else{
    //   enemy->type = 1;
    // }

    enemy->UFOPoints = (esat::Vec3*)malloc(7*sizeof(esat::Vec3));
    // TO-DO encontrar los puntos correctos
    switch (enemy->type)    {
      case 0:
        enemy->UFOPoints[0] = { 0.0f, 0.0f, 1.0f};
        enemy->UFOPoints[1] = { 2.0f, 0.0f, 1.0f};
        enemy->UFOPoints[2] = { 2.0f, 2.0f, 1.0f};
        enemy->UFOPoints[3] = { 0.0f, 2.0f, 1.0f};
        enemy->UFOPoints[4] = { 0.0f, 0.0f, 1.0f};
        enemy->UFOPoints[5] = { 2.0f, 0.0f, 1.0f};
        enemy->UFOPoints[6] = { 2.0f, 2.0f, 1.0f};
      break;
      case 1:
        enemy->UFOPoints[0] = { 0.0f, 0.0f, 1.0f};
        enemy->UFOPoints[1] = { 2.0f, 0.0f, 1.0f};
        enemy->UFOPoints[2] = { 2.0f, 2.0f, 1.0f};
        enemy->UFOPoints[3] = { 0.0f, 2.0f, 1.0f};
        enemy->UFOPoints[4] = { 0.0f, 0.0f, 1.0f};
        enemy->UFOPoints[5] = { 2.0f, 0.0f, 1.0f};
        enemy->UFOPoints[6] = { 2.0f, 2.0f, 1.0f};
      break;
    }
  }
}

void MoveUFO(mm::Vec2 *velo, mm::Vec2 *pos){
  printf("\nPOS--> ");
  mm::Vec2Print(*pos);
  printf("SPEED-->");
  mm::Vec2Print(*velo);
  
  *pos = mm::sumVec2(*pos, *velo);
}

void ManageUFO(UFO *enemy, mm::Vec2 playerPos){
  printf("TYPE: %d", enemy->type);
  switch (enemy->type){
    case 0:
      printf("BRUH");
      if(enemy->fireTime + 750 < esat::Time()){
        printf("||||||||||||||||||||||||");
        mm::Vec2 bpos = enemy->pos;
        mm::Vec2 dir;
        switch(rand()%8){
          case 0: dir = {1.0f,0.0f}; break;
          case 1: dir = {0.0f,1.0f}; break;
          case 2: dir = {-1.0f,0.0f}; break;
          case 3: dir = {0.0f,-1.0f}; break;
          case 4: dir = {0.5f,0.5f}; break;
          case 5: dir = {-0.5f,0.5f}; break;
          case 6: dir = {0.5f,-0.5f}; break;
          case 7: dir = {-0.5f,-0.5f}; break;
        }
        dir = normalize(dir);
        
        mm::Vec2 bspeed;
        bspeed = mm::scaleV2(dir, 7.5f);
        
        printf("[FIRE]\n");
        InsertBullet(&enemy->enemyBullets, bpos, bspeed, 1);
        enemy->fireTime = esat::Time();
      }
    break;
    
    case 1:
      if(enemy->fireTime + 750 < esat::Time()){
        printf("---------------------");

        mm::Vec2 bpos = enemy->pos;
        mm::Vec2 dir;

        dir = mm::subVec2(playerPos, enemy->pos);

        dir = normalize(dir);
        
        mm::Vec2 bspeed;
        bspeed = mm::scaleV2(dir, 7.5f);
        
        printf("[FIRE]\n");
        InsertBullet(&enemy->enemyBullets, bpos, bspeed, 1);
        enemy->fireTime = esat::Time();
      }
    break;
  }

  if(BulletAmount(enemy->enemyBullets) != 0){
    ElimBullet(&enemy->enemyBullets);
  }
}