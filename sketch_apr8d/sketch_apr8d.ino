#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>

#define DATA 5
#define CLK 6
#define LATCH 7
byte segment[10]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x7, 0x7F,0x6F};
int first =0;
int second =0;
int third = 0;
int potansiyometreDeger;


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define PLAYER_WIDTH 10
#define PLAYER_HEIGHT 8
#define PLAYER_SPEED 2
#define PLAYER_HEALTH 3

#define BULLET_WIDTH 2
#define BULLET_HEIGHT 5
#define BULLET_SPEED 5
#define MAX_BULLETS 3

#define METEOR_WIDTH 8
#define METEOR_HEIGHT 5
#define METEOR_SPEED 1 
#define MAX_METEOR 10
#define METEOR_DELAY 4000

#define COP_WIDTH 8
#define COP_HEIGHT 5
#define COP_SPEED 1
#define MAX_COP 10
#define COP_DELAY 2000

#define AMMO_WIDTH 8
#define AMMO_HEIGHT 5
#define AMMO_SPEED 1
#define AMMO_DELAY 8000
#define MAX_AMMO 21

#define HP_WIDTH 8
#define HP_HEIGHT 5
#define HP_SPEED 2
#define HP_DELAY 5000
#define MAX_HP 12

#define SKOR_DELAY 1000


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, 4);

int player_x = 1;
int player_y = 128-PLAYER_WIDTH;
int player_health = 3;
int ammo = 21;
int bulletleft =3;
int menu = 1;
bool fire = false;
bool a = false;
int meteorcan =2;

static const unsigned char PROGMEM playerShip[] ={0xff,0xff,0xff, 0x3c, 0xdb, 0xe7, 0xff,0xff,};
static const unsigned char PROGMEM kalp[] = {
  0xfe,0xfe,0xfe,0xfe,
    0xfe,0xfe,0xfe,
      0xfe,0xfe,
          0xfe, };
static const unsigned char PROGMEM meteortas[] ={ 0xff,0xff,0x3c, 0xe7,0xff,};

int bullet_x[MAX_BULLETS];
int bullet_y[MAX_BULLETS];

bool bullet[MAX_BULLETS];

int meteor_x[MAX_METEOR];
int meteor_y[MAX_METEOR];
int meteor_can[MAX_METEOR];

bool meteor[MAX_METEOR];
unsigned long lastMeteor = 0;

int cop_x[MAX_COP];
int cop_y[MAX_COP];
bool cop[MAX_COP];
unsigned long lastCop=0;

int ammo_x[MAX_AMMO];
int ammo_y[MAX_AMMO];

bool ammo_package[MAX_AMMO];
unsigned long lastAmmo = 0;

int hp_x[MAX_HP];
int hp_y[MAX_HP];

bool hp_package[MAX_HP];
unsigned long lastHp =0;

unsigned long skorTut=0;

void hareket(int x){
  player_x +=x;
  if(player_x<0){
player_x = 0;
  }
  if(player_x > SCREEN_HEIGHT - PLAYER_WIDTH){
    player_x =  SCREEN_HEIGHT - PLAYER_WIDTH;
  }
}
void bulletFire(){
   for(int i=0; i<MAX_BULLETS;i++){
     if(!bullet[i]){
       bullet_x[i]= player_x + PLAYER_WIDTH/2 - BULLET_WIDTH/2;
       bullet_y[i] = player_y - BULLET_HEIGHT;
       bullet[i]=true;
       break;
     }
   }
  }

void meteorUpdate(){
for(int i =0; i<MAX_METEOR;i++)
{
  if(!meteor[i]){
 
meteor_x[i]=random(SCREEN_HEIGHT - METEOR_WIDTH);
meteor_y[i]= -METEOR_HEIGHT;
meteor_can[i]=meteorcan;
meteor[i]=true;

break;
  }

}
}

