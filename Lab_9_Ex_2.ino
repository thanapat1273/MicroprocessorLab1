#define LED_PIN_0 9
#define INT_PIN   3

int count = 0;
int count_ISR;
int button = 0;
int timer1_counter;
int toggle = 1;

void setup()
{
  pinMode(LED_PIN_0, OUTPUT);
  pinMode(INT_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(INT_PIN),
                   ISR_Callback, FALLING);
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  
  timer1_counter = 34286;
  TCNT1 = timer1_counter;
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << TOIE1);
  
  interrupts();
}

void loop()
{
  
}

ISR (TIMER1_OVF_vect)
{
  TCNT1 = timer1_counter;
  count_ISR -= 1;
  if(count_ISR < 1)
  {
    digitalWrite(LED_PIN_0, toggle);
  }
  else if(count_ISR == 5)
  {
    digitalWrite(LED_PIN_0, HIGH);
    count_ISR += 3;
  }
  else if(count_ISR ==7)
  {
    digitalWrite(LED_PIN_0, LOW);
  }
  toggle = !toggle;
}

void ISR_Callback()
{
  count++;
  if(count%3 == 0)
  {
    timer1_counter = 31250;
    count_ISR = 1;
  }
  else if(count%3 == 1)
  {
    timer1_counter = 0;
    count_ISR = 1;
  }
  else if(count%3 == 2)
  {
    timer1_counter = 16125;
    count_ISR = 6;
  }
}
