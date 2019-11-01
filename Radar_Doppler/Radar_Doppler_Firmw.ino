/* Autor: Didan Junqueira Ribeiro - Projeto Radar Doppler
 * Código adaptador e inspirado da biblioteca FreqMeasure que pode ser acessado em:
 * http://www.pjrc.com/teensy/td_libs_FreqMeasure.html
 */
 
#include <FreqMeasure.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(57600);
  lcd.begin(16, 2);
  lcd.print("Freq:");
  lcd.setCursor(10,0);
  lcd.print("Veloc:");
  FreqMeasure.begin();
}

double soma=0;
int conta=0;

void loop() {
  if (FreqMeasure.available()) {
    // Media das 30 leituras juntas pra frequencia
    soma = soma + FreqMeasure.read();
    conta = conta + 1;
    if (conta > 30) {
      float freq = FreqMeasure.countToFrequency(soma / conta);
      float veloc = freq / 19.49; //conversão da frequencia para Km/h
      
      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print(freq);
      lcd.print("Hz");
      //lcd.print("       ");
      lcd.setCursor(8,1);
      lcd.print(veloc);
      lcd.print("km/h");
      soma = 0;
      conta = 0;
    }
  }
}

