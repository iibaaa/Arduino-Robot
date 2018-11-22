//
//  Created by Batuhan Aydın on 16.11.2018.
//  Copyright © 2018 i.Batuhan Aydın. All rights reserved.
//  www.ibaydin.com
//  instagram.com/ibaydinn
//

#include <Servo.h>

long data_speed = 115200;

int data;
int data_foot;
int data_head;
int data_mors;
int data_leftarm;
int data_rightarm;
int data_coloreye;
int data_colorfoot;
int data_light1;
int data_light2;



//-----------SERVO HAREKET HASSASİYETİ---------

int head_angle1 = 5; //left-right

//int head_angle2 = 5; //up-down

int arm1_angle = 3;
int arm2_angle = 3;

int dirsek_angle = 3;
int bilek_angle = 3;
int parmak_angle = 2;

//--------------------------------------------



//---------------------------------------------|
//        MANUEL RGB LED RENK AYARLAMA         |
// eyecolor_send(r,g,b) ---------> göz rengi   |
// footcolor_send(r,g,b) --------> ayak renk   |
// 0-255 arası değer vererek renk ayarla       |
//---------------------------------------------|


//-----------------------

int eye_rpin = 6 ;
int eye_gpin = 7;
int eye_bpin = 8;

int foot_rpin = 2;
int foot_gpin = 3;
int foot_bpin = 5;

int led1_pin = 39;
int led2_pin = 13;

int buzzer = 10 ;
//int voice_pin = 20 ;




//----------TIMING-------------
int time1 = 10;          //delay 1
int time2 = 1000;        //delay 2

int mors_dot = 100;   //nokta
int mors_line = 200;  //çizgi

int mors_wait = 100;  //bekleme


//----------------------


//--Servo Tanımlara------Servo Başlangıç Değeri------Servo Pin---------- //

Servo servobas1;         int bas1 = 78 ;           int p_bas1 = 27;
//Servo servobas2;         int bas2 = 90 ;           int p_bas2 = 41;

Servo servosolomuz1;     int solomuz1 = 90 ;       int p_solomuz1 = 22;
Servo servosolomuz2;     int solomuz2 = 90 ;       int p_solomuz2 = 23;
Servo servosoldirsek;    int soldirsek = 90 ;      int p_soldirsek = 24;
Servo servosolbilek;     int solbilek = 90 ;       int p_solbilek = 25;
Servo servosolparmak;    int solparmak = 90 ;      int p_solparmak = 26;

Servo servosagomuz1;     int sagomuz1 = 90 ;       int p_sagomuz1 = 28;
Servo servosagomuz2;     int sagomuz2 = 90 ;       int p_sagomuz2 = 29;
Servo servosagdirsek;    int sagdirsek = 90 ;      int p_sagdirsek = 30;
Servo servosagbilek;     int sagbilek = 90 ;       int p_sagbilek = 31;
Servo servosagparmak;    int sagparmak = 90 ;      int p_sagparmak = 32;

Servo servoayaksol;      int ayaksol_stop = 92;    int p_ayaksol = 36;
Servo servoayaksag;       int ayaksag_stop = 93;    int p_ayaksag = 37 ;

// int p_servofoot_power = 38;
// int p_servofoot_power2 = 40;


void setup()
{
  Serial.begin(data_speed);
  Serial.println("STARTING");
  servo_pin_attach();
  pin_stuation();
  servo_first_position();
  test_mode1();
}


