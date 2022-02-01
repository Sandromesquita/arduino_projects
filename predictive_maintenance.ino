#define pin_sensor 2
unsigned long current_time;
int pulses = 0;

void setup() {
  Serial.begin(9600);
  pinMode(pin_sensor, INPUT);
  current_time = millis();
}

void loop() {
  bool vibration_sensor = digitalRead(pin_sensor);
  int frequency_time = millis() - current_time;
  
  if (vibration_sensor) pulses++;
  
  if (frequency_time > 1000){
    float vibration_period = 1/pulses;
    float vibration_frequency = 1/vibration_period;
    
    if (vibration_frequency>100) {
      Serial.println("Engine with problem!");
      //Aqui voce pode ligar um led vermelho ou enviar uma mensagem via bluetooth
    }
    else Serial.println("Engine Ok!");
    
    pulses = 0;
    current_time = millis();
  }  
  //Serial.println(vibration_sensor);
}
