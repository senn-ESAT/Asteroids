struct Account{
  int credit, personalHS;
  char  *name,
        *surname,
        *mail,
        *birth,
        *province,
        *nation,
        *nick,
        *psw;
};

// string.append(string2) = string+string2
bool error = false;

void InitAccount(Account *user){
  user->name =    nullptr;
  user->surname = nullptr;
  user->nick =    nullptr;
  user->mail =    nullptr;
  user->psw =     nullptr;
  user->birth =   nullptr;
  user->province= nullptr;
  user->nation =  nullptr;

  user->name =    (char*)malloc(4*sizeof(char));
  user->surname = (char*)malloc(17*sizeof(char));
  user->nick =    (char*)malloc(17*sizeof(char));
  user->mail =    (char*)malloc(17*sizeof(char));
  user->psw =     (char*)malloc(17*sizeof(char));
  user->birth =   (char*)malloc(17*sizeof(char));
  user->province= (char*)malloc(17*sizeof(char));
  user->nation =  (char*)malloc(17*sizeof(char));

  user->name[0] =    '\0';
  user->surname[0] = '\0';
  user->nick[0] =    '\0';
  user->mail[0] =    '\0';
  user->psw[0] =     '\0';
  user->birth[0] =   '\0';
  user->province[0]= '\0';
  user->nation[0] =  '\0';
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

float* ArrowShape(int position){
  float *temp;
  temp = (float*)malloc(6*sizeof(float));
  temp[0] = 20;
  temp[1] = 130 + (50 * position);
  temp[2] = 40;
  temp[3] = temp[1]+10;
  temp[4] = 20;
  temp[5] = temp[1]+20;
  return temp;
}

void cleanUser(Account *user){
  user->name[0] =    '\0';
  user->surname[0] = '\0';
  user->nick[0] =    '\0';
  user->mail[0] =    '\0';
  user->psw[0] =     '\0';
  user->birth[0] =   '\0';
  user->province[0]= '\0';
  user->nation[0] =  '\0';
}

void UpdateAccount(char **campo, int nLetters){
  char input = esat::GetNextPressedKey();
  // If input detected
  if(input != 0){
    int length = strlen(*campo);
    if(length < nLetters){
      (*campo)[length] = input;
      (*campo)[length + 1] = '\0';
    }
  }
  // delete
  if (esat::IsSpecialKeyDown(esat::kSpecialKey_Backspace)){
    int length = strlen(*campo);
    if(length > 0){
      (*campo)[length - 1] = '\0';
    }
  }
}

void freeTemp(Account *temp){
  // free(temp->name); temp->name = NULL;
  // free(temp->surname); temp->surname = NULL;
  // free(temp->nick); temp->nick = NULL;
  // free(temp->mail); temp->mail = NULL;
  // free(temp->psw);  temp->psw = NULL;
  // free(temp->birth);  temp->birth = NULL;
  // free(temp->province); temp->province = NULL;
  // free(temp->nation); temp->nation = NULL;
}

int CheckValidity(Account **users, bool option){
  printf("\n------[STARTING VERIFICATION]------\n");
  FILE *f1;
  
  // esta verifica sirve para ambos casos
  if((*users)->mail[0] == '\0' && (*users)->psw[0] == '\0'){
    printf("EMPTY\n");
    return 1;
  }

  Account temp;
  temp.name =    (char*)malloc(4*sizeof(char));
  temp.surname = (char*)malloc(17*sizeof(char));
  temp.nick =    (char*)malloc(17*sizeof(char));
  temp.mail =    (char*)malloc(17*sizeof(char));
  temp.psw =     (char*)malloc(17*sizeof(char));
  temp.birth =   (char*)malloc(17*sizeof(char));
  temp.province= (char*)malloc(17*sizeof(char));
  temp.nation =  (char*)malloc(17*sizeof(char));
  
  // LOGIN
  if(option == 1){
    printf("[LOG IN]\n");

    f1 = fopen("accounts.dat", "rb");
    if(f1 != NULL){
      printf("[FILE EXIST]\n");
      while(fread(&temp, sizeof(temp), 1, f1)){
        if((*users)->mail == temp.mail && (*users)->psw == temp.psw){
          printf("[SUCCESS]\n");
          *(*users) = temp;
          fclose(f1);
          freeTemp(&temp);
          return 0;
        }
      }
    }
    // no file no accounts
    // or while ended so no match
    printf("[FOUND NOT]\n");
    freeTemp(&temp);
    return 1;
  }// REGISTER
  else{
    printf("[------REGISTER START------]\n");
    if((*users)->name[0] == '\0'
      && (*users)->surname[0] == '\0'
      && (*users)->nick[0] == '\0'
      && (*users)->birth[0] == '\0'
      && (*users)->province[0] == '\0'
      && (*users)->nation[0] == '\0'){
      printf("EMPTY\n");
      freeTemp(&temp);
      return 1;
    }

    f1 = fopen("accounts.dat", "rb");
    if(f1 != NULL){
      printf("[FILE EXIST]\n");
      while(fread(&temp, sizeof(temp), 1, f1)){
        // if account alredy exist then stop and exit
        if((*users)->mail == temp.mail && (*users)->nick == temp.nick){
          // if it match then account alredy registered
          printf("[ACCOUNT ALREDY EXIST]\n");
          fclose(f1);
          freeTemp(&temp);
          return 1;
        }
      }
      fclose(f1);
    }
    // if exited while it means that there is no match in the current list of accounts
    // or the file is empty so no need for verifiation if it exist

    printf("[ADDING ACCOUNT]\n");
    temp = *(*users);
    temp.credit = 10;
    
    // ab+ is w/r at the last positions
    f1 = fopen("accounts.dat", "ab+");
    fwrite(&temp, sizeof(temp), 1, f1);
    fclose(f1);
    freeTemp(&temp);
    return 0;
  }
  printf("[INVALID OPERATION]\n");
  freeTemp(&temp);
  return 1;
}

void Register(int *form, Account *user, int *screen){

  if(esat::IsSpecialKeyDown(esat::kSpecialKey_Down) && *form < 8){
    *form += 1;
  }

  float *formSquare, *arrow;
  // Indication arrow
  arrow = ArrowShape((*form));
  // the square of both form section and buttons
  formSquare = (float*)malloc(10*sizeof(float));
  formSquare[0] = ScreenX/2;  // x p1
  formSquare[1] = 120;        // y p1
  // i reuse the same shape and this help me change the shape and position
  UpdateFormSection(&(*formSquare), 300);

  esat::DrawText(50, 150, "NAME:");
  esat::DrawText(formSquare[6] + 10, formSquare[7] - 5, user->name);
  esat::DrawPath(formSquare, 5);
  
  esat::DrawText(50, 200, "SURNAME:");
  formSquare[1] += 50;
  UpdateFormSection(&(*formSquare), 300);
  esat::DrawText(formSquare[6] + 10, formSquare[7] - 5, user->surname);
  esat::DrawPath(formSquare, 5);

  esat::DrawText(50, 250, "NICKNAME:");
  formSquare[1] += 50;
  UpdateFormSection(&(*formSquare), 300);
  esat::DrawText(formSquare[6] + 10, formSquare[7] - 5, user->nick);
  esat::DrawPath(formSquare, 5);
  
  esat::DrawText(50, 300, "EMAIL:");
  formSquare[1] += 50;
  UpdateFormSection(&(*formSquare), 300);
  esat::DrawText(formSquare[6] + 10, formSquare[7] - 5, user->mail);
  esat::DrawPath(formSquare, 5);

  esat::DrawText(50, 350, "PASSWORD:");
  formSquare[1] += 50;
  UpdateFormSection(&(*formSquare), 300);
  esat::DrawText(formSquare[6] + 10, formSquare[7] - 5, user->psw);
  esat::DrawPath(formSquare, 5);

  esat::DrawText(50, 400, "BIRTH YEAR:");
  formSquare[1] += 50;
  UpdateFormSection(&(*formSquare), 300);
  esat::DrawText(formSquare[6] + 10, formSquare[7] - 5, user->birth);
  esat::DrawPath(formSquare, 5);

  esat::DrawText(50, 450, "PROVINCE:");
  formSquare[1] += 50;
  UpdateFormSection(&(*formSquare), 300);
  esat::DrawText(formSquare[6] + 10, formSquare[7] - 5, user->province);
  esat::DrawPath(formSquare, 5);

  esat::DrawText(50, 500, "NATION:");
  formSquare[1] += 50;
  UpdateFormSection(&(*formSquare), 300);
  esat::DrawText(formSquare[6] + 10, formSquare[7] - 5, user->nation);
  esat::DrawPath(formSquare, 5);

  formSquare[0] = ScreenX/2 - 110;    // x p1
  formSquare[1] = 520;                // y p1
  UpdateFormSection(&(*formSquare), 150);
  
  // this indicate if the user is on the confirm button or not
  if(*form <= 7){
    esat::DrawSolidPath(arrow, 3);
    esat::DrawPath(formSquare, 5);
  }
  else{
    esat::DrawSolidPath(formSquare, 5);
    esat::DrawSetFillColor(0,0,0);
  }
  
  esat::DrawText(ScreenX/2 - 100, ScreenY - 50, "CONFIRM");

  //////////////////// INPUT MANAGER ////////////////////

  switch (*form){
    case 0: UpdateAccount(&user->name, 16);     break;
    case 1: UpdateAccount(&user->surname, 16);  break;
    case 2: UpdateAccount(&user->nick, 3);      break;
    case 3: UpdateAccount(&user->mail, 16);     break;
    case 4: UpdateAccount(&user->psw, 16);      break;
    case 5: UpdateAccount(&user->birth, 16);    break;
    case 6: UpdateAccount(&user->province, 16); break;
    case 7: UpdateAccount(&user->nation, 16);   break;
    case 8:
      if(esat::IsSpecialKeyDown(esat::kSpecialKey_Enter)){
        // if 1 error if 0 change screen
        if(!CheckValidity(&user, 0)){
          *form = 0;
          *screen = 1;
        }else{
          error = true;
        }
      }
    break;
  }

  if(error == true){
    printf("Entered ERROR");
    esat::DrawSetFillColor(255,0,0);
    esat::DrawText(ScreenX + 150, 550, "NOT VALID");
  }
}

void LogIn(int *form, Account *user, int *screen){
  if(esat::IsSpecialKeyDown(esat::kSpecialKey_Down) && *form < 3){
    *form+= 1;
  }

  float *formSquare, *arrow;

  formSquare = (float*)malloc(10*sizeof(float));
  formSquare[0] = 80;  // x p1
  formSquare[1] = 200; // y p1
  UpdateFormSection(&(*formSquare), 600);

  arrow = ArrowShape((*form));

  esat::DrawText(100, 180, "EMAIL:");
  esat::DrawText(formSquare[6] + 10, formSquare[7] - 5, user->mail);
  esat::DrawPath(formSquare, 5);

  formSquare[1] = 350;
  UpdateFormSection(&(*formSquare), 600);
  esat::DrawText(100, 330, "PASSWORD:");
  esat::DrawText(formSquare[6] + 10, formSquare[7] - 5, user->psw);
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

  switch (*form){
    case 0: UpdateAccount(&user->mail, 16);     break;
    case 1: UpdateAccount(&user->psw, 16);  break;
    case 2: 
      if(esat::IsSpecialKeyDown(esat::kSpecialKey_Enter)){
        // if outcome = 1 both mail and password are correct and present in the file
        if(!CheckValidity(&user, 1)){
          *form = 0;
          *screen = 1;
        }
        error = true;
      }
    break;
  }

  if(error){
    printf("Entered ERROR");
    esat::DrawSetFillColor(255,0,0);
    esat::DrawText(ScreenX + 150, 550, "NOT VALID");
  }
}

void Usersmanagement(int *screen, int *option, int *form, Account *user){

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
    case 0: Register(&(*form), &(*user), &(*screen)); break;
    case 1: LogIn(&(*form), &(*user), &(*screen));    break;
  }

  if(esat::IsSpecialKeyDown(esat::kSpecialKey_Right) && *option == 0){
    printf("[GO TO LOGIN]\n");
    *option = 1;
    *form = 0;
    error = 0;
    cleanUser(&(*user));
  }else if(esat::IsSpecialKeyDown(esat::kSpecialKey_Left) && *option == 1){
    printf("[GO TO REGISTER]\n");
    *option = 0;
    *form = 0;
    error = 0;
    cleanUser(&(*user));
  }else if(esat::IsSpecialKeyDown(esat::kSpecialKey_Up) && *form > 0){
    *form-= 1;
  }
}

