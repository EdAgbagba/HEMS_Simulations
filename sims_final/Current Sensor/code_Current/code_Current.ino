// include the library code: 
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins 
LiquidCrystal lcd(13, 12, 11, 10, 9, 8); 

// Connect current sensor to A1 pin of Arduino
const int Sensor_Pin = A1;

void setup()
{
  lcd.begin(20, 4); // set up the LCD's number of columns and rows
  lcd.setCursor(0,0);
  lcd.print("  AC CURRENT READER             ");
}

void loop()
{
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

  lcd.setCursor(0,2);
  lcd.print("   Current = ");
  lcd.print(AC_Current);
  lcd.print("A         ");
  delay(500);
}
