#include <Adafruit_NeoPixel.h>
#define LED_PIN    6
#define LED_COUNT 460
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

#define NumOfDigits 8
int seg[(7*NumOfDigits)][2] ={
  {21,26}, //A1
  {27,36}, //B
  {38,46}, //C
  {47,52}, //D
  {1,10}, //E
  {12,20}, //F
  {53,59}, //G
  {86,93}, //A2
  {94,103}, //B
  {105,113}, //C
  {114,121}, //D
  {68,75}, //E
  {78,85}, //F
  {122,130}, //G
  {147,152}, //A3
  {153,158}, //B
  {161,166}, //C
  {167,172}, //D
  {133,138}, //E
  {141,146}, //F
  {173,178}, //G
  {193,198}, //A4
  {199,203}, //B
  {207,211}, //C
  {213,218}, //D
  {179,184}, //E
  {187,192}, //F
  {219,224}, //G
  {242,247}, //A5
  {248,252}, //B
  {256,260}, //C
  {262,267}, //D
  {229,233}, //E
  {237,241}, //F
  {268,273}, //G
  {288,293}, //A6
  {294,298}, //B
  {302,306}, //C
  {313,308}, //D
  {275,278}, //E
  {282,287}, //F
  {314,319}, //G
  {340,347}, //A7
  {349,355}, //B
  {359,366}, //C
  {368,375}, //D
  {321,328}, //E
  {332,338}, //F
  {376,383}, //G
  {403,410}, //A8
  {412,418}, //B
  {422,429}, //C
  {432,438}, //D
  {384,391}, //E
  {395,401}, //F
  {439,445}, //G
};

String inputString = "";
bool stringComplete = false;

int scoreLeft = 0;
int scoreRight= 0;
int timerMin  = 0;
int timerSec  = 0;

void setup() {
  delay(500);
  Serial.begin(9600);
  Serial1.begin(9600); 
  /*while(!Serial) {
  Serial1.begin(9600);  
  Serial.println("STARTING NOW");
  }*/
  
  strip.begin();
  strip.setBrightness(255);
  strip.clear();
  strip.show();
  
  inputString.reserve(200);
}

#define TEST 0
void loop() {

/*if(Serial.available() > 0)
   {
      // Deal with serial data

      while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
 
  }


  
   }*/
if(Serial1.available() > 0)
   {
      
      while (Serial1.available()) {
    // get the new byte:
    char inChar = (char)Serial1.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }

  if (stringComplete) {
    Serial1.println(inputString);
    if(inputString.length()!=4){
      inputString = "";
      stringComplete = false;
      Serial1.println("InCorrect LENGTH String Received!");
    }
    char cmd = inputString[0];
    char param = inputString[1]-'0';
    inputString = "";
    stringComplete = false;
    switch(cmd){
      case 'L':
        scoreLeft = scoreLeft+param;
        Serial1.print("Score LEFT = ");
        Serial1.println(scoreLeft );
        showScore(scoreLeft,1);
        break; 
      case 'l':
        scoreLeft = scoreLeft-param;
        Serial1.print("Score LEFT = ");
        Serial1.println(scoreLeft );
        showScore(scoreLeft,1);
        break;
      case 'R':
        scoreRight= scoreRight+param;
        Serial1.print("Score RIGHT = ");
        Serial1.println(scoreRight);
        showScore(scoreRight,2);
        break; 
      case 'r':
        scoreRight= scoreRight-param;
        Serial1.print("Score RIGHT = ");
        Serial1.println(scoreRight);
        showScore(scoreRight,2);
        break;
       case 'N':
        scoreLeft = 0;
        Serial1.print("Reset Score LEFT = ");
        Serial1.println(scoreLeft );
        showScore(scoreLeft,1);
        break;
       case 'H':
        scoreLeft = param;
        Serial1.print("Putting the Hunderd = ");
        Serial1.println(scoreLeft );
        showScore(scoreLeft,3);
        break; 
      /*case 'l':
        scoreLeft = scoreLeft-param;
        Serial1.print("Score LEFT = ");
        Serial1.println(scoreLeft );
        showScore(scoreLeft,1);
        break; */
      default:
        Serial1.println("COMMAND NOT RECOGNIZED YET");
        break;
    }
  }

  if(TEST==1){
    for(int i=1; i<9; i++){
      for(int j=0; j<100; j++){
        showScore(j,i);
        strip.show();
        delay(500);  
      }
    }
  }

  if(TEST==2){
    for(int i=1; i<9; i++){
      for(char j='A'; j<'H'; j++){
        showSegment(j,i);
        strip.show();
        delay(500); 
      }
      strip.clear();
    }
  }
  }
      // Deal with serial1 data
   }

  /*if (stringComplete) {
    Serial1.println(inputString);
    if(inputString.length()!=4){
      inputString = "";
      stringComplete = false;
      Serial1.println("InCorrect LENGTH String Received!");
    }
    char cmd = inputString[0];
    char param = inputString[1]-'0';
    inputString = "";
    stringComplete = false;
    switch(cmd){
      case 'L':
        scoreLeft = scoreLeft+param;
        Serial1.print("Score LEFT = ");
        Serial1.println(scoreLeft );
        showScore(scoreLeft,1);
        break; 
      case 'l':
        scoreLeft = scoreLeft-param;
        Serial1.print("Score LEFT = ");
        Serial1.println(scoreLeft );
        showScore(scoreLeft,1);
        break;
      case 'R':
        scoreRight= scoreRight+param;
        Serial1.print("Score RIGHT = ");
        Serial1.println(scoreRight);
        showScore(scoreRight,2);
        break; 
      case 'r':
        scoreRight= scoreRight-param;
        Serial1.print("Score RIGHT = ");
        Serial1.println(scoreRight);
        showScore(scoreRight,2);
        break;
      default:
        Serial1.println("COMMAND NOT RECOGNIZED YET");
        Serial1.println("ask ZAID to write more code");
        break;
    }
  }

  if(TEST==1){
    for(int i=1; i<9; i++){
      for(int j=0; j<100; j++){
        showScore(j,i);
        strip.show();
        delay(500);  
      }
    }
  }

  if(TEST==2){
    for(int i=1; i<9; i++){
      for(char j='A'; j<'H'; j++){
        showSegment(j,i);
        strip.show();
        delay(500); 
      }
      strip.clear();
    }
  }*/
  
}