void copUpdate(){
  for(int i =0; i<MAX_COP;i++){
    if(!cop[i]){
      cop_x[i]=random(SCREEN_HEIGHT-COP_WIDTH);
      cop_y[i]=-COP_HEIGHT;
      cop[i]=true;
      break;
    }
  }
}
void ammoUpdate(){
for(int i=0; i<MAX_AMMO;i++){
if(!ammo_package[i]){
  ammo_x[i]=random(SCREEN_HEIGHT - AMMO_WIDTH);
  ammo_y[i]=-AMMO_HEIGHT;
  ammo_package[i]=true;
  break;
}

}

}
void hpUpdate(){
for(int i=0; i<MAX_HP; i++){
if(!hp_package[i]){
  hp_x[i]=random(SCREEN_HEIGHT - HP_WIDTH);
  hp_y[i]=-HP_HEIGHT;
  hp_package[i]=true;
  break;
}

}

}




void update(){
if (digitalRead(A0) == HIGH) {
    hareket(-PLAYER_SPEED);
  }
  if (digitalRead(A1) == HIGH) {
    hareket(PLAYER_SPEED);
  }
  if(digitalRead(A6)==HIGH)
  {
     hareket(PLAYER_SPEED);
  }
  if(digitalRead(A6)==LOW)
  {
     hareket(-PLAYER_SPEED);
  }
 
  if (digitalRead(A2) == HIGH && !fire && bulletleft>0) {
    fire = true;
    bulletFire();
    bulletleft--;
    if(bulletleft==3)
   {
    digitalWrite(12,HIGH);
    digitalWrite(11,HIGH);
    digitalWrite(10,HIGH);
       
    }
     if(bulletleft==2)
   {
    digitalWrite(12,LOW);
    digitalWrite(11,HIGH);
    digitalWrite(10,HIGH);
       
    }
     if(bulletleft==1)
   {
    digitalWrite(12,LOW);
    digitalWrite(11,LOW);
    digitalWrite(10,HIGH);
       
    }
     if(bulletleft==0)
   {
    digitalWrite(12,LOW);
    digitalWrite(11,LOW);
    digitalWrite(10,LOW);
       
    }
  }
  if (digitalRead(A2) == LOW) {
    fire = false;
  }
 for (int i = 0; i < MAX_BULLETS; i++) {
    if (bullet[i]) {
      bullet_y[i] -= BULLET_SPEED;
      if (bullet_y[i] < 0) {
        bullet[i] = false;
      }
    }
  }
  unsigned long current = millis();
  if(current - lastMeteor > METEOR_DELAY){
    meteorUpdate();
    lastMeteor = current;
  }
  unsigned long current4 = millis();
  if(current4-lastCop>COP_DELAY){
    copUpdate();
    lastCop=current4;
  }
  
  unsigned long current1 = millis();
  if(current1 - lastAmmo > AMMO_DELAY){
    ammoUpdate();
    lastAmmo = current1;
  }
  unsigned long current2 = millis();
  if(current2 - lastHp > HP_DELAY){
    hpUpdate();
    lastHp = current2;
  }
  
  unsigned long current3 = millis();
  if(current3-skorTut>SKOR_DELAY){
        first++;
if(first>9)
{
  first=0;
  second++;
  if(second>9)
  {
    second=0;
    third++;
    if(third>9)
    {
      third=0;
    }
  }
}
skorTut = current3;
  }

  
for(int i=0; i<MAX_METEOR; i++){
if(meteor[i]){
meteor_y[i]+=METEOR_SPEED;
if(meteor_y[i]>SCREEN_WIDTH){
  meteor[i]=false;
}


for(int a=0; a<MAX_BULLETS; a++)
{
if(bullet[a]){
if(bullet_x[a]+BULLET_WIDTH >= meteor_x[i] && bullet_x[a]<=meteor_x[i] + METEOR_WIDTH && bullet_y[a] + BULLET_HEIGHT>= meteor_y[i] && bullet_y[a]<= meteor_y[i]+METEOR_HEIGHT){
  bullet[a]=false;
  meteor_can[i]--;
  if(meteor_can[i]==0){
    meteor[i]=false;
  }
  break;
}

}


}

if(player_x + PLAYER_WIDTH >= meteor_x[i] && player_x<= meteor_x[i]+METEOR_WIDTH && player_y + PLAYER_HEIGHT >= meteor_y[i] && player_y <= meteor_y[i]+METEOR_HEIGHT){
player_health = player_health-1;
meteor[i]=false;
digitalWrite(13,HIGH);
delay(500);
digitalWrite(13,LOW);

if(player_health==0){
 
  digitalWrite(0,LOW);
  digitalWrite(3,LOW);
  digitalWrite(2,LOW);
 
display.clearDisplay();
display.setCursor(SCREEN_WIDTH/2-32, SCREEN_HEIGHT/2 - 5);
display.println("GAME OVER");
display.display();
while(true){

}
  
}
}

}

}

for(int i=0; i<MAX_COP; i++){
if(cop[i]){
cop_y[i]+=COP_SPEED;
if(cop_y[i]>SCREEN_WIDTH){
  cop[i]=false;
}


for(int a=0; a<MAX_BULLETS; a++)
{
if(bullet[a]){
if(bullet_x[a]+BULLET_WIDTH >= cop_x[i] && bullet_x[a]<=cop_x[i] + COP_WIDTH && bullet_y[a] + BULLET_HEIGHT>= cop_y[i] && bullet_y[a]<= cop_y[i]+COP_HEIGHT){
  bullet[a]=false;
  cop[i]=false;
  break;
}

}


}

if(player_x + PLAYER_WIDTH >= cop_x[i] && player_x<= cop_x[i]+COP_WIDTH && player_y + PLAYER_HEIGHT >= cop_y[i] && player_y <= cop_y[i]+COP_HEIGHT){
player_health = player_health-1;
cop[i]=false;
digitalWrite(13,HIGH);
delay(500);
digitalWrite(13,LOW);

if(player_health==0){
 
  digitalWrite(0,LOW);
  digitalWrite(3,LOW);
  digitalWrite(2,LOW);
 
display.clearDisplay();
display.setCursor(SCREEN_WIDTH/2-32, SCREEN_HEIGHT/2 - 5);
display.println("GAME OVER");
display.display();
while(true){

}
  
}
}

}

}




for(int i=0; i<ammo; i++){
if(ammo_package[i]){
ammo_y[i]+=AMMO_SPEED;
if(ammo_y[i]>SCREEN_WIDTH){
  ammo_package[i]=false;
}
if(player_x + PLAYER_WIDTH >= ammo_x[i] && player_x<= ammo_x[i]+AMMO_WIDTH && player_y + PLAYER_HEIGHT >= ammo_y[i] && player_y <= ammo_y[i]+AMMO_HEIGHT){
ammo_package[i]=false;
if(bulletleft<3){
  bulletleft=3;
}

  if(bulletleft==3)
   {
    digitalWrite(12,HIGH);
    digitalWrite(11,HIGH);
    digitalWrite(10,HIGH);
       
    }
    if(bulletleft==2)
   {
    digitalWrite(12,LOW);
    digitalWrite(11,HIGH);
    digitalWrite(10,HIGH);
       
    }
    if(bulletleft==1)
   {
    digitalWrite(12,LOW);
    digitalWrite(11,LOW);
    digitalWrite(10,HIGH);
       
    }





}
}
}

for(int i=0;i<MAX_HP;i++)
{
  if(hp_package[i]){
    hp_y[i]+=HP_SPEED;
    if(hp_y[i]>SCREEN_WIDTH){
      hp_package[i]=false;
    }
    if(player_x + PLAYER_WIDTH >= hp_x[i] && player_x<= hp_x[i]+HP_WIDTH && player_y + PLAYER_HEIGHT >= hp_y[i] && player_y <= hp_y[i]+HP_HEIGHT){
    hp_package[i]=false;
    if(player_health<3)
    {
player_health++;
    }
    
    if(player_health==3){
  digitalWrite(0,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(2,HIGH);
 }
 else if(player_health==2)
 {
  digitalWrite(0,LOW);
  digitalWrite(3,HIGH);
  digitalWrite(2,HIGH);
 }
 else if(player_health==1)
 {
  digitalWrite(0,LOW);
  digitalWrite(3,LOW);
  digitalWrite(2,HIGH);
 }
  }
}








}



}








void gameScreen(){
display.clearDisplay();
 display.drawBitmap(player_x,player_y,playerShip, PLAYER_WIDTH,PLAYER_HEIGHT,WHITE);
for (int i = 0; i < MAX_BULLETS; i++) {
    if (bullet[i]) {
      display.drawRect(bullet_x[i], bullet_y[i], BULLET_WIDTH, BULLET_HEIGHT, WHITE);
    }
  }
  for(int i=0; i<MAX_METEOR;i++){
    if(meteor[i]){
     display.drawBitmap(meteor_x[i],meteor_y[i],meteortas,METEOR_WIDTH,METEOR_HEIGHT,WHITE);   
    }
  }
  for(int i=0; i<MAX_AMMO;i++){
    if(ammo_package[i]){
     display.drawCircle(ammo_x[i], ammo_y[i], AMMO_HEIGHT, WHITE);     
    }
  }
  for(int i=0; i<MAX_HP;i++){
    if(hp_package[i]){
     //display.drawCircle(hp_x[i], hp_y[i],HP_HEIGHT, WHITE);    
     display.drawBitmap(hp_x[i],hp_y[i], kalp, HP_WIDTH,HP_HEIGHT,WHITE); 
    }
  }
  for(int i=0; i<MAX_COP;i++){
    if(cop[i]){
      
      display.drawRect(cop_x[i],cop_y[i],COP_WIDTH,COP_HEIGHT,WHITE); 
    }
  }
  display.display();
}

void updtMenu(){
switch(menu){
case 0:
menu=1;
break;
case 1: 
display.clearDisplay();
display.setTextSize(1);            
display.setTextColor(SSD1306_WHITE);   
display.setCursor(0,0);                  
display.println((">Baslat"));
display.setTextSize(1);            
display.setTextColor(SSD1306_WHITE);
display.print(("Zorluk"));

display.display();
  delay(50);
break;
case 2: 
display.clearDisplay();
display.setTextSize(1);            
display.setTextColor(SSD1306_WHITE);  
display.setCursor(0,0);                 
display.println(("Baslat")); 
display.print((">Zorluk"));

display.display();
  delay(50);
break;
case 3:
menu = 2;
break;

}


}
void selectedButton(){
switch(menu){
  case 1:
  menu1();
  break;
  case 2:
  menu2();
  break;
}
}

void menu1(){
display.clearDisplay();
delay(100);


}
void menu2(){

}
void setup() {
 display.begin(SSD1306_SWITCHCAPVCC, 0x3D);
 Serial.begin(9600);
 display.setRotation(3);
 pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3,INPUT_PULLUP);
  pinMode(0,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(2,OUTPUT);
  digitalWrite(0,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(2,HIGH);
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  digitalWrite(12,HIGH);
  digitalWrite(11,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(A2,LOW);
  updtMenu();

  pinMode(LATCH,OUTPUT);
  pinMode(CLK,OUTPUT);
  pinMode(DATA,OUTPUT);
  pinMode(A7,INPUT);
  
}

void loop() {
  if((!digitalRead(A0))&&a==false){
    menu++;
    updtMenu();
    delay(50);
    while(!digitalRead(A0));
  }
  if((!digitalRead(A1))&& a==false){
    menu--;
    updtMenu();
    delay(50);
    while(!digitalRead(A1));
  }
  if(!digitalRead(A3)){
    selectedButton();
    a=true;
    delay(50);
    while(!digitalRead(A3));
  }
  if(analogRead(A7)>512)
{
for(int a=0;a<display.width();a++)
{
  for(int b=0;b<display.height();b++){
    uint16_t color = display.getPixel(a,b);
    if(color==WHITE){
      display.drawPixel(a,b,BLACK);
    }
    else{
      display.drawPixel(a,b,WHITE);
    }
  }
  
}
display.display();
  delay(5000);
}
  potansiyometreDeger = digitalRead(A6);
potansiyometreDeger = map(potansiyometreDeger,0,1023,0,255);
  if(a==true){
update();
gameScreen();
delay(50);
  }
 if(player_health==3){
  digitalWrite(0,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(2,HIGH);
 }
 else if(player_health==2)
 {
  digitalWrite(0,LOW);
  digitalWrite(3,HIGH);
  digitalWrite(2,HIGH);
 }
 else if(player_health==1)
 {
  digitalWrite(0,LOW);
  digitalWrite(3,LOW);
  digitalWrite(2,HIGH);
 }
 
 digitalWrite(LATCH,LOW);
 shiftOut(DATA, CLK, MSBFIRST, ~segment[first]);
 shiftOut(DATA, CLK, MSBFIRST, ~segment[second]);
 shiftOut(DATA, CLK, MSBFIRST, ~segment[third]);
  digitalWrite(LATCH,HIGH);
  





}
