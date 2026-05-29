#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

#define TFT_CS 5
#define TFT_RST 16
#define TFT_DC 17
#define TFT_BL 4

#define PULS_DESTRA   27
#define PULS_SINISTRA   25
#define PULS_ALTO   26
#define PULS_BASSO   33
#define SELECT  14
#define INTERRUTTORE 13
#define BUZZER 12

#define T_ON_OFF 5000
#define DEBOUNCE 75

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void home();
void piano();
void breakout();
void question();
void calcolatrice();

uint16_t verdeblu = tft.color565(128, 255, 0);
uint16_t grigio = tft.color565(128, 128, 128);
uint16_t mattone = tft.color565(33, 35, 89);
uint16_t marrone = tft.color565(9, 21, 54);
uint16_t oro = tft.color565(0, 215, 255);
uint16_t viola = tft.color565(128, 0, 128);
uint16_t ciano = tft.color565(255, 255, 0);
uint16_t rossisso = tft.color565(0, 0, 102);

int appx = 0;
int appy = 1;
int apri = 0;
int selx1 = 23; int selx2 = 24; int selx3 = 25;
int sely1 = 13; int sely2 = 14; int sely3 = 15;
int rselx1 = 23; int rselx2 = 24; int rselx3 = 25;
int rsely1 = 13; int rsely2 = 14; int rsely3 = 15;

bool onApp = false;
bool sCONSOLE = false;
bool sSELECT = false;         bool sSEL = false;   bool ssSEL = false;
bool sPULS_DESTRA = false;    bool sPDX = false;   bool ssPDX = false;
bool sPULS_SINISTRA = false;  bool sPSX = false;   bool ssPSX = false;
bool sPULS_ALTO = false;      bool sPA = false;    bool ssPA = false;
bool sPULS_BASSO = false;     bool sPB = false;    bool ssPB = false;

unsigned long tUltimoPulsante = 0;
unsigned long tPressione = 0;

void setup() {

 Serial.begin(115200);

 tft.initR(INITR_GREENTAB);
 tft.setRotation(1);
 tft.fillScreen(ST77XX_BLACK);

 pinMode(PULS_DESTRA, INPUT);
 pinMode(PULS_ALTO, INPUT);
 pinMode(PULS_SINISTRA, INPUT);
 pinMode(PULS_BASSO, INPUT);
 pinMode(SELECT, INPUT);
 pinMode(INTERRUTTORE, INPUT);
 pinMode(BUZZER, OUTPUT);
 pinMode(TFT_BL, OUTPUT);

}

