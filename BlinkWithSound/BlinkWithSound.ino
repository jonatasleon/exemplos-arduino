#define RELE_PIN 7
#define LED_PIN 4
#define SA_PIN A0
#define SD_PIN 9

int rele_ligado = HIGH;

const int maxInterval = 1000;
const int minInterval = 300;

int SAValue, SDValue;
int palmCounter = 0;
unsigned long timeCounter;
 
void setup() 
{
  Serial.begin(9600);   // Inicia a serial

  pinMode(SA_PIN, INPUT);
  pinMode(SD_PIN, INPUT);

  pinMode(RELE_PIN, OUTPUT);
  digitalWrite(RELE_PIN, rele_ligado);

  pinMode(LED_PIN, OUTPUT);
}
 
void loop() 
{
  SAValue = analogRead(SA_PIN);
  SDValue = digitalRead(SD_PIN);
  
  Serial.print("Saida A0: ");
  Serial.println(SAValue);

  if (SAValue < 300) {
    return;
  }

  if(palmCounter == 0) {
    timeCounter = millis();
    palmCounter += 1;
    return;
  }
  
  unsigned long nowCounter = millis();

  if(timeCounter + minInterval >= nowCounter && timeCounter + maxInterval <= nowCounter) {
    if (rele_ligado == HIGH) {
      rele_ligado = LOW;
    } else {
      rele_ligado = HIGH;
    }

    palmCounter = 0;
    digitalWrite(RELE_PIN, rele_ligado);
  }
  
  timeCounter = 0;

}
