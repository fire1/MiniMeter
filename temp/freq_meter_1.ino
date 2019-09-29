#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 7, 8, 9, 10); //(RS,EN,D4,D5,D6,D7)
unsigned int count;
unsigned int getCount()
{
  TCCR1B = 0 ; 
  count = TCNT1;
  TCNT1 = 0;
  bitSet(TCCR1B , CS12); 
  bitSet(TCCR1B , CS11); 
  bitSet(TCCR1B , CS10); 
  return count;
}
void setup_()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  digitalWrite(5, HIGH);
  TCCR1A = 0; 
  getCount(); 
}
void loop_()
{
  delay(1000);
  Serial.print(getCount()/2);
  Serial.println("Hz");
  lcd.clear();
  delay(1000);
  lcd.print("Frequency:");
  lcd.setCursor(0, 1);
  lcd.print(getCount()/2);
  lcd.print(" Hz           ");
}
