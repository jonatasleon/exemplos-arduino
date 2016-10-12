#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
#define RELE_PIN 7
#define LED_PIN 4
int rele_ligado = LOW;

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

int rfidInterval = 1000;
unsigned long previousRfid = 0;
unsigned long currentRfid;
bool isReaded = false;
 
char st[20];
 
void setup() 
{
  Serial.begin(9600);   // Inicia a serial
  SPI.begin();      // Inicia  SPI bus
  mfrc522.PCD_Init();   // Inicia MFRC522
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println();

  pinMode(RELE_PIN, OUTPUT);
  digitalWrite(RELE_PIN, rele_ligado);

  pinMode(LED_PIN, OUTPUT);
}
 
void loop() 
{
  currentRfid = millis();
  if (previousRfid + rfidInterval > currentRfid && isReaded) {
    digitalWrite(LED_PIN, LOW);
    return;
  }
  isReaded = false;
  digitalWrite(LED_PIN, HIGH);
  previousRfid = currentRfid;
  
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  
  isReaded = true;  
  
  //Mostra UID na serial
  Serial.print("UID da tag :");
  String conteudo= "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Mensagem : ");
  conteudo.toUpperCase();
  if (conteudo.substring(1) == "55 2A 0B A6") {
    Serial.println("Ola Jonatas(Token)!");
    Serial.println();
    if (rele_ligado == HIGH) {
      rele_ligado = LOW;
    } else {
      rele_ligado = HIGH;
    }

    digitalWrite(RELE_PIN, rele_ligado);
  }
 
  if (conteudo.substring(1) == "9E 4A E6 20") {
    Serial.println("Ola Jonatas(Cartao)!");
    Serial.println();
    if (rele_ligado == HIGH) {
      rele_ligado = LOW;
    } else {
      rele_ligado = HIGH;
    }

    digitalWrite(RELE_PIN, rele_ligado);
  }
}
