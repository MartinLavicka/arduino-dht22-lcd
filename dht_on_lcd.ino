#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
#include "DHT.h"
//#include <Math.h>

#define DHTPIN 2
// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

LiquidCrystal_PCF8574 lcd(0x3F);  // set the LCD address to 0x27 for a 16 chars and 2 line display
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  int error;

  Serial.begin(115200);
  Serial.println("DHT na LCD");

  while (! Serial);

  Serial.println("Dose: check for LCD");

  // See http://playground.arduino.cc/Main/I2cScanner
  Wire.begin();
  Wire.beginTransmission(0x3F);
  error = Wire.endTransmission();
  Serial.print("Error: ");
  Serial.print(error);

  if (error == 0) {
    Serial.println(": LCD found.");

  } else {
    Serial.println(": LCD not found.");
  } // if

  lcd.begin(16, 2); // initialize the lcd
  dht.begin();

  lcd.setBacklight(255);
  lcd.home(); lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Teplota:");
  lcd.setCursor(0, 1);
  lcd.print("Vlhkost:");
} // setup()

void loop()
{
  delay(2000);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  //int hum =  round (h);
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  //float temp = (round (t * 10))/10.0;
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Celsius (isFahreheit = false)
  //float hic = dht.computeHeatIndex(t, h, false);
  
  lcd.setCursor(9, 0);
  lcd.print(t,1);
  lcd.print(" C");
  lcd.setCursor(9, 1);
  lcd.print(h,1);
  lcd.print(" %");
  
  delay(3000);
} // loop()
