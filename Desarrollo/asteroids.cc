struct colisionArea{
  int nPoints;
  esat::Vec3 *area;   // puntos area
};

struct Asteroids{
  float size;
  int nPoints, nAreas;
  mm::Vec2 pos, speed;
  esat::Vec3 *points;
  colisionArea* areas;
};


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
    esat::Vec2 *tr_circle = nullptr;
  tr_circle = (esat::Vec2*)malloc(nPoint * sizeof(esat::Vec2));

  for (int i = 0; i < nPoint; ++i) {
    esat::Vec3 tmp = esat::Mat3TransformVec3(m, points[i]);    
    tr_circle[i] = { tmp.x, tmp.y };
  }
  esat::DrawSetFillColor(0,0,0,0);
  esat::DrawSetStrokeColor(255, 255, 255, 255);
  esat::DrawSolidPath(&tr_circle[0].x, nPoint);
}

esat::Vec3* AsteroidShapes(int n){
  esat::Vec3 *vertices;
  switch (n){
    case 0:
      vertices = (esat::Vec3*)malloc(10 * sizeof(esat::Vec3));
      *(vertices)     = {-0.20f,  -0.40f, 1.0f}; //A
      *(vertices + 1) = { 0.00f,  -0.60f, 1.0f}; //B
      *(vertices + 2) = { 0.20f,  -0.40f, 1.0f}; //C
      *(vertices + 3) = { 0.40f,  -0.60f, 1.0f}; //D
      *(vertices + 4) = { 0.60f,  -0.40f, 1.0f}; //E
      *(vertices + 5) = { 0.40f,  -0.16f, 1.0f}; //F
      *(vertices + 6) = { 0.52f,   0.00f, 1.0f}; //G
      *(vertices + 7) = { 0.40f,   0.20f, 1.0f}; //H
      *(vertices + 8) = { 0.00f,   0.20f, 1.0f}; //I
      *(vertices + 9) = {-0.20f,   0.00f, 1.0f}; //J

    break;
    case 1:
      vertices = (esat::Vec3*)malloc(12 * sizeof(esat::Vec3));

      *(vertices)      =  { 0.08f,  -0.20f, 1.0f}; //A
      *(vertices + 1)  =  {-0.17f,  -0.40f, 1.0f}; //B
      *(vertices + 2)  =  { 0.2f,   -0.4f, 1.0f}; //C
      *(vertices + 3)  =  { 0.40f,  -0.28f, 1.0f}; //D
      *(vertices + 4)  =  { 0.4f,   -0.2f, 1.0f}; //E
      *(vertices + 5)  =  { 0.30f,  -0.0f   , 1.0f}; //F
      *(vertices + 6)  =  { 0.4f,    0.2f   , 1.0f}; //G
      *(vertices + 7)  =  { 0.2f,    0.4f   , 1.0f}; //H
      *(vertices + 8)  =  { 0.085f,  0.315f , 1.0f}; //I
      *(vertices + 9)  =  {-0.12f,   0.4f   , 1.0f}; //J
      *(vertices + 10) =  {-0.31,    0.13f  , 1.0f}; //K
      *(vertices + 11) =  {-0.31,    -0.2f  , 1.0f}; //L
    break;
    case 2:
      vertices = (esat::Vec3*)malloc(12 * sizeof(esat::Vec3));

      *(vertices)      =  { 0.15f,   0.47f, 1.0f};
      *(vertices + 1)  =  { 0.00f,   0.40f, 1.0f};
      *(vertices + 2)  =  {-0.20f,   0.47f, 1.0f};
      *(vertices + 3)  =  {-0.41f,   0.36f, 1.0f};
      *(vertices + 4)  =  {-0.30f,   0.11f, 1.0f};
      *(vertices + 5)  =  {-0.45f,  -0.12f, 1.0f};
      *(vertices + 6)  =  {-0.19f,  -0.51f, 1.0f};
      *(vertices + 7)  =  { 0.05f,  -0.44f, 1.0f};
      *(vertices + 8)  =  { 0.20f,  -0.51f, 1.0f};
      *(vertices + 9)  =  { 0.46f,  -0.13f, 1.0f};
      *(vertices + 10) =  { 0.34f,   0.08f, 1.0f};
      *(vertices + 11) =  { 0.46f,   0.36f, 1.0f};
    break;
    case 3:
      vertices = (esat::Vec3*)malloc(11 * sizeof(esat::Vec3));

      *(vertices)      =  {-0.34f,   0.70f, 1.0f};
      *(vertices + 1)  =  { 0.25f,   0.69f, 1.0f};
      *(vertices + 2)  =  { 0.67f,   0.09f, 1.0f};
      *(vertices + 3)  =  { 0.67f,  -0.12f, 1.0f};
      *(vertices + 4)  =  { 0.26f,  -0.71f, 1.0f};
      *(vertices + 5)  =  { 0.00f,  -0.71f, 1.0f};
      *(vertices + 6)  =  { 0.00f,  -0.31f, 1.0f};
      *(vertices + 7)  =  {-0.24f,  -0.71f, 1.0f};
      *(vertices + 8)  =  {-0.63f,  -0.13f, 1.0f};
      *(vertices + 9)  =  {-0.51f,   0.00f, 1.0f};
      *(vertices + 10) =  {-0.64f,   0.10f, 1.0f};

    break;
  }
  return vertices;
}

