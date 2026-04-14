struct Account{
  int id, credit;
  char  *name,
        *surname,
        *mail,
        *birth,
        *province,
        *nation,
        *nick,
        *psw;
};

FILE *f;
// string.append(string2) = string+string2

void InitAccount(Account *user){
  user->name =    nullptr;
  user->surname = nullptr;
  user->nick =    nullptr;
  user->mail =    nullptr;
  user->psw =     nullptr;
  user->birth =   nullptr;
  user->province= nullptr;
  user->nation =  nullptr;

  user->name =    (char*)malloc(20*sizeof(char));
  user->surname = (char*)malloc(20*sizeof(char));
  user->nick =    (char*)malloc(20*sizeof(char));
  user->mail =    (char*)malloc(30*sizeof(char));
  user->psw =     (char*)malloc(20*sizeof(char));
  user->birth =   (char*)malloc(20*sizeof(char));
  user->province= (char*)malloc(20*sizeof(char));
  user->nation =  (char*)malloc(20*sizeof(char));

  user->name[0] =    '\0';
  user->surname[0] = '\0';
  user->nick[0] =    '\0';
  user->mail[0] =    '\0';
  user->psw[0] =     '\0';
  user->birth[0] =   '\0';
  user->province[0]= '\0';
  user->nation[0] =  '\0';

}

int getID() {
  Account last;

  if (fseek(f, -sizeof(Account), SEEK_END) != 0){
    return 0;
  }

  fread(&last, sizeof(Account), 1, f);
  return last.id + 1;
}

void UpdateFormSection(float *section, float size){
  section[2] = section[0] + size; // x p2
  section[3] = section[1];        // y p2
  section[4] = section[2];        // x p3
  section[5] = section[1] + 35;   // y p3
  section[6] = section[0];        // x p4
  section[7] = section[1] + 35;   // y p4
  section[8] = section[0];        // x p5
  section[9] = section[1];        // y p5
}

void UpdateAccount(char **campo){
  printf("[START UPDATE ACCOUNT]\n");
  printf("[RESERVAR MEMORIA]\n");

  char *c = nullptr;
  c = (char*)malloc(sizeof(*campo) * sizeof(char));

  int index = 0;
  printf("[INPUT]\n");
  while(!esat::IsSpecialKeyDown(esat::kSpecialKey_Enter)){
    c[index] = getch();
    printf(" GOT: %c");
    index++;
  }
  printf("[SAVE BACK]\n");

  strcpy(*campo, c);
  campo[strlen(*campo)] = '\0';
  printf("[END UPDATE ACCOUNT]\n");
}

void Register(int *form, Account *user){
  printf("[VERTICAL MOVEMENT CHECK]\n");

  if(esat::IsSpecialKeyDown(esat::kSpecialKey_Down) && *form < 8){
    printf("[GO DOWN]\n");
    *form += 1;
  }

  printf("[INIT SHAPES]\n");
  float *formSquare, *arrow;
  // Indication arrow
  arrow = (float*)malloc(6*sizeof(float));
  arrow[0] = 20;
  arrow[1] = 130 + (50 * (*form));
  arrow[2] = 40;
  arrow[3] = arrow[1]+10;
  arrow[4] = 20;
  arrow[5] = arrow[1]+20;
  
  formSquare = (float*)malloc(10*sizeof(float));
  formSquare[0] = ScreenX/2;  // x p1
  formSquare[1] = 120;        // y p1
  UpdateFormSection(&(*formSquare), 300);

  printf("[START FORM]\n");


  esat::DrawText(50, 150, "NAME:");
  esat::DrawText(formSquare[6] + 10, formSquare[7] - 5, user->name);
  esat::DrawPath(formSquare, 5);
  
  esat::DrawText(50, 200, "SURNAME:");
  formSquare[1] += 50;
  UpdateFormSection(&(*formSquare), 300);
  esat::DrawText(formSquare[6] + 10, formSquare[7] - 5, user->surname);
  esat::DrawPath(formSquare, 5);

  esat::DrawText(50, 500, "EMAIL:");
  formSquare[1] += 50;
  UpdateFormSection(&(*formSquare), 300);
  esat::DrawText(formSquare[6] + 10, formSquare[7] - 5, user->mail);
  esat::DrawPath(formSquare, 5);

  esat::DrawText(50, 400, "NICKNAME:");
  formSquare[1] += 50;
  UpdateFormSection(&(*formSquare), 300);
  esat::DrawText(formSquare[6] + 10, formSquare[7] - 5, user->nick);
  esat::DrawPath(formSquare, 5);

  esat::DrawText(50, 450, "PASSWORD:");
  formSquare[1] += 50;
  UpdateFormSection(&(*formSquare), 300);
  esat::DrawText(formSquare[6] + 10, formSquare[7] - 5, user->psw);
  esat::DrawPath(formSquare, 5);

  esat::DrawText(50, 250, "BIRTH YEAR:");
  formSquare[1] += 50;
  UpdateFormSection(&(*formSquare), 300);
  esat::DrawText(formSquare[6] + 10, formSquare[7] - 5, user->birth);
  esat::DrawPath(formSquare, 5);

  esat::DrawText(50, 300, "PROVINCE:");
  formSquare[1] += 50;
  UpdateFormSection(&(*formSquare), 300);
  esat::DrawText(formSquare[6] + 10, formSquare[7] - 5, user->province);
  esat::DrawPath(formSquare, 5);

  esat::DrawText(50, 350, "NATION:");
  formSquare[1] += 50;
  UpdateFormSection(&(*formSquare), 300);
  esat::DrawText(formSquare[6] + 10, formSquare[7] - 5, user->nation);
  esat::DrawPath(formSquare, 5);

  formSquare[0] = ScreenX/2 - 110;    // x p1
  formSquare[1] = 520;                // y p1
  UpdateFormSection(&(*formSquare), 150);
  
  printf("[END FORM]\n");
  
  if(*form <= 7){
    esat::DrawSolidPath(arrow, 3);
    esat::DrawPath(formSquare, 5);
  }
  else{
    esat::DrawSolidPath(formSquare, 5);
    esat::DrawSetFillColor(0,0,0);
  }
  
  esat::DrawText(ScreenX/2 - 100, 550, "CONFIRM");

  //////////////////// INPUT MANAGER ////////////////////

  if(esat::IsSpecialKeyDown(esat::kSpecialKey_Space)){
    switch (*form){
      case 0: UpdateAccount(&user->name);     break;
      case 1: UpdateAccount(&user->surname);  break;
      case 2: UpdateAccount(&user->mail);     break;
      case 3: UpdateAccount(&user->nick);     break;
      case 4: UpdateAccount(&user->psw);      break;
      case 5: UpdateAccount(&user->birth);    break;
      case 6: UpdateAccount(&user->province); break;
      case 7: UpdateAccount(&user->nation);   break;
    }
  }
}

