#define LED_PIN 12
#define PERIOD 10

String inp="";
int string_length;

/*
 test message : 
 Elon Reeve Musk FRS is an entrepreneur and business magnate. 
 He is the founder, CEO, and Chief Engineer at SpaceX; early-stage investor, 
 CEO, and Product Architect of Tesla.

 characters : 174
 */

void setup() 
{
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.setTimeout(10);
  Serial.println("Hello From Transmitter 2!");
  digitalWrite(LED_PIN, LOW);
}

void loop() 
{
  inp="";
  if(Serial.available()){
    inp = Serial.readString();
    sendMessage(inp);

    Serial.println(inp);
    Serial.print("Done");
    Serial.println();
    digitalWrite(LED_PIN, LOW);
  }
}

void sendMessage(String string){
  int string_length = string.length();
  Serial.println("Initiated");
  digitalWrite(LED_PIN, HIGH);
  delay(PERIOD);
  for(int i = 0; i < string_length; i ++)
  {
    send_byte(string[i]);
    if( (i%3==0 and i!=0) or i==2)   wait_time(); 
  }
  digitalWrite(LED_PIN, LOW);
}

void wait_time(){
  digitalWrite(LED_PIN, LOW);
  delay(PERIOD*10);
  digitalWrite(LED_PIN, HIGH);
  delay(PERIOD);
  return;
}

void send_byte(char my_byte)
{
  String bits = "";
  for (int i = 7; i >= 0; --i) {
        int state = (my_byte & (1 << i))? 1 : 0;
        digitalWrite(LED_PIN, state);
        Serial.print(state);
        delay(PERIOD);
  }
  Serial.print(" -> ");
  Serial.print(my_byte);
  Serial.println();
        
  return;

  digitalWrite(LED_PIN, HIGH);
  delay(PERIOD);
}
