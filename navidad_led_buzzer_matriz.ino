#include <Adafruit_GFX.h>
#include <gfxfont.h>
  
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

//#include <LCD.h>                  
#include <LiquidCrystal_I2C.h>
  
Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

/*
 * CONEXIONES
 *  Del pin 2 hasta el 10 para los leds.
 *  Zumbador en el 13
 *  Matrix en el I²C
 */

/* declaracion objeto LCD */
#define I2C_ADDR          0x27 
//LiquidCrystal_I2C      lcd(I2C_ADDR, En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
LiquidCrystal_I2C      lcd(I2C_ADDR, 20,4);
  
/* Declaración de las frecuencias de las notas musicales */

const float c = 261.63; // Do (Octava 0)
const float d = 293.66; // Re (Octava 0)
const float e = 329.63; // Mi (Octava 0)
const float f = 349.23; // Fa (Octava 0)
const float g = 392.00; // Sol (Octava 0)
const float gS = 415.30;  // Sol# (Octava 0)
const float a = 440.00; // La (Octava 0)
const float b = 466.16; // La# (Octava 0)
const float cH = 523.25;   // Do (Octava 1)
const float cSH = 554.37;  // Do# (Octava 1)
const float dH = 587.33; // Re (Octava 1)
const float dSH = 622.25; // Re# (Octava 1)
const float eH = 659.26; // Mi (Octava 1)
const float fH = 698.46; // Fa (Octava 1)
const float fSH = 739.99; // Fa# (Octava 1)
const float gH = 783.99;  // Sol (Octava 1)
const float gSH = 830.61; // Sol# (Octava 1)
const float aH = 880.00; // La (Octava 1)
   
const int zumbador = 13; // Pin digital para el zumbador

const int led1 = 2; // Pin digital para el LED 1
const int led2 = 3; // Pin digital para el LED 2
const int led3 = 4; // Pin digital para el LED 3
const int led4 = 5; // Pin digital para el LED 4
const int led5 = 6; // Pin digital para el LED 5
const int led6 = 7; // Pin digital para el LED 6
const int led7 = 8; // Pin digital para el LED 7
const int led8 = 9; // Pin digital para el LED 8
const int led9 = 10; // Pin digital para el LED 9


int contador = 0;

/*
 * Declaracion de los smiles, muñecos, numeros 
 * y constantes usadas para la matrix
 * 
 */

boolean cambia_cara = true;

static const uint8_t PROGMEM
  smile_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10100101,
    B10011001,
    B01000010,
    B00111100 },
    
 
  copoNieve1_bmp[] =
  { B00011100,
    B01010101,
    B11001001,
    B01110111,
    B01001001,
    B00101010,
    B00011100,
    B00000000
   },
  
  copoNieve2_bmp[] =
  { B00001000,
    B00101010,
    B00011100,
    B01110111,
    B00011100,
    B00101010,
    B00001000,
    B00000000
  },
  
  copoNieve3_bmp[] =
  { B00010100,
    B00101010,
    B01011101,
    B00101010,
    B01011101,
    B00101010,
    B00010100,
    B00000000
  },
  
  copoNieve4_bmp[] =
  { B01001001,
    B00010100,
    B00111110,
    B01010101,
    B00111110,
    B00010100,
    B01001001,
    B00000000
  },
  
  copoNieve5_bmp[] =
  { B00001000,
    B00110110,
    B00101010,
    B01011101,
    B00101010,
    B00110110,
    B00001000,
    B00000000
  },

  copoNieve6_bmp[] =
  { B00001000,
    B00011100,
    B00101010,
    B01110111,
    B00101010,
    B00011100,
    B00011100,
    B00000000
  };
 
/*    
 * funcion texto, pintara el texto de agradecimiento
 */
void texto(){
    matrix.clear();
    matrix.setTextSize(0.1);
    matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
    matrix.setTextColor(LED_ON);
    for (int8_t x=0; x>=-36; x--) {
      matrix.clear();
      matrix.setCursor(x,0);
      matrix.print("GRACIAS");
      matrix.writeDisplay();
      delay(100);
    }
   
}

/*
 * funcion cara. mostrara la carita, smail o lo que sea
 */