void loop() {

  //-----------------------------------------
  //--- PULSANTE ACCENSIONE E SPEGNIMENTO ---
  //-----------------------------------------

  if(digitalRead(INTERRUTTORE)) {
    if(millis() - tPressione > T_ON_OFF) {
     tft.fillScreen(ST77XX_BLACK);
     sCONSOLE = !sCONSOLE;
     tPressione = millis();
    }
  }
  else {
   tPressione = millis();
  }

  //--------------------------------
 noTone(BUZZER);
  //--------------------------------

  switch(sCONSOLE) {

    //------------------------------
    //--- CONSOLE SPENTA --- OFF ---
    //------------------------------

    case false:
     digitalWrite(TFT_BL, LOW);
    break;

    //-----------------------------
    //--- CONSOLE ACCESA --- ON ---
    //-----------------------------

    case true:
     digitalWrite(TFT_BL, HIGH);

      //--------------------------------
      //--- GESTIONE PULSANTE SELECT ---
      //--------------------------------

      if (digitalRead(SELECT) != sSELECT && millis() - tUltimoPulsante > DEBOUNCE) {
       sSELECT = digitalRead(SELECT);
       tUltimoPulsante = millis();
        if(sSELECT) {
         sSEL = true;
        }
      else {
         sSEL = false;
        }
      }

      //--------------------------------
      //--- GESTIONE PULSANTE DESTRA ---
      //--------------------------------

      if (digitalRead(PULS_DESTRA) != sPULS_DESTRA && millis() - tUltimoPulsante > DEBOUNCE) {
       sPULS_DESTRA = digitalRead(PULS_DESTRA);
       tUltimoPulsante = millis();
        if(sPULS_DESTRA) {
         sPDX = true;
        }
        else {
         sPDX = false;
        }
      } 

      //----------------------------------
      //--- GESTIONE PULSANTE SINISTRA ---
      //----------------------------------

      if (digitalRead(PULS_SINISTRA) != sPULS_SINISTRA && millis() - tUltimoPulsante > DEBOUNCE) {
       sPULS_SINISTRA = digitalRead(PULS_SINISTRA);
       tUltimoPulsante = millis();
        if(sPULS_SINISTRA) {
         sPSX = true;
        }
        else {
         sPSX = false;
        }
      }

      //------------------------------
      //--- GESTIONE PULSANTE ALTO ---
      //------------------------------

      if (digitalRead(PULS_ALTO) != sPULS_ALTO && millis() - tUltimoPulsante > DEBOUNCE) {
       sPULS_ALTO = digitalRead(PULS_ALTO);
       tUltimoPulsante = millis();
        if(sPULS_ALTO) {
         sPA = true;
        }
        else {
         sPA = false;
        }
      }

      //-------------------------------
      //--- GESTIONE PULSANTE BASSO ---
      //-------------------------------

      if (digitalRead(PULS_BASSO) != sPULS_BASSO && millis() - tUltimoPulsante > DEBOUNCE) {
       sPULS_BASSO = digitalRead(PULS_BASSO);
       tUltimoPulsante = millis();
        if(sPULS_BASSO) {
         sPB = true;
        }
        else {
         sPB = false;
        }
      }

      //--- PORTA IN HOME ---
      home();
    break;
  }
}