void loop()
{
  while (Serial.available() > 0)
  {
    data = Serial.read();
    switch (data)
    {

      //-------CASE-----

      case 'W': // hareket
        Serial.println("Hareket");
        servoayaksol.write(0);
        servoayaksag.write(0);
        delay(1);
        break;

       case 'S':
       servoayaksol.write(180);
        servoayaksag.write(180);
        delay(1);
        break;

        case 'A':
        servoayaksol.write(180);
        servoayaksag.write(0);
        delay(1);
        break;

        case 'D':
        servoayaksol.write(0);
        servoayaksag.write(180);
        delay(1);
        break;

        case 'V':
        servoayaksol.write(ayaksol_stop);
        servoayaksag.write(ayaksag_stop);
        delay(1);
        break;

        case 'Q':
        soldier_hi();
        break;

        case 'E':
        person_hi();
        break;

        case 'B':
        test_color();
        break;
        
       

      case 'L': // sol kol komutları
        Serial.println("Sol Kol");
        leftarm_move();
        break;

      case 'R': // sağ kol komutları
        Serial.println("Sağ kol");
        rightarm_move();
        break;

      case 'H': // kafa hareket
        Serial.println("Kafa Hareket");
        head_move();
        break;

      case 'M': // mors iletişimi
        Serial.println("Mors Code");
        mors_code();
        break;

      case '1': // göz renk ayarlama
        Serial.println("Göz Renk");
        color_eye();
        break;

      case '2': // ayak renk ayarlama
        Serial.println("Ayak Renk");
        color_foot();
        break;

      case '3': // konuşma
        //  talk_voice();
        break;

      case '4': // ışık 1
        Serial.println("Işık Mode");
        light1_mode();
        break;

      case '5': // ışık 2
        light2_mode();
        break;

      case '6': // özel hareketler
        //   special_moves();
        break;


      case '7': // test başlangıç
        Serial.println("Test Mode Led-Buzzer");
        test_mode1(); // led-buzzer test
        break;


      case '8':
        // test_mode2();
        break;

      case '9':
        servo_angle();
        break;




        //-----CASE END-------
    }
  }
}


void light1_mode()
{
  while (Serial.available() > 0)
  {
    data_light1 = Serial.read();
    switch (data_light1)
    {
      case 'o':
        digitalWrite(led1_pin, HIGH);
        break;

      case 'c':
        digitalWrite(led1_pin, LOW);
        break;
    }
  }
}
void light2_mode()
{
  while (Serial.available() > 0)
  {
    data_light2 = Serial.read();
    switch (data_light2)
    {
      case 'o':
        digitalWrite(led2_pin, HIGH);
        break;

      case 'c':
        digitalWrite(led2_pin, LOW);
        break;
    }
  }
}


void test_color()
{
  eyecolor_send(0,255,255);
  footcolor_send(80,255,255);
  delay(1000);
  eyecolor_send(80,0,255);
  footcolor_send(0,255,0);
  servobas1.write(180);
  delay(1500);
  servobas1.write(0);
  delay(1500);
  servobas1.write(bas1);
  eyecolor_send(0,0,255);
  footcolor_send(0,255,0);
  mors_code_dot();
  mors_code_dot();
  mors_code_line();
  mors_code_wait();
  mors_code_dot();
  mors_code_line();
  mors_code_line();
  servobas1.write(180);
  delay(300);
  servobas1.write(150);
  delay(300);
  servobas1.write(100);
  delay(300);
  servobas1.write(70);
  delay(300);
  servobas1.write(40);
  delay(300);
  servobas1.write(0);
  delay(300);
  servobas1.write(bas1);

}
void test_mode1()
{
  eyecolor_send(0, 255, 255);
  footcolor_send(80, 255, 255);
  delay(500);
  eyecolor_send(80, 255, 0);
  footcolor_send(80, 255, 0);
  delay(500);
  eyecolor_send(0, 0, 0);
  footcolor_send(0, 0, 0);
  delay(1000);
}

