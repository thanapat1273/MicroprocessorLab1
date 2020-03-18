#define LED_PIN_0 9
#define INT_PIN   3

int count;
int button = 0;

void setup()
{
  pinMode(LED_PIN_0, OUTPUT);
  pinMode(INT_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(INT_PIN),
                   ISR_Callback, FALLING);
  count = 0;
}

void loop()
{
  if(count == 0)
  {
    digitalWrite(LED_PIN_0, LOW);
  }
  else if((count%3) == 0)
  {
    digitalWrite(LED_PIN_0, HIGH);
    delay(1500);
    digitalWrite(LED_PIN_0, LOW);
    delay(1500);
  }
  else if((count%3) == 1)
  {
    digitalWrite(LED_PIN_0, HIGH);
    delay(500);
    digitalWrite(LED_PIN_0, LOW);
    delay(500);
  }
  else if((count%3) == 2)
  {
    digitalWrite(LED_PIN_0, HIGH);
    delay(1000);
    digitalWrite(LED_PIN_0, LOW);
    delay(1000);
  }
}

void ISR_Callback()
{
  count++;
}
