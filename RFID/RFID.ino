#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
#define RELE_PIN 7
int rele_ligado = HIGH;

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
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
}
 
void loop() 
{
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
  if (conteudo.substring(1) == "55 2A 0B A6") //UID 1 - Chaveiro
  {
    Serial.println("Ola Jonatas Leon!");
    Serial.println();
    if (rele_ligado == HIGH) {
      rele_ligado = LOW;
    } else {
      rele_ligado = HIGH;
    }

    digitalWrite(RELE_PIN, rele_ligado);
  }
 
  if (conteudo.substring(1) == "9E 4A E6 20") //UID 2 - Cartao
  {
    Serial.println("Ola cartao!");
    Serial.println();
  }
  delay(500);
}
