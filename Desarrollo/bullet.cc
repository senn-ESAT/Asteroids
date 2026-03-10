struct Bullet{
  mm::Vec2 p1, speed;
  double timeFire;
  bool fired = false;
  Bullet *prox;
};

void InsertBullet(Bullet **lista, mm::Vec2 pos, mm::Vec2 speed, double timeFire){
  Bullet *temp;
  printf("a");
  temp = (Bullet*)malloc(1 * sizeof(Bullet));
  printf("b");
  temp->p1 = pos;
  printf("c");
  temp->speed = speed;
  printf("d");
  temp->timeFire = timeFire;
  printf("f");
  temp->prox = *lista;
  printf("g");
  *lista = temp;
}

int BulletAmount(Bullet *lista){
  Bullet *loop = nullptr;
  int i = 0;
  for(loop = lista; loop != nullptr; loop = loop->prox){
    i++;
  }
  return i;
}

void ElimBullet(Bullet **lista, double time){
  Bullet *aux;
  Bullet *proximo;
  aux = *lista;
  printf("PRE DO ");
  do{
    printf("PRE PROX ");
    proximo = aux->prox;
    printf("POST PROX ");

    // en caso de ser el rpimero
    if(aux->timeFire + 2000 < time){
      printf("case1 ");
      aux->prox = nullptr;
    }

    // para los otros
    if(proximo){
      if(proximo->timeFire + 2000 < time){
        printf("case2 ");
        aux->prox = proximo->prox;
      }
      else{
        printf("case0 ");
        aux = aux->prox;
      }
    }
  }while(aux->prox != nullptr);
  printf("end ELIM ");

}