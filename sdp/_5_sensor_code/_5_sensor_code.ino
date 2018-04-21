const int sensorPin1 = A0;  // pinky finger   
const int sensorPin2 = A1;  // ring finger
const int sensorPin3 = A2;  // middle finger 
const int sensorPin4 = A3;  // index finger
const int sensorPin5 = A4;  // thumb

float Vcc = 5.06; // measure Vcc of Arduino from multimeter

float R21 = 109600; //200K resistance as R2 of voltage divider     // formula for voltage divider V= [R2/(R1+R2)]*Vcc //R1 is the flex sensor
float R22 = 150600; //200K resistance as R2 of voltage divider     // formula for voltage divider V= [R2/(R1+R2)]*Vcc //R1 is the flex sensor
float R23 = 112000; //200K resistance as R2 of voltage divider     // formula for voltage divider V= [R2/(R1+R2)]*Vcc //R1 is the flex sensor
float R24 = 95000; //200K resistance as R2 of voltage divider     // formula for voltage divider V= [R2/(R1+R2)]*Vcc //R1 is the flex sensor
float R25 = 150200; //200K resistance as R2 of voltage divider     // formula for voltage divider V= [R2/(R1+R2)]*Vcc //R1 is the flex sensor

 
 float straightResistance1 = 45000.0; // resistance when straight
 float bendResistance1     = 220000.0; // resistance at 180 deg

 float straightResistance2 = 125000.0; // resistance when straight
 float bendResistance2     = 280000.0; // resistance at 180 deg

 float straightResistance3 = 65000.0; // resistance when straight
 float bendResistance3     = 285000.0; // resistance at 180 deg

 float straightResistance4 = 53000.0; // resistance when straight
 float bendResistance4     = 290000.0; // resistance at 180 deg

 float straightResistance5 = 125000.0; // resistance when straight
 float bendResistance5     = 340000.0; // resistance at 180 deg

void setup() 
{
  Serial.begin(9600);
  pinMode(sensorPin1, INPUT);
  pinMode(sensorPin2, INPUT);
  pinMode(sensorPin3, INPUT);
  pinMode(sensorPin4, INPUT);
  pinMode(sensorPin5, INPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
}

void loop() 
{
  // calculating the analog value
  
  int flexADC1 = analogRead(sensorPin1);
  int flexADC2 = analogRead(sensorPin2);
  int flexADC3 = analogRead(sensorPin3);
  int flexADC4 = analogRead(sensorPin4);
  int flexADC5 = analogRead(sensorPin5);


  //calculating the voltage corresponding to the analog value
  
  float flexV1 = (flexADC1 / 1023.0)* Vcc ;
  float flexV2 = (flexADC2 / 1023.0)* Vcc ;
  float flexV3 = (flexADC3 / 1023.0)* Vcc ;
  float flexV4 = (flexADC4 / 1023.0)* Vcc ;
  float flexV5 = (flexADC5 / 1023.0)* Vcc ;


  // calculating the resistance of the flex sensor from the voltage output
  
  float flexR1 = R21 * (Vcc / flexV1 - 1.0);
  float flexR2 = R22 * (Vcc / flexV2 - 1.0);
  float flexR3 = R23 * (Vcc / flexV3 - 1.0);
  float flexR4 = R24 * (Vcc / flexV4 - 1.0);
  float flexR5 = R25 * (Vcc / flexV5 - 1.0);
  
  

  // Use the calculated resistance to estimate the sensor's  bend angle:
  
  float angle1 = map(flexR1, straightResistance1, bendResistance1, 0, 180.0);
  float angle2 = map(flexR2, straightResistance2, bendResistance2, 0, 180.0);
  float angle3 = map(flexR3, straightResistance3, bendResistance3, 0, 180.0);
  float angle4 = map(flexR4, straightResistance4, bendResistance4, 0, 180.0);
  float angle5 = map(flexR5, straightResistance5, bendResistance5, 0, 180.0);



  // if the angle ranges from 45 to 90 degrees then display the details on the serial monitor
  
  if(angle1>=45 && angle1<=180)
  {
  Serial.println("Resistance: " + String(flexR1) + " ohms");
  Serial.println("Bend: " + String(angle1) + " degrees");
  Serial.println("Pinky finger active");
  digitalWrite(2,HIGH);
  Serial.println();
  delay(1000);
  digitalWrite(2,LOW);
  delay(1000);
  }

  else if(angle2>=45 && angle2<=180)
  {
  Serial.println("Resistance: " + String(flexR2) + " ohms");
  Serial.println("Bend: " + String(angle2) + " degrees");
  Serial.println("Ring finger active");
  digitalWrite(3,HIGH);
  Serial.println();
  delay(1000);
  digitalWrite(3,LOW);
  delay(1000);
  }

  else if(angle3>=45 && angle3<=180)
  {
  Serial.println("Resistance: " + String(flexR3) + " ohms");
  Serial.println("Bend: " + String(angle3) + " degrees");
  Serial.println("Middle finger active");
  digitalWrite(4,HIGH);
  Serial.println();
  delay(1000);
  digitalWrite(4,LOW);
  delay(1000);
  }

 else if(angle4>=45 && angle4<=180)
  {
  Serial.println("Resistance: " + String(flexR4) + " ohms");
  Serial.println("Bend: " + String(angle4) + " degrees");
  Serial.println("Index finger active");
  digitalWrite(5,HIGH);
  Serial.println();
  delay(1000);
  digitalWrite(5,LOW);
  delay(1000);
  }

 else if(angle5>=45 && angle5<=180)
  {
  Serial.println("Resistance: " + String(flexR5) + " ohms");
  Serial.println("Bend: " + String(angle5) + " degrees");
  Serial.println("Thumb active");
  digitalWrite(6,HIGH);
  Serial.println();
  delay(1000);
  digitalWrite(6,LOW);
  delay(1000);
  }
  else
  {
  Serial.println("No fingers active");
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  delay(1000);  
  }
 
}

