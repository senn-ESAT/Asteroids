struct Bullet{
  mm::Vec2 p1, speed;
  Bullet *prox;
  double timeFire;
  bool from; // 0 disparo player 1 disparo alien
};

int BulletAmount(Bullet *lista){
  if(lista == nullptr){
    return 0;
  }

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

  (*lista) = temp;
}

//  delete bullet 2 seconds after being shot
void ElimBullet(Bullet **lista){
  Bullet *aux;
  aux = *lista;
  double time = esat::Time();
  
  if(BulletAmount(*lista) > 1){
    
    Bullet *b;
    for(b = *lista; b != nullptr; b = b->prox){
      if(b->timeFire + 2000 - time < 0){    // no elimina rapido y van a - 100 
        b->prox = nullptr;
      }
    }
  }else{
    if(aux->timeFire + 2000 < time){
      aux = nullptr; 
    }
  }
  *lista = aux;
}

// delete bullets when they collide with an object
void DellBulletOnHit(Bullet *TheOne, Bullet **lista){
  // If the one that collided is the first one
  if(*lista == TheOne){
    Bullet *temp = *lista;
    *lista = (*lista)->prox;
    free(temp); // freing up the memory in the first  position
  }else{  // search for the bullet inside the list
    Bullet *b;
    bool continueIterate = true;
    for(b = *lista; b != nullptr && continueIterate; b = b->prox){
      if(b->prox == TheOne){  // it compare in position next
        b->prox = TheOne->prox; // we skip the bullet
        free(TheOne);   // delete the bullet
        continueIterate = false;
      }
    }
  }
}