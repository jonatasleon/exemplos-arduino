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

const int b1 = 4;
const int b2 = 3;
const int b3 = 2;

int valB1, valB2, valB3;

unsigned long previousHominho = 0;
int intervalHominho = 10000;

bool hominho = false;
bool stopAll = false;

int yellowState = LOW;

bool horizontal = false;

unsigned long previous = 0;  

const long interval = 4000;
const long intervalYellow = 6000;
int i;

void setup() {
  Serial.begin(9600);
  for(i = 5; i <= 13; i++) {
    pinMode(i, OUTPUT);
  }
  
  for(i = 2; i <= 4; i++) {
    pinMode(i, INPUT);
  }
}

void loop() {
  unsigned long currentMillis = millis();
  
  Serial.println("Lendo");
  if (currentMillis - previousHominho <= intervalHominho) {
    digitalWrite(hRed[0], HIGH);
    digitalWrite(hRed[1], HIGH);    
    digitalWrite(vRed, HIGH);       
    digitalWrite(hGreen[0], LOW);
    digitalWrite(hGreen[1], LOW); 
    digitalWrite(vGreen, LOW);
    digitalWrite(vGreen, LOW);
    digitalWrite(hYellow[0], LOW);
    digitalWrite(hYellow[1], LOW);
    digitalWrite(vYellow, LOW);
    
    return;
  }

  valB1 = digitalRead(b1);
  valB2 = digitalRead(b2);
  valB3 = digitalRead(b3);

  hominho = (hominho || valB1 == HIGH || valB2 == HIGH || valB3 == HIGH);
  Serial.println((hominho) ? "Ligado" : "Desligado");

  if (currentMillis - previous >= intervalYellow) {
    if(currentMillis - previous >= interval + intervalYellow) {
      if(horizontal && hominho) {
        previousHominho = millis();
        hominho = false;
        return;
      }
      
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