void cara(){
  
  if (cambia_cara) {
    matrix.clear();
    matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(50);
    cambia_cara = !cambia_cara;
  }else{
    /*
    matrix.clear();
    matrix.drawBitmap(0, 0, copoNieve1_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(300);
    matrix.clear();
    matrix.drawBitmap(0, 0, copoNieve2_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(300);
    matrix.clear();
    matrix.drawBitmap(0, 0, copoNieve3_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(300);
    matrix.clear();
    matrix.drawBitmap(0, 0, copoNieve4_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(300);
    matrix.clear();
    matrix.drawBitmap(0, 0, copoNieve5_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(300);
    matrix.clear();
    matrix.drawBitmap(0, 0, copoNieve6_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    */
  }
}

void tono(int frecuencia, int duracion) {
  // Suena el tono en el zumbador
  tone(zumbador, frecuencia, duracion);
   
  // Se encienden los leds alternamente 
  if(contador % 2 == 0){
    digitalWrite(led1, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led5, HIGH);
    digitalWrite(led7, HIGH);
    digitalWrite(led9, HIGH);
    delay(duracion);
    digitalWrite(led1, LOW);   
    digitalWrite(led3, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led7, LOW);
    digitalWrite(led9, LOW);
    
  }
  else {
    digitalWrite(led2, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led6, HIGH);
    digitalWrite(led8, HIGH);
    delay(duracion);
    digitalWrite(led2, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led6, LOW);
    digitalWrite(led8, LOW);
  }
  //cara(); 
  // Para de sonar el tono en el zumbador
  noTone(zumbador);
  delay(50);
   
  // Se incrementa el contador
  contador++;
}

void villancico(){
  digitalWrite(zumbador,LOW);
  matrix.clear();
  matrix.drawBitmap(0, 0, copoNieve1_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  matrix.clear();
  matrix.drawBitmap(0, 0, copoNieve2_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  tono(e, 500);
  tono(e, 500);
  tono(e, 500);
  tono(e, 500);    
  tono(e, 500);
  tono(e, 500);    
  tono(e, 500);    
  tono(g, 500);
  tono(c, 500);
  tono(d, 500);  
  tono(e, 500);
  delay(500);
  matrix.clear();
  matrix.drawBitmap(0, 0, copoNieve3_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  matrix.clear();
  matrix.drawBitmap(0, 0, copoNieve4_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
   
  tono(f, 500);
  tono(f, 500);
  tono(f, 500);  
  tono(f, 500);
  tono(f, 500);
  tono(e, 500);
  tono(e, 500);
  tono(e, 500);
  tono(e, 500);
  tono(d, 500);
  tono(d, 500);
  tono(e, 500);
  tono(d, 500);
  tono(g, 500);
  delay(500);
  
  matrix.clear();
  matrix.drawBitmap(0, 0, copoNieve5_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  matrix.clear();
  matrix.drawBitmap(0, 0, copoNieve6_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
}
void setup() {
  Serial.begin(9600);

  /* declaro pin para zumbador y leds */
  pinMode(zumbador, OUTPUT);
  pinMode(led1, OUTPUT); 
  pinMode(led2, OUTPUT); 
  pinMode(led3, OUTPUT); 
  pinMode(led2, OUTPUT); 
  pinMode(led4, OUTPUT); 
  pinMode(led5, OUTPUT); 
  pinMode(led6, OUTPUT); 
  pinMode(led7, OUTPUT); 
  pinMode(led8, OUTPUT); 
  pinMode(led9, OUTPUT); 

  /* declaro LCD 16x2 */
  lcd.init();
  //lcd.setBacklight(HIGH);
  lcd.backlight();
    
  /* declaro matrix */
  matrix.begin(0x70);  // pass in the address 
  matrix.clear();
  delay(5000);
}
   
void loop() { 
    /* lo mandamos al LCD-I2C */
    matrix.clear();
    lcd.setCursor(0,0); 
    lcd.print("Os deseo");         
    lcd.setCursor(0,1); 
    lcd.print("mucha felicidad");
    delay(5000);
    cara();
    delay(1000);
    villancico();
    delay(1000);
    texto();
  
}   


