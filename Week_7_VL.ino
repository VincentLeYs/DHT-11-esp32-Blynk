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
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "IHSFRFateIx0IkG-7Pi8bPkgGPvU6o_O";
char ssid[] = "LAPTOP-VL";
char pass[] = "henk1234";
#define DHTPIN 4          // What digital pin we're connected to
// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
BLYNK_CONNECTED() // runs every time Blynk connection is established
{
    if (isFirstConnect) 
    {
// Request server to re-send latest values for all pins
    Blynk.syncAll();
    isFirstConnect = false;
    }
  }

void sendSensor()
{
  h = dht.readHumidity();
  t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V9, h);
  Blynk.virtualWrite(V10, t);
   str1 = "Temperature Value: " + String(t, 2) + "℃\n";
   str2 = "Humidity Value: " + String(h, 2) + "";
   str = str1 + str2;
if(count==0){//Everytime you start the project it will send a notification for one time
Blynk.email("Value of DHT11", str);
Blynk.notify(str);
count=1;
}
}
void setup()
{
  // Debug console
Serial.begin(9600);
pinMode(led,OUTPUT);
pinMode(button,INPUT_PULLUP);
Blynk.begin(auth, ssid, pass);
dht.begin();
  // Setup a function to be called every second
timer.setInterval(1000L, sendSensor);
}

void loop()
{
    Blynk.run();
  digitalWrite(led,LOW);
  timer.run();
  digitalWrite(led,HIGH);
if(digitalRead(button)==LOW){//It will send a notification for one time when you press the button
Blynk.email("Value of DHT11 sensor", str);
Blynk.notify(str);
delay(500);
}
}
