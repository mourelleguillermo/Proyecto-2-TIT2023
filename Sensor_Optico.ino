const int LED = 13;
const int SENSOR = 2;
int valor;

void setup(){
  pinMode(LED, OUTPUT);
  pinMode(SENSOR, INPUT);  
}

void loop(){
  valor = digitalRead(SENSOR);
  digitalWrite(LED, !valor);

  delay(500);
}
