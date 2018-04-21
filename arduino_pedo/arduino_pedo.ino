#include <EEPROM.h>
#include <I2Cdev.h>
#include <MPU6050.h>

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

MPU6050 accelgyro;

int16_t ax, ay, az,axpre=0, aypre=0, azpre=0;
int count = 0;
int16_t gx, gy, gz;

#define OUTPUT_READABLE_ACCELGYRO

#define LED_PIN 13
bool blinkState = false;
int value;
void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    Serial.begin(9600);

    // initialize device
    //Serial.println("Initializing PEDOMETER ...");
    accelgyro.initialize();

    // verify connection
    //Serial.println("Testing device connections...");
    //Serial.println(accelgyro.testConnection() ? "Pedometer connection successful" : "Pedometer connection failed");
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    // read raw accel/gyro measurements from device
    digitalWrite(7,LOW);
    digitalWrite(6,HIGH);
    
    if(digitalRead(6) == HIGH){
    //Serial.print("Steps counted so far : ");
    //Serial.println(EEPROM.read(100));
    
    axpre = ax; aypre = ay; azpre = az;
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    #ifdef OUTPUT_READABLE_ACCELGYRO
        // display tab-separated accel/gyro x/y/z values
        
        if((ax > (axpre + 2500))&&(ay > (aypre + 2500))||(az > (azpre + 2500))&&(ay > (aypre + 2500))||(ax > (axpre + 2500))&&(az > (azpre + 2500)))
        {
          count ++;
        }
        
        if(digitalRead(3) == LOW){
          
        //printing X, Y, Z co-ordinates  
        //Serial.print("a/g:\t");
        //Serial.print(ax); Serial.print("\t");
        //Serial.print(ay); Serial.print("\t");
        //Serial.print(az); Serial.print("\t");
        //Serial.print(gx); Serial.print("\t");
        //Serial.print(gy); Serial.print("\t");
        //Serial.print(gz);Serial.print("\t");
        Serial.println(count);
        }
        else
        {
         // Serial.println();
         // Serial.print("Total number of Steps : ");
          
          
          Serial.println(count);
          EEPROM.write(100, count);
          value = EEPROM.read(100);
     
          //Serial.print("Value Stored in EEPROM");
          //Serial.println(value);
      }
        
    #endif

    #ifdef OUTPUT_BINARY_ACCELGYRO
        //Serial.write((uint8_t)(ax >> 8)); Serial.write((uint8_t)(ax & 0xFF));
        //Serial.write((uint8_t)(ay >> 8)); Serial.write((uint8_t)(ay & 0xFF));
        //Serial.write((uint8_t)(az >> 8)); Serial.write((uint8_t)(az & 0xFF));
        //Serial.write((uint8_t)(gx >> 8)); Serial.write((uint8_t)(gx & 0xFF));
        //Serial.write((uint8_t)(gy >> 8)); Serial.write((uint8_t)(gy & 0xFF));
        //Serial.write((uint8_t)(gz >> 8)); Serial.write((uint8_t)(gz & 0xFF));
    #endif

    // blink LED to indicate activity
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
}
else

{
  

          digitalWrite(13, HIGH);
          Serial.print("Total Steps:");
          Serial.println(value);
          delay(500);         
          Serial.print("Distance :");
          Serial.print(value*0.3);
          digitalWrite(13,LOW);
}

delay(1000);

}
