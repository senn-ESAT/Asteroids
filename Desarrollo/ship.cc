struct Ship{
  mm::Vec2 pos;
  mm::Vec2 speed;
  float angulo = 0.0f;
  float *puntosNave;
  int health = 3, healthGained = 1, score = 0;
  double deathTime = 0.0f, noHit = 0.0f;
  bool dying = false;
};

float* ShipShape(float angle_a, float angle_b, float angle_c, mm::Vec2 pos){
  float *puntosNave;
  puntosNave = (float*)malloc(8*sizeof(float));
  
  puntosNave[0] = sinf(angle_a)*10+pos.x;
  puntosNave[1] = cosf(angle_a)*10+pos.y;
  puntosNave[2] = sinf(angle_b)*7+pos.x;
  puntosNave[3] = cosf(angle_b)*7+pos.y;
  puntosNave[4] = sinf(angle_c)*7+pos.x;
  puntosNave[5] = cosf(angle_c)*7+pos.y;
  puntosNave[6] = sinf(angle_a)*10+pos.x;
  puntosNave[7] = cosf(angle_a)*10+pos.y;

  return puntosNave;
}

void initShip(Ship *ship){
  float angle_a = ship->angulo;
  float angle_b = -161.0f + angle_a;
  float angle_c = 161.0f + angle_a;

  ship->puntosNave = ShipShape(angle_a, angle_b, angle_c, ship->pos);
}

void Controls(Ship *ship, Bullet **bullets){
  float max_speed = 7.0f;
  //speed
  float current_speed = mm::magnitudeV2(ship->speed);
  if(esat::IsKeyPressed('w') || esat::IsKeyPressed('W')
    || esat::IsSpecialKeyPressed(esat::kSpecialKey_Up)){
    if(current_speed > max_speed){
      ship->speed = mm::normalize(ship->speed);
      ship->speed = mm::scaleV2(ship->speed, max_speed);
    }else{
      mm::Vec2 thrust = {sinf(ship->angulo), cosf(ship->angulo)}; // ship direction
      thrust = mm::scaleV2(thrust, 0.07f);                       // add acceleration
      ship->speed = mm::sumVec2(ship->speed, thrust);             // add thrust to current speed
    }
  }

  //direction
  if(esat::IsKeyPressed('a') || esat::IsKeyPressed('A') 
    || esat::IsSpecialKeyPressed(esat::kSpecialKey_Left)){
    ship->angulo += 0.07f;
  }else if(esat::IsKeyPressed('d') || esat::IsKeyPressed('D')
        || esat::IsSpecialKeyPressed(esat::kSpecialKey_Right)){
    ship->angulo -= 0.07f;
  }

  if(esat::IsKeyDown('g') || esat::IsKeyDown('G')){
    ship->pos = {(float)(rand()%800), (float)(rand()%600)};
    ship->noHit = esat::Time();
  }

  // shoot
  if(esat::IsSpecialKeyDown(esat::kSpecialKey_Space) && 5 > BulletAmount((*bullets))){
    mm::Vec2 pos = ship->pos;
    mm::Vec2 dir = {sinf(ship->angulo), cosf(ship->angulo)};
    mm::Vec2 speed;
    dir = normalize(dir);
    
    speed = mm::scaleV2(dir, 7.5f);
    
    InsertBullet(&(*bullets), pos, speed, 0);
  }
  
  if(BulletAmount(*bullets) != 0){
    ElimBullet(&(*bullets));
  }
}

void SpawnShip(Ship *player){
  player->noHit = esat::Time();
  player->pos = {ScreenX/2, ScreenY/2};
  player->speed = {0.0f, 0.0f};
  player->angulo = 0.0f;   
  player->dying = false; 
}