void home() {

  if(sSEL != ssSEL) {
   ssSEL = sSEL;
    if(ssSEL) {
     tft.fillScreen(ST77XX_BLACK);
     apri += 1;
      if (apri == 2) {
       apri = 0;
      }
    }
  }

  if ((appx == 0) && (appy == 1) && (apri == 1)) { // apre app piano
   onApp = true;
   piano();
  } 
  
  else if ((appx == 0) && (appy == 0) && (apri == 1)) { // apre app ?
   onApp = true;
   question();
  } 
  
  else if ((appx == 1) && (appy == 1) && (apri == 1)) { // apre app calcolatrice
   onApp = true;
   calcolatrice();
  }

  else if ((appx == 1) && (appy == 0) && (apri == 1)) { // apre app breakout
   onApp = true;
   breakout();
  }
  
  else {
   onApp = false;
  }

if (onApp == false) { // serve per non far scrivere questo quando si e apre un app
  
  if(sPDX != ssPDX) {
   ssPDX = sPDX;
    if(ssPDX) {
     rselx1 = selx1; rselx2 = selx2; rselx3 = selx3;
     rsely1 = sely1; rsely2 = sely2; rsely3 = sely3;
     appx += 1;
      if (appx == 2) {
       appx = 0;
      }
    }
  }

  if(sPSX != ssPSX) {
   ssPSX = sPSX;
    if(ssPSX) {
     rselx1 = selx1; rselx2 = selx2; rselx3 = selx3;
     rsely1 = sely1; rsely2 = sely2; rsely3 = sely3;
     appx -= 1;
      if (appx == -1) {
       appx = 1;
      }
    }
  }

  if(sPA != ssPA) {
   ssPA = sPA;
    if(ssPA){
     rselx1 = selx1; rselx2 = selx2; rselx3 = selx3;
     rsely1 = sely1; rsely2 = sely2; rsely3 = sely3;
     appy += 1;
      if (appy == 2) {
       appy = 0;
      }
    }
  }

  if(sPB != ssPB) {
   ssPB = sPB;
    if(ssPB) {
     rselx1 = selx1; rselx2 = selx2; rselx3 = selx3;
     rsely1 = sely1; rsely2 = sely2; rsely3 = sely3;
     appy -= 1;
      if (appy == -1) {
        appy = 1;
      }
    }
  }

  if ((appx == 0) && (appy == 1)) {
     
   // APP DEL PIANO
   selx1 = 23; selx2 = 24; selx3 = 25;
   sely1 = 13; sely2 = 14; sely3 = 15;
  }

  if ((appx == 1) && (appy == 1)) {

   // CALCOLATRICE
   selx1 = 91; selx2 = 92; selx3 = 93;
   sely1 = 13; sely2 = 14; sely3 = 15;
  }

  if ((appx == 0) && (appy == 0)) {

   // ??
   selx1 = 23; selx2 = 24; selx3 = 25;
   sely1 = 69; sely2 = 70; sely3 = 71;
  }

  if ((appx == 1) && (appy == 0)) {

   // BREAKOUT
   selx1 = 91; selx2 = 92; selx3 = 93;
   sely1 = 69; sely2 = 70; sely3 = 71;
  }

   tft.drawRoundRect(rselx1, rsely1, 46, 46, 15, ST77XX_BLACK); //previous selezionato 1 cancellato
   tft.drawRoundRect(rselx2, rsely2, 44, 44, 13, ST77XX_BLACK); //previous selezionato 2 cancellato
   tft.drawRoundRect(rselx3, rsely3, 42, 42, 11, ST77XX_BLACK); //previous selezionato 3 cancellato

   tft.drawRoundRect(selx1, sely1, 46, 46, 15, oro); //selezionato 1
   tft.drawRoundRect(selx2, sely2, 44, 44, 13, oro); //selezionato 2
   tft.drawRoundRect(selx3, sely3, 42, 42, 11, oro); //selezionato 3

   tft.drawRoundRect(26, 16, 40, 40, 10, ST77XX_WHITE); //contorno
   tft.fillRect(27, 21, 1, 28, ST77XX_WHITE); //tasto bianco 1 1
   tft.fillRect(28, 20, 1, 32, ST77XX_WHITE); //tasto bianco 1 2
   tft.fillRect(29, 19, 1, 34, ST77XX_WHITE); //tasto bianco 1 3
   tft.fillRect(30, 18, 2, 36, ST77XX_WHITE); //tasto bianco 1 4
   tft.fillRect(32, 18, 1, 36, ST77XX_WHITE); //tasto bianco 1 5
   tft.fillRect(38, 17, 8, 38, ST77XX_WHITE); //tasto bianco 2
   tft.fillRect(51, 17, 8, 38, ST77XX_WHITE); //tasto bianco 3
   tft.fillRect(64, 23, 1, 28, ST77XX_WHITE); //tasto bianco 4
   tft.fillRect(33, 37, 2, 19, ST77XX_WHITE); //tasto bianco sotto nero 1 1
   tft.fillRect(36, 37, 2, 19, ST77XX_WHITE); //tasto bianco sotto nero 1 2
   tft.fillRect(46, 37, 2, 19, ST77XX_WHITE); //tasto bianco sotto nero 2 1
   tft.fillRect(49, 37, 2, 19, ST77XX_WHITE); //tasto bianco sotto nero 2 2
   tft.fillRect(59, 37, 2, 17, ST77XX_WHITE); //tasto bianco sotto nero 3 1
   tft.fillRect(62, 37, 1, 15, ST77XX_WHITE); //tasto bianco sotto nero 3 2
   tft.fillRect(63, 37, 1, 14, ST77XX_WHITE); //tasto bianco sotto nero 3 3
   tft.fillRect(35, 37, 1, 19, grigio); //parte grigia 1
   tft.fillRect(48, 37, 1, 19, grigio); //parte grigia 1
   tft.fillRect(61, 37, 1, 16, grigio); //parte grigia 1

   // BREAKOUT
   tft.drawRoundRect(94, 72, 40, 40, 10, mattone); //contorno
   tft.fillRect(101, 73, 14, 1, mattone); //mattoncino 1 1
   tft.fillRect(99, 74, 16, 1, mattone); //mattoncino 1 2
   tft.fillRect(98, 75, 17, 1, mattone); //mattoncino 1 3
   tft.fillRect(97, 76, 18, 1, mattone); //mattoncino 1 4
   tft.fillRect(96, 77, 19, 2, mattone); //mattoncino 1 5
   tft.fillRect(115, 73, 2, 6, marrone); //mezzo 1
   tft.fillRect(95, 79, 38, 2, marrone); //mezzo 2
   tft.fillRect(117, 73, 10, 1, mattone); //mattoncino 2 1
   tft.fillRect(117, 74, 12, 1, mattone); //mattoncino 2 2
   tft.fillRect(117, 75, 13, 1, mattone); //mattoncino 2 3
   tft.fillRect(117, 76, 14, 1, mattone); //mattoncino 2 4
   tft.fillRect(117, 77, 15, 2, mattone); //mattoncino 2 5
   tft.fillRect(95, 81, 8, 7, mattone); //mattoncino 3 
   tft.fillRect(103, 81, 2, 7, marrone); //mezzo 3
   tft.fillRect(105, 81, 20, 7, mattone); //mattoncino 4
   tft.fillRect(125, 81, 2, 7, marrone); //mezzo 4
   tft.fillRect(127, 81, 6, 7, mattone); //mattoncino 5
   tft.fillRect(95, 88, 38, 2, marrone); //mezzo 4
   tft.fillCircle(125, 95, 3, oro); //pallina
   tft.fillRoundRect(100, 105, 18, 5, 3, verdeblu); //paddle



   // CALCOLATRICE
   tft.drawRoundRect(94, 16, 40, 40, 10, ST77XX_GREEN); //contorno
   tft.setTextColor(ST77XX_GREEN);
   tft.setTextSize(2);
   tft.setCursor(99, 19);  tft.print('+');
   tft.setCursor(118, 19); tft.print('-');
   tft.setCursor(99, 34);  tft.print('x');
   tft.setCursor(117, 35); tft.print(':');


   // ??
   tft.drawRoundRect(26, 72, 40, 40, 10, viola); //contorno
   tft.setTextColor(viola);
   tft.setTextSize(4);
   tft.setCursor(36, 77);  tft.print('?');
  }
}

