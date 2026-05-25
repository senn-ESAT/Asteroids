struct Account{
  int credit, personalHS;
  bool admin = false;
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
Account tempUser;

void InitAccount(Account *user){
  user->name =    nullptr;
  user->surname = nullptr;
  user->nick =    nullptr;
  user->mail =    nullptr;
  user->psw =     nullptr;
  user->birth =   nullptr;
  user->province= nullptr;
  user->nation =  nullptr;

  user->name =    (char*)malloc(17*sizeof(char));
  user->surname = (char*)malloc(17*sizeof(char));
  user->nick =    (char*)malloc(4*sizeof(char));
  user->mail =    (char*)malloc(17*sizeof(char));
  user->psw =     (char*)malloc(17*sizeof(char));
  user->birth =   (char*)malloc(9*sizeof(char));  // dd-mm-yyyy = 8+\0 = 9
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

float* ArrowShape(int position, float startinPoint, float spacing){
  float *temp;
  temp = (float*)malloc(6*sizeof(float));
  temp[0] = 20;
          // 130            50
  temp[1] = startinPoint + (spacing * position);
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
      if(nLetters == 8){  // is birth
        if(input >=48 && input <= 57){  //accept only numbers
          (*campo)[length] = input;
          (*campo)[length + 1] = '\0';
        }
      }else{
        (*campo)[length] = input;
        (*campo)[length + 1] = '\0';
      }
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

// Qué asco los punteros, Fede, porfa, para los ficheros, déjanos usar los arrays
void writeString(FILE **f, char* text, int length){
  int i = 0;
  char mt = '\0';
  while(i < strlen(text)){
    fwrite(&text[i], sizeof(char), 1, *f);
    i++;
  }
  while(i < length){
    fwrite(&mt, sizeof(char), 1, *f);
    i++;
  }
}

char* readString(FILE *f, char *text, int length){
    fread(text, sizeof(char), length, f);
    text[length - 1] = '\0';
    return text;
}

void AddAdmin(){
  FILE *f1;
  f1 = fopen("accounts.dat", "rb+");
  if(f1 == NULL){

    Account temp;
    temp.name =    (char*)malloc(17*sizeof(char));
    temp.surname = (char*)malloc(17*sizeof(char));
    temp.nick =    (char*)malloc(4*sizeof(char));
    temp.mail =    (char*)malloc(17*sizeof(char));
    temp.psw =     (char*)malloc(17*sizeof(char));
    temp.birth =   (char*)malloc(9*sizeof(char));
    temp.province= (char*)malloc(17*sizeof(char));
    temp.nation =  (char*)malloc(17*sizeof(char));

    temp.mail = "ADMIN\0";
    temp.psw = "A123456\0";
    temp.credit = 0;
    temp.personalHS = 0;
    temp.admin = true;

    temp.name[0] =    '\0';
    temp.surname[0] = '\0';
    temp.nick[0] =    '\0';
    temp.birth[0] =   '\0';
    temp.province[0]= '\0';
    temp.nation[0] =  '\0';

    f1 = fopen("accounts.dat", "wb");
    
    fwrite(&temp.credit, sizeof(temp.credit), 1, f1);
    fwrite(&temp.personalHS, sizeof(temp.personalHS), 1, f1);
    fwrite(&temp.admin, sizeof(temp.admin), 1, f1);

    writeString(&f1, temp.name, 17);
    writeString(&f1, temp.surname, 17);
    writeString(&f1, temp.mail, 17);
    writeString(&f1, temp.birth, 9);
    writeString(&f1, temp.province, 17);
    writeString(&f1, temp.nation, 17);
    writeString(&f1, temp.nick, 4);
    writeString(&f1, temp.psw, 17);
    fclose(f1);
  } else {
    fclose(f1);
  }
}

int CheckValidity(Account **users, bool option){
  FILE *f1;
  
  // esta verifica sirve para ambos casos
  if((*users)->mail[0] == '\0' && (*users)->psw[0] == '\0'){
    return 1;
  }

  Account temp;
  temp.name =    (char*)malloc(17*sizeof(char));
  temp.surname = (char*)malloc(17*sizeof(char));
  temp.nick =    (char*)malloc(4*sizeof(char));
  temp.mail =    (char*)malloc(17*sizeof(char));
  temp.psw =     (char*)malloc(17*sizeof(char));
  temp.birth =   (char*)malloc(9*sizeof(char));
  temp.province= (char*)malloc(17*sizeof(char));
  temp.nation =  (char*)malloc(17*sizeof(char));
  
  // LOGIN
  if(option == 1){

    f1 = fopen("accounts.dat", "rb");
    if(f1 != NULL){
      while(fread(&temp.credit, sizeof(int), 1, f1) &&
            fread(&temp.personalHS, sizeof(int), 1, f1) &&
            fread(&temp.admin, sizeof(bool), 1, f1) &&
            readString(f1, temp.name, 17) &&
            readString(f1, temp.surname, 17) &&
            readString(f1, temp.mail, 17) &&
            readString(f1, temp.birth, 9) &&
            readString(f1, temp.province, 17) &&
            readString(f1, temp.nation, 17) &&
            readString(f1, temp.nick, 4) &&
            readString(f1, temp.psw, 17)){
        if(strcmp((*users)->mail, temp.mail) == 0 && strcmp((*users)->psw, temp.psw) == 0){
          *(*users) = temp;
          fclose(f1);
          return 0;
        }
      }
    }
    // no file no accounts
    // or while ended so no match
    fclose(f1);
    return 1;
  }// REGISTER
  else{
    if((*users)->name[0] == '\0'
      && (*users)->surname[0] == '\0'
      && (*users)->nick[0] == '\0'
      && (*users)->birth[0] == '\0'
      && (*users)->province[0] == '\0'
      && (*users)->nation[0] == '\0'){
      return 1;
    }

    f1 = fopen("accounts.dat", "rb");
    if(f1 != NULL){
      while(fread(&temp.credit, sizeof(int), 1, f1) &&
            fread(&temp.personalHS, sizeof(int), 1, f1) &&
            fread(&temp.admin, sizeof(bool), 1, f1) &&
            readString(f1, temp.name, 17) &&
            readString(f1, temp.surname, 17) &&
            readString(f1, temp.mail, 17) &&
            readString(f1, temp.birth, 9) &&
            readString(f1, temp.province, 17) &&
            readString(f1, temp.nation, 17) &&
            readString(f1, temp.nick, 4) &&
            readString(f1, temp.psw, 17)){

        // if account alredy exist then stop and exit
        if(strcmp((*users)->mail, temp.mail) == 0 && strcmp((*users)->nick, temp.nick) == 0){
          // if it match then account alredy registered
          printf("[ACCOUNT ALREDY EXIST]\n");
          fclose(f1);
          return 1;
        }
      }
      fclose(f1);
    }
    // if exited while it means that there is no match in the current list of accounts
    // or the file is empty so no need for verifiation if it exist

    temp = *(*users);
    temp.credit = 10;
    temp.personalHS = 0;

    (*users)->credit = temp.credit;
    (*users)->personalHS = temp.personalHS;

    // ab+ is w/r at the last positions
    f1 = fopen("accounts.dat", "ab+");

    fwrite(&temp.credit, sizeof(temp.credit), 1, f1);
    fwrite(&temp.personalHS, sizeof(temp.personalHS), 1, f1);
    fwrite(&temp.admin, sizeof(temp.admin), 1, f1);

    writeString(&f1, temp.name, 17);
    writeString(&f1, temp.surname, 17);
    writeString(&f1, temp.mail, 17);
    writeString(&f1, temp.birth, 9);
    writeString(&f1, temp.province, 17);
    writeString(&f1, temp.nation, 17);
    writeString(&f1, temp.nick, 4);
    writeString(&f1, temp.psw, 17);

    fclose(f1);

    return 0;
  }
  printf("[INVALID OPERATION]\n");
  return 1;
}

void Register(int *form, Account *user, int *screen){

  if(esat::IsSpecialKeyDown(esat::kSpecialKey_Down) && *form < 8){
    *form += 1;
  }

  float *formSquare, *arrow;
  // Indication arrow
  arrow = ArrowShape((*form), 130, 50);
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
  char *letter = (char*)malloc(2 * sizeof(char));
  letter[1] = '\0';
  int j = 0;
  for(int i = 0; i < 9 && i < strlen(user->birth); i++){
    if(i != 0 && i%2 == 0 && i < 5){
      j++;
    }
    letter[0] = user->birth[i];
    esat::DrawText(formSquare[6] + 10 + (20*j), formSquare[7] - 5, letter);
    j++;
  }
  letter[0] = '/';
  for(int i = 1; i < 3; i++){
    esat::DrawText(formSquare[6] + 10 * i + (45*i), formSquare[7] - 5, letter);
  }

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
    case 5: UpdateAccount(&user->birth, 8);    break;
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
    esat::DrawSetFillColor(255,0,0);
    esat::DrawText(ScreenX/2 + 100, 550, "NOT VALID");
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

  arrow = ArrowShape((*form), 210, 130);

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
          if(strcmp(user->mail, "ADMIN\0") == 0){
            *screen = 3;
          }else{
            *screen = 1;
          }
          *form = 0;
        }
        error = true;
      }
    break;
  }

  if(error){
    esat::DrawSetFillColor(255,0,0);
    esat::DrawText(ScreenX/2 + 100, 550, "NOT VALID");
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

void editUsers(int nUser, int *form, int *page){
  esat::DrawSetFillColor(255,255,255);
  FILE *f;
  f = fopen("accounts.dat", "rb+");
  if(f == NULL){
  }else{

    fseek(f, nUser*(sizeof(int)*2 + sizeof(bool) + sizeof(char)*115/*4+17*6+9*/), SEEK_SET);
    
    if(tempUser.name[0] == '\0'){ //read only once
      fread(&tempUser.credit, sizeof(int), 1, f);
      fread(&tempUser.personalHS, sizeof(int), 1, f);
      fread(&tempUser.admin, sizeof(bool), 1, f);
      readString(f, tempUser.name, 17);
      readString(f, tempUser.surname, 17);
      readString(f, tempUser.mail, 17);
      readString(f, tempUser.birth, 9);
      readString(f, tempUser.province, 17);
      readString(f, tempUser.nation, 17);
      readString(f, tempUser.nick, 4);
      readString(f, tempUser.psw, 17);
    }
    
    if(esat::IsSpecialKeyDown(esat::kSpecialKey_Down) && *form < 8){
      *form += 1;
    }else if(esat::IsSpecialKeyDown(esat::kSpecialKey_Up) && *form > 0){
      *form -= 1;
    }

    float *formSquare, *arrow;
    // Indication arrow
    arrow = ArrowShape((*form), 130, 50);
    // the square of both form section and buttons
    formSquare = (float*)malloc(10*sizeof(float));
    formSquare[0] = ScreenX/2;  // x p1
    formSquare[1] = 120;        // y p1
    // i reuse the same shape and this help me change the shape and position
    UpdateFormSection(&(*formSquare), 300);

    esat::DrawText(50, 150, "NAME:");
    esat::DrawText(formSquare[6] + 10, formSquare[7] - 5, tempUser.name);
    esat::DrawPath(formSquare, 5);
    
    esat::DrawText(50, 200, "SURNAME:");
    formSquare[1] += 50;
    UpdateFormSection(&(*formSquare), 300);
    esat::DrawText(formSquare[6] + 10, formSquare[7] - 5, tempUser.surname);
    esat::DrawPath(formSquare, 5);

    esat::DrawText(50, 250, "NICKNAME:");
    formSquare[1] += 50;
    UpdateFormSection(&(*formSquare), 300);
    esat::DrawText(formSquare[6] + 10, formSquare[7] - 5, tempUser.nick);
    esat::DrawPath(formSquare, 5);
    
    esat::DrawText(50, 300, "EMAIL:");
    formSquare[1] += 50;
    UpdateFormSection(&(*formSquare), 300);
    esat::DrawText(formSquare[6] + 10, formSquare[7] - 5, tempUser.mail);
    esat::DrawPath(formSquare, 5);

    esat::DrawText(50, 350, "PASSWORD:");
    formSquare[1] += 50;
    UpdateFormSection(&(*formSquare), 300);
    esat::DrawText(formSquare[6] + 10, formSquare[7] - 5, tempUser.psw);
    esat::DrawPath(formSquare, 5);

    esat::DrawText(50, 400, "BIRTH YEAR:");
    formSquare[1] += 50;
    UpdateFormSection(&(*formSquare), 300);
    char *letter = (char*)malloc(2 * sizeof(char));
    letter[1] = '\0';
    int j = 0;
    for(int i = 0; i < 9 && i < strlen(tempUser.birth); i++){
      if(i != 0 && i%2 == 0 && i < 5){
        j++;
      }
      letter[0] = tempUser.birth[i];
      esat::DrawText(formSquare[6] + 10 + (20*j), formSquare[7] - 5, letter);
      j++;
    }
    letter[0] = '/';
    for(int i = 1; i < 3; i++){
      esat::DrawText(formSquare[6] + 10 * i + (45*i), formSquare[7] - 5, letter);
    }

    esat::DrawPath(formSquare, 5);

    esat::DrawText(50, 450, "PROVINCE:");
    formSquare[1] += 50;
    UpdateFormSection(&(*formSquare), 300);
    esat::DrawText(formSquare[6] + 10, formSquare[7] - 5, tempUser.province);
    esat::DrawPath(formSquare, 5);

    esat::DrawText(50, 500, "NATION:");
    formSquare[1] += 50;
    UpdateFormSection(&(*formSquare), 300);
    esat::DrawText(formSquare[6] + 10, formSquare[7] - 5, tempUser.nation);
    esat::DrawPath(formSquare, 5);

    formSquare[0] = ScreenX/2 - 110;    // x p1
    formSquare[1] = 520;                // y p1
    UpdateFormSection(&(*formSquare), 150);
    
    char *p1Score = (char*)malloc(5 * sizeof(char));
    itoa(tempUser.credit, p1Score, 10);

    esat::DrawText(ScreenX/2 - 30, 30, p1Score);

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

      if(esat::IsSpecialKeyDown(esat::kSpecialKey_Shift)){
        tempUser.credit+=1;
      }else if(esat::IsSpecialKeyDown(esat::kSpecialKey_Control)){
        tempUser.credit-=1;
      }

    //////////////////// INPUT MANAGER ////////////////////
    switch (*form){
      case 0: UpdateAccount(&tempUser.name, 16);     break;
      case 1: UpdateAccount(&tempUser.surname, 16);  break;
      case 2: UpdateAccount(&tempUser.nick, 3);      break;
      case 3: UpdateAccount(&tempUser.mail, 16);     break;
      case 4: UpdateAccount(&tempUser.psw, 16);      break;
      case 5: UpdateAccount(&tempUser.birth, 8);     break;
      case 6: UpdateAccount(&tempUser.province, 16); break;
      case 7: UpdateAccount(&tempUser.nation, 16);   break;
      case 8:
        if(esat::IsSpecialKeyDown(esat::kSpecialKey_Enter)){
          fseek(f, nUser*(sizeof(int)*2 + sizeof(bool) + sizeof(char)*115/*4+17*6+9*/), SEEK_SET);

          fwrite(&tempUser.credit, sizeof(tempUser.credit), 1, f);
          fwrite(&tempUser.personalHS, sizeof(tempUser.personalHS), 1, f);
          fwrite(&tempUser.admin, sizeof(tempUser.admin), 1, f);

          writeString(&f, tempUser.name, 17);
          writeString(&f, tempUser.surname, 17);
          writeString(&f, tempUser.mail, 17);
          writeString(&f, tempUser.birth, 9);
          writeString(&f, tempUser.province, 17);
          writeString(&f, tempUser.nation, 17);
          writeString(&f, tempUser.nick, 4);
          writeString(&f, tempUser.psw, 17);
          *form = 0;  // reset de option
          *page = 0;  // back to control pannel
        }
      break;


    }

    free(p1Score);
    fclose(f);
  }
}

void deleteUser(int userSelect, int *page){
  FILE *f1;
  FILE *temp;

  f1 = fopen("accounts.dat", "rb");
  temp = fopen("temp.dat", "wb");

  if(f1 == NULL || temp == NULL){
  }else{
    Account user;
    InitAccount(&user);

    int currentIndex = 0;

    // Read all accounts
    while(fread(&user.credit, sizeof(int), 1, f1) &&
                fread(&user.personalHS, sizeof(int), 1, f1) &&
                fread(&user.admin, sizeof(bool), 1, f1) &&
                readString(f1, user.name, 17) &&
                readString(f1, user.surname, 17) &&
                readString(f1, user.mail, 17) &&
                readString(f1, user.birth, 9) &&
                readString(f1, user.province, 17) &&
                readString(f1, user.nation, 17) &&
                readString(f1, user.nick, 4) &&
                readString(f1, user.psw, 17)){

      // Skip user to delete
      if(currentIndex != userSelect){

        fwrite(&user.credit, sizeof(int), 1, temp);
        fwrite(&user.personalHS, sizeof(int), 1, temp);
        fwrite(&user.admin, sizeof(bool), 1, temp);

        writeString(&temp, user.name, 17);
        writeString(&temp,user.surname, 17);
        writeString(&temp,user.mail, 17);
        writeString(&temp,user.birth, 9);
        writeString(&temp,user.province, 17);
        writeString(&temp,user.nation, 17);
        writeString(&temp,user.nick, 4);
        writeString(&temp,user.psw, 17);
      }

      currentIndex++;
    }

    fclose(f1);
    fclose(temp);
    
    remove("accounts.dat");
    rename("temp.dat", "accounts.dat");
  }
  *page = 0;
}

void Admin(int *option, int *userSelect, int *page){
  
  if(!tempUser.nation){ // ??? supocngo que verifica la existencia de tempUser
    InitAccount(&tempUser);
  }

  switch (*page){
    case 0:
      FILE *f;
      f = fopen("accounts.dat", "rb");
      
      if(f != NULL){
        Account temp;
        temp.name =    (char*)malloc(17*sizeof(char));
        temp.surname = (char*)malloc(17*sizeof(char));
        temp.nick =    (char*)malloc(4*sizeof(char));
        temp.mail =    (char*)malloc(17*sizeof(char));
        temp.psw =     (char*)malloc(17*sizeof(char));
        temp.birth =   (char*)malloc(17*sizeof(char));
        temp.province= (char*)malloc(17*sizeof(char));
        temp.nation =  (char*)malloc(17*sizeof(char));

        esat::DrawSetFillColor(255,255,255);
        esat::DrawSetStrokeColor(255,255,255);

        esat::DrawSetTextSize(20);
        
        int HowMany = 0;
        float scroll = 170.0f - (*userSelect * 80), *formSquare, *arrow;
        arrow = ArrowShape(1, 130, 50);
        esat::DrawSolidPath(arrow, 3);

        if(*option > 0){
          float *selectionSquare;
          selectionSquare = (float*)malloc(10*sizeof(float));
  
          if(*option == 1){
            selectionSquare[0] = 520;            // x p1
            selectionSquare[2] = selectionSquare[0] + 60;  // x p2
          }else if (*option == 2){
            selectionSquare[0] = 650;  // x p1
            selectionSquare[2] = selectionSquare[0] + 80;  // x p2
          }
  
          selectionSquare[1] = 140;                  // y p1
          selectionSquare[3] = 140;                  // y p2
          selectionSquare[4] = selectionSquare[2];  // x p3
          selectionSquare[5] = 180;                  // y p3
          selectionSquare[6] = selectionSquare[0];  // x p4
          selectionSquare[7] = 180;                  // y p4
          selectionSquare[8] = selectionSquare[0];  // x p5
          selectionSquare[9] = 140;                  // y p6
  
          esat::DrawPath(selectionSquare, 5);
        }

        
        esat::DrawText(530, 170, "EDIT");
        esat::DrawText(650, 170, "DELETE");
        bool skipfirst = false;
        while(fread(&temp.credit, sizeof(int), 1, f) &&
              fread(&temp.personalHS, sizeof(int), 1, f) &&
              fread(&temp.admin, sizeof(bool), 1, f) &&
              readString(f, temp.name, 17) &&
              readString(f, temp.surname, 17) &&
              readString(f, temp.mail, 17) &&
              readString(f, temp.birth, 9) &&
              readString(f, temp.province, 17) &&
              readString(f, temp.nation, 17) &&
              readString(f, temp.nick, 4) &&
              readString(f, temp.psw, 17)){
          
          esat::DrawSetStrokeColor(255,255,255);
          esat::DrawLine(100.0f, (scroll - 30), 700.0f, (scroll - 30));

          // the first one will always be the admin so no need to show it
          if(skipfirst){
            if(temp.nick){
              esat::DrawText(100, scroll, temp.nick);
            }
      
            if(temp.mail){
              esat::DrawText(100, scroll + 30, temp.mail);
            }
            
            scroll += 80;
            HowMany++;
          }
          skipfirst = true;
        }

        fclose(f);
        esat::DrawSetTextSize(30);
      
        if(esat::IsSpecialKeyDown(esat::kSpecialKey_Right) && *option < 3){
          *option += 1;
        }else if(esat::IsSpecialKeyDown(esat::kSpecialKey_Left) && *option > 0){
          *option -= 1;
        }else if(esat::IsSpecialKeyDown(esat::kSpecialKey_Up) && *userSelect > 0){
          *userSelect -= 1;
        }else if(esat::IsSpecialKeyDown(esat::kSpecialKey_Down) && *userSelect < HowMany - 1 && HowMany > 0){
          *userSelect += 1;
        }
        if(esat::IsSpecialKeyDown(esat::kSpecialKey_Enter) && *option > 0){
          *page = *option;
          *option = 0;
        }
        fclose(f);
      }
    break;
    case 1:
      // +1 beacouse admins is the 0 so we skip him
      editUsers(*userSelect + 1, &*option, &*page);
    break;
    case 2: // delete user
    // user selector * sizeof user --> delete
    // for user selector[i] * sizeof user = //[i+1]
      deleteUser(*userSelect + 1, &*page);
    break;
  }
}