void soldier_hi()
{
  servosolomuz1.write(solomuz1);
  servosolomuz2.write(solomuz2);
  servosoldirsek.write(soldirsek);
  servosolbilek.write(soldirsek);
  servosolparmak.write(solparmak);

  servosagomuz1.write(sagomuz1);
  servosagomuz2.write(sagomuz2);
  servosagdirsek.write(sagdirsek);
  servosagbilek.write(sagbilek);
  servosagparmak.write(sagparmak);

  servosolomuz1.write(153);
  servosolomuz2.write(75);
  servosoldirsek.write(90);
  servosolbilek.write(90);
  servosolparmak.write(90);
  servosagomuz1.write(144);
  delay(500);
  servosagomuz1.write(132);
  delay(500);
  
  servosagomuz2.write(50);
  delay(300);
  servosagomuz2.write(40);
  delay(500);

  servosagbilek.write(138);
  delay(500);
  servosagparmak.write(114);
  delay(3000);
  
  servosagomuz2.write(50);
  delay(500);
  servosagomuz2.write(84);
  delay(1000);

  servosolomuz1.write(solomuz1);
  servosolomuz2.write(solomuz2);
  servosoldirsek.write(soldirsek);
  servosolbilek.write(soldirsek);
  servosolparmak.write(solparmak);

  servosagomuz1.write(sagomuz1);
  servosagomuz2.write(sagomuz2);
  servosagdirsek.write(sagdirsek);
  servosagbilek.write(sagbilek);
  servosagparmak.write(sagparmak);
  
}

void person_hi()
{
  servosolomuz1.write(solomuz1);
  servosolomuz2.write(solomuz2);
  servosoldirsek.write(soldirsek);
  servosolbilek.write(soldirsek);
  servosolparmak.write(solparmak);

  servosagomuz1.write(sagomuz1);
  servosagomuz2.write(sagomuz2);
  servosagdirsek.write(sagdirsek);
  servosagbilek.write(sagbilek);
  servosagparmak.write(sagparmak);


  servosagomuz1.write(60);
  servosagomuz2.write(60);
  delay(300);
  servosagomuz1.write(30);
  servosagomuz2.write(36);
  delay(200);
  servosagbilek.write(39);
  servosagparmak.write(115);
  servosolomuz1.write(50);
  delay(300);
 
  servosolomuz1.write(0);
  delay(300);
  servosolomuz2.write(78);
  delay(300);
  servosolomuz2.write(99);
  delay(500);
  servosoldirsek.write(60);
  delay(300);
  servosolparmak.write(58);
  servosolbilek.write(15);
  delay(500);

  servosolomuz2.write(80);
  servosoldirsek.write(40);
  delay(500);
  servosolomuz2.write(100);
  servosoldirsek.write(114);
  delay(500);
  servosolomuz2.write(80);
  servosoldirsek.write(40);
  delay(500);
  servosolomuz2.write(100);
  servosoldirsek.write(114);
  delay(500);
  servosolomuz2.write(80);
  servosoldirsek.write(40);
  delay(500);
  servosolomuz2.write(100);
  servosoldirsek.write(114);
  delay(500);
  servosolomuz2.write(80);
  servosoldirsek.write(40);
  delay(500);
  servosolomuz2.write(100);
  servosoldirsek.write(114);
  delay(500);
  servosolomuz2.write(80);
  servosoldirsek.write(40);
  delay(500);
  servosolomuz2.write(100);
  servosoldirsek.write(114);
  delay(2000);

  servosolomuz1.write(solomuz1);
  servosolomuz2.write(solomuz2);
  servosoldirsek.write(soldirsek);
  servosolbilek.write(soldirsek);
  servosolparmak.write(solparmak);

  servosagomuz1.write(sagomuz1);
  servosagomuz2.write(sagomuz2);
  servosagdirsek.write(sagdirsek);
  servosagbilek.write(sagbilek);
  servosagparmak.write(sagparmak);
  
  
  
  
  
}