/*void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}*/


// SCORE LEFT = 1, digits 1 and 2, digit 1 is TENS, 2 is UNITS
// SCORE RIGHT = 2, digits 7 and 8, digit 7 is TENS, 8 is UNITS
void showScore(int n, int i){
  n = constrain(n,0,99);
  switch(i){
    case 1:
      showDigit(n/10,1);
      showDigit(n%10,2);
      break;
    case 2:
      showDigit(n/10,7);
      showDigit(n%10,8);
      break;
     case 3:
      showDigit(n,1);
      break;
  }  
  strip.show();
}


void clearDigit(int n){
  n = n-1;// arrays start with zero
  for(int i=0; i<7; i++){
    for(int j =  seg[(n*7)+i][0]-1; j<seg[(n*7)+i][1]; j++){
      strip.setPixelColor(j, strip.Color(0,   0,   0));
    }
  }
}

//0=A,B,C,D,E,F
//1=B,C
//2=A,B,D,E,G
//3=A,B,C,D,G
//4=B,C,F,G
//5=A,C,D,F,G
//6=A,C,D,E,F,G
//7=A,B,C
//8=A,B,C,D,E,F,G
//9=A,B,C,D,F,G
// int n = number to show, int i = digit to show on
void showDigit(int n, int i){
  clearDigit(i);
  switch(n){
    case 0:
      showSegment('A',i);
      showSegment('B',i);
      showSegment('C',i);
      showSegment('D',i);
      showSegment('E',i);
      showSegment('F',i);
      break;
    case 1:
      showSegment('B',i);
      showSegment('C',i);
      break;
    case 2:
      showSegment('A',i);
      showSegment('B',i);
      showSegment('D',i);
      showSegment('E',i);
      showSegment('G',i);
      break;
    case 3:
      showSegment('A',i);
      showSegment('B',i);
      showSegment('C',i);
      showSegment('D',i);
      showSegment('G',i);
      break;
    case 4:
      showSegment('B',i);
      showSegment('C',i);
      showSegment('F',i);
      showSegment('G',i);
      break;
    case 5:
      showSegment('A',i);
      showSegment('C',i);
      showSegment('D',i);
      showSegment('F',i);
      showSegment('G',i);
      break;
    case 6:
      showSegment('A',i);
      showSegment('C',i);
      showSegment('D',i);
      showSegment('E',i);
      showSegment('F',i);
      showSegment('G',i);
      break;
    case 7:
      showSegment('A',i);
      showSegment('B',i);
      showSegment('C',i);
      break;
    case 8:
      showSegment('A',i);
      showSegment('B',i);
      showSegment('C',i);
      showSegment('D',i);
      showSegment('E',i);
      showSegment('F',i);
      showSegment('G',i);
      break;
    case 9:
      showSegment('A',i);
      showSegment('B',i);
      showSegment('C',i);
      showSegment('D',i);
      showSegment('F',i);
      showSegment('G',i);
      break;
      default:
      showSegment('A',i);
      showSegment('D',i);
      showSegment('E',i);
      showSegment('F',i);
      showSegment('G',i);
      break;
  }
}

void showSegment(char a, int i){
  i = i-1;// arrays start with zero
  int n = a-'A';
  for(int j =  seg[(i*7)+n][0]-1; j<seg[(i*7)+n][1]; j++){
    strip.setPixelColor(j, strip.Color(0,255,0));
  }
}
