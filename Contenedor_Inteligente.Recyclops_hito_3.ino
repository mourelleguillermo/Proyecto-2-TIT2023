#include <Wire.h>
#include "Adafruit_TCS34725.h" //Librería de Sensor de Color
#include <MultiStepper.h>     //Librería de Motor PasoAPaso
#include <Servo.h>            //Librería de Servo Motor

#include <Stepper.h>}
Servo servom1;          //declaramos el nombre del Servo Motor

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
int stepsrevolution = 2048;         // numero de pasos para dar una vuelta
int velocidadMotor = 12;            // variable para la velocidad del motor
Stepper motorcito (stepsrevolution, 8,10,9,11);     // Pines donde esta conectado el motor y nombre del motor
int esperar = 1000;

void setup() {
  Serial.begin(9600);

  motorcito.setSpeed(velocidadMotor);    //Le damos la velocidad del motor
  servom1.attach(7);  // Pin donde esta conectado el servo. (Pin digital 7)

  if (tcs.begin()) {
    Serial.println("Sensor encontrado");  // Avisa que se encuntra el sensor
  } else {
    Serial.println("No se encontró el sensor TCS34725, verifica las conexiones");   // Avisa que no se encontro el sensor.
    while (1);
  }
}

void loop() {
  
  servom1.write(0);     //Pone el servo motor en posición 0 grados
  delay (10);           
  uint16_t r, g, b, c, colorTemp, lux; //variables para almacenar los valores de los componentes de color. temperatura de color y luminosidad

  tcs.getRawData(&r, &g, &b, &c);         // Se obtienen los datos del sensor de color utilizando el método getRawData()  
  colorTemp = tcs.calculateColorTemperature(r, g, b);   // Se calcula la temperatura de color con el método tcs.calculateColorTemperature  del objeto de Adafruit_TCS34725
  lux = tcs.calculateLux(r, g, b);      //Se calcula a luminosidad con el método calculateLux() del objeto de Adafruit_TCS34725
  
  if (r > g && g > b) {   // Se averigua qué color es con un IF
    Serial.println("AMARILLO");     //Se imprime en el Monitor Serial el color que detecto.
    motorcito.step(stepsrevolution *0.25);    //El motor gira la tapa 1/4 de vuelta
    delay (500);        // Se espera medio segundo
    servom1.write(90);   // Gira el servo a 90 grados. La tapa de abajo se mueve y deja caer el recipiente en el contenedor
    delay(1000);        // Espera 1 segundo
    servom1.write(0);    // Gira el servo a 0 grados. La tapa vuelve a la posición de piso del cajón.
    delay(1000);
    motorcito.step(-(stepsrevolution * 0.25)); // El motor vuelve a su posición inicial. La tapa vuelve a posicionarse en frente al usuario
  delay (esperar);
  } 
  else if (g > r && g > b) {
    Serial.println("VERDE");
    motorcito.step(stepsrevolution * 0.50);
    servom1.write(90);   
    delay(1000);        
    servom1.write(0);    
    delay(1000);
    motorcito.step(-(stepsrevolution * 0.50));
  delay (esperar);
  } 
  else if (b > r && b > g) {
    Serial.println("AZUL");
    motorcito.step(stepsrevolution *0.75);
    servom1.write(90);   
    delay(1000);        
    servom1.write(0);    
    delay(1000);
    motorcito.step(-(stepsrevolution * 0.75));
  delay (esperar);
  }
   else if (r > g && r > b){
    Serial.println("ROJO");
    delay(1000);
    servom1.write(90);   
    delay(1000);        
    servom1.write(0);    
    delay(1000);
  }

  delay(5000); // Se espera 5 segundos para volver a repetir el loop. 
}