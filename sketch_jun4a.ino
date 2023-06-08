#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHT11_PIN 4
#define BUTTON_PIN 5
#define POTENTIOMETER_PIN A0

// Este código funcionará com terminal, porém recomenda-se que seja utilizado o Node-RED com o respectivo arquivo de Flow.
// Dependências em Node: node-red-dashboard (3.5.0) e node-red-node-serialport (1.0.4) 

DHT dht(DHT11_PIN, DHT11);

bool buttonState = false;
bool previousButtonState = false;
bool isPotentiometerMode = false; 

void setup() {
  pinMode(DHT11_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  buttonState = digitalRead(BUTTON_PIN);

  if (buttonState != previousButtonState) {
    if (buttonState == LOW) {
      isPotentiometerMode = !isPotentiometerMode;
    }

    previousButtonState = buttonState;
  }

  if (isPotentiometerMode) {
    float potentiometerValue = analogRead(POTENTIOMETER_PIN);
    float temperature = map(potentiometerValue, 0, 1023, 0, 50);
    float humidity = dht.readHumidity();

    Serial.print("POTENCIÔMETRO,");
    Serial.print(temperature);
    Serial.print(",");
    Serial.println(humidity);

  } else {
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    Serial.print("DHT11,");
    Serial.print(temperature);
    Serial.print(",");
    Serial.println(humidity);
  }

  delay(2000); 
}