//-**********RGB LED RENK SEÇİM*******
void color_eye()
{
  while (Serial.available() > 0)
  {
    data_coloreye = Serial.read();
    switch (data_coloreye)
    {
      //-------SWICTH----------------

      case 'n': //------ eye disable
        eyecolor_send(0, 0, 0);
        break;

      case 'k': //------ kırmızı
        eyecolor_send(255, 0, 0);
        break;

      case 'y': //------- yeşil
        eyecolor_send(0, 255, 0);
        break;

      case 'm': //--------mavi
        eyecolor_send(0, 0, 255);
        break;

      case 'c': //-------cyan
        eyecolor_send(0, 255, 255);
        break;

      case 's': //--------sarı
        eyecolor_send(255, 255, 0);
        break;

      case 'p': //--------pembe
        eyecolor_send(255, 0, 255);
        break;

      case 'b': //--------beyaz
        eyecolor_send(255, 255, 255);
        break;

        //------SWITCH END-------
    }
  }
}

void color_foot()
{
  while (Serial.available() > 0)
  {
    data_colorfoot = Serial.read();
    switch (data_colorfoot)
    {
      //-------SWICTH----------------

      case 'n': //------ eye disable
        footcolor_send(0, 0, 0);
        break;

      case 'k': //------ kırmızı
        footcolor_send(255, 0, 0);
        break;

      case 'y': //------- yeşil
        footcolor_send(0, 255, 0);
        break;

      case 'm': //--------mavi
        footcolor_send(0, 0, 255);
        break;

      case 'c': //-------cyan
        footcolor_send(0, 255, 255);
        break;

      case 's': //--------sarı
        footcolor_send(80, 255, 0);
        break;

      case 'p': //--------pembe
        footcolor_send(100, 0, 255);
        break;

      case 'b': //--------beyaz
        footcolor_send(255, 255, 255);
        break;

        //------SWITCH END-------
    }
  }
}
//-***********************************


void eyecolor_send(int eye_red, int eye_green, int eye_blue) //RGB LED EYE RENK GÖNDERME
{
  analogWrite(eye_rpin, 255 - eye_red);
  analogWrite(eye_gpin, 255 - eye_green);
  analogWrite(eye_bpin, 255 - eye_blue);
  delay(1);
}

void footcolor_send(int foot_red, int foot_green, int foot_blue) //RGB LED FOOT RENK GÖNDERME
{
  analogWrite(foot_rpin, foot_red);
  analogWrite(foot_gpin, foot_green);
  analogWrite(foot_bpin, foot_blue);
  delay(1);
}




void leftarm_move() // -----SOL KOL HAREKET--------
{
  while (Serial.available() > 0)
  {
    data_leftarm = Serial.read();
    switch (data_leftarm)
    {

      //-----------SWİTCH---------------

      //-----------SOL OMUZ 1-----------
      case 'a':
        delay(time1);
        if (solomuz1 <= 180)
        {
          solomuz1 = (solomuz1 + arm1_angle);
          servosolomuz1.write(solomuz1);
        }
        break;

      case 'q':
        delay(time1);
        if (solomuz1 >= 0)
        {
          solomuz1 = (solomuz1 - arm1_angle);
          servosolomuz1.write(solomuz1);
        }
        break;


      //----------SOL OMUZ 2--------------
      case 's':
        delay(time1);
        if (solomuz2 <= 180)
        {
          solomuz2 = (solomuz2 + arm2_angle);
          servosolomuz2.write(solomuz2);
        }
        break;

      case 'w':
        delay(time1);
        if (solomuz2 >= 0)
        {
          solomuz2 = (solomuz2 - arm2_angle);
          servosolomuz2.write(solomuz2);
        }
        break;


      //----------SOL DİRSEK--------------
      case 'd':
        delay(time1);
        if (soldirsek <= 180)
        {
          soldirsek = (soldirsek + dirsek_angle);
          servosoldirsek.write(soldirsek);
        }
        break;

      case 'e':
        delay(time1);
        if (soldirsek >= 0)
        {
          soldirsek = (soldirsek - dirsek_angle);
          servosoldirsek.write(soldirsek);
        }
        break;


      //----------SOL BİLEK--------------
      case 'f':
        delay(time1);
        if (solbilek <= 180)
        {
          solbilek = (solbilek + bilek_angle);
          servosolbilek.write(solbilek);
        }
        break;

      case 'r':
        delay(time1);
        if (solbilek >= 0)
        {
          solbilek = (solbilek - bilek_angle);
          servosolbilek.write(solbilek);
        }
        break;


      //----------SOL PARMAK--------------
      case 'z':
        delay(time1);
        if (solparmak <= 180)
        {
          solparmak = (solparmak + parmak_angle);
          servosolparmak.write(solparmak);
        }
        break;

      case 'x':
        delay(time1);
        if (solparmak >= 0)
        {
          solparmak = (solparmak - parmak_angle);
          servosolparmak.write(solparmak);
        }
        break;
        //------------SWİTCH END------------------
    }
  }
}

