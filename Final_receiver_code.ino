#include<math.h>
#define LED_PIN 13
#define LDR_PIN A0
#define THRESHOLD 500
#define PERIOD 10

bool previous_state;
bool current_state;

void setup() 
{
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("Hello from Receiver 2!" );
  digitalWrite(LED_PIN, LOW);
}

unsigned int st=millis();
String message = "";
int count=0;
unsigned long startt;

void loop() 
{
  current_state = get_ldr();
  if(current_state && !previous_state)
  {
    startt=millis();
    digitalWrite(LED_PIN, HIGH);
    delay(PERIOD*1.5);
    char prev_char='a';
    while(1){
      char ch = get_byte();
      if(ch=='\n'){
          //message received
          Serial.println();
          delay(200);
          Serial.println("message : "+message);
          int bitss = message.length()*8;
          Serial.print("Total bits transferred : ");
          Serial.println(bitss);
          //unsigned time_taken = millis()-startt;/
          int time_taken = PERIOD*bitss + (bitss/3)*PERIOD + PERIOD*2;
          
          //              (for every bit)    (hold time)      (for start bit and at bit no 2)
          Serial.print("Total time taken       : ");
          Serial.print(time_taken);
          Serial.println("ms");
          float time_in_sec = time_taken*0.001;
          float speedd =bitss/time_in_sec;
          Serial.print("Speed                  : ");
          Serial.print(speedd);
          Serial.println(" bits/sec");
          message="";
          digitalWrite(LED_PIN, LOW);
          break;
      }
      else if(ch==NULL){
        break;
      }
      else message += ch;
    }
  }
  previous_state = current_state;
}

bool get_ldr()
{
  int voltage = analogRead(LDR_PIN);
  return voltage > THRESHOLD ? false : true;
}

char get_byte()
{
  int res=0;
  int pov=128;
  for(int i = 0; i < 8; i++)
  {
   bool volt = analogRead(LDR_PIN)> THRESHOLD ? false : true;
   Serial.print(volt);
   res += volt*pov;
   pov/=2;
   delay(PERIOD);
  }
  char character = res;
  Serial.print(" -> ");
  Serial.print(character);
  Serial.println();
  return res;
}
