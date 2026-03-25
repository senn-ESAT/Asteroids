struct Bullet{
  mm::Vec2 p1, speed;
  double timeFire;
  Bullet *prox;
};

int BulletAmount(Bullet *lista){
  Bullet *loop = nullptr;
  int i = 0;
  for(loop = lista; loop != nullptr; loop = loop->prox){
    i++;
  }
  return i;
}

void InsertBullet(Bullet **lista, mm::Vec2 pos, mm::Vec2 speed){
  Bullet *temp = nullptr;
  temp = (Bullet*)malloc(1 * sizeof(Bullet));

  temp->prox = *lista;
  temp->p1 = pos;
  temp->speed = speed;

  temp->timeFire = esat::Time();
  mm::Vec2Print(temp->speed);

  (*lista) = temp;
}

void ElimBullet(Bullet **lista, double time){
  Bullet *aux;
  aux = *lista;

  if(BulletAmount(*(lista)) == 1){
    if((aux->timeFire + 2000) < esat::Time()){

      aux = nullptr;
    }
  }else if((aux->timeFire + 2000) < esat::Time()){
    aux = aux->prox;
  }

  *lista = aux;
}