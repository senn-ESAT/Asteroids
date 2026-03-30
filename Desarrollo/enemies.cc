struct UFO{
  mm::Vec2 pos, speed;
  esat::Vec3 *UFOPoints;
  float size; // if small then strong shipe otherwise the dumb one
  Bullet *enemyBullets;
};


void initUFO(UFO **inUFO){
  UFO *enemy = (UFO*)malloc(1*sizeof(UFO));

  enemy->pos = {400.0f, 300.0f};
  enemy->speed = { 1.0f, 0.0f};
  enemy->size = 5.0f;

  enemy->UFOPoints = (esat::Vec3*)malloc(7*sizeof(esat::Vec3));

  enemy->UFOPoints[0] = { 0.0f, 0.0f, 1.0f};
  enemy->UFOPoints[1] = { 2.0f, 0.0f, 1.0f};
  enemy->UFOPoints[2] = { 2.0f, 2.0f, 1.0f};
  enemy->UFOPoints[3] = { 0.0f, 2.0f, 1.0f};
  enemy->UFOPoints[4] = { 0.0f, 0.0f, 1.0f};
  enemy->UFOPoints[5] = { 2.0f, 0.0f, 1.0f};
  enemy->UFOPoints[6] = { 2.0f, 2.0f, 1.0f};

  *inUFO = enemy;
}