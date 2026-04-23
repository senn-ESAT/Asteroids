struct Asteroids{
  int type;
  float size;
  mm::Vec2 pos, speed;
  esat::Vec3 *points;
};

const int kNPoints = 20;

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

void DrawAsteroid(esat::Mat3 m, esat::Vec3 *points, int nPoint) {
  
//  esat::Vec2 tr_circle[kNPoints];
  esat::Vec2 *tr_circle = nullptr;
  tr_circle = (esat::Vec2*)malloc(nPoint * sizeof(esat::Vec2));

  for (int i = 0; i < nPoint; ++i) {
    esat::Vec3 tmp = esat::Mat3TransformVec3(m, points[i]);    
    tr_circle[i] = { tmp.x, tmp.y };
  }
  esat::DrawSetStrokeColor(0,0,0,0);
  esat::DrawSetStrokeColor(255, 255, 255, 255);
  esat::DrawPath(&tr_circle[0].x, nPoint);
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
    // no normalizo
    (*aste)[i].size = 4.0f; // size also functions as lives
    (*aste)[i].pos = {(float)(rand()%800), (float)(rand()%600)};   // random position 
    (*aste)[i].speed = {-1.0f + (float)(rand()%3), -1.0f + (float)(rand()%3)};; // random speed between -1 ad +1
  }
}

void SplitAste(Asteroids **aste){
  float actualSize = (*aste)->size;
  mm::Vec2 actualPos = (*aste)->pos;

  if((*aste)->size > 1){
    *aste = (Asteroids*)realloc(*aste ,2 * sizeof(Asteroids));
    
    for (int i = 0; i < 2; i++){
      (*aste)[i].type = 3;    // shape
      (*aste)[i].points = (esat::Vec3*)malloc(7*sizeof(esat::Vec3));
      (*aste)[i].points[0] = {  0.0f,   2.0f, 1.0f};
      (*aste)[i].points[1] = {- 5.0f, - 8.0f, 1.0f};
      (*aste)[i].points[2] = {- 3.0f, - 8.0f, 1.0f};
      (*aste)[i].points[3] = {  0.0f,   5.0f, 1.0f};
      (*aste)[i].points[4] = {  8.0f, - 0.0f, 1.0f};
      (*aste)[i].points[5] = {  5.0f, - 8.0f, 1.0f};
      (*aste)[i].points[6] = {  0.0f,   2.0f, 1.0f};
      (*aste)[i].size = actualSize - 1; // size also functions as lives
      (*aste)[i].pos = actualPos;
      (*aste)[i].speed = {-1.0f + (float)(rand()%3), -1.0f + (float)(rand()%3)}; // random speed between -1 ad +1
    }
  }
}

/*

/////////// ASTEROIDS SHAPES ///////////

void VertsAsteroid_A(esat::Vec2 *vertices){
  *(vertices)     = {-0.20f,  -0.40f}; //A
  *(vertices + 1) = { 0.00f,  -0.60f}; //B
  *(vertices + 2) = { 0.20f,  -0.40f}; //C
  *(vertices + 3) = { 0.40f,  -0.60f}; //D
  *(vertices + 4) = { 0.60f,  -0.40f}; //E
  *(vertices + 5) = { 0.40f,  -0.16f}; //F
  *(vertices + 6) = { 0.52f,   0.00f}; //G
  *(vertices + 7) = { 0.40f,   0.20f}; //H
  *(vertices + 8) = { 0.00f,   0.20f}; //I
  *(vertices + 9) = {-0.20f,   0.00f}; //J
}

void VertsAsteroid_B(esat::Vec2 *vertices){
  *(vertices)      =  { 0.0769f,  -0.20274f}; //A
  *(vertices + 1)  =  {-0.1679f,  -0.39662f}; //B
  *(vertices + 2)  =  { 0.2f,         -0.4f}; //C
  *(vertices + 3)  =  { 0.40188f, -0.28188f}; //D
  *(vertices + 4)  =  { 0.4f,         -0.2f}; //E
  *(vertices + 5)  =  { 0.30691f,  -0.0049f}; //F
  *(vertices + 6)  =  { 0.4f,          0.2f}; //G
  *(vertices + 7)  =  { 0.2f,          0.4f}; //H
  *(vertices + 8)  =  { 0.08533f,    0.3156}; //I
  *(vertices + 9)  =  {-0.12042,    0.39869}; //J
  *(vertices + 10) =  {-0.31035,    0.13359}; //K
  *(vertices + 11) =  {-0.3143,    -0.20274}; //L
}

void VertsAsteroid_C(esat::Vec2 *vertices){
  *(vertices)      =  { 0.15f,   0.47f};
  *(vertices + 1)  =  { 0.00f,   0.40f};
  *(vertices + 2)  =  {-0.20f,   0.47f};
  *(vertices + 3)  =  {-0.41f,   0.36f};
  *(vertices + 4)  =  {-0.30f,   0.11f};
  *(vertices + 5)  =  {-0.45f,  -0.12f};
  *(vertices + 6)  =  {-0.19f,  -0.51f};
  *(vertices + 7)  =  { 0.05f,  -0.44f};
  *(vertices + 8)  =  { 0.20f,  -0.51f};
  *(vertices + 9)  =  { 0.46f,  -0.13f};
  *(vertices + 10) =  { 0.34f,   0.08f};
  *(vertices + 11) =  { 0.46f,   0.36f};
}

void VertsAsteroid_D(esat::Vec2 *vertices){
  *(vertices)      =  {-0.34f,   0.70f};
  *(vertices + 1)  =  { 0.25f,   0.69f};
  *(vertices + 2)  =  { 0.67f,   0.09f};
  *(vertices + 3)  =  { 0.67f,  -0.12f};
  *(vertices + 4)  =  { 0.26f,  -0.71f};
  *(vertices + 5)  =  { 0.00f,  -0.71f};
  *(vertices + 6)  =  { 0.00f,  -0.31f};
  *(vertices + 7)  =  {-0.24f,  -0.71f};
  *(vertices + 8)  =  {-0.63f,  -0.13f};
  *(vertices + 9)  =  {-0.51f,   0.00f};
  *(vertices + 10) =  {-0.64f,   0.10f};
}
*/