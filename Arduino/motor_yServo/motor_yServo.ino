#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include <Servo.h>

// Provide the token generation process info.
#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "ABB_Gym_IOT"
#define WIFI_PASSWORD "Welcome2abb"

#define motorPinRightDir 0  // Replace with the appropriate GPIO pin for motor direction
#define motorPinRightSpeed 5  // Replace with the appropriate GPIO pin for motor speed

// Insert Firebase project API Key
#define API_KEY "AIzaSyABXTpgXJhHMPcv9E5jb8VYCoGFzjvX3Rg"

// Insert RTDB URL
#define DATABASE_URL "https://clawmachine-37996-default-rtdb.europe-west1.firebasedatabase.app/"

// Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

Servo servo; // Create a Servo object

unsigned long readDataPrevMillis = 0;
bool signupOK = false;

void setup()
{
  servo.attach(5);
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  servo.attach(D1); // Attach the servo to pin D1

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", ""))
  {
    Serial.println("ok");
    signupOK = true;
  }
  else
  {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long-running token generation task */
  config.token_status_callback = tokenStatusCallback; // See addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  pinMode(motorPinRightDir, OUTPUT);
  pinMode(motorPinRightSpeed, OUTPUT);
}

void loop()
{
  if (Firebase.ready() && (millis() - readDataPrevMillis > 10 || readDataPrevMillis == 0))
  {
    readDataPrevMillis = millis();

    // Read an Int number from the database path servo/slider
    int ServoData;
    if (Firebase.RTDB.getInt(&fbdo, "servo/data"))
    {
      ServoData = fbdo.intData();
      Serial.println("Read Servo Data: " + String(ServoData));

      // Set the position of the servo based on the retrieved value
      setServoPosition(ServoData);
    }
    else
    {
      Serial.println("Failed to read Servo data. Reason: " + fbdo.errorReason());
    }

    // Read an Int number from the database path motor/data
    int MotorData;
    if (Firebase.RTDB.getInt(&fbdo, "motor/data"))
    {
      MotorData = fbdo.intData();
      Serial.println("Read Motor Data: " + String(MotorData, 2));

      setMotorPosition(MotorData);
    }
    else
    {
      Serial.println("Failed to read Motor data. Reason: " + fbdo.errorReason());
    }
  }
}

void setServoPosition(int position)
{
  // Ensure the position is within valid range (0 to 90)
  position = constrain(position, 0, 90);

  // Map the position to servo range (adjust if needed)
  int servoPosition = map(position, 0, 90, 0, 180);

  // Set the position of the servo
  servo.write(servoPosition);

  Serial.println("Set Servo Position: " + String(position));
  delay(10); // Add a delay to allow servo to reach the desired position
}

void setMotorPosition(int MotorData)
{
  if (MotorData == 0)
  {
    analogWrite(motorPinRightSpeed, 0);
  }
  else if (MotorData == 1)
  {
    // Adjust the direction pin value based on your motor's requirement
    digitalWrite(motorPinRightDir, 1);  // or LOW depending on your motor
    analogWrite(motorPinRightSpeed, 900);

  }
    else if (MotorData == 2)
  {
    // Adjust the direction pin value based on your motor's requirement
    digitalWrite(motorPinRightDir, 0);  // or LOW depending on your motor
    analogWrite(motorPinRightSpeed, 1000);
  }
}