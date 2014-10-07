#define ON 1
#define OFF 0

int button = 0;
int old_button = 0;
int state = OFF;
int pinButton = 10;

void setup() {  
  pinMode(pinButton, INPUT);
}

void accendiLed(int porta) {
  pinMode(porta, OUTPUT);
  digitalWrite(porta, HIGH);  
}

void spegniLed(int porta) {
  pinMode(porta, OUTPUT);
  digitalWrite(porta, LOW);
}

void parseButton(){
  button = digitalRead(pinButton);
  if (button == HIGH && old_button == LOW) {
    state = 1 - state;
    delay(10);
  }
  old_button = button;
}

void spegniAccendi(int porta, int ms) {
  accendiLed(porta);
  delay(ms);
  spegniLed(porta);
  delay(ms);
}

void loop() {
  parseButton();
  if (state == OFF) {
      //spegniAccendi(12, 50);
      spegniLed(11);
      accendiLed(12);
  } else {
      //spegniAccendi(11, 50);
      spegniLed(12);
      accendiLed(11);
  }
}

