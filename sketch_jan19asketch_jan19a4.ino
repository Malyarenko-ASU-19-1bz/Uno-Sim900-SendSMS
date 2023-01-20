// подключение библиотеки SoftwareSerial 
#include <SoftwareSerial.h> 
// номер телефона для отправки sms 
#define PHONE "+79526576604" 
// Выводы для SoftwareSerial 
SoftwareSerial Sim900Serial(7, 8);
int lm335=A0; // подключение датчика к аналоговому входу АО
int relayPin=10; // подключение чипа Arduino к выводу D10
void setup() 
{
  Serial.begin(9600); 
}
// замер температуры
double GetTemp()
{
  double val1 = analogRead(lm335); 
  double voltage1 = val1*5.0/1024; // перевод в значение в вольтах 
  double temp = voltage1*100 - 273.15; // перевод в градусы Цельсия 
  return temp;
}
int main()
{
  int tmr=0; //текущее значение таймера
  int iter=0; //итератор таймера
  int min=18; //нижний предел температуры
  int max=24; //верхний предел температуры
  double t; // текущая температура
  pinMode(relayPin, OUTPUT); // настроить вывод D10, как выход (OUTPUT) 
  Sim900Serial(19200); // активация последовательного соединения 
  while(true)
  {
    t=GetTemp();
    if (t<=min)
    {
      digitalWrite(relayPin, HIGH); // включить реле
      while(t<max)
      {
        t=GetTemp();
        iter++; // отсчет времени в секундах пока реле включено
        delay(1000);        
      }
      digitalWrite(relayPin, LOW); // выключить реле 
      tmr=iter; // конечное значение итератора присваивается к переменной таймера
      iter=0;
    }
    if (tmr!=0)
    {
      // АТ-команда установки text mode 
      Sim900Serial.print("AT+CMGF=l\r"); 
      delay(100); 
      // номер телефона получателя 
      Sim900Serial.println("AT + CMGS = V") ; 
      Sim900Serial.println(PHONE) ; 
      Sim900Serial.println("\""); 
      delay(100); 
      Sim900Serial.println(tmr); 
      delay(100); 
      // ASCII код ctrl+z - окончание передачи 
      Sim900Serial.println((char)26); 
      delay(100); 
      Sim900Serial.println(); 
    }
    tmr=0; 
    delay(100);
  }
  return 0;
}
