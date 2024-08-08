#include <ESP8266WiFi.h> 
#include <PubSubClient.h>
const char *ssid = "Mithun"; // Enter your WiFi name 
const char *password = "indian789";
const char *mqtt_broker ="91.121.93.94" ;
const char *message="Patient 2";
const char *outTopic="ABC";
WiFiClient espClient1;
PubSubClient client(espClient1);


int LED=D7;
int BUTTON=D1;
int BUZZER=D8;

void setup()
{
  pinMode(LED,OUTPUT);
  pinMode(BUZZER,OUTPUT);
  pinMode(BUTTON,INPUT);
  Serial.begin(115200);
   Serial.begin(115200); 
     delay(1000); // Delay for stability 
  
     // Connecting to a WiFi network 
     WiFi.begin(ssid, password); 
     while (WiFi.status() != WL_CONNECTED) { 
         delay(500); 
         Serial.println("Connecting to WiFi..."); 
     } 
     Serial.println("Connected to the WiFi network"); 
  
     // Connecting to an MQTT broker 
     client.setServer(mqtt_broker, 1883); 
      
     while (!client.connected()) { 
         String client_id = "esp8266-client-"; 
         client_id += String(WiFi.macAddress()); 
         Serial.printf("The client %s connects to the MQTT broker\n", client_id.c_str()); 
         if (client.connect(client_id.c_str(),NULL,NULL)) { 
             Serial.println("MQTT broker connected"); 
         } else { 
             Serial.print("Failed with state "); 
             Serial.print(client.state()); 
             delay(2000); 
         } 
     } 
 
  
}

void loop()
{  
  
  int input=digitalRead(BUTTON);
  if(input==HIGH)
  {
    digitalWrite(LED,HIGH);
    delay(1000);
    client.publish(outTopic,message);
    Serial.println("Publish acknowledged.");
    
    digitalWrite(BUZZER,HIGH);
    delay(500);
    
  }
  else{
    digitalWrite(LED,LOW);
    digitalWrite(BUZZER,LOW);
  }
    
  
    
}
