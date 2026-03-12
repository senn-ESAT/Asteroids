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
  *aste = (Asteroids*)malloc(5 * sizeof(Asteroids));
  
  for (int i = 0; i < 5; i++){
    (*aste)[i].type = 3; printf("TYPE ");
    (*aste)[i].size = 2.0f; printf("SIZE ");
    (*aste)[i].pos = {(float)(rand()%800), (float)(rand()%600)};printf("pos "); //pos random entre 800 y 600 pero en float 
    (*aste)[i].speed = {-0.5f + (float)(rand()%2), -0.5f + (float)(rand()%2)};printf("speed ");
  }
}