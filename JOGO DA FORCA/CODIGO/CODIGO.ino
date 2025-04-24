/*******************************************************************************
*
*  Jogo 1 - Jogo da Fora
*  Créditos: Laboratório de Garagem
*  Adaptções: Squids Arduino 
*
*                   http://squids.com.br/arduino
*
*******************************************************************************/
#include "notas.h" // Baixe e instale o header notas.h
const byte buzzer = 12; // Define o pino onde o buzzer será conectado
const int compasso = 1500; //Define o compasso da música
byte ledPin[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 13}; // cria um array para os pinos digitais dos LEDs (10 da barra + 1 led)
byte nleds = 11; // números de leds (barra + led) // se você utilizar somente leds, mude para 6

int erros=0, acertos, i, j;
String segredo= "SQUIDS ARDUINO"; //<-Altere nesta String a palavra secreta
const String dica= "Onde voce encontra os melhores PROJETOS sobre Arduino"; //<-Altere nesta linha a dica sobre a palavra utilizada
String tentativas = " -", test;
char inChar;

const int gameover[] = {   
NOTE_C5,NOTE_G4,NOTE_E4,NOTE_A4,NOTE_B4,NOTE_A4,NOTE_GS4,NOTE_AS4, NOTE_GS4, NOTE_E4,NOTE_D4,NOTE_E4
};

const int tempo_gameover[] = {   
4,4,4,8,8,8,8,8,8,   
12,12,4
};

boolean temletra=0;

void setup() {   

Serial.begin(9600);   

for (int x=0; x<nleds; x++) { // define todos os pinos dos LEDs como saída
    pinMode(ledPin[x], OUTPUT); 
    digitalWrite(ledPin[x], HIGH);
    }

  
delay(1000);     

segredo.toUpperCase();   
Serial.println();   
Serial.println(" Jogo da forca");   
Serial.println();   
Serial.print("Dica: ");   
Serial.println(dica);   
Serial.println();   

for (i = 0; i < segredo.length(); i++){     
if (segredo[i] == 0x20){       
test += " ";     
}     
else if(segredo[i] == 0x2D){       
test += "- ";     
}     
else{       
test += "_ ";     
}   
}   

for (i = 0; i < (segredo.length()*2); i++)
{     
Serial.print(test[i]);   
}   
Serial.println();   
Serial.println();
}

void loop() {   

while (Serial.available() > 0) {     
char caracter = Serial.read();     

if(isAlphaNumeric(caracter) || isDigit(caracter)) {       
caracter = toupper(caracter);       
for (j = 0; j < tentativas.length(); j++){         
if( tentativas[j] == (caracter) ){           
temletra = 1;         
}       
}       

if (temletra == 1)       
{         
Serial.println("Letra ja digitada");         
temletra = 0;       
}       

else       
{         
tentativas += caracter;                  

if(segredo.indexOf(caracter) <0 ){           
erros++;         
}         

acertos = 0;         

for (j = 0; j < tentativas.length(); j++){           
for (i = 0; i < segredo.length(); i++){             
if( segredo[i]== tentativas[j]){               
test[i*2]=  segredo[i];               
acertos++;             
}           
}         
}          

Serial.print("ERROS: ");         
Serial.println(erros);         
Serial.println();         

//###########################################################
        
// imprime letras na tela         
for ( i = 0; i < (segredo.length()*2); i++){           
Serial.print(test[i]);         
}         
Serial.println();         
Serial.println();       
}      
}     

else {       
Serial.println("Digite um caracter valido");       
Serial.println();     
}     

//Atualiza LEDs que indicam os erros
byte led_ind = erros;
byte leda = ((2 * led_ind)-1)-1;
byte ldeb = leda+1;
digitalWrite(1, LOW); 
digitalWrite(ledPin[leda], LOW);
digitalWrite(ledPin[ldeb], LOW); // elimine essa linha se estiver usando 6 leds

if (acertos == segredo.length()){       
Serial.println("Voce venceu!!!");       
while(1){ // looping infinito       
}     
}     

if (erros >=6){       
Serial.println("GAME OVER");       //Toca musica de GAME OVER       
for (int Nota = 0; Nota < 12; Nota++) {         
int tempo = compasso/tempo_gameover[Nota];         
tone(buzzer, gameover[Nota],tempo);         
delay(tempo*1.2);       
}       
while(1){       
}     
}   
}
}





    
