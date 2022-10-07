#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>

#include <Servo.h>

Servo myservo;


int addr = 0;
byte value;
int x;
int val;
int led_1=6;
int led_2=7;
int led_3=8;
int beep=5;
constexpr uint8_t RST_PIN = 9;     // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = 10;     // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance




void setup() {
  Serial.begin(9600); 
  myservo.attach(7); // Initialize serial communications with the PC
  pinMode(led_1,OUTPUT);
  pinMode(led_2,OUTPUT);
  pinMode(led_3,OUTPUT);
  pinMode(beep,OUTPUT);
  digitalWrite(led_1, HIGH);
  myservo.write(0);
  
  SPI.begin();                                                  // Init SPI bus
  mfrc522.PCD_Init();                                              // Init MFRC522 card
  Serial.println(F("Read personal data on a MIFARE PICC:"));    //shows in serial that it is ready to read
  
  while (!Serial) ; // wait for serial
  delay(200);
 // Serial.println("send command to check data");
  Serial.println("-------------------");

}


void loop() {


                  // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
                  MFRC522::MIFARE_Key key;
                  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
                
                  //some variables we need
                  byte block;
                  byte len;
                  MFRC522::StatusCode status;
                
                  //-------------------------------------------
                
                  // Look for new cards
                  if ( ! mfrc522.PICC_IsNewCardPresent()) {
                    return;
                  }
                
                  // Select one of the cards
                  if ( ! mfrc522.PICC_ReadCardSerial()) {
                    return;
                  }
                
                  Serial.println(F("**Card Detected:**"));


                //start rfid check
                String content= "";
                  byte letter;
                  for (byte i = 0; i < mfrc522.uid.size; i++) 
                  {
                    // Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                     //Serial.print(mfrc522.uid.uidByte[i], HEX);
                     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
                     content.concat(String(mfrc522.uid.uidByte[i], HEX));
                  }
                
                  content.toUpperCase();
                
                  if (content.substring(1) == "C0 35 0E 7C") //change here the UID of the card/cards that you want to give access
                  {
                   
                    Serial.print("open");
                    
                            Serial.print("Card Number : C0 35 0E 7C");
                            delay(1000); 
                            myservo.write(90);
                            delay(2000);
                            myservo.write(0);
                  }        
                  
                  else {
                    
                  if (content.substring(1) == "C0 35 0E 7C") //change here the UID of the card/cards that you want to give access
                  {
                   
                    Serial.print("open");
                    
                            Serial.print("Card Number : C0 35 0E 7C");
                            delay(1000); 
                            myservo.write(90);
                            delay(2000);
                            myservo.write(0);
                           //Serial.println("wrong card");
                  }  else
                           {if (content.substring(1) == "C0 35 0E 7C") //change here the UID of the card/cards that you want to give access
                  {
                   
                    Serial.print("open");
                    
                            Serial.print("Card Number : C0 35 0E 7C");
                            delay(1000); 
                            myservo.write(90);
                            delay(2000);
                            myservo.write(0);
                  } 
                  else {
                     Serial.print("Card Number : A0 6D CB 80"); 
                     digitalWrite(2,HIGH);
                     Serial.println("Wrong Card Detected");
                     tone(3,800,5000);
                     delay(3000);
                     digitalWrite(2,LOW);
                  }
                           }


                  
                   
                delay(1000); //change value if you want to read cards faster
              
                mfrc522.PICC_HaltA();
                mfrc522.PCD_StopCrypto1();
                  Serial.println(F("\n**End Reading**\n"));  
                  

                  }              }



