#include <Bridge.h>

void setup() {
  // put your setup code here, to run once:
  Bridge.begin();
  Serial.begin(9600);
}

long steps = 0;
char c = 0;
void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    steps = 0;
    while(Serial.available()) {
      c = Serial.read();
      if(c == '#'){
        break;
      }
      steps = (steps * 10) + (c - '0');
    }
    Serial.println(steps);
    Bridge.put("ZIP", String(steps));
  }

}
