#include <Servo.h> // library for servo motors

// 180 horizontal MAXIMUM
Servo horizontal; // Value for horizontal servo
int servoh = 180;        

int servohLimitHigh = 180; //Upper limit
int servohLimitLow = 65; //Lower limit


Servo vertical;   // Vertical servo 
int servov = 45;    
int servovLimitHigh = 80;
int servovLimitLow = 15;



int ldrTL = 0; // Connection to LDR resistors
int ldrTR = 1; 
int ldrBL = 2; 
int ldrBR = 3; 

void setup()
{
  Serial.begin(9600);
  horizontal.attach(9); // Horizontal servo to digital pin 9
  vertical.attach(10); // Vertical servo to digital pin 10
  horizontal.write(180);
  vertical.write(45);
  delay(3000);
}

void loop() 
{
  int lt = analogRead(ldrTL); // Top left 
  int rt = analogRead(ldrTR); // Top right 
  int bl = analogRead(ldrBL); // Bottom left 
  int br = analogRead(ldrBR); // Bottom rigt 
  
  int dtime = 10;
  int tol = 50;
  
  int avt = (lt + rt) / 2; // Maximum upper value
  int avd = (bl + br) / 2; // Maximum lower value
  int avl = (lt + bl) / 2; // Maximum left value
  int avr = (rt + br) / 2; // Maximum right value

  int dvert = avt - avd; // difference between upper and lower
  int dhoriz = avl - avr;// difference between right and left
  
  
  Serial.print(avt);  
  Serial.print(" ");
  Serial.print(avd);
  Serial.print(" ");
  Serial.print(avl);
  Serial.print(" ");
  Serial.print(avr);
  Serial.print("   ");
  Serial.print(dtime);
  Serial.print("   ");
  Serial.print(tol);
  Serial.println(" ");
  
    
  if (-1*tol > dvert || dvert > tol) // Check the difference to switch to the vertical angle
  {
  if (avt > avd)
  {
    servov = ++servov;
     if (servov > servovLimitHigh) 
     { 
      servov = servovLimitHigh;
     }
  }
  else if (avt < avd)
  {
    servov= --servov;
    if (servov < servovLimitLow)
  {
    servov = servovLimitLow;
  }
  }
  vertical.write(servov);
  }
  
  if (-1*tol > dhoriz || dhoriz > tol) // Check the difference to switch to the horizontal angle
  {
  if (avl > avr)
  {
    servoh = --servoh;
    if (servoh < servohLimitLow)
    {
    servoh = servohLimitLow;
    }
  }
  else if (avl < avr)
  {
    servoh = ++servoh;
     if (servoh > servohLimitHigh)
     {
     servoh = servohLimitHigh;
     }
  }
  else if (avl = avr)
  {
    
  }
  horizontal.write(servoh);
  }
   delay(dtime);

}