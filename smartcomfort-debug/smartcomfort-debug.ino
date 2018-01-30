
// Pinout DigiSpark:
// P5 --> D5 A0
// P4 --> D4 A2  PWM4A2  USB-
// P3 --> D3 A3          USB+
// P2 --> D2 A1  SCK     SCL
// P1 --> D1     PWM1    MISO
// P0 --> D0     PWM0    AREF  MOSI  SDA

// LM35 on analog 1
// Ventilator relay on digital P2

// For debugging
#include "DigiKeyboard.h"

const int ventilatorPin = 1;  // Digital P1
const int temperaturePin = 1; // Confusingly, analog 1 is P2

const int maximumTemperature = 33; // Temperature vents on
const int minimumTemperature = 24; // Temperature vents off
const int timeBetweenChecks = 2000;

void setup()
{
  analogReference(DEFAULT);       // Use internal voltage reference as will be more accurate / consistent
  analogRead(temperaturePin);     // Reference voltage is actually set on the first analogRead after changed
  analogRead(temperaturePin);     // Discard the first measurement as it may be off
  pinMode(ventilatorPin, OUTPUT); // Make output so we can turn the vents on and off
}

void loop()
{

  //For debugging
  DigiKeyboard.sendKeyStroke(0);
  
  int reading = analogRead(temperaturePin);
  float temperature = reading * 0.48828125;
  
  //For debugging
  DigiKeyboard.println(temperature);

  if (temperature >= maximumTemperature) {
    digitalWrite(ventilatorPin, HIGH); // Vents on if maximum temperature reached
  }
  else if (temperature <= minimumTemperature){
    digitalWrite(ventilatorPin, LOW); // Vents off if minimum temperature reached
  }

  // For debugging
  DigiKeyboard.delay(timeBetweenChecks); // hang around for specified milliseconds
}
