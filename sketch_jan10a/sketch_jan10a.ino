uint8_t i,veri,eskiveri,dizi[8];
int8_t kalan;
uint32_t kuzeyaci;
#include<liquidCrystal.h>
int encoder_sol=2;
int encoder_sag=3;
int motor_sol=4;
int motor_sag=5;
unsigned long solplus=0;
unsigned long sagplus=0;
unsigned long oncekizaman=0;
bool ilk_deger_okundu=false;

liquidCrystal lcd(45,43,41,39,37,35);

int hız_normal=127;//%50 pwm 255*0.5
int hız_hızlı=178;//%40




void setup() {
  pinMode(encoder_sol,OUTPUT);
  pinMode(enoder_sag,OUTPUT);
   pinMode(motor_sol,OUTPUT);
  pinMode(motor_sag,OUTPUT);
  atttachInterrupt(2,solsayac,RISING);
  attachInterrupt(3,sagsayac,RISING);
  //başlangıçta
  analogWrite(motorsol,hız_normal);
  analogWrite(motorsag,hız_normal);
  
  serial.begin(230400);
  serial.begin(9600);

lcd.begin(16,2);
lcd.clear();
for(int i=35;i<=45;i++){
  pinmode(i,OUTPUT);
}



  )

}

void loop() {
  if(serial.available()){
    veri=serial1.read();
  
    if(veri=='A' && eskiveri=='G'){
      kalan=37;
    }
    else{
      if(kalan>0){
        dizi[37-kalan]=veri;
        kalan--;
      }
    }
    else if(kalan==0){
      if(!ilk_deger_okundu){
        ilkdogu  = dogu;
        ilkkuzey = kuzey;
        ilk_deger_okundu = true;
    }

    sondogu  = dogu  - ilkdogu;
    sonkuzey = kuzey - ilkkuzey;

    
serial.print("saat:");
for(i=1;i=<7;i++){
  dizi[i]-=48;

  //serial.Write(dizi[i]);
 saat=10*dizi[1]+dizi[2];

 dakika=10*dizi[3]+dizi[4];
 saniye=10*dizi[5]+dizi[6];
 lcd.print(saat);
 lcd.print(":");
 lcd.print(dakika);
 lcd.print(":");
 lcd.print();
}
  for(i=11;i<21;i++){
  dizi[i]-=48;//Klavyeden gelen '0' karakterinin bilgisayardaki sayısal değeri 48'dir. Bundan 48 çıkararak gerçek 0 sayısına ulaşır. 
  for(i=24;i<35;i++)//enlemin derece kısmı 3 haneli olduğu için 
  dizi[i]-=48;

kuzeyderece=10*dizi[11]+dizi[12];//derece hesabı
kuzeydakika=1000000*dizi[13]+100000*dizi[14]+10000*dizi[16]+1000*dizi[17]+100*dizi[18]+10*dizi[19];
kuzey=6000000*kuzeyderece+kuzeydakika;//1derece=60dakika
kuzeyaci=(float)kuzeyderece+(((float)kuzeydakika)/6000000.0);
kuzeyaci*=0.0174532925199432957690768489;//enlem radyan pi/180

doguderece=100*dizi[24]+10*dizi[25]+dizi[26];//derecenin 3 hanesi
dogudakika=1000000*dizi[27]+100000*dizi[28]+10000*dizi[30]+100*dizi[31]+100*dizi[32]+10*dizi[33];//dakikanın hanesi
dogu=6000000*doguderece+dogudakika;// tam sayı ama  çarpınca küsürat floatta çevirmessek 
serial.print((uint32_t)(1.852*(float)kuzey));//5. noktadan sonra her hane 1.852 cm  denk gelir. 1 deniz mili=1.852cm
dogu=((uint32_t)(((float)dogu)*cos(kuzeyaci)*1.852);

kalan--;// kalan ifin içine girereken 0 şimdi -1 oldu
}
    }
    
    }
      eskiveri=veri;
  
    serial.print(dogu:)
    serial.print('sondogu');
    serial.print(kuzey);
    serial.print('sonkuzey');


  }
  if(millis()-oncekizaman>100){
    unsigned long anliksol=solplus;
    unsigned long anliksag=sağplus;
  }
  if(anliksol>anliksag){
    analogWrite(MOT_SOL, HIZ_NORMAL); // %50 PWM
      analogWrite(MOT_SAG, HIZ_HIZLI);  // %70 PWM
  }
  else if(anliksag>anliksol){
    nalogWrite(MOT_SOL, HIZ_HIZLI); // %70 PWM
      analogWrite(MOT_SAG, HIZ_NORMAL); 
  }
  else{
     analogWrite(MOT_SOL, HIZ_NORMAL);
      analogWrite(MOT_SAG, HIZ_NORMAL);
  }
  oncekizaman=millis();


}
void solsayac(){
  solpuls++;
}
void sagsayac(){
  sagplus++;
}

