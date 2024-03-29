#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include <Servo.h>

// Provide the token generation process info.
#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
// #define WIFI_SSID "COMHEM_f2578a"
// #define WIFI_PASSWORD "btmughdz"

#define WIFI_SSID "ABB_Gym_IOT"
#define WIFI_PASSWORD "Welcome2abb"

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
}

void loop()
{
  if (Firebase.ready() && (millis() - readDataPrevMillis > 10 || readDataPrevMillis == 0))
  {
    readDataPrevMillis = millis();

    // Read an Int number from the database path servo/slider
    // int ServoData;
    // if (Firebase.RTDB.getInt(&fbdo, "servo/data"))
    // {
    //   ServoData = fbdo.intData();
    //   Serial.println("Read Servo Data: " + String(ServoData));

    //   // Set the position of the servo based on the retrieved value
    //   setServoPosition(ServoData);
    // }
    // else
    // {
    //   Serial.println("Failed to read Servo data. Reason: " + fbdo.errorReason());
    // }

     int ClawServo;
    if (Firebase.RTDB.getInt(&fbdo, "servo/claw"))
    {
      ClawServo = fbdo.intData();
      Serial.println("Read Claw Data: " + String(ClawServo));

      // Set the position of the servo based on the retrieved value
      setClawPosition(ClawServo);
    }
    else
    {
      Serial.println("Failed to read Servo data. Reason: " + fbdo.errorReason());
    }

    // Read a Float number from the database path motor/data
    float MotorData;
    if (Firebase.RTDB.getFloat(&fbdo, "motor/data"))
    {
      MotorData = fbdo.floatData();
      Serial.println("Read Motor Data: " + String(MotorData, 2));
    }
    else
    {
      Serial.println("Failed to read Float data. Reason: " + fbdo.errorReason());
    }
  }
}

void setClawPosition(int ClawServo)
{
  if (ClawServo == 1)
  {
    servo.write(180);
  }
    else if (ClawServo == 2)
  {
    servo.write(0);
  }
      else if (ClawServo == 0)
  {
    servo.write(90);
  }
}
