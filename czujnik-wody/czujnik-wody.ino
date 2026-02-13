#include <Wire.h> //  załączenie wymaganych bibliotek
#include<LiquidCrystal_I2C.h>
#define czerwona 4  //  nazwanie komponentów projektu
#define zolta 5
#define zielona 6
#define niebieska 7

#define buzzer 8  //  brzęczyk
int czujnik = A0;   //  pin analogowy A0 – podłączony czujnik poziomu wody
LiquidCrystal_I2C lcd(0x27, 16, 2);   //  0x27 – adres I2C, 16 – liczba kolumn, 2 – liczba wierszy

void setup(){
  Serial.begin(9600);   //  uruchomienie monitora portu szeregowego
  lcd.init();   // inicjalizacja LCD
  lcd.backlight();  //  włączenie LCD
  pinMode(czerwona,OUTPUT);   //  określenie pinów jako wyjścia
  pinMode(zolta,OUTPUT);
  pinMode(zielona,OUTPUT);
  pinMode(niebieska,OUTPUT);
  pinMode(buzzer,OUTPUT);

}
void loop(){
  Serial.println(analogRead(czujnik));   // wyświetlenie odczytu z czujnika w porcie szeregowym
  int wartosc = analogRead(czujnik);  //  odczyt wartości analogowej z czujnika 
  lcd.setCursor(0,0);   //  ustawienie kursora w pierwszym wierszu
  lcd.print("poziom wody");   //  wyświetlenie nagłówka
  lcd.setCursor(0,1); //  ustawienie kursora w drugim wierszu
  digitalWrite(niebieska,LOW);  //  wyłączenie wszytskich komponentow z wyjątkiem czujnika
  digitalWrite(zielona,LOW);
  digitalWrite(zolta,LOW);
  digitalWrite(czerwona,LOW);
  digitalWrite(buzzer,LOW);
  if(wartosc<=50){  //  jeśli odczyt mniejszy niż 50 - brak wody
    digitalWrite(niebieska,HIGH);   //  załączenie niebieskiej diody
     lcd.setCursor(0,1);
     lcd.print("brak            ");   //  wyświetlenie komunikatu
     }
     else if(wartosc>50 && wartosc<=660){   //  niski poziom
     
     digitalWrite(zielona,HIGH);
      lcd.setCursor(0,1);
     lcd.print("maly              ");

  }else if(wartosc>660 && wartosc<698){   //  średni poziom
    digitalWrite(zolta,HIGH);
     lcd.setCursor(0,1);
     lcd.print("sredni            ");

  }else if(wartosc>=698)
  {
    digitalWrite(czerwona,HIGH);  //  wysoki poziom
     lcd.setCursor(0,1);
     lcd.print("wysoki           ");
     digitalWrite(buzzer,HIGH);   //  załączanie i wyłączanie brzęczyka z przerwami ma na celu stworzyć przerywany dźwięk alarmu
     delay(200);
     digitalWrite(buzzer,LOW);
     delay(200);
  }
  delay(250);  // opóźnienia między pomiarami czujnika
}
