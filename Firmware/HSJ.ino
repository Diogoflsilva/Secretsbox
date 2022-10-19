
#include "HUSKYLENS.h"
#include "wire.h"

//Hardware
const char* RED_PIN = 6;
const char* GREEN_PIN = 7;
const char* Button = 5;
const char* lock = 12;


//Auxiliar Variable
int Button_status;

// Create HuskyLens object
   HUSKYLENS huskylens; 

   void setNewName (String newname, uint8_t ID) 
    {
   while (!huskylens.setCustomName(newname, ID)) 
  {
    Serial.println(F("Custom name failed!"));
    delay(100); 
} 
}


void setup() 
 {
   // Setup serial monitor 
    digitalWrite(lock, HIGH);
    Serial.begin(9600);
    Wire.begin();

    pinMode(RED_PIN, OUTPUT);
    pinMode(lock, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(Button, INPUT);
  
    while(!huskylens.begin(Wire));
 {
    Serial.println(F("success"));
    delay(100); 
  }
  
  delay(100);
  setNewName ("Owner", 1);
       
}
      
void loop() {
  Button_status = digitalRead(Button); 


if (!huskylens.request()) {}
  else if(!huskylens.isLearned()) {}
  else if(!huskylens.available()) {}
  else{
    while (huskylens.available()){
      HUSKYLENSResult result = huskylens.read();
      if (result.command == COMMAND_RETURN_BLOCK){
        
        if(result.ID == 1){
          Serial.println("Face detected");
         if (Button_status == 1) {
          digitalWrite(GREEN_PIN, HIGH);
          digitalWrite(RED_PIN, LOW);
          digitalWrite(lock, LOW);
          delay(1500);
          digitalWrite(GREEN_PIN, LOW);
          digitalWrite(RED_PIN, LOW);
          digitalWrite(lock, HIGH);
          }
        }
        if(result.ID != 1){
        if (Button_status == 1) {
          digitalWrite(RED_PIN, HIGH);
          digitalWrite(GREEN_PIN, LOW);
          delay(1500);
          digitalWrite(GREEN_PIN, LOW);
          digitalWrite(RED_PIN, LOW); 
          }      
       }
      }
     }
    }
}

