
int motorpin1=5;
int motorpin2=4;
int sensorpin=A7;
int sensorvalue=0;
int outputvalue=0;
int targetvalue;
float preverror=0;
int diff=0;
int inte=0;
int dt;
int t1;
int t2;   //290=0V NL region=300-310
int maxoutputvalue=255;

int zeroreading = 883;
int lowreading = 0;
int lowangle = 295;
int highreading = 1023;
int highangle = 307;

double span = lowangle+(360-highangle);
double resolution = (highreading-lowreading)/span;
double rotate = (180*resolution);

//int rotate=550;
int zero=0;

float kp=10, kd=20, ki=0.001;

void setup() {
  // put your setup code here, to run once:
  pinMode(sensorpin, INPUT); //input is output of the potentiometer (voltage)
  pinMode(motorpin1,OUTPUT); // outputs are the input to the IC. But outputs are digital
  pinMode(motorpin2,OUTPUT);
  Serial.begin(9600);
  sensorvalue=analogRead(sensorpin);
  t1=millis();
//  targetvalue=100;
  if(sensorvalue > rotate)
  {
    targetvalue=sensorvalue-rotate;
  }
  else
  {
    targetvalue=sensorvalue+rotate;
  }
  preverror=(targetvalue-sensorvalue);
  inte=preverror;
}

void loop() {
 sensorvalue=analogRead(sensorpin);
 t2=millis();
 Serial.print(t2);
 Serial.print('\t');
 
   float err=(targetvalue-sensorvalue);
   Serial.println(sensorvalue);Serial.print('\t');
   dt=t2-t1;
   inte=inte+(err*dt);
   diff=(err-preverror)/dt;
   t1=t2;
   outputvalue = 5*abs(kp*err+kd*diff+ki*inte);
   if(outputvalue>maxoutputvalue)
   {
    outputvalue=maxoutputvalue;
   }
  
  if (err>0)
  {
    analogWrite(motorpin1, outputvalue);
    analogWrite(motorpin2, zero);
  }
  else
  {
    analogWrite(motorpin2, outputvalue);
    analogWrite(motorpin1, zero);
  }
  preverror=err;
delay(10);
}
