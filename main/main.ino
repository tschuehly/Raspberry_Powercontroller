const uint8_t INPUT_PIN = A2; // Battery
const uint8_t POWER_PIN = 1;  // Shutdown Button
const uint8_t MOSFET_PIN = 0; // Raspberry Power Supply switch
const uint8_t PISTATE_PIN = 3; // Connect to GPIO26 to sense if Raspberry is on
const uint8_t PISWITCH_PIN = 2;
uint8_t piState = 0;          //Raspberry On/Off State
void setup() 
{
  //Serial.begin(57600);        
  pinMode(MOSFET_PIN, OUTPUT);
  pinMode(POWER_PIN, OUTPUT);
  pinMode(PISWITCH_PIN, OUTPUT);
  pinMode(PISTATE_PIN, INPUT);
  digitalWrite(PISWITCH_PIN, LOW);
}

void loop() 
{  
  uint16_t sensorValue = analogRead(INPUT_PIN); 
  //Serial.print(sensorValue);Serial.println("V");
  uint8_t buttonState = digitalRead(POWER_PIN);
  //Serial.println(buttonState);
  if(buttonState==1){
    piState=digitalRead(PISTATE_PIN);
    //Serial.println(piState);
    if(piState == 1){
      digitalWrite(PISWITCH_PIN, HIGH);
      delay(1000);
      digitalWrite(PISWITCH_PIN, LOW);
      while(piState == 1){
        piState=digitalRead(PISTATE_PIN);
        delay(500);
      }
      delay(2000);
      digitalWrite(MOSFET_PIN, LOW);
    }else{
      digitalWrite(MOSFET_PIN, HIGH);
      delay(80000);
    }
  }
  delay(1000);   
}
