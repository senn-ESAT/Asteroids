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
      (*scoreThing)[i].name = (char*)malloc(4 * sizeof(char));

      (*scoreThing)[i].score = temp.score;
      strcpy((*scoreThing)[i].name, temp.name);

      i++;
    }
    while(i < 10){
      (*scoreThing)[i].name = (char*)malloc(4 * sizeof(char));
      (*scoreThing)[i].score = 0;
      memset((*scoreThing)[i].name, '\0', 4);
      i++;
    }
    fclose(f);
    free(temp.name);
  }else{
    f = fopen("HS.dat", "wb");
    for(int i = 0; i < 10; i++){

      (*scoreThing)[i].score = 0;
      (*scoreThing)[i].name = (char*)malloc(4 * sizeof(char));
      memset((*scoreThing)[i].name, '\0', 4);

      fwrite(&(*scoreThing)[i].score, sizeof((*scoreThing + i)->score), 1, f);
      writeString(&f, (*scoreThing)[i].name, 4);
    }
    fclose(f);
  }
}