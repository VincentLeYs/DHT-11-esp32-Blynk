#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
bool isFirstConnect = true;
String str1;
String str2;
String str;
int led=2;
int button=23;
int count=0;
float h=0;
float t=0;
char auth[] = "IHSFRFateIx0IkG-7Pi8bPkgGPvU6o_O";
char ssid[] = "LAPTOP-VL";
char pass[] = "henk1234";
#define DHTPIN 4         
#define DHTTYPE DHT11     
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

BLYNK_CONNECTED() 
{
    if (isFirstConnect) 
    {

    Blynk.syncAll();
    isFirstConnect = false;
    }
  }

void sendSensor()
{
  h = dht.readHumidity();
  t = dht.readTemperature(); 

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
 
  Blynk.virtualWrite(V9, h);
  Blynk.virtualWrite(V10, t);
   str1 = "Temperature Value: " + String(t, 2) + "℃\n";
   str2 = "Humidity Value: " + String(h, 2) + "";
   str = str1 + str2;
if(count==0){
Blynk.email("Value of DHT11", str);
Blynk.notify(str);
count=1;
}
}
void setup()
{
  
Serial.begin(9600);
pinMode(led,OUTPUT);
pinMode(button,INPUT_PULLUP);
Blynk.begin(auth, ssid, pass);
dht.begin();
  
timer.setInterval(1000L, sendSensor);
}

void loop()
{
    Blynk.run();
  digitalWrite(led,LOW);
  timer.run();
  digitalWrite(led,HIGH);
if(digitalRead(button)==LOW){
Blynk.email("Value of DHT11 sensor", str);
Blynk.notify(str);
delay(500);
}
}
