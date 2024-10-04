/*
Sillion Technical Test
SillionTest V1.0
Author: Kaik Paixão Oliveira

*/

#include <Wire.h>

#define BUTTON 4   // Define a porta D4 como B1, ligada ao botão de acionamento pelo esquemático da placa
#define MOTOR_PIN 5    // Define a porta D5 como a saída que ativará o motor
#define MOTOR_TIME 10000  // Define o tempo que o motor ficará ligado (10 segundos)

/* 
Nota: O deboounce pode ser descrito como um processo de filtragem de sinais
Como a leitura do botão pode estar suscetível a rúidos, fazendo que se possa ter uma leitura errônea do mesmo,
foi colocada uma lógica de debounce. A mesma consiste em verificar se o estado do botão permaneceu o mesmo por um período de tempo
 */
 
int LastButtonState = 0; // Variável que irá armazenar o último estado do botão
unsigned long DebounceDelay = 50; // Define o tempo de debounce como 50 milisegundos
unsigned long LastDebounceTime = 0; // Variável para o debounce


void setup() {
  // put your setup code here, to run once:
  Wire.begin(21, 22); // Define as portas I2C do ESP32: SDA = D21, SCL = D22
  Serial.begin(115200); // Configura o monitor serial


  pinMode(BUTTON, INPUT_PULLUP);  // Define a porta selecionada para o botão como entrada e ativa o pull-up interno do ESP32
  pinMode(MOTOR_PIN, OUTPUT);     // Define a porta selecionada para o acionamento do motor como saída
  digitalWrite(MOTOR_PIN, LOW);   // Configura o valor incial do motor como 0, para que não comece acionado


}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (digitalRead(BUTTON)!= LastButtonState ){ // Verficia se o estado atual do botão é diferente do último estado lido
  LastDebounceTime = millis(); // A função millis registra o tempo que se passou desde o início do código. Nesse trecho, a varíavel LastDebounceTime assume o valor do momento em que o botão foi pressionado
  }

    if ((millis ()- LastDebounceTime) > DebounceDelay){ //Subtrai o tempo atual do código pelo tempo incial do Debounce, para verificar se é maior que o tempo definido
    
    if(digitalRead(BUTTON)== LOW){ // Verifica se o estado da porta designada para o botão é 0 (ativada)
      
    Serial.println ("O botão foi pressionado");
    digitalWrite (MOTOR_PIN, HIGH); // Ativa o motor
    Serial.println ("Motor acionado");
    delay (MOTOR_TIME);
    digitalWrite(MOTOR_PIN, LOW); // Desliga o motor
    Serial.println ("Motor Desligado"); 
    }
    }

  LastButtonState = digitalRead(BUTTON);
    
}
