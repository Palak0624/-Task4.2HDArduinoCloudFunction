#include <WiFiNINA.h> 
#include <Firebase_Arduino_WiFiNINA.h>  

const int redPin = 5;
const int greenPin = 6;
const int bluePin = 7;

FirebaseData firebaseData;
String firebaseHost = "trafficlightproject-c5137-default-rtdb.firebaseio.com"; 
String firebaseAuth = "gG6EHFLX8MYRwel9NJSTIRz9AKZ74njvWUgy6Ol8";  

char ssid[] = "Palak";
char pass[] = "11223344";  

void setup() {
  Serial.begin(9600);

  // Connect to Wi-Fi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize Firebase
  Firebase.begin(firebaseHost, firebaseAuth, ssid, pass);
  Firebase.reconnectWiFi(true);

  // Initialize LED pins
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
}

void loop() {
  if (Firebase.getString(firebaseData, "/trafficLight")) {
    String command = firebaseData.stringData();
    Serial.println("Command received from Firebase: " + command);
    controlTrafficLight(command);  
  } else {
    Serial.println("Failed to get data from Firebase: " + firebaseData.errorReason());
  }
  delay(1000);  
}

void controlTrafficLight(String command) {
  command.toLowerCase();  
  char firstChar = command.charAt(0);  

  if (firstChar == 'r') {  
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
    Serial.println("Red light ON");

  } else if (firstChar == 'g') {  
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
    Serial.println("Green light ON");

  } else if (firstChar == 'b') {  
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, HIGH);
    Serial.println("Blue light ON");

  } else {  
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
    Serial.println("All lights OFF");
  }
}