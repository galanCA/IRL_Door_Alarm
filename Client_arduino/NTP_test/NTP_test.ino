#include <SPI.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

//Wifi network name and passwd
const char * networkName = "IRLab";
const char * networkPswd = "robots4ever";

const int LED_PIN = 2;

// Variables to save date and time
String formattedDay;
String formattedDate;
String formattedHour;
String dayStamp;
String timeStamp;
String hourStamp;

void setup() {
  // Setup Serial command
  Serial.begin(115200);
  
  // connect to wifi
  connectToWiFi(networkName, networkPswd);

  timeClient.begin();
  timeClient.setTimeOffset(-3600*7);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }
  // The formattedDate comes with the following format:
  // 2018-05-28T16:00:13Z
  // We need to extract date and time
  formattedDate = timeClient.getFormattedDate();
  formattedDay = timeClient.getDay();
  formattedHour = timeClient.getHours();
  Serial.println(formattedDay + " " + "Hour" + formattedHour+ formattedDate);

  // Extract date
  int splitT = formattedDate.indexOf("T");
  dayStamp = formattedDate.substring(0, splitT);
  Serial.print("DATE: ");
  Serial.println(dayStamp);
  // Extract time
  timeStamp = formattedDate.substring(splitT+1, formattedDate.length()-1);
  Serial.print("HOUR: ");
  Serial.println(timeStamp);
  // Extract hour
  hourStamp = formattedDate.substring(splitT+1,splitT+3);
  Serial.print(hourStamp);
  if (hourStamp.toInt() > 16 || hourStamp.toInt() < 07) {
    Serial.println(" Off Hours");
  }

  else {
    Serial.println(" On Hours");
  }
  
  delay(1000);
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
  Serial.print("IP address: ");
  Serial.println(String(WiFi.localIP()));
  }

// Function to show a line
void printLine() {
  Serial.println();
  for (int i = 0; i <30; i++){
    Serial.print("-");
  }
  Serial.println();
}
