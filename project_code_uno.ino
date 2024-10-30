// include the library code:
#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
#define IR1 A1
#define IR2 A0
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
unsigned int visin = 0, visout = 0;
unsigned int flh1,flh2;
unsigned long valY, valX;

void counter_algorithm()
{
  valY = analogRead(IR1);  valX = analogRead(IR2);
  Serial.print("SENS1:");  Serial.print(valX);
  Serial.print(",SENS2:"); Serial.println(valY);

  if(flh1==0)
  {
    if(valY<500)    // IR value, adjust/change as per your sensor's logic
    {
      flh1=1;
      flh2=0;
      
    }
    else if(valX<500)   // IR value, adjust/change as per your sensor's logic
    {
      flh1=1;
      flh2=1;
    }
  }                                                            
  
  if(flh1==1)
  {
    if(flh2==1)
    {
      if(valY<500)    // IR value, adjust/change as per your sensor's logic
      {
        flh1=0;
        if(visin<999)
        {     
          visin++;
        }
        //led_on_off();
  
        while(valY<500) // IR value, adjust/change as per your sensor's logic
        {
          valY = analogRead(IR1);  
        }
        
        lcd.setCursor(0, 0);
        lcd.print("Count : ");
        lcd.print(visin);
       }
    }
    
    if(flh2==0)
    {
      if(valX<500)  // IR value, adjust/change as per your sensor's logic
      {
        flh1=0;
        if(visin>0)
        {
          visin--;
        }
        //led_on_off();
        
      while(valX<500) // IR value, adjust/change as per your sensor's logic
      {
        valX = analogRead(IR2);   
      }
      lcd.setCursor(0, 0);
      lcd.print("Count : ");
      lcd.print(visin);
      }                 
    }
  } 
}

void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows: 
  pinMode(IR1, INPUT_PULLUP);  pinMode(IR2, INPUT_PULLUP); pinMode(8, OUTPUT);
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print(" Bidirectional  ");//Bidirectional Visitor Counter
  lcd.setCursor(0, 1);
  lcd.print("Visitor Counter ");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Count : ");
  lcd.print(visin);
}

void loop() 
{
  counter_algorithm();
  if(visin>0) {
    digitalWrite(8, LOW);
  }
  else {
    digitalWrite(8, HIGH);
  }}