void rightarm_move() // -----SAĞ KOL HAREKET--------
{
  while (Serial.available() > 0)
  {
    data_rightarm = Serial.read();
    switch (data_rightarm)
    {

      //-----------SWİTCH---------------

      //-----------SAĞ OMUZ 1-----------
      case 'p':
        delay(time1);
        if (sagomuz1 <= 180)
        {
          sagomuz1 = (sagomuz1 + arm1_angle);
          servosagomuz1.write(sagomuz1);
        }
        break;

      case 'l':
        delay(time1);
        if (sagomuz1 >= 0)
        {
          sagomuz1 = (sagomuz1 - arm1_angle);
          servosagomuz1.write(sagomuz1);
        }
        break;


      //----------SAĞ OMUZ 2--------------
      case 'o':
        delay(time1);
        if (sagomuz2 <= 180)
        {
          sagomuz2 = (sagomuz2 + arm2_angle);
          servosagomuz2.write(sagomuz2);
        }
        break;

      case 'k':
        delay(time1);
        if (sagomuz2 >= 0)
        {
          sagomuz2 = (sagomuz2 - arm2_angle);
          servosagomuz2.write(sagomuz2);
        }
        break;


      //----------SAĞ DİRSEK--------------
      case 'i':
        delay(time1);
        if (sagdirsek <= 180)
        {
          sagdirsek = (sagdirsek + dirsek_angle);
          servosagdirsek.write(sagdirsek);
        }
        break;

      case 'j':
        delay(time1);
        if (sagdirsek >= 0)
        {
          sagdirsek = (sagdirsek - dirsek_angle);
          servosagdirsek.write(sagdirsek);
        }
        break;


      //----------SAĞ BİLEK--------------
      case 'u':
        delay(time1);
        if (sagbilek <= 180)
        {
          sagbilek = (sagbilek + bilek_angle);
          servosagbilek.write(sagbilek);
        }
        break;

      case 'h':
        delay(time1);
        if (sagbilek >= 0)
        {
          sagbilek = (sagbilek - bilek_angle);
          servosagbilek.write(sagbilek);
        }
        break;


      //----------SOL PARMAK--------------
      case 'm':
        delay(time1);
        if (sagparmak <= 180)
        {
          sagparmak = (sagparmak + parmak_angle);
          servosagparmak.write(sagparmak);
        }
        break;

      case 'n':
        delay(time1);
        if (sagparmak >= 0)
        {
          sagparmak = (sagparmak - parmak_angle);
          servosagparmak.write(sagparmak);
        }
        break;
        //------------SWİTCH END------------------
    }
  }
}

