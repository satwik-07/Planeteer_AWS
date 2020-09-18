#include<WiFi.h>
#include<AWS_IOT.h>

#define MQ2 34 // pin connected to data pin of MQ2
#define GREEN 2
#define RED 32
int sensorValue = 0;

#define WIFI_SSID "A5" // SSID of your WIFI
#define WIFI_PASSWD "Shams@1131" //your wifi password

#define CLIENT_ID "MQ2__Planeteer"// thing unique ID, this id should be unique among all things associated with your AWS account.
#define MQTT_TOPIC "$aws/things/Planeteer/shadow/update" //topic for the MQTT data
#define AWS_HOST "a37k6n8dtl7oxu-ats.iot.us-east-2.amazonaws.com" // your host for uploading data to AWS,

AWS_IOT aws;

void setup(){
  Serial.begin(9600);
  Serial.print("\nInitializing thing\n");

  Serial.print("\n  Initializing WIFI: Connecting to ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWD);
  Serial.print("  ");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println("\n  Connected.\n  Done");

  Serial.print("\n  Initializing...");
  Serial.println("  Done.");

  Serial.println("\n  Initializing connetction to AWS....");
  if(aws.connect(AWS_HOST, CLIENT_ID) == 0){ // connects to host and returns 0 upon success
    Serial.println("  Connected to AWS\n  Done.");
  }
  else {
    Serial.println("  Connection failed!\n make sure your subscription to MQTT in the test page");
  }
  Serial.println("  Done.\n\nDone.\n");
  pinMode(MQ2, INPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
}

void loop(){
  sensorValue = analogRead(MQ2);
  Serial.println(sensorValue);

  if (sensorValue > 18)
  {
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, HIGH);
  }

  else
  {
    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, LOW);
  }


   String value ="value is :";
   value += String(sensorValue);
   value += "PPM";
    char payload[40];
    value.toCharArray(payload, 40);

    Serial.println("Publishing:- ");
    Serial.println(payload);
     if(aws.publish(MQTT_TOPIC, payload) == 0){// publishes payload and returns 0 upon success
      Serial.println("Success\n");
    }
    else{
      Serial.println("Failed!\n");
    }
    delay(1000);
  }

  
