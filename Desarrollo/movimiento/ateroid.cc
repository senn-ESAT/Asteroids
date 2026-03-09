#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "esat/window.h"
#include "esat/draw.h"
#include "esat/input.h"
#include "esat/sprite.h"
#include "esat/time.h"
#include "../2D/MathLib.h"

struct Ship{
  mm::Vec2 pos;
  mm::Vec2 speed;
  float angulo = 0.0f;
};

struct Bullet{
  mm::Vec2 p1, speed;
  double timeFire;
  bool fired = false;;
};

const unsigned int ScreenX = 800;
const unsigned int ScreenY = 600;
const float max_speed = 10.0f;

Ship Nave = {{ScreenX/2.0f, ScreenY/2.0f}, {0.0f, 0.0f}};
Bullet bullet;

float puntosNave[8];

void initShip(){
  float angle_a = Nave.angulo;
  float angle_b = -160.0f + angle_a;
  float angle_c = 160.0f + angle_a;

  puntosNave[0] = sinf(angle_a)*10+Nave.pos.x;
  puntosNave[1] = cosf(angle_a)*10+Nave.pos.y;
  puntosNave[2] = sinf(angle_b)*40+Nave.pos.x;
  puntosNave[3] = cosf(angle_b)*40+Nave.pos.y;
  puntosNave[4] = sinf(angle_c)*40+Nave.pos.x;
  puntosNave[5] = cosf(angle_c)*40+Nave.pos.y;
  puntosNave[6] = sinf(angle_a)*10+Nave.pos.x;
  puntosNave[7] = cosf(angle_a)*10+Nave.pos.y;
}

void DrawThings(){
  esat::DrawSetStrokeColor(255, 255, 255);
  esat::DrawPath(puntosNave, 4);

if(bullet.fired){
  float puntosDisparo[10];
  puntosDisparo[0] = bullet.p1.x - 2;
  puntosDisparo[1] = bullet.p1.y;
  puntosDisparo[2] = bullet.p1.x + 2;
  puntosDisparo[3] = bullet.p1.y;
  puntosDisparo[4] = bullet.p1.x;
  puntosDisparo[5] = bullet.p1.y - 2;
  puntosDisparo[6] = bullet.p1.x;
  puntosDisparo[7] = bullet.p1.y + 2;
  puntosDisparo[8] = bullet.p1.x - 2;
  puntosDisparo[9] = bullet.p1.y;
  esat::DrawSolidPath(puntosDisparo, 5);
}

}

void Controls(){
  //speed
  float current_speed = mm::magnitudeV2(Nave.speed);
  if(esat::IsKeyPressed('w') || esat::IsKeyPressed('W')){

    if(current_speed > max_speed){
      Nave.speed = normalize(Nave.speed);
      Nave.speed = mm::scaleV2(Nave.speed, max_speed);
    }else{
      mm::Vec2 thrust = {sinf(Nave.angulo), cosf(Nave.angulo)};
      thrust = mm::scaleV2(thrust, 0.1f);
      Nave.speed = mm::sumVec2(Nave.speed, thrust);
    }
  }

  if(esat::IsKeyPressed('s') || esat::IsKeyPressed('S')){
    if(mm::magnitudeV2(Nave.speed) < 0.05){Nave.speed = {0,0};}
    else{Nave.speed = mm::scaleV2(Nave.speed, 0.95f);}
  }

  //direction
  if(esat::IsKeyPressed('d') || esat::IsKeyPressed('D')){
    Nave.angulo += 0.05f;
  }else if(esat::IsKeyPressed('a') || esat::IsKeyPressed('A')){
    Nave.angulo -= 0.05f;
  }

  // shoot
  if(esat::IsSpecialKeyPressed(esat::kSpecialKey_Space) && !bullet.fired){
    bullet.fired = true;
    bullet.p1 = Nave.pos;

    mm::Vec2 dir = { sinf(Nave.angulo), cosf(Nave.angulo) };
    dir = normalize(dir);
    if(current_speed > 8.0f){
      bullet.speed = mm::scaleV2(dir, mm::magnitudeV2(Nave.speed)+2);
    }
    else{bullet.speed = mm::scaleV2(dir, 8.0f);}

    bullet.timeFire = esat::Time();
  }

  if(bullet.timeFire + 2000 < esat::Time()){
    bullet.fired = false;
  }
}

void Move(){

  Nave.pos = mm::sumVec2(Nave.pos, Nave.speed);
      
  if(bullet.fired){
    bullet.p1 = mm::sumVec2(bullet.p1, bullet.speed);
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

void CheckBorder(){
  int colision = 0;
  colision = checkBorderColisions(Nave.pos);
  if(colision != 0){
    pacman(&Nave.pos, &colision);
  }

  colision = checkBorderColisions(bullet.p1);
  if(colision != 0){
    pacman(&bullet.p1, &colision);
  }
}

int esat::main(int argc, char** argv) {
  srand(time(nullptr));
  double current_time = 0.0;
  double last_time = 0.0;
  double fps = 60.0;

  esat::WindowInit(ScreenX, ScreenY);
  esat::WindowSetMouseVisibility(true);

  
  while (!esat::IsSpecialKeyDown(esat::kSpecialKey_Escape) && esat::WindowIsOpened()) {
    last_time = esat::Time();
    esat::DrawBegin();
    esat::DrawClear(0, 0, 0);
    
    initShip();
    DrawThings();
    Controls();
    Move();
    CheckBorder();
    
    // friction
    Nave.speed = mm::scaleV2(Nave.speed, 0.995f);
    
    esat::DrawEnd();
    esat::WindowFrame();
    do {
      current_time = esat::Time();
    } while((current_time - last_time) <= 1000.0 / fps);
  }
  esat::WindowDestroy();
  return 0;
}