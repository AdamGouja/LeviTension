#include <PID_v1.h>
#define IN1 14 //entrée analogique
#define IN2 15 //entrée analogique
#define OUT1 5 //sortie PWM
#define OUT2 6 //sortie PWM

double Setpoint_X, Input_X, Output_X;
double p_X = 1;
double i_X = 0;
double d_X = 0.01;

double Setpoint_Y, Input_Y, Output_Y;
double p_Y = 1;
double i_Y = 0;
double d_Y = 0.01;

PID PID_X(&Input_X, &Output_X, &Setpoint_X, p_X, i_X, d_X, DIRECT);
PID PID_Y(&Input_Y, &Output_Y, &Setpoint_Y,p_Y,i_Y,d_Y, DIRECT);

void turn_X(int a)
{
  if(a>=0)
  {
    analogWrite(OUT1,a);//OUT1
  }
  else
  {
    a=-a;
    analogWrite(OUT1,a);//OUT1
  }
}

void turn_Y(int a)
{
  if(a>=0)
  {
    analogWrite(OUT2,a);//OUT2
  }
  else
  {
    a=-a;
    analogWrite(OUT2,a);//OUT2
  }
}

void setup()
{
  pinMode(OUT1,OUTPUT);
  pinMode(OUT2,OUTPUT);
  analogWrite(OUT1,0);
  analogWrite(OUT2,0);
  Setpoint_X = 560;
  Setpoint_Y = 560;
  PID_X.SetTunings(p_X,i_X,d_X);
  PID_Y.SetTunings(p_Y,i_Y,d_Y);
  PID_X.SetOutputLimits(-255,255);
  PID_Y.SetOutputLimits(-255,255);
  PID_X.SetSampleTime(5);
  PID_Y.SetSampleTime(5);
  PID_X.SetMode(AUTOMATIC);
  PID_Y.SetMode(AUTOMATIC);
}

void loop()
{  
  Input_X = analogRead(IN1);//A1
  Input_Y = analogRead(IN2);//A0
  
  PID_X.Compute();
  PID_Y.Compute();
  turn_X(Output_X);
  turn_Y(Output_Y);
}
