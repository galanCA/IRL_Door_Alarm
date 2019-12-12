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
  waitTime = true;
  while(state) {
    if (waitTime){
      delay(15000);
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
