#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "esat/window.h"
#include "esat/draw.h"
#include "esat/input.h"
#include "esat/sprite.h"
#include "esat/time.h"

#include "./MathLib.h"
#include "./bullet.cc"
#include "./asteroids.cc"

struct Ship{
  mm::Vec2 pos;
  mm::Vec2 speed;
  float angulo = 0.0f;
  float *puntosNave;
};

const unsigned int ScreenX = 800;
const unsigned int ScreenY = 600;
const float max_speed = 10.0f;

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

void DrawThings(Ship ship, Bullet *bullets, Asteroids *aste){
  esat::DrawSetStrokeColor(255, 255, 255);
  esat::DrawPath(ship.puntosNave, 4);

  float *puntosDisparo;
  puntosDisparo = (float*)malloc(10*sizeof(float));  
  for(int i = 0; i < BulletAmount(bullets); i++){
    puntosDisparo[0] = bullets[i].p1.x - 1;
    puntosDisparo[1] = bullets[i].p1.y;
    puntosDisparo[2] = bullets[i].p1.x + 1;
    puntosDisparo[3] = bullets[i].p1.y;
    puntosDisparo[4] = bullets[i].p1.x;
    puntosDisparo[5] = bullets[i].p1.y - 1;
    puntosDisparo[6] = bullets[i].p1.x;
    puntosDisparo[7] = bullets[i].p1.y + 1;
    puntosDisparo[8] = bullets[i].p1.x - 1;
    puntosDisparo[9] = bullets[i].p1.y;
    esat::DrawSolidPath(puntosDisparo, 5);
  }

  for(int i = 0; i < 5; i++){
    esat::Mat3 a = MatAsteroid(aste[i].pos, aste[i].size);
    DrawAsteroid(a);
  }
}

void Controls(Ship *ship, Bullet **bullets){
  //speed
  float current_speed = mm::magnitudeV2(ship->speed);
  if(esat::IsKeyPressed('w') || esat::IsKeyPressed('W')){
    if(current_speed > max_speed){
      ship->speed = mm::normalize(ship->speed);
      ship->speed = mm::scaleV2(ship->speed, max_speed);
    }else{
      mm::Vec2 thrust = {sinf(ship->angulo), cosf(ship->angulo)};
      thrust = mm::scaleV2(thrust, 0.1f);
      ship->speed = mm::sumVec2(ship->speed, thrust);
    }
  }

  //direction
  if(esat::IsKeyPressed('d') || esat::IsKeyPressed('D')){
    ship->angulo += 0.08f;
  }else if(esat::IsKeyPressed('a') || esat::IsKeyPressed('A')){
    ship->angulo -= 0.08f;
  }

  // shoot
  if(esat::IsSpecialKeyDown(esat::kSpecialKey_Space)){
    mm::Vec2 pos = ship->pos;
    mm::Vec2 dir = {sinf(ship->angulo), cosf(ship->angulo)};
    mm::Vec2 speed;
    dir = normalize(dir);
    if(current_speed > 8.0f){
      speed = mm::scaleV2(dir, mm::magnitudeV2(ship->speed)+2);
    }
    else{speed = mm::scaleV2(dir, 8.0f);}

    InsertBullet(&(*bullets), pos, speed, esat::Time());
  }

  if(BulletAmount(*bullets)){
    ElimBullet(&(*bullets), esat::Time());
  }
}

void Move(Ship *ship, Bullet **bullets){

  ship->pos = mm::sumVec2(ship->pos, ship->speed);
  
  for(int i = 0; i < BulletAmount(*bullets); i++){
    printf("i");
    bullets[i]->p1 = mm::sumVec2(bullets[i]->p1, bullets[i]->speed);
  }
}

int checkBorderColisions(mm::Vec2 coord){
  if(coord.x < 0)       {return 1;}
  if(coord.x > ScreenX) {return 2;}
  if(coord.y < 0)       {return 3;}
  if(coord.y > ScreenY) {return 4;}
  return 0;
}

void pacman(mm::Vec2 *coord, int *way){
  switch(*way){
    printf("[pacma] ");

    case 1: coord->x = ScreenX; break;
    case 2: coord->x = 0;       break;
    case 3: coord->y = ScreenY; break;
    case 4: coord->y = 0;       break;
  }
  *way = 0;
}

void CheckBorder(Ship *ship, Bullet **bullets){
  int colision = 0;
  colision = checkBorderColisions(ship->pos);
  if(colision != 0){
    pacman(&ship->pos, &colision);
  }

  for(int i = 0; i < BulletAmount(*bullets); i++){
    colision = checkBorderColisions(bullets[i]->p1);
    if(colision != 0){
      pacman(&bullets[i]->p1, &colision);
    }
  }
}

int esat::main(int argc, char** argv) {
  Ship ship = {{ScreenX/2.0f, ScreenY/2.0f}, {0.0f, 0.0f}};
  Bullet *bullets; bullets = nullptr;
  Asteroids *asteroid = nullptr;
  srand(time(nullptr));
  double current_time = 0.0;
  double last_time = 0.0;
  double fps = 60.0;

  esat::WindowInit(ScreenX, ScreenY);
  esat::WindowSetMouseVisibility(true);

  initAsteroids(&asteroid);

  while (!esat::IsSpecialKeyDown(esat::kSpecialKey_Escape) && esat::WindowIsOpened()) {
    last_time = esat::Time();
    esat::DrawBegin();
    esat::DrawClear(0, 0, 0);
    
    printf(" [init: %d ", BulletAmount(bullets));
    initShip(&ship);
    printf(" Draw: %d ", BulletAmount(bullets));
    DrawThings(ship, bullets, asteroid);
    printf(" Controls: %d ", BulletAmount(bullets));
    Controls(&ship, &bullets);
    printf(" Move: %d ", BulletAmount(bullets));
    Move(&ship, &bullets);
    printf(" border%d ", BulletAmount(bullets));
    CheckBorder(&ship, &bullets);
    printf(" %d] ", BulletAmount(bullets));
    
    // friction
    ship.speed = mm::scaleV2(ship.speed, 0.995f);
    
    esat::DrawEnd();
    esat::WindowFrame();
    do {
      current_time = esat::Time();
    } while((current_time - last_time) <= 1000.0 / fps);
    printf("[end]\n");
  }
  esat::WindowDestroy();
  return 0;
}