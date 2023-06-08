// include the library code: 
#include <LiquidCrystal.h> //library for LCD 

// initialize the library with the numbers of the interface pins 
LiquidCrystal lcd(13, 12, 11, 10, 9, 8); 

// Measuring Voltage
#include "EmonLib.h"   // Include Emon Library
EnergyMonitor emon1;   // Create an instance

// Measuring Current Using ACS712
const int Sensor_Pin = A1; //Connect current sensor with A1 of Arduino

//Relay control
const int relayPin = 2;

void setup()
{
  emon1.voltage(A0,202.248, 1.7); // Voltage: input pin, calibration, phase_shift
  lcd.begin(20, 5); // set up the LCD's number of columns and rows:
  pinMode(relayPin, OUTPUT);
}

void loop()
{
  //Measure Voltage
  emon1.calcVI(20,2000); // Calculate all. No.of half wavelengths (crossings), time-out
  int volt   = emon1.Vrms;  //extract Vrms
  
  lcd.setCursor(0,0);
  lcd.print("   VOLTAGE = ");
  lcd.print(volt);
  lcd.print("V  ");

  //Measure Current
  float temp=0;
  float maxpoint = 0;
  for(int i=0;i<500;i++)
  {
    temp = analogRead(Sensor_Pin);
    if(temp>maxpoint)
    {
      maxpoint = temp;
    }
    delay(1);
  }
  float ADCvalue = maxpoint; 
  float Veq = ADCvalue * (5.0 / 1023.0);
  float Current = (Veq-2.5) / (66e-3);
  float AC_Current = ( Current ) / ( sqrt(2) );

  lcd.setCursor(0,1);
  lcd.print("   Current = ");
  lcd.print(AC_Current);
  lcd.print("A         ");
  
  //Measure Power
  int Power = (volt * AC_Current);
  
  lcd.setCursor(0,2);
  lcd.print("   Power = ");
  lcd.print(Power);
  lcd.print("W  ");
  
  //Measure Energy
  long milisec = millis(); //time in milliseconds 
  long time=milisec/1000; //milliseconds to seconds 
  
  float Energy = (Power*time)/3600; //Watt-Hr(3600sec) 

  lcd.setCursor(0,3);
  lcd.print("   Energy = ");
  lcd.print(Energy,1);
  lcd.print("Wh    ");

  if (volt > 255 || volt<206) {
    digitalWrite(relayPin, HIGH); // Open the relay
  } else {
    digitalWrite(relayPin, LOW); // Close the relay
  }  
  delay(200);
}
