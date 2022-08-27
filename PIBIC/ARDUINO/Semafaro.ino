//artibuindo portas as variaveis
#define led_vermelho 8
#define led_amarelo 9
#define led_verde 10

void setup() 
{
  //definido portas do tipo de saida
  pinMode(led_vermelho, OUTPUT);  
  pinMode(led_amarelo, OUTPUT);
  pinMode(led_verde, OUTPUT);
}
//funçoes para acender os respectivos leds com parametro da duracao em segundos
void vermelho(int tmp)
{
  digitalWrite(led_vermelho, HIGH);
  digitalWrite(led_amarelo, LOW);
  digitalWrite(led_verde,LOW);
  delay(tmp*1000);  
}
void verde(int tmp)
{
  digitalWrite(led_vermelho, LOW);
  digitalWrite(led_amarelo, LOW);
  digitalWrite(led_verde, HIGH);
  delay(tmp*1000);      
}
void amarelo(int tmp)
{
  digitalWrite(led_vermelho, LOW);
  digitalWrite(led_amarelo, HIGH);
  digitalWrite(led_verde, LOW);  
  delay(tmp*1000);  
}

void loop()
{
  vermelho(7);
  verde(9);
  amarelo(2);
}
