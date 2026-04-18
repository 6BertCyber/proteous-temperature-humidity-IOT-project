#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// DHT setup
#define DHTPIN 2          // DATA pin
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// LCD setup (address may be 0x27 or 0x3F)
LiquidCrystal_I2C lcd(0x3F, 20, 4);

// Pins
int redLED = 6;
int greenLED = 5;
int buzzer = 4;

void setup() {
  Serial.begin(9600);

  dht.begin();
  lcd.init();
  lcd.backlight();

  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("System Starting...");
  delay(2000);
  lcd.clear();
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  // Check if reading failed
  if (isnan(temp) || isnan(hum)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!   ");
    return;
  }

  // Display on LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print(" C   ");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(hum);
  lcd.print(" %   ");

  // Control logic
  if (temp > 30) {
    digitalWrite(redLED, HIGH);
    digitalWrite(buzzer, HIGH);
    digitalWrite(greenLED, LOW);

    lcd.setCursor(0, 2);
    lcd.print("Status: HOT     ");
  } else {
    digitalWrite(redLED, LOW);
    digitalWrite(buzzer, LOW);
    digitalWrite(greenLED, HIGH);

    lcd.setCursor(0, 2);
    lcd.print("Status: NORMAL  ");
  }

  delay(2000);
}