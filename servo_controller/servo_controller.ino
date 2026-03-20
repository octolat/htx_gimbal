#include <Servo.h>


const int servo_num = 2;
const String servo_names[servo_num] = {"pan", "tilt"};
const int servo_pins[servo_num] = {D2, D5}; // must be pwm pins
Servo servos[2];

const int servo_limits_sent[2] = {520,2525}; // 350, 2600 are true max values beyond 180
const int servo_limits_deg[2] = {-90, 90};



const char terminate_char = '\n';
const char seperate_char = '_';
bool debug = true;




bool isNumeric(String test);
void holdyourhorses(String errormsg);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  for (int i = 0; i < servo_num; i++) {
    servos[i].attach(servo_pins[i], servo_limits_sent[0], servo_limits_sent[1]); // pulse width numbers from raw dog testing
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    String instruc = Serial.readStringUntil(terminate_char);

    //skip if a seperator doesnt exist
    if (instruc.indexOf(seperate_char) == -1) {
      holdyourhorses("seperator doesnt exist");
      return;
    }

    bool seperated = false;
    String cmd;
    String value;
    for (int i = 0; i < instruc.length(); i++) {
      char ch = instruc[i];
      if (ch == seperate_char) seperated = true;
      else if (!seperated) cmd += ch;
      else value += ch;
    }

    // check it it is editing settings
    if (cmd == "debug") {
      if (value == "true") {
        debug = true;
        Serial.println("debug setting change successful");
      }
      else if (value == "false") debug = false;
      else holdyourhorses("command debug came with invalid value: "+value);
      return;
    }

    //find which servo
    int servo_select = -1;
    for (int i = 0; i < servo_num; i++) {
      if (cmd == servo_names[i]) {
        servo_select = i;
        break;
      }
    }

    // if not in servoname list skip
    if (servo_select == -1) {
      holdyourhorses("servo name("+cmd+") not in name list");
      return;
    }

    //convert degrees to int
    if (!isNumeric(value)) {
      holdyourhorses("degrees ("+value+") not made of integers");
      return;
    }

    //map it
    int servo_degrees = map(value.toInt(), servo_limits_deg[0], servo_limits_deg[1], servo_limits_sent[0], servo_limits_sent[1]);

    //send it
    servos[servo_select].write(servo_degrees);
    if (debug) Serial.println("sending servo "+String(servo_select)+" the following millis sig: "+servo_degrees);


    


  }
  else {
    delay(10);
  }
}

bool isNumeric(String test){
  for (int i = 0; i < test.length(); i++) {
    if (!isDigit(test[i]) and test[i] != '-') return false;
  }
  return true;
}

void holdyourhorses(String errormsg) {
  if (debug) {
    Serial.print("ERROR: ");
    Serial.println(errormsg);
  }
}
