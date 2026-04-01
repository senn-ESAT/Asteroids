#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "esat/window.h"
#include "esat/draw.h"
#include "esat/input.h"
#include "esat/sprite.h"
#include "esat/time.h"

const unsigned int ScreenX = 800;
const unsigned int ScreenY = 600;
const float max_speed = 7.0f;

#include "./MathLib.h"
#include "./bullet.cc"
#include "./asteroids.cc"
#include "./enemies.cc"
#include "./accounts.cc"
#include "./ship.cc"

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
  Account user;
  double current_time = 0.0, last_time = 0.0, fps = 60.0;
  int screenSelector = 0, accountOption = 0, formSection = 0;   // 0 login/registrar 1 menu de juego 2 juego
  
  srand(time(nullptr));
  esat::WindowInit(ScreenX, ScreenY);
  esat::WindowSetMouseVisibility(true);
  printf("---------[START INIT]--------\n");
  printf("[INIT ASTEROID]\n");
  initAsteroids(&asteroid, 5);
  printf("[INIT ENEMY]\n");
  initUFO(&enemy);
  printf("[INIT ACCOUNT]\n");
  InitAccount(&user);
  printf("---------[END INIT]--------\n");


  esat::DrawSetTextFont("./assets/Hyperspace-JvEM.ttf");
  esat::DrawSetTextSize(30);

  while (!esat::IsSpecialKeyDown(esat::kSpecialKey_Escape) && esat::WindowIsOpened()) {
    last_time = esat::Time();
    esat::DrawBegin();
    esat::DrawClear(0, 0, 0);

    switch(screenSelector){
      case 0:
        Usersmanagement(&accountOption, &formSection, &user);
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