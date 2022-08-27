void setup()
{
  pinMode(13, OUTPUT);//definindo a porta 13 com saida
}
void loop() 
{
  digitalWrite(13, HIGH);//porta esta fornecendo dados altos(ligado)
  delay(2000);//inserindo pausa de 2 seg
  digitalWrite(13, LOW);//porta esta fornecendo dados baixo(desligado)
  delay(2000);//inserindo pausa de 2 seg
}