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

void UpdateFormSection(float *section){
  section[2] = section[0] + 300;  // x p2
  section[3] = section[1];        // y p2
  section[4] = section[2];        // x p3
  section[5] = section[1] + 35;   // y p3
  section[6] = section[0];        // x p4
  section[7] = section[1] + 35;   // y p4
  section[8] = section[0];        // x p5
  section[9] = section[1];        // y p6
}

void Register(int *form){
  if(esat::IsSpecialKeyDown(esat::kSpecialKey_Down) && *form < 8){
    *form+= 1;
  }else if(esat::IsSpecialKeyDown(esat::kSpecialKey_Up) && *form > 0){
    *form-= 1;
  }

  float *formSquare, *arrow;
  formSquare = (float*)malloc(10*sizeof(float));
  arrow = (float*)malloc(6*sizeof(float));
  arrow[0] = 20;
  arrow[1] = 130 + (50 * (*form));
  arrow[2] = 40;
  arrow[3] = arrow[1]+10;
  arrow[4] = 20;
  arrow[5] = arrow[1]+20;
  printf("[FORM]: %d\n", *form);
  formSquare[0] = ScreenX/2;  // x p1
  formSquare[1] = 120;        // y p1
  UpdateFormSection(&(*formSquare));

  esat::DrawText(50, 150, "NAME:");
  esat::DrawPath(formSquare, 5);

  esat::DrawText(50, 200, "SURNAME:");
  formSquare[1] += 50;
  UpdateFormSection(&(*formSquare));
  esat::DrawPath(formSquare, 5);

  esat::DrawText(50, 250, "BIRTH YEAR:");
  formSquare[1] += 50;
  UpdateFormSection(&(*formSquare));
  esat::DrawPath(formSquare, 5);

  esat::DrawText(50, 300, "PROVINCE:");
  formSquare[1] += 50;
  UpdateFormSection(&(*formSquare));
  esat::DrawPath(formSquare, 5);

  esat::DrawText(50, 350, "NATION:");
  formSquare[1] += 50;
  UpdateFormSection(&(*formSquare));
  esat::DrawPath(formSquare, 5);

  esat::DrawText(50, 400, "NICKNAME:");
  formSquare[1] += 50;
  UpdateFormSection(&(*formSquare));
  esat::DrawPath(formSquare, 5);

  esat::DrawText(50, 450, "PASSWORD:");
  formSquare[1] += 50;
  UpdateFormSection(&(*formSquare));
  esat::DrawPath(formSquare, 5);

  esat::DrawText(50, 500, "CONFIRM PASSWORD:");
  formSquare[1] += 50;
  UpdateFormSection(&(*formSquare));
  esat::DrawPath(formSquare, 5);
  
  formSquare[0] = ScreenX/2 - 110;      // x p1
  formSquare[1] = 520;            // y p1
  formSquare[2] = formSquare[0] + 150;  // x p2
  formSquare[3] = formSquare[1];        // y p2
  formSquare[4] = formSquare[2];        // x p3
  formSquare[5] = formSquare[1] + 35;   // y p3
  formSquare[6] = formSquare[0];        // x p4
  formSquare[7] = formSquare[1] + 35;   // y p4
  formSquare[8] = formSquare[0];        // x p5
  formSquare[9] = formSquare[1];        // y p6
  
  if(*form < 7){
    esat::DrawSolidPath(arrow, 3);
    esat::DrawPath(formSquare, 5);
  }
  else{
    esat::DrawSolidPath(formSquare, 5);
    esat::DrawSetFillColor(0,0,0);

  }
  esat::DrawText(ScreenX/2 - 100, 550, "CONFIRM");
  

  // provincia, país, usuario y contraseña, 
  // créditos de partidas y dirección de email.

}

void LogIn(){

}

void Account(int *option, int *form){
  esat::DrawSetFillColor(255,255,255);
  esat::DrawText(ScreenX/3 - 80, 80, "REGISTER");
  esat::DrawText(ScreenX - ScreenX/3 - 50, 80, "LOGIN");
  
  float *selectionSquare;
  selectionSquare = (float*)malloc(10*sizeof(float));

  if(*option == 0){
    selectionSquare[0] = ScreenX/3 - 90;  // x p1
    selectionSquare[2] = selectionSquare[0] + 160;  // x p2
  }else{
    selectionSquare[0] = ScreenX - ScreenX/3 - 60;  // x p1
    selectionSquare[2] = selectionSquare[0] + 110;  // x p2
  }
  selectionSquare[1] = 50;  // y p1
  selectionSquare[3] = 50;  // y p2
  selectionSquare[4] = selectionSquare[2];  // x p3
  selectionSquare[5] = 85;  // y p3
  selectionSquare[6] = selectionSquare[0];  // x p4
  selectionSquare[7] = 85;  // y p4
  selectionSquare[8] = selectionSquare[0];  // x p5
  selectionSquare[9] = 50;  // y p6

  esat::DrawPath(selectionSquare, 5);

  switch(*option){
    case 0:
      Register(&(*form));
    break;
    case 1:
      LogIn();
    break;
  }

  if(esat::IsSpecialKeyDown(esat::kSpecialKey_Right) && *option == 0){
    *option = 1;
    *form = 0;
  }else if(esat::IsSpecialKeyDown(esat::kSpecialKey_Left) && *option == 1){
    *option = 0;
    *form = 0;
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
  double current_time = 0.0;
  double last_time = 0.0;
  double fps = 60.0;
  int screenSelector = 0, accountOption = 0, formSection = 0;   // 0 login/registrar 1 menu de juego 2 juego
  
  srand(time(nullptr));
  esat::WindowInit(ScreenX, ScreenY);
  esat::WindowSetMouseVisibility(true);
  printf("---------[Start Init]--------\n");
  printf("[Init Asteroids]\n");
  initAsteroids(&asteroid, 5);
  printf("[Init Enemy]\n");
  initUFO(&enemy);

  esat::DrawSetTextFont("./assets/Hyperspace-JvEM.ttf");
  esat::DrawSetTextSize(30);

  while (!esat::IsSpecialKeyDown(esat::kSpecialKey_Escape) && esat::WindowIsOpened()) {
    last_time = esat::Time();
    esat::DrawBegin();
    esat::DrawClear(0, 0, 0);

    switch(screenSelector){
      case 0:
        Account(&accountOption, &formSection);
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