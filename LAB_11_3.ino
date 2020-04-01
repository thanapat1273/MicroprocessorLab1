#include <SPI.h>

#define DATA_PIN 11
#define CLOCK_PIN 13
#define SS_PIN_1 10
#define SS_PIN_2 9
#define MOTOR_D1_PIN 7 
#define MOTOR_D2_PIN 8 
#define MOTOR_PWM_PIN 6 
int INT_PIN_B = 3;
int INT_PIN_A = 2;
#define LED 12
#define P_METER A0

volatile int num = 0;
int count = 1;
int A = 0;
int ENA = 0;
int ENB = 0;
int l = 1;
int setpoint = 0;
volatile int encoderCount = 0;
volatile int encoderDir = 0;
volatile int timer1_counter;

int map7seg[10] = {
  0b00111111, 
  0b00000110, 
  0b01011011, 
  0b01001111, 
  0b01100110, 
  0b01101101, 
  0b01111101, 
  0b00000111, 
  0b01111111, 
  0b01101111
};

void spi_write_1(unsigned char cData){
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, cData);
  digitalWrite(SS_PIN_1, HIGH);
  digitalWrite(SS_PIN_1, LOW);
}
void spi_write_2(unsigned char cData){
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, cData);
  digitalWrite(SS_PIN_2, HIGH);
  digitalWrite(SS_PIN_2, LOW);
}
void write7Segment(unsigned char num){
  spi_write_1( map7seg[num/10] );
  spi_write_2( map7seg[num%10] );
}
void InitialInterruptTimer(int freq)
{
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  
  timer1_counter = 62500/freq;
  TCNT1 = timer1_counter;
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << TOIE1);
  interrupts();
}

void setup()
{
  pinMode(SS_PIN_1, OUTPUT);
  pinMode(SS_PIN_2, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(INT_PIN_B, INPUT_PULLUP);
  pinMode(INT_PIN_A, INPUT_PULLUP);
  pinMode(MOTOR_D1_PIN, OUTPUT);
  pinMode(MOTOR_D2_PIN, OUTPUT);
  pinMode(MOTOR_PWM_PIN, OUTPUT);
  pinMode(LED, OUTPUT); 
  pinMode(P_METER, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(INT_PIN_A),
                 Channel1A_callback, RISING);
  attachInterrupt(digitalPinToInterrupt(INT_PIN_B),
                 Channel1B_callback, RISING);
  
  
  Serial.begin(9600);
  Serial.setTimeout(10);
  Serial.println("TestEncoder");
}

void loop()
{
  setpoint = analogRead(P_METER);
  if (Serial.available() > 0)
  {
    setpoint = Serial.parseInt();
  }
  if(setpoint < 0)
  {
    digitalWrite(LED,HIGH);
  }
  else if(setpoint > 0)
  {
    digitalWrite(LED,LOW);
  }
  int error = setpoint - encoderCount;
  int p = 1.25*(float)(error);
  write7Segment(encoderCount);
  Setspeed(p);
  Serial.print(setpoint);
  Serial.print(",");
  Serial.println(encoderCount);
  delay(10);
}

void Channel1A_callback()
{
  if (digitalRead(INT_PIN_A)==1 && 
    digitalRead(INT_PIN_B)==0)
  {
    encoderCount++;
    encoderDir = 1;
  }
}

void Channel1B_callback()
{
  if (digitalRead(INT_PIN_A)==0 && 
    digitalRead(INT_PIN_B)==1)
  {
    encoderCount--;
    encoderDir = 0;
  }
}

void Cwise(int speed) 
{
  digitalWrite(MOTOR_D1_PIN,HIGH);
  digitalWrite(MOTOR_D2_PIN,LOW);
  analogWrite(MOTOR_PWM_PIN,speed);
}

void CCwise(int speed) 
{
  digitalWrite(MOTOR_D1_PIN,LOW);
  digitalWrite(MOTOR_D2_PIN,HIGH);
  analogWrite(MOTOR_PWM_PIN,speed);
}

void Setspeed(int speed)
{
  if(speed > 0)
  {
    if(speed > 255)
    {
      speed = 255;
    }
    Cwise(speed);
  }
  else if(speed < 0)
  {
    speed = speed * (-1);
    if(speed > 255)
    {
      speed = 255;
    }
    CCwise(speed);
  }
  else
  {
    Cwise(1);
  }
}