void head_move() // ----BAŞ HAREKET--------
{
  
  while (Serial.available() > 0)
  {
    data_head = Serial.read();
    switch (data_head)
    {
      //---------CASE-----------

      case 't': //
        delay(time1);
        if (bas1 <= 180)
        {
          bas1 = (bas1 + head_angle1);
          servobas1.write(bas1);
        }
        break;

      case 'y':
        delay(time1);
        if (bas1 >= 0)
        {
          bas1 = (bas1 - head_angle1);
          servobas1.write(bas1);
        }
        break;
        /*
              case 'g':
                delay(time1);
                if (bas2 <= 180)
                {
                  bas2 = (bas2 + head_angle2);
                  servobas2.write(bas2);
                }
                break;

              case 'h':

                delay(time1);
                if (bas2 >= 0)
                {
                  bas2 = (bas2 - head_angle2);
                  servobas2.write(bas2);
                }
                break;
        */
        //------CASE END-------
    }
  }
}

/*
void foot_move() // ----AYAK HAREKET------
{
  while (Serial.available() > 0)
  {
    data_foot = Serial.read();
    switch (data_foot)
    {
      case 'w': // ileri
        Serial.println("ileri");
        //     digitalWrite(p_servofoot_power, HIGH);
        //     digitalWrite(p_servofoot_power2, LOW);
        servoayaksol.write(0);
        servoayaksag.write(0);
        delay(1);
        break;

      case 's':
        Serial.println("geri");
        //      digitalWrite(p_servofoot_power, HIGH);
        //      digitalWrite(p_servofoot_power2, LOW);
        servoayaksol.write(180);
        servoayaksag.write(180);
        delay(1);
        break;

      case 'a':
        Serial.println("sol");
        //       digitalWrite(p_servofoot_power, HIGH);
        //       digitalWrite(p_servofoot_power2, LOW);
        servoayaksol.write(180);
        servoayaksag.write(0);
        delay(1);
        break;

      case 'd':
        Serial .println("sağ");
        //     digitalWrite(p_servofoot_power, HIGH);
        //     digitalWrite(p_servofoot_power2, LOW);
        servoayaksol.write(0);
        delay(1);
        break;

      case 'v':
        Serial.println("dur");
        servoayaksol.write(ayaksol_stop);
        servoayaksag.write(ayaksag_stop);
        delay(1);
        //     digitalWrite(p_servofoot_power, LOW);
        //     digitalWrite(p_servofoot_power2, LOW);
        break;
    }
  }
}
*/



void mors_code() // ----MORS CODE SENDER--------
{
  while (Serial.available() > 0)
  {
    data_mors = Serial.read();
    switch (data_mors)
    {
      //--------------SWITCH----------------

      case '.':
        mors_code_dot();
        break;

      case '-':
        mors_code_line();
        break;


      case '/':
        mors_code_wait();
        break;
        //---------------SWITCH END------------

    }
  }
}

void servo_angle()
{
  Serial.println("|------------------------|");
  Serial.println("|    Servo Dereceleri    |");
  Serial.println("|------------------------|");
  Serial.print("|  >Kafa = ");
  Serial.print(bas1);
  Serial.println("            |");
  Serial.println("|------------------------|");
  //------------------------------------------

  Serial.print("|  >Sol Omuz1 = ");
  Serial.print(solomuz1);
  Serial.println("       |");
  //------------------------------------------

  Serial.print("|  >Sol Omuz2 = ");
  Serial.print(solomuz2);
  Serial.println("       |");
  //------------------------------------------

  Serial.print("|  >Sol Dirsek = ");
  Serial.print(soldirsek);
  Serial.println("      |");
  //------------------------------------------

  Serial.print("|  >Sol Bilek = ");
  Serial.print(solbilek);
  Serial.println("       |");
  //-----------------------------------------

  Serial.print("|  >Sol Parmak = ");
  Serial.print(solparmak);
  Serial.println("      |");
  //------------------------------------------

  Serial.println("|------------------------|");

  Serial.print("|  >Sag Omuz1 = ");
  Serial.print(sagomuz1);
  Serial.println("       |");
  //------------------------------------------

  Serial.print("|  >Sag Omuz2 = ");
  Serial.print(sagomuz2);
  Serial.println("       |");
  //------------------------------------------

  Serial.print("|  >Sag Dirsek = ");
  Serial.print(sagdirsek);
  Serial.println("      |");
  //------------------------------------------

  Serial.print("|  >Sag Bilek = ");
  Serial.print(sagbilek);
  Serial.println("       |");
  //-----------------------------------------

  Serial.print("|  >Sag Parmak = ");
  Serial.print(sagparmak);
  Serial.println("      |");
  //------------------------------------------
  Serial.println("|------------------------|");




}




