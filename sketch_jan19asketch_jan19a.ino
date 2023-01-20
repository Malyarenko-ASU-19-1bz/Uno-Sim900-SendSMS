int lm335=A0; // подключение датчика к аналоговому входу АО
int tmr=0; //текущее значение таймера
int iter=0; //итератор таймера
int min=18; //нижний предел температуры
int max=24; //верхний предел температуры
void setup() 
{
  Serial.begin(9600); 
}
int main()
{
  while(true)
  {
  double val1 = analogRead(lm335); // чтение 
  double voltage1 = val1*5.0/1024; // перевод в значение в вольтах 
  double temp = voltage1*100 - 273.15; // перевод в градусы Цельсия 
  delay(1000);
  }
  return 0;
}
