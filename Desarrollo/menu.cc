void initialScreen(int *option, int *screenP){
  esat::DrawSetFillColor(255,255,255);
  esat::DrawSetTextSize(70);
  esat::DrawText(230, 200, "ASTEROID");
  esat::DrawSetTextSize(30);

  float *arrow;

  arrow = (float*)malloc(6*sizeof(float));
  arrow[0] = 230;
  arrow[1] = (ScreenX/2 - 120) + (100 * (*option));
  arrow[2] = 250;
  arrow[3] = arrow[1]+10;
  arrow[4] = 230;
  arrow[5] = arrow[1]+20;

  esat::DrawSolidPath(arrow, 3);

  esat::DrawSetFillColor(255,255,255);
  esat::DrawText(ScreenX/2 - 100, 300, "START GAME");
  esat::DrawText(ScreenX/2 - 100, 400, "SECOND PLAYER");

  if(esat::IsSpecialKeyPressed(esat::kSpecialKey_Up) && *option > 0){
    *option -= 1;
  }else if(esat::IsSpecialKeyPressed(esat::kSpecialKey_Down) && *option < 1){
    *option += 1;
  }

  if(esat::IsSpecialKeyPressed(esat::kSpecialKey_Enter)){
    switch(*option){
    case 0:
      // if(credit > 0){
        *screenP = 2; // start game
      // }      
    break;
    case 1:
        *screenP = 0; // second player log in   
    break;
    }
  }
}

void HSList(){

  esat::DrawSetFillColor(255,255,255);
  esat::DrawText((ScreenX/2)-120, 150, "SCORE RANKING");

  esat::DrawSetFillColor(255,255,255);

  esat::DrawText((ScreenX/2)-200, 250, "1 ST              PTS");
  esat::DrawText((ScreenX/2)-200, 300, "2 ND              PTS");
  esat::DrawText((ScreenX/2)-200, 350, "3 RD              PTS");
  esat::DrawText((ScreenX/2)-200, 400, "4 TH              PTS");
  esat::DrawText((ScreenX/2)-200, 450, "5 TH              PTS");
}

void Menu(int *page, Account *user, int *option, int *screen){
  printf(" -------- [MENU START] -------- \n");
  printf("--> dCredit");
  char *dCredit;
  dCredit = (char*)malloc(3 * sizeof(char));
  if(user->credit){
    printf("  C: %d  ", user->credit);
    itoa(user->credit, dCredit, 10);
  }else{
    dCredit[0] = '0';
    dCredit[1] = '0';
  }
  dCredit[2] = '\0';

  printf(" --> Start Drawing");
  esat::DrawText(20, 30, "00");               // P1 hs
  esat::DrawText(ScreenX/2 - 30, 30, "00");   // max hs
  esat::DrawText(ScreenX - 50, 30, "00");     // P2 hs
  printf(" --> NAME");
  if(user->nick){
    fputs(user->nick, stdout);
    esat::DrawText(20, ScreenY - 20, user->nick);
  }
  printf(" --> dCredit");
  fputs(dCredit, stdout);
  esat::DrawText(ScreenX - 50, ScreenY - 20, dCredit);
  esat::DrawText(ScreenX/2 - 120, ScreenY - 20, "©1979 ATARY INC");

  printf(" --> MENU PAGES");
  switch (*page){
    case 0:
      initialScreen(&(*option), &(*screen));
    break;
    case 1:
      HSList();
    break;
  }

  printf(" --> INPUT PAGES");
  if(esat::IsSpecialKeyPressed(esat::kSpecialKey_Right) && *page == 0){
    *page += 1;
  }else if(esat::IsSpecialKeyPressed(esat::kSpecialKey_Left) && *page == 1){
    *page -= 1;
  }
  printf(" -------- [MENU END] -------- \n");
}