//--------------------------------------------------------
void mors_code_dot() // mors kodu nokta
{
  digitalWrite(buzzer, HIGH);
  delay(mors_dot);
  digitalWrite(buzzer, LOW);
  delay(mors_wait);
}
void mors_code_line() // mors kodu çizgi
{
  digitalWrite(buzzer, HIGH);
  delay(mors_line);
  digitalWrite(buzzer, LOW);
  delay(mors_wait);
}
void mors_code_wait() // mors kodu bekle
{
  digitalWrite(buzzer, LOW);
  delay(50);
  delay(mors_wait);
  delay(mors_wait);
  delay(mors_wait);
}
//--------------------------------------------------------


//-------------------TEK SEFER-----------------------------------------
//----------------KULLANILACAKLAR--------------------------------------
void servo_first_position() //SERVO BAŞLANGIÇ KONUMLARI-------------
{
  //-------SERVO BAŞLANGIÇ KONUMLARI----------
  servobas1.write(bas1);
  //  servobas2.write(bas2);

  servosolomuz1.write(solomuz1);
  servosolomuz2.write(solomuz2);
  servosoldirsek.write(soldirsek);
  servosolbilek.write(soldirsek);
  servosolparmak.write(solparmak);

  servosagomuz1.write(sagomuz1);
  servosagomuz2.write(sagomuz2);
  servosagdirsek.write(sagdirsek);
  servosagbilek.write(sagbilek);
  servosagparmak.write(sagparmak);

  servoayaksol.write(ayaksol_stop);
  servoayaksag.write(ayaksag_stop);
  delay(500);
}

void servo_pin_attach() //Servo pin tanımlama-----------------------
{

  //-----------SERVO PİN TANIMLAMA----------------
  servobas1.attach(p_bas1);
  //  servobas2.attach(p_bas2);

  servosolomuz1.attach(p_solomuz1);
  servosolomuz2.attach(p_solomuz2);
  servosoldirsek.attach(p_soldirsek);
  servosolbilek.attach(p_solbilek);
  servosolparmak.attach(p_solparmak);

  servosagomuz1.attach(p_sagomuz1);
  servosagomuz2.attach(p_sagomuz2);
  servosagdirsek.attach(p_sagdirsek);
  servosagbilek.attach(p_sagbilek);
  servosagparmak.attach(p_sagparmak);

  servoayaksol.attach(p_ayaksol);
  servoayaksag.attach(p_ayaksag);
  //-------------------------------------------
}

void pin_stuation() //Diğer şeyler pin  output-input---------------
{
  //------Led-Buzzer-Ses vb. Pin OUTPUT-INPUT -----------------
  pinMode(eye_rpin, OUTPUT);
  pinMode(eye_gpin, OUTPUT);
  pinMode(eye_bpin, OUTPUT);
  //------------
  pinMode(foot_rpin, OUTPUT);
  pinMode(foot_gpin, OUTPUT);
  pinMode(foot_bpin, OUTPUT);
  //-------------
  pinMode(led1_pin, OUTPUT);
  pinMode(led2_pin, OUTPUT);
  //-------------
  pinMode(buzzer, OUTPUT);
  //  pinMode(voice_pin, OUTPUT);
  //------------

  //  pinMode(p_servofoot_power, OUTPUT);
  //  pinMode(p_servofoot_power2, OUTPUT);

  //------------------------------------------
}

