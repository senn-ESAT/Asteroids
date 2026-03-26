struct alien{
  mm::Vec2 pos, speed;
  bool type;  // if 0 dumb ship if 1 dangerus ship
  
};

void DrawUFO(){

}

void initUFO(){
  alien *UFO = (alien*)malloc(1*sizeof(alien));

  UFO->pos = {0, (float)(rand()%600)};
  UFO->speed = { 1.0f, 0.0f};
  UFO->type = 0;
}