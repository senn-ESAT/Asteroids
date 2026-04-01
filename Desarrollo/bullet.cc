struct Bullet{
  mm::Vec2 p1, speed;
  double timeFire;
  Bullet *prox;
  bool from; // 0 disparo player 1 disparo alien
};

int BulletAmount(Bullet *lista){
  Bullet *loop = nullptr;
  int i = 0;
  for(loop = lista; loop != nullptr; loop = loop->prox){
    i++;
  }
  return i;
}

void InsertBullet(Bullet **lista, mm::Vec2 pos, mm::Vec2 speed, int type){
  Bullet *temp = nullptr;
  temp = (Bullet*)malloc(1 * sizeof(Bullet));

  temp->prox = *lista;
  temp->p1 = pos;
  temp->speed = speed;
  temp->from = type;

  temp->timeFire = esat::Time();
  mm::Vec2Print(temp->speed);

  (*lista) = temp;
}

void ElimBullet(Bullet **lista, double time){
  Bullet *aux;
  aux = *lista;
  // TO-DO no elimina el ultimo
    Bullet *b;
    for(b = *lista; b != nullptr; b = b->prox){
      if((b->timeFire + 2000) < time){
        b->prox = nullptr;
      }
    }
  
  *lista = aux;
}