void piano() {

 tft.fillRect(0, 0, 11, 128, ST77XX_WHITE); //tasto 1
 tft.fillRect(11, 45, 4, 83, ST77XX_WHITE); //sotto tasto 1
 tft.fillRect(15, 45, 2, 83, grigio); //mezzo 1
 tft.fillRect(17, 45, 4, 83, ST77XX_WHITE); //sotto tasto 2
 tft.fillRect(21, 0, 11, 128, ST77XX_WHITE); //tasto 2
 tft.fillRect(32, 45, 4, 83, ST77XX_WHITE); //sotto tasto 3
 tft.fillRect(36, 45, 2, 83, grigio); //mezzo 2
 tft.fillRect(38, 45, 4, 83, ST77XX_WHITE); //sotto tasto 4
 tft.fillRect(42, 0, 11, 128, ST77XX_WHITE); //tasto 3
 tft.fillRect(53, 45, 4, 83, ST77XX_WHITE); //sotto tasto 5
 tft.fillRect(57, 45, 2, 83, grigio); //mezzo 3
 tft.fillRect(59, 45, 4, 83, ST77XX_WHITE); //sotto tasto 6
 tft.fillRect(63, 0, 11, 128, ST77XX_WHITE); //tasto 4
 tft.fillRect(74, 45, 4, 83, ST77XX_WHITE); //sotto tasto 7
 tft.fillRect(78, 45, 2, 83, grigio); //mezzo 4
 tft.fillRect(80, 45, 4, 83, ST77XX_WHITE); //sotto tasto 8
 tft.fillRect(84, 0, 11, 128, ST77XX_WHITE); //tasto 5
 tft.fillRect(95, 45, 4, 83, ST77XX_WHITE); //sotto tasto 9
 tft.fillRect(99, 45, 2, 83, grigio); //mezzo 5
 tft.fillRect(101, 45, 4, 83, ST77XX_WHITE); //sotto tasto 10
 tft.fillRect(105, 0, 11, 128, ST77XX_WHITE); //tasto 6
 tft.fillRect(116, 45, 4, 83, ST77XX_WHITE); //sotto tasto 11
 tft.fillRect(120, 45, 2, 83, grigio); //mezzo 6
 tft.fillRect(122, 45, 4, 83, ST77XX_WHITE); //sotto tasto 12
 tft.fillRect(126, 0, 11, 128, ST77XX_WHITE); //tasto 7
 tft.fillRect(137, 45, 4, 83, ST77XX_WHITE); //sotto tasto 13
 tft.fillRect(141, 45, 2, 83, grigio); //mezzo 7
 tft.fillRect(143, 45, 4, 83, ST77XX_WHITE); //sotto tasto 14
 tft.fillRect(147, 0, 11, 128, ST77XX_WHITE); //tasto 8
 tft.fillRect(158, 45, 4, 83, ST77XX_WHITE); //sotto tasto 15
 tft.fillRect(160, 45, 2, 83, grigio); //mezzo 7
}

