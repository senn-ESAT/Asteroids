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
#include "./enemies.cc"

struct Ship{
  mm::Vec2 pos;
  mm::Vec2 speed;
  float angulo = 0.0f;
  float *puntosNave;
};

const unsigned int ScreenX = 800;
const unsigned int ScreenY = 600;
const float max_speed = 7.0f;

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

void DrawThings(Ship ship, Bullet *bullets, Asteroids *aste, UFO *enemy){
  esat::DrawSetStrokeColor(255, 255, 255);
  esat::DrawPath(ship.puntosNave, 4);

  float *puntosDisparo;
  puntosDisparo = (float*)malloc(10*sizeof(float));
  Bullet *b;
  for(b = bullets; b != nullptr; b = b->prox){
    puntosDisparo[0] = b->p1.x - 1;
    puntosDisparo[1] = b->p1.y;
    puntosDisparo[2] = b->p1.x + 1;
    puntosDisparo[3] = b->p1.y;
    puntosDisparo[4] = b->p1.x;
    puntosDisparo[5] = b->p1.y - 1;
    puntosDisparo[6] = b->p1.x;
    puntosDisparo[7] = b->p1.y + 1;
    puntosDisparo[8] = b->p1.x - 1;
    puntosDisparo[9] = b->p1.y;
    esat::DrawSolidPath(puntosDisparo, 5);
  }

  for(int i = 0; i < 5; i++){
    esat::Mat3 a = MatAsteroid(aste[i].pos, aste[i].size);
    DrawAsteroid(a, aste[i].points);
  }

  esat::Mat3 a = MatAsteroid(enemy->pos, enemy->size);
  DrawAsteroid(a, enemy->UFOPoints);
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
  if(esat::IsSpecialKeyDown(esat::kSpecialKey_Space) && 4 > BulletAmount((*bullets))){
    mm::Vec2 pos = ship->pos;
    mm::Vec2 dir = {sinf(ship->angulo), cosf(ship->angulo)};
    mm::Vec2 speed;
    dir = normalize(dir);

    speed = mm::scaleV2(dir, 7.5f);
    mm::Vec2Print(speed);

    InsertBullet(&(*bullets), pos, speed, 0);
  }

  if(BulletAmount(*bullets) != 0){

    ElimBullet(&(*bullets), esat::Time());

  }
}

void Move(Ship *ship, Bullet **bullets, Asteroids **aste){

  ship->pos = mm::sumVec2(ship->pos, ship->speed);
  
  Bullet *b;
  for(b = *bullets; b != nullptr; b = b->prox){
    b->p1 = mm::sumVec2(b->p1, b->speed);
  }

  for(int i = 0; i < 5; i++){
    (*aste)[i].pos = mm::sumVec2((*aste)[i].pos, (*aste)[i].speed);
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

    case 1: coord->x = ScreenX; break;
    case 2: coord->x = 0;       break;
    case 3: coord->y = ScreenY; break;
    case 4: coord->y = 0;       break;
  }
  *way = 0;
}

void CheckBorder(Ship *ship, Bullet **bullets, Asteroids **aste){
  int colision = 0;
  colision = checkBorderColisions(ship->pos);
  if(colision != 0){
    pacman(&ship->pos, &colision);
  }
  colision = 0;

  Bullet *b;
  for(b = *bullets; b != nullptr; b = b->prox){
    colision = checkBorderColisions(b->p1);
    if(colision != 0){
      pacman(&b->p1, &colision);
    }
  }
   colision = 0;

  for(int i = 0; i < 5; i++){
    colision = checkBorderColisions((*aste)[i].pos);
    if(colision != 0){
      pacman(&(*aste)[i].pos, &colision);
    }
  }
}

void LogIn(){}

void Menu(){}

void InGame(Ship *ship, Bullet **bullets, Asteroids **asteroid, UFO **enemy){
  initShip(&(*ship));

  DrawThings(*ship, *bullets, *asteroid, *enemy);

  Controls(&*ship, &*bullets);

  Move(&*ship, &*bullets, &*asteroid);

  CheckBorder(&*ship, &*bullets, &*asteroid);
    
    // friction
    ship->speed = mm::scaleV2(ship->speed, 0.995f);
}

int esat::main(int argc, char** argv) {
  Ship ship = {{ScreenX/2.0f, ScreenY/2.0f}, {0.0f, 0.0f}};
  Bullet *bullets = nullptr;
  Asteroids *asteroid = nullptr;
  UFO *enemy = nullptr;
  double current_time = 0.0;
  double last_time = 0.0;
  double fps = 60.0;
  int screen = 2; // 0 login/registrar 1 menu de juego 2 juego
  
  srand(time(nullptr));
  esat::WindowInit(ScreenX, ScreenY);
  esat::WindowSetMouseVisibility(true);
  printf("---------[Start Init]--------\n");
  printf("[Init Asteroids]\n");
  initAsteroids(&asteroid, 5);
  printf("[Init Enemy]\n");
  initUFO(&enemy);

  esat::DrawSetTextFont("./assets/VectorBattle-e9XO.ttf");

  while (!esat::IsSpecialKeyDown(esat::kSpecialKey_Escape) && esat::WindowIsOpened()) {
    last_time = esat::Time();
    esat::DrawBegin();
    esat::DrawClear(0, 0, 0);

    switch(screen){
      case 0:
        LogIn();
      break;
      case 1:
        Menu();
      break;
      case 2:
        InGame(&ship, &bullets, &asteroid, &enemy);
      break;    
    } 
    
    esat::DrawEnd();
    esat::WindowFrame();
    do {
      current_time = esat::Time();
    } while((current_time - last_time) <= 1000.0 / fps);
  }
  esat::WindowDestroy();
  return 0;
}