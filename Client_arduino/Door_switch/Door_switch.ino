const int DOOR_PIN = 35;
int val = 0;

void setup() {

  Serial.begin(115200);
  pinMode(DOOR_PIN, INPUT);
    
}

void loop() {
  val = digitalRead(DOOR_PIN);
  Serial.println(val);
  //delay(100);
}
