void initialScreen(int *option, int *screenP, Ship *ship, int *credit){
  esat::DrawSetFillColor(255,255,255);
  esat::DrawSetTextSize(70);
  esat::DrawText(230, 200, "ASTEROID");
  esat::DrawSetTextSize(30);

  esat::DrawSetFillColor(255,255,255);
  esat::DrawText(ScreenX/2 - 100, 300, "START GAME");

  if(esat::IsSpecialKeyDown(esat::kSpecialKey_Enter)){
    if(*credit > 0){
      *screenP = 2; // start game
      ship->noHit = esat::Time();
      ship->health = 3;
      ship->score = 0;
      *credit-= 1 ;
    }      
  }
}

void Scores(int p1, int HS){
  char *p1Score = (char*)malloc(5 * sizeof(char));
  itoa(p1, p1Score, 10);

  esat::DrawSetFillColor(255,255,255);
  esat::DrawText(20, 30, p1Score);        // P1 hs
  itoa(HS, p1Score, 10);
  esat::DrawText(ScreenX/2 - 30, 30, p1Score);   // max hs
}

void HSList(ScoreBoard *scores){
  char *p1Score = (char*)malloc(5 * sizeof(char));

  esat::DrawSetFillColor(255,255,255);
  esat::DrawText((ScreenX/2)-120, 80, "SCORE RANKING");

  esat::DrawText((ScreenX/2)-200, 140, "1");
  esat::DrawText((ScreenX/2)-200, 180, "2");  
  esat::DrawText((ScreenX/2)-200, 220, "3");
  esat::DrawText((ScreenX/2)-200, 260, "4");
  esat::DrawText((ScreenX/2)-200, 300, "5");
  esat::DrawText((ScreenX/2)-200, 340, "6");
  esat::DrawText((ScreenX/2)-200, 380, "7");
  esat::DrawText((ScreenX/2)-200, 420, "8");
  esat::DrawText((ScreenX/2)-200, 460, "9");
  esat::DrawText((ScreenX/2)-200, 500, "10");

  for(int i = 0; i < 10 ; i++){
    itoa(scores[i].score, p1Score, 10);
    esat::DrawText((ScreenX/2), 140+(i*40), p1Score);
  }
  
  esat::DrawText((ScreenX)-200, 140, scores[0].name);
  esat::DrawText((ScreenX)-200, 180, scores[1].name);
  esat::DrawText((ScreenX)-200, 220, scores[2].name);
  esat::DrawText((ScreenX)-200, 260, scores[3].name);
  esat::DrawText((ScreenX)-200, 300, scores[4].name);
  esat::DrawText((ScreenX)-200, 340, scores[5].name);
  esat::DrawText((ScreenX)-200, 380, scores[6].name);
  esat::DrawText((ScreenX)-200, 420, scores[7].name);
  esat::DrawText((ScreenX)-200, 460, scores[8].name);
  esat::DrawText((ScreenX)-200, 500, scores[9].name);
}

void Menu(int *page, Account *user, int *option, int *screen, Ship *ship, ScoreBoard *scores){
  char *dCredit;
  dCredit = (char*)malloc(3 * sizeof(char));
  if(user->credit){
    itoa(user->credit, dCredit, 10);
  }else{
    dCredit[0] = '0';
    dCredit[1] = '0';
  }
  dCredit[2] = '\0';

  if(user->nick){
    fputs(user->nick, stdout);
    esat::DrawText(20, ScreenY - 20, user->nick);
  }

  fputs(dCredit, stdout);
  esat::DrawText(ScreenX - 50, ScreenY - 20, dCredit);
  esat::DrawText(ScreenX/2 - 120, ScreenY - 20, "©1979 ATARY INC");

  switch (*page){
    case 0:
      initialScreen(&(*option), &(*screen), &(*ship), &user->credit);
    break;
    case 1:
      HSList(scores);
    break;
  }

  if(esat::IsSpecialKeyPressed(esat::kSpecialKey_Right) && *page == 0){
    *page += 1;
  }else if(esat::IsSpecialKeyPressed(esat::kSpecialKey_Left) && *page == 1){
    *page -= 1;
  }

  free(dCredit);
}