/*
void DubujarMenu(){
  switch(TipoMenu){
    case 0:
      esat::DrawSprite(FROGGER, (ScreenX/2)-180, SpritesHeight*3);

      esat::DrawSetFillColor(255,255,255);
      esat::DrawText((ScreenX/2)-140, SpritesHeight*6, "-POINT TABLE-");
      esat::DrawText((ScreenX/2)-200, SpritesHeight*15, "KONAMI  a  1981");
      
      esat::DrawSetFillColor(255,255,0);
      esat::DrawText((ScreenX/2)-250, SpritesHeight*7, "10 PTS FORRR EACH STEP");
      esat::DrawText((ScreenX/2)-250, (SpritesHeight*8)+20, "50 PTS FOR EVERY FROG");
      esat::DrawText((ScreenX/2)-250, (SpritesHeight*10)+20, "1000 PTS BY SAVING FROGS");
      esat::DrawText((ScreenX/2)-250, (SpritesHeight*12)+20, "PLUS BONUS");

      esat::DrawSetFillColor(255,0,0);
      esat::DrawText((ScreenX/2)-250, SpritesHeight*9, "ARRIVED HOME SAFELY");
      esat::DrawText((ScreenX/2)-250, SpritesHeight*11, "INTO FIVE HOMES");
      esat::DrawText((ScreenX/2)-250, SpritesHeight*13, "10 PTS X REMAINING SECOND");
    break;
    case 1:
      int PlayerSelection;
      esat::DrawSetFillColor(255,255,255);
      esat::DrawText((ScreenX/2)-50, SpritesHeight*5, "PUSH");
      esat::DrawText((ScreenX/2)-100, SpritesHeight*9, "ONE PLAYER");

      esat::DrawSetFillColor(255,192,203);
      esat::DrawText((ScreenX/2)-120, (SpritesHeight*7), "START BUTTON");

      esat::DrawSetFillColor(255,0,0);
      esat::DrawText((ScreenX/2)-260, SpritesHeight*12, "ONE EXTRA FROGG 20000 PTS");
    break;
    case 2:
      esat::DrawSprite(FROGGER, (ScreenX/2)-180, SpritesHeight*3);

      esat::DrawSetFillColor(255,255,0);
      esat::DrawText((ScreenX/2)-160, SpritesHeight*7, "SCORE RANKING");

      esat::DrawSetFillColor(255,255,255);

      esat::DrawText((ScreenX/2)-200, SpritesHeight*9,  "1 ST         PTS");
      esat::DrawText((ScreenX/2)-200, SpritesHeight*10, "2 ND         PTS");
      esat::DrawText((ScreenX/2)-200, SpritesHeight*11, "3 RD         PTS");
      esat::DrawText((ScreenX/2)-200, SpritesHeight*12, "4 TH         PTS");
      esat::DrawText((ScreenX/2)-200, SpritesHeight*13, "5 TH         PTS");

      char  ScoreHistory1[5] = {0}, 
            ScoreHistory2[5] = {0}, 
            ScoreHistory3[5] = {0}, 
            ScoreHistory4[5] = {0}, 
            ScoreHistory5[5] = {0};

      //itoa de int a char
      itoa(ScoreList[0] +100000, ScoreHistory1, 10);
      itoa(ScoreList[1] +100000, ScoreHistory2, 10);
      itoa(ScoreList[2] +100000, ScoreHistory3, 10);
      itoa(ScoreList[3] +100000, ScoreHistory4, 10);
      itoa(ScoreList[4] +100000, ScoreHistory5, 10);

      esat::DrawText((ScreenX/2)-80, SpritesHeight*9,  ScoreHistory1 + 1);
      esat::DrawText((ScreenX/2)-80, SpritesHeight*10, ScoreHistory2 + 1);
      esat::DrawText((ScreenX/2)-80, SpritesHeight*11, ScoreHistory3 + 1);
      esat::DrawText((ScreenX/2)-80, SpritesHeight*12, ScoreHistory4 + 1);
      esat::DrawText((ScreenX/2)-80, SpritesHeight*13, ScoreHistory5 + 1);


      esat::DrawText((ScreenX/2)-180, SpritesHeight*15, "KONAMI  a  1981");
    break;
  }
}
*/