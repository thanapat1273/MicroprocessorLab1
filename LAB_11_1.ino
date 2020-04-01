#include <SPI.h>

#define DATA_PIN 11
#define CLOCK_PIN 13
#define SS_PIN_1 10
#define SS_PIN_2 9
#define MOTOR_D1_PIN 7 
#define MOTOR_D2_PIN 8 
#define MOTOR_PWM_PIN 6 
#define INT_PIN_1 3
#define INT_PIN_2 2
#define LED 12

volatile int timer1_counter;
volatile int num = 0;
int count = 1;
int A = 0;
int ENA = 0;
int ENB = 0;
int l = 1;

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
  pinMode(INT_PIN_1, INPUT_PULLUP);
  pinMode(INT_PIN_2, INPUT_PULLUP);
  pinMode(MOTOR_D1_PIN, OUTPUT);
  pinMode(MOTOR_D2_PIN, OUTPUT);
  pinMode(MOTOR_PWM_PIN, OUTPUT);
  pinMode(LED, OUTPUT);
  Serial.println("TestEncoder");
  
  InitialInterruptTimer(1);
  
  attachInterrupt(digitalPinToInterrupt(INT_PIN_1),
                  ISR_Ext, RISING);
  
  
  Serial.begin(9600);
  Serial.println("TestEncoder");
}

void loop()
{
  ENA = digitalRead(INT_PIN_1);
  ENB = digitalRead(INT_PIN_2);
  digitalWrite(MOTOR_D1_PIN,LOW); 
  digitalWrite(MOTOR_D2_PIN,HIGH); 
  analogWrite(MOTOR_PWM_PIN,100);
  num = count/100;
  if(num == 100)
  {
    num = 0;
    count = 0;
  }
  if((count>0)&&((count%2) == 1))
  {
    num++;
  }
  else if((count>0)&&((count%2) ==0))
  {
    num = num;
  }
  if( A == 0 && ENA == 1)
  {
    if(ENB == 1)
    {
      Serial.println("Counter-Clockwise");
      l++;
    }
    else if(ENB == 0)
    {
      Serial.println("Clockwise");
      l--;
    }
  }  
  if(l > 0)
  {
    digitalWrite(LED,HIGH);
  }
  A = 1;
  
  Serial.println(count);
  delay(500);
}

ISR(TIMER1_OVF_vect)
{
  TCNT1 = timer1_counter;
  write7Segment(num);
}

void ISR_Ext(){
   count++;
}
