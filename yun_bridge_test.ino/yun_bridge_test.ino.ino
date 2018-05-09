
#include <Bridge.h>
#include <Process.h>
#include <Stepper.h>
#include <Keypad.h>

#define STEPS 600


long steps = 0;
char c = 0;
char message[10];
Process proc;

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {5, 6, 7, 8}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {2, 3, 4}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  // put your setup code here, to run once:
  Bridge.begin();
  Serial.begin(9600);

  stepper.setSpeed(60);
}


void loop() {
  // put your main code here, to run repeatedly:
  char key = keypad.getKey();
  if (key) {
    steps = 0;
    while (key != '#') {
      switch (key) {

        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
          steps = (steps * 10) + (key - '0');
          break;
        case '#':
        default:
          break;
      }
      key = keypad.getKey();
    }
    if (key == '#') {
      Serial.println(steps);
      Bridge.put("ZIP", String(steps));
      stepper.step(-STEPS);
      proc.runShellCommand("python /root/aqi.py > /root/test.log");
      while (proc.running());
      Serial.println("done");
    }
  }
  if (Bridge.get("LEVEL", message, 2)) {
    if (message[0] == 'L') {
      Serial.println(message);
      Serial.println(90 + ((message[1] - '0') * 60));
      stepper.step(90 + ((message[1] - '0') * 60));
      memset(message, 0, sizeof(message));
    }

    proc.runShellCommand("python /root/delete_values.py");
    while (proc.running());

  }

}
