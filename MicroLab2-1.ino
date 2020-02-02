int clk_pin = 13;
int latch_pin = 10;
int data_pin = 11;
bool toggle;
int count = 0;

void setLED(uint16_t state)
{
  digitalWrite(latch_pin,LOW);
  for(int i=0; i<16; i++)
  {
    digitalWrite(data_pin, (state>>(15-i)) & 0x0001);
    digitalWrite(clk_pin,HIGH);
    digitalWrite(clk_pin,LOW);
  }
  digitalWrite(latch_pin,HIGH);
}

void setup()
{
  pinMode(clk_pin,OUTPUT);
  pinMode(latch_pin,OUTPUT);
  pinMode(data_pin,OUTPUT);
}

void loop()
{
  setLED(0b00000000001 << count);
  count++;
  delay(1000);
}
