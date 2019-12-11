#include <WiFi.h>

// WiFi network name and password:
const char * networkName = "IRLab";
const char * networkPswd = "robots4ever";

// Host 
const char * host = "192.168.50.40";
const int port = 3300;

const int BUTTON_PIN = 0;
const int LED_PIN = 33;

const char ON_STM[] = "On";
const char OFF_STM[] = "Off";


char msg[20];
WiFiClient client;

void setup() {
  // Initilize hardware:
  Serial.begin(115200);
  
  // Connect to the WiFi network (see function below loop)
  connectToWiFi(networkName, networkPswd);

  connectToServer(host, port); 

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN,0);
}

void loop() {
  
  client.write("Hello From ESP32");
  // Connect to Server
  delay(1000);
  Serial.println("Start main loop");

  // Main loop
  while (1) {
    // Check if there is a message
    //if (readMsg(msg) == -1) {Serial.println("Lol");return; } 
    readMsg(msg);
    Serial.println(msg);
    if (strcmp(msg, ON_STM) == 0) {
      Serial.println("It works");
      /* Led  */
      while (client.available() == 0) {
        digitalWrite(LED_PIN,1);
        delay(1000);
        digitalWrite(LED_PIN,0);
        delay(500);
      }
    }
    else if (strcmp(msg, OFF_STM) == 0) {
      digitalWrite(LED_PIN,0);
      while (client.available() == 0) { delay(1000);}  
    } 
  }
  
}

int readMsg(char *message) {
  if (client.available() == 0){
    return -1;
  }
  char data = client.read();
  message[0] = data; 
  int i = 1;
  delay(10);
  while (client.available() > 0) {
      data = client.read();
      message[i] = data; 
      delay(10);
      i++;
  } 
  return 0;
}


void connectToServer(const char * IP, const int Port) {
  if (client.connect(IP, Port)){
    Serial.println("Serve connected");
    client.flush();
  }
}


void connectToWiFi(const char * ssid, const char * pwd)
{
  int ledState = 0;

  printLine();
  Serial.println("Connecting to WiFi network: " + String(ssid));

  WiFi.begin(ssid, pwd);

  while (WiFi.status() != WL_CONNECTED) 
  {
    // Blink LED while we're connecting:
    digitalWrite(LED_PIN, ledState);
    ledState = (ledState + 1) % 2; // Flip ledState
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void printLine()
{
  Serial.println();
  for (int i=0; i<30; i++)
    Serial.print("-");
  Serial.println();
}
