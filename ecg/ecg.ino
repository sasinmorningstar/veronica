int value=0;
int val[700];
int a=0;

void setup() {
  // initialize the serial communication:
  Serial.begin(9600);
  pinMode(10, INPUT); // Setup for leads off detection LO +
  pinMode(11, INPUT); // Setup for leads off detection LO -
  
}

void loop() {
  if(a<=699){
  if((digitalRead(10) == 1)||(digitalRead(11) == 1)){
    Serial.println('!');
  }
  else{
    // send the value of analog input 0:
//      for(int i=0;i<14;i++)
//      {
//       value = value + (analogRead(A0)-338);  
//      }
//      value=value/14;
      value= analogRead(A0)-338;
      val[a]=value;
      a++;
      Serial.println(a);
      delay(15);
      }
  //Wait for a bit to keep serial data from saturating
  }
  else{
    for(int b=0;b<=699;b++)
    {
    Serial.println(val[b]);
    delay(15);
    }
  }
}
