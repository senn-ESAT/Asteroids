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

void InsertBullet(Bullet **lista, mm::Vec2 pos, mm::Vec2 speed, double timeFire){
  Bullet *temp;
  temp = (Bullet*)malloc(1 * sizeof(Bullet));

  temp->prox = *lista;
  temp->p1 = pos;
  temp->speed = speed;
  temp->timeFire = timeFire;

  *lista = temp;
}

void ElimBullet(Bullet **lista, double time){
  Bullet *aux = nullptr, *proximo = nullptr;
  aux = *lista;
  do{
    proximo = aux->prox;

    if((aux->timeFire + 2000) < esat::Time()){
      aux = proximo;
    }

    if(proximo){
      if((proximo->timeFire + 2000) < esat::Time()){
        aux->prox = proximo->prox;
      }else{
        aux = aux->prox;
      }
    }

  }while(aux != nullptr && aux->prox != nullptr);
  *lista = aux;
}