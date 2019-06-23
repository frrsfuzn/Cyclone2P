int pinLed[] = {3,4,5,6,7,8,9,10,11};
int counter=0;
int player1=2;
int player2=12;
int ledState=1;
int score1=0;
int score2=0;

boolean gamePlay=false;
boolean aman=false;
boolean naik=true;
const long interval = 50;
const long intervalMainMenu = 500;
const long intervalToPlay=1000;
unsigned long previousMillisMainMenu=0;
unsigned long previousMillis=0;
unsigned long previousMillisPlay=0;
void setup() {
  // put your setup code here, to run once:
  for (int i=0; i<9;i++){
    pinMode(pinLed[i],OUTPUT);
  }
  pinMode(player1, INPUT_PULLUP);
  pinMode(player2, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(gamePlay);
  if(gamePlay){
    play();
  }else{
    mainMenu();
  }
}

void mainMenu(){
  int val1=digitalRead(player1);
  int val2=digitalRead(player2);
  unsigned long currentMillis = millis();
  if(counter==8){
    naik=false;
  }else if(counter==0){
    naik=true;
  }
  if(currentMillis-previousMillisMainMenu >= intervalMainMenu){
    previousMillisMainMenu=currentMillis;
    digitalWrite(pinLed[counter],LOW);  
    if(naik){
      counter++;
    }else{
      counter--;
    }
    digitalWrite(pinLed[counter],HIGH);  
  }
  if(val1==0&&val2==0){
    if(currentMillis-previousMillisPlay>=intervalToPlay){
      previousMillisPlay=currentMillis;
      gamePlay=true;
      for(int i=0;i<3;i++){
        digitalWrite(pinLed[0],HIGH);
        digitalWrite(pinLed[8],HIGH);
        delay(500);
        digitalWrite(pinLed[0],LOW);
        digitalWrite(pinLed[8],LOW);
        delay(500);
      }
    }
  }
}

void play(){
  unsigned long currentMillis = millis();
  int val1=digitalRead(player1);
  int val2=digitalRead(player2);
  
  /*
  Serial.print(score1);
  Serial.print("vs");
  Serial.print(score2);
  Serial.print("---");
  Serial.print(val1);
  Serial.print("---");
  Serial.print(val2);
  Serial.println(naik);
  */
  if(counter==8){
    naik=false;
  }else if(counter==0){
    naik=true;
  }


  if(counter!=8&&counter!=0){
    if(val1==1&&val2==1){
      aman=true;
    }else{
      aman=false;
    }
  }
  
  if(currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
    digitalWrite(pinLed[counter],LOW);
    if(naik){
      counter++;
    }else{
      counter--;
    }
    digitalWrite(pinLed[counter],HIGH); 
  }

  if(counter==0&&aman==1){
      if(val2==0){
        score1++;
        aman=false;
        for(int i=0;i<score1;i++){
          digitalWrite(pinLed[counter],HIGH);
          delay(300);
          digitalWrite(pinLed[counter],LOW);
          delay(300);
        }
        counter=random(1,7);
        naik=random(0,1);
      }
  }else if (counter==8&&aman==1){
    if(val1==0){
      score2++;
      aman=false;
      for(int i=0;i<score2;i++){
          digitalWrite(pinLed[counter],HIGH);
          delay(300);
          digitalWrite(pinLed[counter],LOW);
          delay(300);
      }
      counter=random(1,7);
      naik=random(0,1);
    }
  }else if(aman==0&&(val1==0||val2==0)){
    /*
     * Versi Lain jika tidak tepat sasaran
    for(int i=0;i<5;i++){
      for (int i=0; i<9;i++){
        digitalWrite(pinLed[i],HIGH);
      }
      delay(100);
      for (int i=0; i<9;i++){
        digitalWrite(pinLed[i],LOW);
      }
      delay(100);
    }
    */
    //yang bawah versi Jabrils
    digitalWrite(pinLed[counter],HIGH);
    delay(500);
    digitalWrite(pinLed[counter],LOW);
    counter=random(1,7);
    naik=random(0,1);
  }
  if(score1==5){
    for(int i=0;i<3;i++){
      for (int i=8;i>=0;i--){
          digitalWrite(pinLed[i],HIGH);
          delay(50);
      }
      delay(50);
      for (int i=8;i>=0;i--){
          digitalWrite(pinLed[i],LOW);
      }
    }
    score1=0;
    score2=0;
    gamePlay=false;
  }else if(score2==5){
    for(int i=0;i<3;i++){
      for (int i=0;i<9;i++){
          digitalWrite(pinLed[i],HIGH);
          delay(50);
      }
      delay(50);
      for (int i=0;i<9;i++){
          digitalWrite(pinLed[i],LOW);
      }
    }
    score1=0;
    score2=0;
    gamePlay=false;
  }
}
