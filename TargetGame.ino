#include <TFT_eSPI.h> 

TFT_eSPI    tft = TFT_eSPI(); 
TFT_eSprite img = TFT_eSprite(&tft);

const int pwmFreq = 5000;
const int pwmResolution = 8;
const int pwmLedChannelTFT = 5;

float x=100;
float y=100;
float s=2.25; //speed of cursor
float eSpeed=1.1; //enemy speed

int score=0;
int rTime=60;  //remaining time

float enemyX[5];
float enemyY[5];

int deb=0; //debounce help variable
int deb2=0;
int currTime=1000;
bool hit=0;

int hits=0;
int miss=0;
int fired=0;
int ammo=5;

float accuracy=0;
bool gameOver=false;

void setup() {

 pinMode(25,INPUT_PULLUP); 
 pinMode(26,INPUT_PULLUP); 
 tft.init();
 tft.setRotation(2);
 tft.setSwapBytes(true);
 tft.setFreeFont(&FreeMonoBold9pt7b);
 tft.fillScreen(TFT_WHITE); 
 tft.drawLine(0,19,240,19,TFT_BLACK);
 tft.drawLine(0,167,240,167,TFT_BLACK);
 tft.setTextColor(TFT_BLACK,TFT_WHITE);
 tft.drawString("SCORE:       TIME:",6,2);
 tft.drawString(String(rTime),206,2);
 tft.drawString("STATS",6,174);
 tft.drawString("hits:",6,194);
 tft.drawString("fired:",120,194);
 tft.drawString("accur:",120,214);
 tft.drawString("ammo :",120,174);
 tft.drawString("miss:",6,214);

 
 img.createSprite(240, 146);
 


 for(int i=0;i<5;i++)
   {
    enemyX[i]=250+(i*random(50,80));
    enemyY[i]=random(15,130);
    tft.fillRect(186+(i*9),174,6,14,TFT_RED);
    tft.fillRect(186+(i*9),185,6,4,TFT_GOLD);
   }
}

void loop() {
  
 if(gameOver==0){
 if(millis()>currTime)
 {
  currTime=millis()+1000;
  rTime--;
  tft.drawString(String(rTime),206,2);
 }

 if(analogRead(39)<1000 && x<204)
 x=x+s; 

 if(analogRead(36)>3000 && y<138)
 y=y+s;

  if(analogRead(39)>3000 && x>0)
 x=x-s; 

 if(analogRead(36)<1000 && y>0)
 y=y-s; 

 draw(x,y);

 if(digitalRead(26)==0)
 {
  if(deb2==0)
  {
    deb2=1;
    ammo=5;
    tft.fillRect(186,174,60,15,TFT_WHITE);
      for(int i=0;i<ammo;i++)
      {
      tft.fillRect(186+(i*9),174,6,14,TFT_RED);
      tft.fillRect(186+(i*9),185,6,4,TFT_GOLD);
     }
    
  }
  }else deb2=0;

 if(ammo>0)
 if(digitalRead(25)==0)
 {
  if(deb==0)
    {
      deb=1;
      tft.fillRect(186,174,60,15,TFT_WHITE);
      ammo--;
      for(int i=0;i<ammo;i++)
      {
      tft.fillRect(186+(i*9),174,6,14,TFT_RED);
      tft.fillRect(186+(i*9),185,6,4,TFT_GOLD);
     }
      
      for(int i=0;i<5;i++)
      if(x>enemyX[i]-14 && x<enemyX[i]+14 && y>enemyY[i]-14 && y<enemyY[i]+14)
       {
       score=score+5;
       fired++;
       hits++;
       accuracy=(float)hits/(float)fired*100;
       tft.drawString(String(hits),62,194);
       tft.drawString(String((int)accuracy)+"%   ",186,214);
       tft.drawString(String(fired),186,194);
       tft.drawString(String(score),74,2);
       enemyX[i]=random(270,300);
       enemyY[i]=random(15,130); 
       hit=1;
       }
      if(hit==0)
      {
       score--;
       hit=1;
       miss++;
       fired++;
       accuracy=(float)hits/(float)fired*100;
       tft.drawString(String(miss),62,214);
       tft.drawString(String((int)accuracy)+"%   ",186,214);
       tft.drawString(String(fired),186,194);
       tft.drawString(String(score)+"   ",74,2);  
      }
      
    }
  }else {deb=0; hit=0;}
 }
}

void draw(int x, int y)
{
  
 img.fillSprite(0x7EBF); 

 if(rTime==0)
{
  gameOver=1;
  img.setTextColor(TFT_RED,TFT_YELLOW);
  img.setFreeFont(&FreeMonoBold18pt7b);
  img.drawString("GAME OVER!",20,50);
  img.setFreeFont(&FreeMonoBold9pt7b);
}else{
 for(int i=0;i<5;i++){
 img.fillCircle(enemyX[i],enemyY[i],14,TFT_RED);
 img.fillCircle(enemyX[i],enemyY[i],11,TFT_WHITE);
 img.fillCircle(enemyX[i],enemyY[i],8,TFT_RED);
 img.fillCircle(enemyX[i],enemyY[i],5,TFT_WHITE);
 img.fillCircle(enemyX[i],enemyY[i],2,TFT_RED);
 enemyX[i]=enemyX[i]-eSpeed;
 if(enemyX[i]<16){
 enemyX[i]=random(270,300);
 enemyY[i]=random(15,130); 
 }
 }
  
 img.drawCircle(x,y,10,TFT_BLACK);
 img.drawCircle(x,y,9,TFT_BLACK);

 img.drawLine(x,y-6,x,y-12,TFT_BLACK);
 img.drawLine(x,y+6,x,y+12,TFT_BLACK);

 img.drawLine(x-6,y,x-12,y,TFT_BLACK);
 img.drawLine(x+6,y,x+12,y,TFT_BLACK);
 
 img.fillCircle(x,y,1,TFT_BLACK);
}
 img.pushSprite(0,20);

}
