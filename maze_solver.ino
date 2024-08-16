#define SATIR 27
#define SUTUN 27

byte trig_pin=9,echo_pin=10;
long sure;
long uzunluk;

const int number_1=2;
const int number_2=3;
const int number_3=4;
const int number_4=5;

const int  pwm_1=6;
const int  pwm_2=11;

int dizi[SATIR][SUTUN]={{0}};

int x_pozisyon=12;
int y_pozisyon=12;

int mesafe_sensor;
int aci_yonu;
int kontrol;

void setup() {

   pinMode(trig_pin,OUTPUT);
   pinMode(echo_pin,INPUT);
   pinMode(number_1,OUTPUT);
   pinMode(number_2,OUTPUT);
   pinMode(number_3,OUTPUT);
   pinMode(number_4,OUTPUT); 
   pinMode(pwm_1,OUTPUT);
   pinMode(pwm_2,OUTPUT);
   
   dizi[0][0]=1;
   aci_yonu=0;
   kontrol=0;

   analogWrite(pwm_1,100); // sağ motor
   analogWrite(pwm_2,100);
}
void loop() 
{
   
   mesafe_sensor = mesafe_sensor_fonk();

   if(mesafe_sensor >= 10)
   {
       if(dizi[y_pozisyon][x_pozisyon + 1] == 0)
       {
           aci_yonu=yon_belirle(aci_yonu);
           hareket(aci_yonu);

       }
       else if(dizi[y_pozisyon][x_pozisyon + 1] == 1)
       {
            aci_yonu +=90;
            aci_yonu=yon_belirle(aci_yonu);
            robotun_donus_hareketi();

            if(dizi[y_pozisyon-1][x_pozisyon]==0 && mesafe_sensor >= 10)
            {
               aci_yonu=yon_belirle(aci_yonu);
               hareket(aci_yonu);
               robotun_ileri_hareketi();
            }
            else
            {
               aci_yonu +=90;
               aci_yonu=yon_belirle(aci_yonu);
               robotun_donus_hareketi(); 

               if(dizi[y_pozisyon][x_pozisyon-1]==0 && mesafe_sensor >= 10)
               {
                  aci_yonu=yon_belirle(aci_yonu);
                  hareket(aci_yonu);
                  robotun_ileri_hareketi();
               }
               else
               {
                  aci_yonu +=90;
                  aci_yonu=yon_belirle(aci_yonu);
                  robotun_donus_hareketi();

                  if(dizi[y_pozisyon +1][x_pozisyon]==0 && mesafe_sensor >= 10)
                  {
                     aci_yonu=yon_belirle(aci_yonu);
                     hareket(aci_yonu);
                     robotun_ileri_hareketi();                    
                  }
                  else
                  {
                      aci_yonu +=90;
                      aci_yonu=yon_belirle(aci_yonu);
                      robotun_donus_hareketi();

                      kontrol=1;
                  }

                  if(kontrol==1)
                  {
                     aci_yonu=yon_belirle(aci_yonu);
                     hareket(aci_yonu);
                     robotun_ileri_hareketi();
                  }                  
               }
            }
       }

       else if (dizi[y_pozisyon][x_pozisyon + 1] == 2)
       {
          aci_yonu +=90;
          aci_yonu=yon_belirle(aci_yonu);
          robotun_donus_hareketi();
       } 
   }

   else
   {
         aci_yonu +=90;
         aci_yonu=yon_belirle(aci_yonu);
         robotun_donus_hareketi();
   }
}


int mesafe_sensor_fonk(void)
{
  digitalWrite(trig_pin,LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin,LOW);
  digitalWrite(echo_pin,HIGH);
  
  sure=pulseIn(echo_pin,HIGH); //LOW ve HIGH komutları arasındaki süreyü us cinsinden hesaplar
  uzunluk=(sure/2)/29.154;// ses sinyalinin bir cm  hareket etmesi için 29.154 us sürer.

  return uzunluk;
}
int yon_belirle(int aci)
{
   int sonuc;

   if(aci < 0)
   {
       sonuc=360 + aci;
   }
   else if(aci >= 360)
   {
       sonuc=aci-360;
   }
   else
   {
       sonuc=aci;
   }
   return sonuc;
}

void hareket(const int aci )
{
    int x_yeni_pozisyon;
    int y_yeni_pozisyon;

    if(aci==0)               // satirda pozistonu koru stunda saga git 
    {
       x_yeni_pozisyon=1;
       y_yeni_pozisyon=0;
    }
    else if(aci==90)         // stunda pozisyonu koru satirda yukari git 
    {
       x_yeni_pozisyon=0;
       y_yeni_pozisyon=-1;
    }
    else if(aci==180)         // satirda pozisyonunu koru stunda sola git
    {
       x_yeni_pozisyon=-1;
       y_yeni_pozisyon=0;    
    }
    else if(aci==270)         // stunda pozisyonunu koru satirda asagi git 
     {
       x_yeni_pozisyon=0;
       y_yeni_pozisyon=1;    
     }

     x_pozisyon +=x_yeni_pozisyon;

     if(x_pozisyon < 0)
     {
        x_pozisyon -=x_yeni_pozisyon;
     }
     else if(x_pozisyon > SATIR)
     {
         x_pozisyon -=x_yeni_pozisyon;
     }

     y_pozisyon +=x_yeni_pozisyon;


     if(y_pozisyon < 0)
     {
        y_pozisyon -=y_yeni_pozisyon;
     }
     else if(y_pozisyon > SATIR)
     {
         y_pozisyon -=y_yeni_pozisyon;
     }     

     dizi[y_pozisyon][x_pozisyon]+=1;
}

void robotun_ileri_hareketi(void)
{
       //robot belirlenen süre kadar ileri gidecektir
       digitalWrite(number_1,LOW);  //sağ motor ileri
       digitalWrite(number_2,HIGH);
       digitalWrite(number_3,LOW);  //sol motor ileri
       digitalWrite(number_4,HIGH);
       delay(365);
       //robot durmasını sağlayan kod dizini
       digitalWrite(number_1,LOW);
       digitalWrite(number_2,LOW);
       digitalWrite(number_3,LOW);
       digitalWrite(number_4,LOW);
       delay(250);      
}

void robotun_donus_hareketi(void)
{
       // robot 90 derece solo donecektir
       digitalWrite(number_1,LOW);  
       digitalWrite(number_2,HIGH);
       digitalWrite(number_3,HIGH);  
       digitalWrite(number_4,LOW);
       delay(255);       
       digitalWrite(number_1,LOW);
       digitalWrite(number_2,LOW);
       digitalWrite(number_3,LOW);
       digitalWrite(number_4,LOW);
       delay(500); 
}
