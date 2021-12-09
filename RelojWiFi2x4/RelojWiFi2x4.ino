#include "WiFi.h"
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

#define NMATRIZH   4
#define NMATRIZV   2
#define CLK       18 // or SCK
#define DIN       23 // or MOSI
#define CS        5  // or SS
#define BTN       25

Max72xxPanel MD = Max72xxPanel(CS, NMATRIZH, NMATRIZV);
WiFiUDP ntpUDP;
NTPClient tiempo(ntpUDP);

char* ssid = "Red";
char* psswd = "internet10";
int zona = -21600;
bool hv=false;

byte h;
byte m;
byte s;
byte u;
byte d;

boolean formato12=true;

byte d0[5][14] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
byte d1[5][14] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}};
byte d2[5][14] = {{1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1}};
byte d3[5][14] = {{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
byte d4[5][14] = {{1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
byte d5[5][14] = {{1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
byte d6[5][14] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
byte d7[5][14] = {{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
byte d8[5][14] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
byte d9[5][14] = {{1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

byte p1[3][8]={{0,0,0,0,0,0,0,0},{0,1,0,0,0,0,1,0},{0,0,0,0,0,0,0,0}};
byte p2[3][8]={{0,0,0,0,0,0,0,0},{0,0,1,0,0,1,0,0},{0,0,0,0,0,0,0,0}};

byte s0[3][5]={{1,1,1,1,1},{1,0,0,0,1},{1,1,1,1,1}};
byte s1[3][5]={{0,1,0,0,1},{1,1,1,1,1},{0,0,0,0,1}};
byte s2[3][5]={{1,0,1,1,1},{1,0,1,0,1},{1,1,1,0,1}};
byte s3[3][5]={{1,0,1,0,1},{1,0,1,0,1},{1,1,1,1,1}};
byte s4[3][5]={{1,1,1,0,0},{0,0,1,0,0},{1,1,1,1,1}};
byte s5[3][5]={{1,1,1,0,1},{1,0,1,0,1},{1,0,1,1,1}};
byte s6[3][5]={{1,1,1,1,1},{1,0,1,0,1},{1,0,1,1,1}};
byte s7[3][5]={{1,0,0,0,0},{1,0,0,0,0},{1,1,1,1,1}};
byte s8[3][5]={{1,1,1,1,1},{1,0,1,0,1},{1,1,1,1,1}};
byte s9[3][5]={{1,1,1,0,1},{1,0,1,0,1},{1,1,1,1,1}};

void setup() {
  Serial.begin(115200);
  pinMode(BTN, INPUT);
  MD.setIntensity(0); //brillo [0-15]
  
  MD.setPosition(0,0,0);
  MD.setPosition(1,1,0);
  MD.setPosition(2,2,0);
  MD.setPosition(3,3,0);
  MD.setPosition(4,3,1);
  MD.setPosition(5,2,1);
  MD.setPosition(6,1,1);
  MD.setPosition(7,0,1);
  MD.setRotation(0, 1);
  MD.setRotation(1, 1);
  MD.setRotation(2, 1);
  MD.setRotation(3, 1);
  MD.setRotation(4, 3);
  MD.setRotation(5, 3);
  MD.setRotation(6, 3);
  MD.setRotation(7, 3);


  Serial.println("Iniciando conexion...");
  iniciarConexion(ssid, psswd);
  
  tiempo.begin();
  tiempo.setTimeOffset(zona);
}

void loop() {
  obtenerFecha();
  
  separarNumero(s);
  elegirSeg(27, 4, d);
  elegirSeg(27, 10, u);

  if(u%2==0){
      MD.drawPixel(12, 5, 1);
      MD.drawPixel(12, 10, 1);
      MD.drawPixel(12, 4, 0);
      MD.drawPixel(12, 11, 0);
  }else{
      MD.drawPixel(12, 5, 0);
      MD.drawPixel(12, 10, 0);
      MD.drawPixel(12, 4, 1);
      MD.drawPixel(12, 11, 1);
  }

  separarNumero(m);
  elegirNumero(14, d);
  elegirNumero(20, u);

  if(digitalRead(BTN)){
    hv=true;
  }

  if(hv){
    h++;
  }
  
  
  if(formato12 && h>12){
    h-=12;
  }
 
  separarNumero(h);
  elegirNumero(0, d);
  elegirNumero(6, u);
  
  MD.write();
  delay(998);
  //Serial.println(millis());
}

//****** FUNCIONES ******//

void iniciarConexion(char* red, char* pass){
  WiFi.begin(red, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("*");
    delay(500);
  }
  Serial.println();
}

void obtenerFecha(){
  while (!tiempo.update()) {
    tiempo.forceUpdate();
  }
  String formatoFecha = tiempo.getFormattedDate();
  int y = formatoFecha.indexOf("T");
  int x = formatoFecha.lastIndexOf(":");
  String hora = formatoFecha.substring(y+1, x);
  h = formatoFecha.substring(y+1, y+3).toInt();
  m = formatoFecha.substring(y+4, x).toInt();
  s = formatoFecha.substring(x+1, formatoFecha.length()-1).toInt();
}

void separarNumero(int a){
  u=a%10;
  if(a<10){
    d=0;  
  }else{
    d=a/10;
  }
}

void verDigitoXY3x5(int x, int y, byte m[3][5]){
  for(int i=0; i<5; i++){
    for(int j=0; j<3; j++){
      MD.drawPixel(j+x, i+y, m[j][i]);
      //MD.write();
    }
  }
}

void verDigitoXY5x14(int x, byte m[5][14]){
  for(int i=0; i<14; i++){
    for(int j=0; j<5; j++){
      MD.drawPixel(j+x, i+1, m[j][i]);
      //MD.write();
    }
  }
}


void elegirNumero(int x, int n){
  switch(n){
    case 0:
      verDigitoXY5x14(x, d0);
      break;
    case 1:
      verDigitoXY5x14(x, d1);
      break;
    case 2:
      verDigitoXY5x14(x, d2);
      break;
    case 3:
      verDigitoXY5x14(x, d3);
      break;
    case 4:
      verDigitoXY5x14(x, d4);
      break;
    case 5:
      verDigitoXY5x14(x, d5);
      break;
    case 6:
      verDigitoXY5x14(x, d6);
      break;
    case 7:
      verDigitoXY5x14(x, d7);
      break;
    case 8:
      verDigitoXY5x14(x, d8);
      break;
    case 9:
      verDigitoXY5x14(x, d9);
      break;
  }
}

void elegirSeg(int x, int y, int n){
  switch(n){
    case 0:
      verDigitoXY3x5(x, y, s0);
      break;
    case 1:
      verDigitoXY3x5(x, y, s1);
      break;
    case 2:
      verDigitoXY3x5(x, y, s2);
      break;
    case 3:
      verDigitoXY3x5(x, y, s3);
      break;
    case 4:
      verDigitoXY3x5(x, y, s4);
      break;
    case 5:
      verDigitoXY3x5(x, y, s5);
      break;
    case 6:
      verDigitoXY3x5(x, y, s6);
      break;
    case 7:
      verDigitoXY3x5(x, y, s7);
      break;
    case 8:
      verDigitoXY3x5(x, y, s8);
      break;
    case 9:
      verDigitoXY3x5(x, y, s9);
      break;
  }
}
