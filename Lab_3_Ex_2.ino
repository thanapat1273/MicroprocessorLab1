#define DATA_PIN 9
#define CLOCK_PIN 10
#define LATCH_PIN 11
#define BUTTONA A0
#define BUTTONB A1
int b;
int num;

int map7seg[10] = {
  0x3f, //0
  0x06, //1
  0x5b, //2
  0x4f, //3
  0x66, //4
  0x6d, //5
  0x7d, //6
  0x07, //7
  0x7f, //8
  0x6f, //9
  
};

void setLed( uint8_t _state ){
  digitalWrite(LATCH_PIN,LOW);
  for(int i=0;i<8;i++){
    digitalWrite(DATA_PIN,(_state>>(7-i))&0x01);
    digitalWrite(CLOCK_PIN,HIGH);
    digitalWrite(CLOCK_PIN,LOW);
  }
  digitalWrite(LATCH_PIN,HIGH);
}
void setup()
{
  Serial.begin(9600);
  pinMode(DATA_PIN,OUTPUT);
  pinMode(CLOCK_PIN,OUTPUT);
  pinMode(LATCH_PIN,OUTPUT);  
  pinMode(BUTTONA,INPUT_PULLUP);
  pinMode(BUTTONB,INPUT_PULLUP);
  setLed(map7seg[0]);
}

void loop(){
  if (Serial.available() > 0) {
      char inByte = Serial.read();
    if(('0' <= inByte)&&(inByte <='9')){
      num = inByte - '0';
    }
    Serial.println(num);
    setLed(map7seg[num]);
 }
}
