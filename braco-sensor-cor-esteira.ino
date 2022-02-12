#include <Servo.h>

Servo base, avanco, elevacao, garra;

//Pinos de conexao do modulo
const int s0 = 8;
const int s1 = 9;
const int s2 = 12;
const int s3 = 11;
const int out = 10;

//Variaveis cores
int vermelho = 0;
int verde = 0;
int azul = 0;

void setup() {
  Serial.begin(9600);
  //Configuracoes sensor de cor
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);

  digitalWrite(s0, HIGH);
  digitalWrite(s1, LOW);

  //Configurações servos do braço
  base.attach(A0);
  avanco.attach(A1);
  elevacao.attach(A2);
  garra.attach(A3);

  posInicial();

  pinMode(A4, OUTPUT); //Rele do motor
  digitalWrite(A4, HIGH); //Desliga a esteira
}

void loop() {
  digitalWrite(A4, LOW); //Liga a esteira
  //Detecta a cor
  color();
  imprimiCor();
  //Verifica se a cor vermelha foi detectada
  if (vermelho < azul && vermelho < verde && vermelho < 100)
  {
    pegarPeca();
    base.write(0);
    soltarPeca();
    posInicial();
  }

  //Verifica se a cor azul foi detectada
  else if (azul < vermelho && azul < verde && azul < 1000)
  {
    pegarPeca();
    base.write(180);
    soltarPeca();
    posInicial();
  }

  //Verifica se a cor verde foi detectada
  else if (verde < vermelho && verde < azul)
  {
    //deixa passar
  }

  //Delay para apagar os leds e reiniciar o processo
  delay(50);
}

void color()
{
  //Rotina que le o valor das cores
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  //count OUT, pRed, RED
  vermelho = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s3, HIGH);
  //count OUT, pBLUE, BLUE
  azul = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s2, HIGH);
  //count OUT, pGreen, GREEN
  verde = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
}

void imprimiCor() {
  //Mostra valores no serial monitor
  Serial.print("Vermelho :");
  Serial.print(vermelho, DEC);
  Serial.print(" Verde : ");
  Serial.print(verde, DEC);
  Serial.print(" Azul : ");
  Serial.print(azul, DEC);
  Serial.println();
}

void pegarPeca() {
  digitalWrite(A4, HIGH); //Desliga a esteira
  
  garra.write(70);    //Abre a garra
  delay(500);
  elevacao.write(120);//Abaixa o braço
  delay(500);
  avanco.write(70);   //Avanca o braço para a peça
  delay(500);
  garra.write(110);    //Fecha a garra
  delay(500);
  elevacao.write(60);//Levanta o braço
  delay(500);
  avanco.write(110);   //Recua o braço para a peça
  delay(500);
}

void soltarPeca() {
  digitalWrite(A4, HIGH); //Desliga a esteira

  avanco.write(30);   //Avanca o braço para a peça
  delay(500);
  elevacao.write(170);//Abaixa o braço
  delay(500);
  garra.write(70);    //Abre a garra
  delay(500);
}

void posInicial() {
  digitalWrite(A4, HIGH); //Desliga a esteira
  
  elevacao.write(90);
  delay(500);
  avanco.write(90);   
  delay(500);
  garra.write(90);    
  delay(500);
  base.write(90);
  delay(500);
}
