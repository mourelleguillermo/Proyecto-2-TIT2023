#define trigPin 12
#define echoPin 11
long duracion, distancia;

void setup() {
  Serial.begin(9600);
  pinMode(echoPin,INPUT);
  pinMode(trigPin,OUTPUT);
  pinMode(13,1);
}
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);


  duracion = pulseIn(echoPin, HIGH);
  distancia = (duracion/2) / 29;

if (distancia >= 500 || distancia <= 0){
  Serial.println("----");
}
else {
  Serial.print(distancia);
  Serial.println("cm");
}
}





