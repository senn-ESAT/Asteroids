struct Ship{
  mm::Vec2 pos;
  mm::Vec2 speed;
  float angulo = 0.0f;
  float *puntosNave;
};

void initShip(Ship *ship){
  float angle_a = ship->angulo;
  float angle_b = -160.8f + angle_a;
  float angle_c = 160.8f + angle_a;

  ship->puntosNave = (float*)malloc(8*sizeof(float));

  ship->puntosNave[0] = sinf(angle_a)*5+ship->pos.x;
  ship->puntosNave[1] = cosf(angle_a)*5+ship->pos.y;
  ship->puntosNave[2] = sinf(angle_b)*10+ship->pos.x;
  ship->puntosNave[3] = cosf(angle_b)*10+ship->pos.y;
  ship->puntosNave[4] = sinf(angle_c)*10+ship->pos.x;
  ship->puntosNave[5] = cosf(angle_c)*10+ship->pos.y;
  ship->puntosNave[6] = sinf(angle_a)*5+ship->pos.x;
  ship->puntosNave[7] = cosf(angle_a)*5+ship->pos.y;
}

void Controls(Ship *ship, Bullet **bullets){
  //speed
  float current_speed = mm::magnitudeV2(ship->speed);
  if(esat::IsKeyPressed('w') || esat::IsKeyPressed('W')){
    if(current_speed > max_speed){
      ship->speed = mm::normalize(ship->speed);
      ship->speed = mm::scaleV2(ship->speed, max_speed);
    }else{
      mm::Vec2 thrust = {sinf(ship->angulo), cosf(ship->angulo)}; // ship direction
      thrust = mm::scaleV2(thrust, 0.065f);                       // add acceleration
      ship->speed = mm::sumVec2(ship->speed, thrust);             // add thrust to current speed
    }
  }

  //direction
  if(esat::IsKeyPressed('d') || esat::IsKeyPressed('D')){
    ship->angulo += 0.08f;
  }else if(esat::IsKeyPressed('a') || esat::IsKeyPressed('A')){
    ship->angulo -= 0.08f;
  }

  // shoot
  if(esat::IsSpecialKeyDown(esat::kSpecialKey_Space) && 5 > BulletAmount((*bullets))){
    mm::Vec2 pos = ship->pos;
    mm::Vec2 dir = {sinf(ship->angulo), cosf(ship->angulo)};
    mm::Vec2 speed;
    dir = normalize(dir);

    speed = mm::scaleV2(dir, 7.5f);

    printf("[FIRE]\n");
    InsertBullet(&(*bullets), pos, speed, 0);
  }

  if(BulletAmount(*bullets) != 0){

    ElimBullet(&(*bullets), esat::Time());

  }
}