colisionArea* asteAreas(int n){
  colisionArea *areas;
  areas = (colisionArea*)malloc(2 * sizeof(colisionArea));

  switch (n)
  {
  case 0:
    areas[0].nPoints = 8;
    areas[0].area = (esat::Vec3*)malloc(9 * sizeof(esat::Vec3));

    areas[0].area[0] = {-0.20f,  -0.40f, 1.0f}; //0 0
    areas[0].area[1] = { 0.00f,  -0.60f, 1.0f}; //1 1
    areas[0].area[2] = { 0.20f,  -0.40f, 1.0f}; //2 2
    areas[0].area[3] = { 0.40f,  -0.16f, 1.0f}; //5 3
    areas[0].area[4] = { 0.52f,   0.00f, 1.0f}; //6 4
    areas[0].area[5] = { 0.40f,   0.20f, 1.0f}; //7 5
    areas[0].area[6] = { 0.00f,   0.20f, 1.0f}; //8 6
    areas[0].area[7] = {-0.20f,   0.00f, 1.0f}; //9 7
    areas[0].area[8] = {-0.20f,  -0.40f, 1.0f}; //0 8

    areas[1].nPoints = 4;
    areas[1].area = (esat::Vec3*)malloc(5 * sizeof(esat::Vec3));

    areas[1].area[0] = { 0.20f,  -0.40f, 1.0f}; //2 0
    areas[1].area[1] = { 0.40f,  -0.60f, 1.0f}; //3 1
    areas[1].area[2] = { 0.60f,  -0.40f, 1.0f}; //4 2
    areas[1].area[3] = { 0.40f,  -0.16f, 1.0f}; //5 3
    areas[1].area[4] = { 0.20f,  -0.40f, 1.0f}; //2

    break;
          
  }
  return areas;
}

void ValuesAste(Asteroids **aste, int i){
  //int random = rand()%4;
  int random = 0;
  switch (random){
  case 0: 
    (*aste)[i].nPoints = 10; 
    (*aste)[i].nAreas = 2;
   break;
  case 1: (*aste)[i].nPoints = 12; break;
  case 2: (*aste)[i].nPoints = 12; break;
  case 3: (*aste)[i].nPoints = 11; break;
  }

  (*aste)[i].points = AsteroidShapes(random);
  (*aste)[i].areas = asteAreas(random);


  (*aste)[i].size = 40.0f; // size also functions as lives
  (*aste)[i].pos = {(float)(rand()%800), (float)(rand()%600)};   // random position 

  do{
    (*aste)[i].speed = {-1.0f + ((float)(rand()%3)),
                        -1.0f + ((float)(rand()%3))}; // random speed between -1 ad +1
  }while((*aste)[i].speed.x == 0.0f || (*aste)[i].speed.y == 0.0f);
}

void initAsteroids(Asteroids **aste, int amount){
  nAste = amount;
  *aste = (Asteroids*)malloc(nAste * sizeof(Asteroids));
  
  for (int i = 0; i < nAste; i++){
    ValuesAste(&(*aste), i);
  }
}

int SplitAste(Asteroids **aste, int hitted){
  //////////////////////////////////////
  //      EL SIZE VA EN NEGATIVO      //
  //////////////////////////////////////

  // TO-DO AREGLAR LA SIZE EN NEGATIVO
  // MUY PROVABLEMENTE EL PROBLEMA ES ESTE IF
  // PORQUE SE TOCA EL SIZE
  
  if((*aste)->size > 10.0f){    // if bigger than smallest size
    printf("\n[Aste split]\n");
    
    float NewSize = (*aste)[hitted].size - 10.0f;
    mm::Vec2 actualPos = (*aste)[hitted].pos;

    printf(" --> REALLOC");
    (*aste) = (Asteroids*)realloc((*aste), (nAste + 1) * sizeof(Asteroids));
    printf(" --> FOR");
    for (int i = 0; i < 2; i++){
      printf(" --> Asigning Values");

      ValuesAste(&(*aste), hitted);   // overwrites on old position
      ValuesAste(&(*aste), nAste);    // write in last/new position
      
      printf(" --> Setting pos adn size");
      (*aste)[hitted].size = NewSize;
      (*aste)[hitted].pos = actualPos;

      (*aste)[nAste].size = NewSize;
      (*aste)[nAste].pos = actualPos;
    }
    nAste += 1;
  }else{    // too small so destroy
    printf("\n[Aste Dest]\n");
    if(nAste > 1){
      printf(" --> FOR");
      for(int i = hitted; i < nAste - 1; i++){
        printf(" --> REPOS");
        (*aste)[i] = (*aste)[i + 1];
      }
      nAste -= 1;
      printf(" --> REALLOC - 1");
      (*aste) = (Asteroids*)realloc((*aste), nAste  * sizeof(Asteroids));
    }else{
      free((*aste));
      return 1;   // this is the last one so we have to load a new level
    }
  }
  printf("\n--------------------------------------\n");
  return 0;
}