
#include <Bridge.h>
#include <Process.h>
void setup() {
  // put your setup code here, to run once:
  Bridge.begin();
  Serial.begin(9600);
}

long steps = 0;
char c = 0;
char message[10];
Process proc;
void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    steps = 0;
    while(Serial.available()) {
      c = Serial.read();
      if(c == '#'){
        Serial.println(steps);
        Bridge.put("ZIP", String(steps));
        
        proc.runShellCommand("python /root/aqi.py > /root/test.log");
        while (proc.running());
        Serial.println("done");
        break;
      }
      steps = (steps * 10) + (c - '0');
    }
    
  }
  if(Bridge.get("LEVEL", message, 2)){
    if(message[0] == 'L'){
      Serial.println(message);
      memset(message, 0, sizeof(message));
    }
    
    proc.runShellCommand("python /root/delete_values.py");
    while (proc.running());
    
  }

}
