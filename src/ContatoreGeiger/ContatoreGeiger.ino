/*
 *  Marco La Barbera - 2019
 *  Rilevazione Contatore Geiger
 *  Bergamo Scienze 2019
 *
 *

*/

#include <Wire.h> //Libreria display
#include <LiquidCrystal_I2C.h> //Libreria display I2C

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  //indirizzo dell'LCD I2C

unsigned long int milli_time; //variabile conteggio tempo assoluto dall'accensione di arduino

int buzzerPin = 2; //buzzer inserito nel pin digitale 2
int cont = 0; //contatore di rilevamenti dall'accensione
float becq = 0; //frequenza becquerel (particelle per secondo)
int temp = 0; //variabile scarto tra una rilevazione all'altra

int contT3 = 0; //contatore numero coincidenze

void setup() {
  
 Serial.begin(9600); //inizializza porta seriale
 
 pinMode(8, INPUT); //entrata dato collegamento sensore Geiger T1
 pinMode(12, INPUT);//entrata dato collegamento sensore Geiger T2
 pinMode(10, INPUT); //entrata dato coincidenza COIN
 pinMode(buzzerPin, OUTPUT); //definizione di tipo digitale e OUTPUT del buzzer 

 Serial.println("CLEARDATA"); //This string is defined as a 
 Serial.println("LABEL, Computer Time , N, f,  Time, T1 , T2, T3, TOT3");  

 //////////////////////////////////////////////////////////////
 
  tone(buzzerPin, 660 ,100);  //Suono di corretta accensione di Arduino
  delay (150); //prolunga il suono di 0.15 sec

  lcd.begin(16,2); //inizializza display
  lcd.backlight(); //luce di contrasto display

}

void loop() {
  
  int ValoreRicevuto = digitalRead(8); //variabile stato T1
  int ValoreRicevuto2 = digitalRead(12); //variabile stato T2
  int ValoreRicevuto3 = digitalRead(10); //variabile stato COIN
  
  milli_time = millis(); //attribuisci alla variabile il tempo contato dall'accensione di arduino


  //becq = ((cont)*100000/((milli_time) - temp)); //decommenta se si vuole frequenza tra due successivi conteggi, è stata inserita una moltiplicazione per 100000 perchè a quanto pare arduino non riesce a calcolare numeri troppo piccoli
    becq = ((cont)*100000/(milli_time)); //frequenza dall'inizio della registrazione, è stata inserita una moltiplicazione per 100000 perchè a quanto pare arduino non riesce a calcolare numeri troppo piccoli

if((ValoreRicevuto!=0)||(ValoreRicevuto2!=0)||(ValoreRicevuto3!=0)) //caso in cui almeno uno dei sensori geiger abbia rilevato un segnale
{

  Serial.print("DATA, TIME,"); //codice per PLX-DAQ
  Serial.print(cont); //stampa rilevamenti totali fino ad ora
  Serial.print(",");
  Serial.print(becq); //stampa frequenza
  Serial.print(",");
//Serial.print(milli_time - temp); //decommenta per tempo tra due successivi conteggi
  Serial.print(milli_time); //tempo dall'inizio del conteggi
  Serial.print(",");
  Serial.print(ValoreRicevuto, DEC); //stampa stato T1
  Serial.print(",");
  Serial.print(ValoreRicevuto2, DEC); //stampa stato T2
  Serial.print(",");
  Serial.print(ValoreRicevuto3, DEC); //stampa stato T3
  Serial.print(",");
  Serial.println(contT3); //stampa totale coincidenze


  lcd.clear(); //cancella lo schermo
  lcd.setCursor(3,0); //posiziona cursore nella matrice 16x2 in posizione riga 0 e colonna 3
  lcd.print("Becquerel"); //quindi stampa il titolo
  lcd.setCursor(3,1); //posiziona cursore nella matrice 16x2 in posizione riga 1 e colonna 3
  lcd.print(becq); //quindi stampa valore attribuito alla variabile
  lcd.setCursor(9,1); //posiziona cursore nella matrice 16x2 in posizione riga 1 e colonna 9
  lcd.print("cBq"); //stampa unità di misura

if(((ValoreRicevuto!=0)||(ValoreRicevuto2!=0))&&(ValoreRicevuto3==0)) //nel caso in cui almeno uno dei due sensori abbia rilevato qualcosa
  { 
   tone(buzzerPin, 10, 440); //attiva buzzer ed emetti un suono
   cont = cont+1; //incrementa contatore per tenere traccia di tutti i rilevamenti
  
  }

  if(ValoreRicevuto3!=0) //nel caso in cui ci sia stata una coincidenza
  { 
    tone(buzzerPin, 6000, 300); //attiva buzzer ed emetti un suono di tonalità e durata differente
    cont = cont+1;  //incrementa contatore per tenere traccia di tutti i rilevamenti
    contT3=contT3+1;  //incrementa contatore delle coincidenze
  }
  
temp = milli_time; //la variabile temp si aggiorna, la si rende uguale al tempo assoluto solo alla fine del programma per conservare lo scarto del tempo tra due successive rilevazioni

}//chiusura if

}//chiusura void loop
