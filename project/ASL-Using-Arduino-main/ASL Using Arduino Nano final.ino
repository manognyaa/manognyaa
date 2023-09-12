/*
 How to use a flex sensor/resistro - Arduino Tutorial
   Fade an LED with a flex sensor
   More info: http://www.ardumotive.com/how-to-use-a-flex-sensor-en.html
   Dev: Michalis Vasilakis // Date: 9/7/2015 // www.ardumotive.com  
*/

#include <Arduino_LSM9DS1.h>

float x, y, z;
int degreesX = 0;
int degreesY = 0;
int degreesZ = 0;

const int ledPin = 3; 

const int flexPin1 = A0; 
const int flexPin2 = A1; 
const int flexPin3 = A2; 
const int flexPin4 = A3; 
const int flexPin5 = A4; 

bool no = false;
bool goodbye = false;

int value[5];

void setup(){
  
  pinMode(ledPin, OUTPUT); 
  Serial.begin(9600);       

  while (!Serial);
  Serial.println("Started");

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println("Hz");
}

void loop(){
  
  value[0] = analogRead(flexPin1);
  value[1] = analogRead(flexPin2);
  value[2] = analogRead(flexPin3);
  value[3] = analogRead(flexPin4);
  value[4] = analogRead(flexPin5);

// Mapping the Potentiometer 
  for(int i =0; i<5; i++)
  {
    value[i] = map(value[i], 700, 1023, 0, 255);//Map value 0-1023 to 0-255 (PWM)
    Serial.print("Flex Sensor ");
    Serial.println(i);
    Serial.println( value[i]);
    analogWrite(ledPin, value[i]);          //Send PWM value to led
    delay(500);                          //Small delay
  }


  
  if (Serial.available())
    {   
        Serial.println("Loveday");
        String BT_input = Serial.readString();   // read input string from bluetooth 
        
        if (BT_input=="A")                
        {
          Serial.println(BT_input);
          Serial.println("LED is ON");
        }
        else if (BT_input=="B")
        {
          Serial.println(BT_input);
          Serial.println("LED is OFF");
        }
        else 
        {
          Serial.println(BT_input);        
          Serial.println("Send 'A' to get LED ON");
          Serial.println("Send 'B' to get LED OFF");
        }
        


      
      if (x > 0.1) {
        x = 100 * x;
        degreesX = map(x, 0, 97, 0, 90);
        Serial.print("Tilting up ");
        Serial.print(degreesX);
        Serial.println("  degrees");
      }
      if (x < -0.1) {
        x = 100 * x;
        degreesX = map(x, 0, -100, 0, 90);
        Serial.print("Tilting down ");
        Serial.print(degreesX);
        Serial.println("  degrees");
      }
      if (y > 0.1) {
        y = 100 * y;
        degreesY = map(y, 0, 97, 0, 90);
        Serial.print("Tilting left ");
        Serial.print(degreesY);
        Serial.println("  degrees");
      }
      if (y < -0.1) {
        y = 100 * y;
        degreesY = map(y, 0, -100, 0, 90);
        Serial.print("Tilting right ");
        Serial.print(degreesY);
        Serial.println("  degrees");
      }
      if (z > 0.1) {
        z = 100 * z;
        degreesZ = map(z, 0, 97, 0, 90);
        Serial.print("Board is facing UP ");
        Serial.print(degreesZ);
        Serial.println("  degrees");
      }
      if (z < -0.1) {
        z = 100 * z;
        degreesZ = map(y, 0, -100, 0, 90);
        Serial.print("Board is facing Down");
        Serial.print(degreesZ);
        Serial.println("  degrees");
      }

    // obtaining direction of hand movement
      if (IMU.accelerationAvailable()) {
        IMU.readAcceleration(x, y, z);

      }
      if(value[0]<=200 && value[1] >=200  && value[2] <=200  && value[3] <=200  && value[4] <=200)
      {
        if(x < -0.1)
          Serial.println("\I ask you?\n");
        else
          Serial.println("\nWhere?\n");
        delay(1000);
      }

      else if(value[0]<=200 && value[1] <=  200  && value[2] <= 200  && value[3] <= 200  && value[4] <=200)
      {
        if(x < -0.1)
          Serial.println("\nYes\n");
        delay(1000);
      }
      else if(value[0]>=200 && value[1] >= 200  && value[2] >=200  && value[3] <= 200  && value[4] <=200)
      {
        no = true;
        delay(1000);
      }
      if(no && value[0]<=200 && value[1] <= 200  && value[2] <=200  && value[3] <= 200  && value[4] <=200)
      {
          Serial.println("\n No!!\n ");
          delay(1000);
          no = false;
      }
      else if(value[0]<=200 && value[1] >= 200  && value[2] >=200  && value[3] <= 200  && value[4] <=200)
      {
        Serial.println("\n Peace!!\n ");
        delay(1000);
      }
      else if(value[0]>=200 && value[1] >= 200  && value[2] >=200  && value[3] >=200  && value[4] >=200)
      {
        Serial.println("\nNULL\n");
        delay(1000);
      }
      else if(value[0]<=200 && value[1] <= 200  && value[2] >=200  && value[3] >=200  && value[4] >=200)
      {
        Serial.println("\nPerfect\n");
        delay(1000);
      }
      else if(value[0]<=200 && value[1] >= 200  && value[2] >=200  && value[3] >=200  && value[4] <=200)
      {
        Serial.println("\W\n");
        delay(1000);
      }

      else
      {
        Serial.println("\nThank you Sir!!\n");
        delay(1000);
      }
    }
}

