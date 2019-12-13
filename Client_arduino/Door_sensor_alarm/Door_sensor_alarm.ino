//Libraries
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// Declaring class
WiFiClient client;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

//Wifi network name and passwd
const char * networkName = "IRLab";
const char * networkPswd = "robots4ever";

// Host
const char * host = "192.168.50.40";
const int port = 3300;

// PINS
const int DOOR_PIN = 33;
const int ALARM_PIN = 32;
const int LED_PIN = 2;

// Const variable
const int timeOffset = -7*3600; // Denver time
const int endDayHour = 17;
const int startDayHour = 7;


// Variable
int state;
bool waitTime;
int currentHour;
int currentDay;

void setup() {
  // Setup Serial command
  Serial.begin(115200);

  // Setup pins
  pinMode(DOOR_PIN, INPUT_PULLUP);
  pinMode(ALARM_PIN, OUTPUT);

  // connect to wifi
  connectToWiFi(networkName, networkPswd);
  
  // Start client time
  timeClient.begin();

  // Set it to Mountain Time
  //timeClient.setTimeOffset(timeOffset);
}

void loop() {
  // Get current time
  currentHour = getHour();
  currentDay  = getDays();

  // Dertermine if its off hours
  if (currentHour >= endDayHour || currentHour <= startDayHour || currentDay == 6 || currentDay == 0) {
    Serial.println("Off Working Hours");
    // Check to see if the state of the door has changed
    state = digitalRead(DOOR_PIN);
    waitTime = true;
    Serial.println(state);
    while(state) {
      if (waitTime){
        delay(10000);
        Serial.println("Waittime");
        waitTime = false;
        state = digitalRead(DOOR_PIN);
        Serial.println(state);
        if (!state) {
          Serial.println("Break");
          break;
        }
      }
      digitalWrite(ALARM_PIN, HIGH);
      delay(500);
      digitalWrite(ALARM_PIN, LOW);
      delay(150);
      state = digitalRead(DOOR_PIN);
    }
  }

  // Otherwise wait 15 min
  else {
    Serial.println("Working Hours");
    delay(60000);
    delay(60000);
    delay(60000);
    delay(60000);
    delay(60000);
  }
}

int getDays() {
  // Get Current time
  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }

  // Extract Hour
  return timeClient.getDay();
}

int getHour() {
  // Get Current time
  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }

  // Extract Hour
  return timeClient.getHours();
}

//Function to read messages from Server
int readMsg(char *message) {
  // Check if the message is empty
  if (client.available() == 0 ){
    return -1;
  }

  // read the first letter
  char data = client.read();
  message[0] = data;
  int i = 1;
  delay(10);

  // read the rest of the letters until message is empty
  while ( client.available()> 0 ) {
    data = client.read();
    message[i] =  data;
    delay(10);
    i++;
  }
  return 0;
}

// Function to Connect to computer server
void connectToServer(const char * IP, const int Port) {
  // connect to server
  if (client.connect(IP, Port)){
    Serial.print("Connected to server IP: " + String(IP));
    client.flush(); // clean storage
  }
}

// Function to connect to Wifi
void connectToWiFi(const char * ssid, const char * pwd) {
  // set up led on the ESP32
  int ledState = 0;

  // Set up a reply to command line
  printLine();
  Serial.println("Connecting to WiFi network: " + String(ssid));

  //Start connection
  WiFi.begin(ssid, pwd);

  // Wating for connection
  while (WiFi.status() != WL_CONNECTED) {
    // Blink LED while we are connecting
    digitalWrite(LED_PIN, ledState);
    ledState = (ledState + 1) % 2;// Flip state
    delay(500);
    Serial.print(".");
    }
  // Show credentials after connected to WiFi
  Serial.println();
  Serial.println("WiFi connected!");
  Serial.println("IP address: " + String(WiFi.localIP()));
  }

// Function to show a line
void printLine() {
  Serial.println();
  for (int i = 0; i <30; i++){
    Serial.print("-");
  }
  Serial.println();
}
