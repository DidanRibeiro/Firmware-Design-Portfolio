/* Comunicação Serial para Detector de Radiação junto ao Arduino
   Com adaptações por: Didan Junqueira Ribeiro
*/


#include <SPI.h>
#define LOG_PERIOD 15000  // Período de registro em milissegundos, valor recomendado 15000-60000.
#define MAX_PERIOD 60000  // Período máximo de registro 

unsigned long counts;     // variável para eventos do tubo GM
unsigned long cpm;        // variável para CPM
unsigned int multiplier;  // variável para cálculo CPM 
unsigned long previousMillis;  // variável para medição de tempo



void tube_impulse(){       // subprocedimento para capturar eventos do Geiger
  counts++;
}

void setup(){             // subprocedimento de configuração
  counts = 0;
  cpm = 0;
  multiplier = MAX_PERIOD / LOG_PERIOD;      // calculando multiplicador, depende do seu período de registro
  Serial.begin(9600);
  attachInterrupt(0, tube_impulse, FALLING); // define interrupções externas
  
}

void loop(){                                 
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > LOG_PERIOD){
    previousMillis = currentMillis;
    cpm = counts * multiplier;
    
    Serial.println(cpm);
    counts = 0;
  }
  
}

