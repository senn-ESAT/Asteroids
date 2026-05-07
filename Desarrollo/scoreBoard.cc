struct ScoreBoard{
  int score;
  char *name;
};

void InitScoreList(ScoreBoard **scoreThing){
  FILE *f;
  printf(" --> MALLOC");
  (*scoreThing) = (ScoreBoard*)malloc(10 * sizeof(ScoreBoard));
  
  f = fopen("HS.dat", "rb");
  
  if(f != NULL){
    ScoreBoard temp;
    temp.name = (char*)malloc(4 * sizeof(char));
    int i = 0;
    printf(" --> REaDing");
    while(fread(&temp.score, sizeof(int), 1, f)
          && readString(f, temp.name, 4)){
      *scoreThing[i] = temp;
      i++;
    }
    while(i < 10){
      scoreThing[i]->score = 0;
      scoreThing[i]->name[0] = '\0';
      i++;
    }
  }else{
    printf(" --> ALL 0");
    for(int i = 0; i < 10; i++){
      printf(" [%d] --> 1-", i);
      (*scoreThing + i)->score = 0;
      printf("2-");
      (*scoreThing + i)->name = (char*)malloc(4 * sizeof(char));
      printf("3-");
      (*scoreThing + i)->name[0] = '\0';
      printf("4");
    }
  }
}