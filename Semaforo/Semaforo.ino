const int hRed[] = { 13, 7 };
const int hYellow[] = { 12, 6 };
const int hGreen[] = { 11, 5 };

const int vRed = 10;
const int vYellow = 9;
const int vGreen = 8;

int hRedState = LOW;
int hGreenState;
int vRedState;
int vGreenState;

int yellowState = LOW;

bool horizontal = false;

unsigned long previous = 0;  

const long interval = 2000;
const long intervalYellow = 3000;
int i;

void setup() {
  for(i = 5; i <= 13; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previous >= intervalYellow) {
    if(currentMillis - previous >= interval + intervalYellow) {
      horizontal = !horizontal;
      yellowState = LOW;
      previous = currentMillis;
    } else {
      yellowState = HIGH;
    }
  } 

  if(horizontal) {
    hRedState = LOW;
    hGreenState = (yellowState == HIGH) ? LOW : HIGH;
    vRedState = HIGH;
    vGreenState = LOW;

    digitalWrite(hYellow[0], yellowState);
    digitalWrite(hYellow[1], yellowState);
    digitalWrite(vYellow, LOW);
  } else {
    vRedState = LOW;
    vGreenState = (yellowState == HIGH) ? LOW : HIGH;    
    hRedState = HIGH;
    hGreenState = LOW;

    digitalWrite(vYellow, yellowState);
    digitalWrite(hYellow[0], LOW);
    digitalWrite(hYellow[1], LOW);
  }
  
  digitalWrite(hRed[0], hRedState);
  digitalWrite(hRed[1], hRedState);
  
  digitalWrite(hGreen[0], hGreenState);
  digitalWrite(hGreen[1], hGreenState);
  
  digitalWrite(vRed, vRedState);
  
  digitalWrite(vGreen, vGreenState);
}

