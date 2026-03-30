struct Asteroids{
  int type;
  float size;
  mm::Vec2 pos, speed;
  esat::Vec3 *points;
};

const int kNPoints = 7;

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

void DrawAsteroid(esat::Mat3 m, esat::Vec3 *points) {
  esat::Vec2 tr_circle[kNPoints];
  for (int i = 0; i < kNPoints; ++i) {
    esat::Vec3 tmp = esat::Mat3TransformVec3(m, points[i]);
    tr_circle[i] = { tmp.x, tmp.y };
  }
  esat::DrawSetStrokeColor(0,0,0,0);
  esat::DrawSetStrokeColor(255, 255, 255, 255);
  esat::DrawPath(&tr_circle[0].x, kNPoints);
}

void initAsteroids(Asteroids **aste, int amount){
  *aste = (Asteroids*)malloc(amount * sizeof(Asteroids));
  
  for (int i = 0; i < amount; i++){
    (*aste)[i].type = 3;    // shape
    (*aste)[i].points = (esat::Vec3*)malloc(7*sizeof(esat::Vec3));
    (*aste)[i].points[0] = {  0.0f,   2.0f, 1.0f};
    (*aste)[i].points[1] = {- 5.0f, - 8.0f, 1.0f};
    (*aste)[i].points[2] = {- 3.0f, - 8.0f, 1.0f};
    (*aste)[i].points[3] = {  0.0f,   5.0f, 1.0f};
    (*aste)[i].points[4] = {  8.0f, - 0.0f, 1.0f};
    (*aste)[i].points[5] = {  5.0f, - 8.0f, 1.0f};
    (*aste)[i].points[6] = {  0.0f,   2.0f, 1.0f};
    (*aste)[i].size = 3.0f; // size also functions as lives
    (*aste)[i].pos = {(float)(rand()%800), (float)(rand()%600)};   // random position 
    (*aste)[i].speed = {-1.0f + (float)(rand()%3), -1.0f + (float)(rand()%3)};; // random speed between -1 ad +1
  }
}