void LogIn(int *form){
  if(esat::IsSpecialKeyDown(esat::kSpecialKey_Down) && *form < 3){
    *form+= 1;
  }

  float *formSquare, *arrow;

  formSquare = (float*)malloc(10*sizeof(float));
  formSquare[0] = 80;  // x p1
  formSquare[1] = 200;        // y p1
  UpdateFormSection(&(*formSquare), 600);

  arrow = (float*)malloc(6*sizeof(float));
  arrow[0] = 20;
  arrow[1] = 210 + (140 * (*form));
  arrow[2] = 40;
  arrow[3] = arrow[1]+10;
  arrow[4] = 20;
  arrow[5] = arrow[1]+20;


  esat::DrawText(100, 180, "EMAIL");
  esat::DrawPath(formSquare, 5);

  formSquare[1] = 350;
  UpdateFormSection(&(*formSquare), 600);
  esat::DrawText(100, 330, "PASSWORD");
  esat::DrawPath(formSquare, 5);

  formSquare[0] = ScreenX/2 - 110;      // x p1
  formSquare[1] = 520;            // y p1
  UpdateFormSection(&(*formSquare), 150);

  if(*form < 2){
    esat::DrawSolidPath(arrow, 3);
    esat::DrawPath(formSquare, 5);
  }
  else{
    esat::DrawSolidPath(formSquare, 5);
    esat::DrawSetFillColor(0,0,0);
  }

  esat::DrawText(ScreenX/2 - 100, 550, "CONFIRM");
}

void Usersmanagement(int *option, int *form, Account *user){
  printf("-------[START USER MANAGEMENT]--------\n");

  esat::DrawSetFillColor(255,255,255);
  esat::DrawText(ScreenX/3 - 80, 80, "REGISTER");
  esat::DrawText(ScreenX - ScreenX/3 - 50, 80, "LOGIN");
  
  float *selectionSquare;
  selectionSquare = (float*)malloc(10*sizeof(float));

  if(*option == 0){
    selectionSquare[0] = ScreenX/3 - 90;            // x p1
    selectionSquare[2] = selectionSquare[0] + 160;  // x p2
  }else{
    selectionSquare[0] = ScreenX - ScreenX/3 - 60;  // x p1
    selectionSquare[2] = selectionSquare[0] + 110;  // x p2
  }

  selectionSquare[1] = 50;                  // y p1
  selectionSquare[3] = 50;                  // y p2
  selectionSquare[4] = selectionSquare[2];  // x p3
  selectionSquare[5] = 85;                  // y p3
  selectionSquare[6] = selectionSquare[0];  // x p4
  selectionSquare[7] = 85;                  // y p4
  selectionSquare[8] = selectionSquare[0];  // x p5
  selectionSquare[9] = 50;                  // y p6

  esat::DrawPath(selectionSquare, 5);

  switch(*option){
    case 0:
      printf("[START REGISTER]\n");
      Register(&(*form), &(*user));
      printf("[END REGISTER]\n");
    break;
    case 1:
      printf("[START LOGIN]\n");
      LogIn(&(*form));
      printf("[END LOGIN]\n");
    break;
  }

  if(esat::IsSpecialKeyDown(esat::kSpecialKey_Right) && *option == 0){
    printf("[GO TO LOGIN]\n");
    *option = 1;
    *form = 0;
  }else if(esat::IsSpecialKeyDown(esat::kSpecialKey_Left) && *option == 1){
    printf("[GO TO REGISTER]\n");
    *option = 0;
    *form = 0;
  }else if(esat::IsSpecialKeyDown(esat::kSpecialKey_Up) && *form > 0){
    printf("[GO UP]\n");
    *form-= 1;
  }

  printf("-------[END USER MANAGEMENT]--------\n");
}