//////////////////////////////////
//            ADMIN             //
//////////////////////////////////

void Admin(int *option, int *userSelect){
  // TO-DO admin login
  FILE *f;
  f = fopen("accounts.dat", "rb");
  
  if(f != NULL){
    Account temp;
    temp.name =    (char*)malloc(4*sizeof(char));
    temp.surname = (char*)malloc(17*sizeof(char));
    temp.nick =    (char*)malloc(17*sizeof(char));
    temp.mail =    (char*)malloc(17*sizeof(char));
    temp.psw =     (char*)malloc(17*sizeof(char));
    temp.birth =   (char*)malloc(17*sizeof(char));
    temp.province= (char*)malloc(17*sizeof(char));
    temp.nation =  (char*)malloc(17*sizeof(char));
    esat::DrawSetStrokeColor(255,255,255);
    esat::DrawSetTextSize(20);
    
    int HowMany = 0;
    float scroll = 150.0f, *formSquare, *arrow;
    arrow = ArrowShape(1);
    esat::DrawSolidPath(arrow, 3);

    // formSquare = (float*)malloc(10*sizeof(float));
    // formSquare[0] = 520;  // x p1
    // formSquare[1] = 120;  // y p1
    // UpdateFormSection(&(*formSquare), 120);
  
    // TO-DO Terminar los botones y entender crash
    // if(*option < 1){
    //   esat::DrawPath(formSquare, 5);
    // }
    // else{
    //   esat::DrawSolidPath(formSquare, 5);
    //   esat::DrawSetFillColor(0,0,0);
    // }

    printf("\nOPTION: %d, USERSELECT: %d\n", *option, *userSelect);
    
    esat::DrawText(530, scroll + 15, "EDIT");
    esat::DrawText(650, scroll + 15, "DELETE");

    printf("------------ADMIN------------\n");
    while(fread(&temp, sizeof(temp), 1, f)){
      printf("DrawLine\n");
      esat::DrawLine(100.0f, (scroll - 30), 700.0f, (scroll - 30));
      printf("[NICK: ");  fputs(temp.nick, stdout);
      esat::DrawText(100, scroll, temp.nick);
      printf("  MAIL: "); fputs(temp.mail, stdout);
      esat::DrawText(100, scroll + 30, temp.mail);
      
      scroll += 80;
      HowMany++;
      printf("\nEnd While\n");
    }
    printf("Fclose\n");

    fclose(f);
    esat::DrawSetTextSize(30);
  
    printf("MENU INPUTS\n");
    if(esat::IsSpecialKeyDown(esat::kSpecialKey_Right) && *option != 2){
      *option += 1;
    }else if(esat::IsSpecialKeyDown(esat::kSpecialKey_Left) && *option != 0){
      *option -= 1;
    }else if(esat::IsSpecialKeyDown(esat::kSpecialKey_Up) && *userSelect > 0){
      *userSelect -= 1;
    }else if(esat::IsSpecialKeyDown(esat::kSpecialKey_Down) && *userSelect < HowMany){
      *userSelect += 1;
    }
    if(esat::IsSpecialKeyDown(esat::kSpecialKey_Enter) && *option > 0){
      // TO-DO cambia paginas a o edit o elim dempendiendo de option si es 1 o 2
    }

    printf("FREE temp\n");
    freeTemp(&temp);
  }
  printf("\n---------------------------\n");
}