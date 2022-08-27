int LED = 10;//variavel que armazena a porta digital de saida

void setup()
{
    pinMode(LED, OUTPUT);//definindo a porta 13 com saida
}
void loop() 
{
    digitalWrite(LED, HIGH);//porta esta fornecendo dados altos(ligado)
    delay(2000);//inserindo pausa de 2 seg
    digitalWrite(LED, LOW);//porta esta fornecendo dados baixo(desligado)
    delay(2000);//inserindo pausa de 2 seg
}