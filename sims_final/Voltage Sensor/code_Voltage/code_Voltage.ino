// include the library code
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins 
LiquidCrystal lcd(13, 12, 11, 10, 9, 8); 

// Include Emon Library and Create an instance
#include "EmonLib.h"
EnergyMonitor emon1;

void setup()
{
  emon1.voltage(A0,202.248, 1.7); // Voltage: input pin, calibration, phase_shift

  lcd.begin(20, 4); // set up the LCD's number of columns and rows:
  lcd.setCursor(0,0);
  lcd.print(" MEASURE AC VOLTAGE             ");
}

void loop()
{
  emon1.calcVI(20,2000); // Calculate all. No.of half wavelengths (crossings), time-out
  int volt   = emon1.Vrms;  //extract Vrms into Variable
  
  lcd.setCursor(0,2);
  lcd.print("   VOLTAGE = ");
  lcd.print(volt);
  lcd.print("V         ");
}
