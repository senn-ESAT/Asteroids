struct Asteroids{
  int type;
  float size;
  mm::Vec2 pos, speed;
};

const int kNPoints = 7;
esat::Vec3 points[14] = 
{
  {  0.0f,   2.0f, 1.0f},
  {- 5.0f, - 8.0f, 1.0f},
  {- 3.0f, - 8.0f, 1.0f},
  {  0.0f,   5.0f, 1.0f},
  {  8.0f, - 0.0f, 1.0f},
  {  5.0f, - 8.0f, 1.0f},
  {  0.0f,   2.0f, 1.0f}
};

// esto es un modo simplificado para normalisar
void homogeneizar(){
  // el 8 es el valor mas alto de el array
  float r = 1.0f / 8;
  for(int i = 0; i < kNPoints; i++){
    points[i].x *= r;
    points[i].y *= r;
    // en la z no hace falta porque es un punto
  }
}

esat::Mat3 MatAsteroid(mm::Vec2 pos, float size){
  esat::Mat3 m = esat::Mat3Identity();
  // escalar y por lo tanto el radio
  m = esat::Mat3Multiply(esat::Mat3Scale(size, size), m);
  // rotar la figura por un valor velocidad
  m = esat::Mat3Multiply(esat::Mat3Rotate(0.0f), m);
  // translate es el punto de origen
  m = esat::Mat3Multiply(esat::Mat3Translate(pos.x, pos.y ), m);
  return m;
}

void DrawAsteroid(esat::Mat3 m) {
  esat::Vec2 tr_circle[kNPoints];
  for (int i = 0; i < kNPoints; ++i) {
    esat::Vec3 tmp = esat::Mat3TransformVec3(m, points[i]);
    tr_circle[i] = { tmp.x, tmp.y };
  }
  esat::DrawSetStrokeColor(0,0,0,0);
  esat::DrawSetStrokeColor(255, 255, 255, 255);
  esat::DrawPath(&tr_circle[0].x, kNPoints);
}

void initAsteroids(Asteroids **aste){
  printf(" A");
  *aste = (Asteroids*)malloc(5 * sizeof(Asteroids));
  printf("A ");
  for(int i = 0; i < 5; i++){
    printf("%d B", i);

    aste[i]->pos = {((rand() % 8000)/10.0f), ((rand() % 6000 )/10.0f)};
    printf(" [X]: %f [Y]: %f", aste[i]->pos.x, aste[i]->pos.y);
    aste[i]->speed = {1.0f + ((rand() % 2000)/1000.0f), 1.0f + ((rand() % 2000)/1000.0f)};
    printf(" [SX]: %f [SY]: %f", aste[i]->speed.x, aste[i]->speed.y);
    aste[i]->type = rand()%4;
    switch(aste[i]->type){
      case 0: aste[i]->size = 20.0f;break;
      case 1: aste[i]->size = 30.0f;break;
      case 2: aste[i]->size = 40.0f;break;
      case 3: aste[i]->size = 50.0f;break;
    }
    printf("C \n");
  }
}