void breakout() {
 tft.setTextColor(ST77XX_WHITE);
 tft.setTextSize(6);
 tft.setCursor(10, 60);  tft.print("PROSSIMAMENTE");
}

void question() {
 tft.fillRect(55, 44, 50, 17, ST77XX_BLUE);
 tft.fillCircle(64, 44, 20, ST77XX_BLUE);
 tft.fillCircle(95, 44, 20, ST77XX_BLUE);
 tft.fillTriangle(47, 54, 80, 88, 112, 54, ST77XX_BLUE);
}

void calcolatrice() {
// CALCOLATRICE NON FUNZIONANTE
tft.setTextSize(2);
tft.drawRect(0, 0, 160, 28, ciano);
// striscia numeri 7, 4, 1 e canc
tft.drawRect(0, 29, 39, 24, ST77XX_GREEN);
tft.setTextColor(ST77XX_GREEN);
tft.setCursor(15, 34);  tft.print('7');
tft.drawRect(0, 54, 39, 24, ST77XX_GREEN);
tft.setCursor(15, 59);  tft.print('4');
tft.drawRect(0, 79, 39, 24, ST77XX_GREEN);
tft.setCursor(15, 84);  tft.print('1');
tft.drawRect(0, 104, 39, 24, rossisso);
tft.fillRect(5, 110, 16, 12, rossisso);
tft.fillTriangle(21, 110, 21, 121, 29, 115, rossisso);
// striscia mumeri 8, 5, 3 e 0
tft.drawRect(40, 29, 39, 24, ST77XX_GREEN);
tft.setCursor(55, 34);  tft.print('8');
tft.drawRect(40, 54, 39, 24, ST77XX_GREEN);
tft.setCursor(55, 59);  tft.print('5');
tft.drawRect(40, 79, 39, 24, ST77XX_GREEN);
tft.setCursor(55, 84);  tft.print('2');
tft.drawRect(40, 104, 39, 24, ST77XX_GREEN);
tft.setCursor(55, 109);  tft.print('0');
// striscia numeri 9, 6, 3 e =
tft.drawRect(80, 29, 39, 24, ST77XX_GREEN);
tft.setCursor(95, 34);  tft.print('9');
tft.drawRect(80, 54, 39, 24, ST77XX_GREEN);
tft.setCursor(95, 59);  tft.print('6');
tft.drawRect(80, 79, 39, 24, ST77XX_GREEN);
tft.setCursor(95, 84);  tft.print('3');
tft.drawRect(80, 104, 39, 24, oro);
tft.setTextColor(oro);
tft.setCursor(95, 109);  tft.print('=');
// striscia calcolo :, x, - e +
tft.drawRect(120, 29, 40, 24, ST77XX_BLUE);
tft.setTextColor(ST77XX_BLUE);
tft.setCursor(135, 34);  tft.print(':');
tft.drawRect(120, 54, 40, 24, ST77XX_BLUE);
tft.setCursor(135, 59);  tft.print('x');
tft.drawRect(120, 79, 40, 24, ST77XX_BLUE);
tft.setCursor(135, 84);  tft.print('-');
tft.drawRect(120, 104, 40, 24, ST77XX_BLUE);
tft.setCursor(135, 109);  tft.print('+');
}