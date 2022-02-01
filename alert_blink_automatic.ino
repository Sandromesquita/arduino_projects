//*********BLINKERS***********
#define left_blink 3
#define right_blink 4
#define btn_alert_blink 12
#define btn_left_blink 8
#define btn_right_blink 7

//*********HEADLIGHT**********
#define low_beam 6
#define high_beam 13

#define taillight 5
#define horn 9

//*********ENGINES************
#define positive_right_engine 14
#define negative_right_engine 15
#define right_engine_speed 10
#define positive_left_engine 16
#define negative_left_engine 17
#define left_engine_speed 11

//******AUXILIARY VARIABLES***
bool status_alert_blink = 0, status_left_blink= 0, status_right_blink= 0;
unsigned long time_actual_left = 0, time_actual_right = 0, time_actual = 0,
              turn_on_off_left = 0, turn_on_off_right = 0, turn_on_off = 0;
void setup() {
  Serial.begin(9600);

  for (byte pin = 2; pin < 18; pin++) {
    pinMode(pin, OUTPUT); //Declare all pins as OUTPUT
    /*Turn on/off the buzzer to signal startup*/
    tone(horn, 3000);
    delay(250);
    noTone(horn);
    delay(250);
  }

  pinMode(btn_alert_blink, INPUT_PULLUP); //Change pin 12 to INPUT
  pinMode(btn_left_blink, INPUT_PULLUP);  //Change pin 08 to INPUT
  pinMode(btn_right_blink, INPUT_PULLUP); //Change pin 07 to INPUT

  /*Long sound to signal that initialization is complete*/
  tone(horn, 2000);
  delay(1500);
  noTone(horn);
}

void loop() {
  bool status_btn_alert_blink = digitalRead(btn_alert_blink);
  bool status_btn_left_blink = digitalRead(btn_left_blink);
  bool status_btn_right_blink = digitalRead(btn_right_blink);
  
  if (!status_btn_alert_blink) {
    status_alert_blink = !status_alert_blink;
    delay(300);
  }
  else if (!status_btn_left_blink) {
    status_left_blink = !status_left_blink;
    status_right_blink = 0;
    delay(300);
  }
  else if (!status_btn_right_blink) {
    status_right_blink = !status_right_blink;
    status_left_blink = 0;
    delay(300);
  }
  
  blinks(status_left_blink, status_right_blink, status_alert_blink);
}

void blinks(bool status_left_blink, bool status_right_blink, bool status_alert_blink) {
  if (status_left_blink) {
    if (status_alert_blink) {
      int time_blink_left = millis() - time_actual_left;
      if (time_blink_left > 200) {
        turn_on_off_left = !turn_on_off_left;
        digitalWrite(left_blink, turn_on_off_left);
        time_actual_left = millis();
      }
      int time_blink_right = millis() - time_actual_right;
      if (time_blink_right > 600) {
        turn_on_off_right = !turn_on_off_right;
        digitalWrite(right_blink, turn_on_off_right);
        time_actual_right = millis();
      }
    }
    else {
      int time_blink = millis() - time_actual;
      if (time_blink > 600) {
        turn_on_off = !turn_on_off;
        digitalWrite(left_blink, turn_on_off);
        digitalWrite(right_blink, LOW);
        time_actual = millis();
      }
    }
  }
  else if (status_right_blink) {
    if (status_alert_blink) {
      int time_blink_right = millis() - time_actual_right;
      if (time_blink_right > 200) {
        turn_on_off_right = !turn_on_off_right;
        digitalWrite(right_blink, turn_on_off_right);
        time_actual_right = millis();
      }
      int time_blink_left = millis() - time_actual_left;
      if (time_blink_left > 600) {
        turn_on_off_left = !turn_on_off_left;
        digitalWrite(left_blink, turn_on_off_left);
        time_actual_left = millis();
      }
    }
    else {
      int time_blink = millis() - time_actual;
      if (time_blink > 600) {
        turn_on_off = !turn_on_off;
        digitalWrite(left_blink, LOW);
        digitalWrite(right_blink, turn_on_off);
        time_actual = millis();
      }
    }
  }
  else if (status_alert_blink) {
    int time_blink = millis() - time_actual;
    if (time_blink > 600) {
      turn_on_off = !turn_on_off;
      digitalWrite(left_blink, turn_on_off);
      digitalWrite(right_blink, turn_on_off);
      time_actual = millis();
    }
  }
  else {
    digitalWrite(left_blink, LOW);
    digitalWrite(right_blink, LOW);
  }
}
