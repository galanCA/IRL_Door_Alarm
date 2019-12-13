const int DOOR_PIN = 33;
const int ALARM_PIN = 32;

int state;
bool waitTime;

void setup() {
  Serial.begin(115200);
  
  pinMode(DOOR_PIN, INPUT_PULLUP);
  pinMode(ALARM_PIN, OUTPUT);
    
}

void loop() {
  state = digitalRead(DOOR_PIN);
  Serial.println(state);
  
  waitTime = true;
  while(state) {
    Serial.println();
    if (waitTime){
      delay(10000);
      waitTime = false;
      state = digitalRead(DOOR_PIN);
      if (!state) {
         break;
      }
    }
    digitalWrite(ALARM_PIN, HIGH);
    delay(850);
    digitalWrite(ALARM_PIN, LOW);
    delay(150);
    state = digitalRead(DOOR_PIN);
  }

}
