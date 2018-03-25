//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdlib.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int x = -6;
int y = -6;
int pointsLeftPlayer = 0;
int pointsRightPlayer = 0;
int setsLeftPlayer = 0;
int setsRightPlayer = 0;
int numberOfReflections = 0;
bool pause = false;


void accelerateBall(){
}

void increaseAngle(){

}

void reduceAngle(){

}

void newService(){
  // set paddles in start position
 Form1->paddleLeft->Top = (Form1->table->Height/2) - (Form1->paddleLeft->Height/2);
  Form1->paddleRight->Top = (Form1->table->Height/2) - (Form1->paddleRight->Height/2);
  numberOfReflections = 0;

  // set ball in postion
  // win right player
  if(Form1->ball->Left < Form1->table->Width/2) {
     Form1->ball->Left = Form1->paddleRight->Left - Form1->ball->Width -10;
     Form1->ball->Top = Form1->paddleRight->Top + Form1->paddleRight->Width/2;
     x = -abs(x);

  // win left player
  } else {
     Form1->ball->Left = (Form1->paddleLeft->Left + Form1->paddleLeft->Width + 10);
     Form1->ball->Top = Form1->paddleLeft->Top + Form1->paddleLeft->Width/2;
     x = abs(x);
  }

  Form1->ball->Visible = true;
  Form1->winerArrow->Visible = false;
  Form1->nextRound->Visible = false;
  Form1->winerLabel->Visible = false;
  Form1->TimerBall->Enabled = true;
  x = -6;
  y = -6;
}

void newGame1(){
  pointsLeftPlayer = 0;
  pointsRightPlayer = 0;
  setsLeftPlayer = 0;
  setsRightPlayer = 0;
  Form1->newGameBtn->Visible = false;
  newService();
  Form1->score->Caption =  IntToStr(pointsLeftPlayer) +
                       " : " + IntToStr(pointsRightPlayer);
  Form1->sets->Caption =  IntToStr(setsLeftPlayer) +
                       " : " + IntToStr(setsRightPlayer);


}

void setsControle(){
    if( pointsLeftPlayer >= 6 && (pointsLeftPlayer - pointsRightPlayer >= 2)){
      pointsLeftPlayer = 0;
      pointsRightPlayer = 0;
      Form1->winerLabel->Caption =
      "Set wygra³ gracz po lewej stronie \n <<<<<<";
      Form1->winerLabel->Visible = true;
      setsLeftPlayer++;
      Form1->score->Caption =  IntToStr(pointsLeftPlayer) +
                       " : " + IntToStr(pointsRightPlayer);
      Form1->sets->Caption =  IntToStr(setsLeftPlayer) +
                       " : " + IntToStr(setsRightPlayer);
    }

    if( pointsRightPlayer >= 6 && (pointsRightPlayer - pointsLeftPlayer >= 2)){
      pointsLeftPlayer = 0;
      pointsRightPlayer = 0;
      Form1->winerLabel->Caption =
            "Set wygra³ gracz po prawej stronie \n >>>>>>";
      Form1->winerLabel->Visible = true;
      setsRightPlayer++;
      Form1->score->Caption =  IntToStr(pointsLeftPlayer) +
                       " : " + IntToStr(pointsRightPlayer);
      Form1->sets->Caption =  IntToStr(setsLeftPlayer) +
                       " : " + IntToStr(setsRightPlayer);
    }

    if(abs(setsLeftPlayer - setsRightPlayer) >=2 ||
       setsLeftPlayer >= 3 || setsRightPlayer >= 3){
      Form1->winerLabel->Caption =
      "Mecz zakoñczy³ siê wynikiem " + IntToStr(setsLeftPlayer) +
       " : " + IntToStr(setsRightPlayer);
      Form1->winerLabel->Visible = true;
      Form1->nextRound->Visible = false;
      Form1->newGameBtn->Visible = true;
      pointsLeftPlayer = 0;
      pointsRightPlayer = 0;
      setsLeftPlayer = 0;
      setsRightPlayer = 0;
    }
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TForm1::TimerLeftUpTimer(TObject *Sender)
{
   if(paddleLeft->Top >= 10)  paddleLeft->Top -= 9;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TimerLeftDownTimer(TObject *Sender)
{
  if(paddleLeft->Top <= table->Height - paddleLeft->Height - 10)
   paddleLeft->Top += 9;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
 if(pause == false){
    if(Key == 0x41) TimerLeftUp->Enabled = true;
    if(Key == 0x5A) TimerLeftDown->Enabled = true;
    if(Key == VK_UP) TimerRightUp->Enabled = true;
    if(Key == VK_DOWN) TimerRightDown->Enabled = true;
  }

  if(Key == 0x50) {
     if(pause == false){
       pause = true;
       TimerBall->Enabled = false;
     } else {
       pause = false;
       TimerBall->Enabled = true;
     }
  }

  if(Key == VK_SPACE  && nextRound->Visible) newService();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if(Key == 0x41) TimerLeftUp->Enabled = false;
  if(Key == 0x5A) TimerLeftDown->Enabled = false;
  if(Key == VK_UP) TimerRightUp->Enabled = false;
  if(Key == VK_DOWN) TimerRightDown->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TimerRightUpTimer(TObject *Sender)
{
  if(paddleRight->Top >= 10)  paddleRight->Top -= 9;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TimerRightDownTimer(TObject *Sender)
{
  if(paddleRight->Top <= table->Height - paddleRight->Height - 10)
   paddleRight->Top += 9;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TimerBallTimer(TObject *Sender)
{
  ball->Left += x;
  ball->Top += y;

  // top bottom ball reflection
  if(ball->Top <= 10) y = -y;
  if(ball->Top >= table->Height - ball->Height - 10) y = -y;

  // reflection form left paddle
  if((ball->Top - (ball->Width/2) >= paddleLeft->Top-10) &&
     (ball->Top - (ball->Width/2) <= paddleLeft->Top + paddleLeft->Height +10) &&
     (ball->Left <= paddleLeft->Left + paddleLeft->Width)){
     //top part of paddle
     if(ball->Top - (ball->Width/2) >= paddleLeft->Top-10 &&
        ball->Top - (ball->Width/2) <= paddleLeft->Top + paddleLeft->Height/3){
         if(y <= 0) {
            if(abs(x) < 10) y -= 2;
            if(abs(x) > 4) x += 2;
          } else {
            y += 2;
            x += 2;
          }

        }
     //middle part of paddle
     if(ball->Top - (ball->Width/2) > paddleLeft->Top + paddleLeft->Height/3 &&
        ball->Top - (ball->Width/2) <= paddleLeft->Top + (paddleLeft->Height/3)*2){
        if(y <= 0) {
            y += 1;
            if(abs(x) < 10) x -= 2;
          } else {
            y -= 1;
            x -= 2;
          }

        }
     //bottom parto of paddle
     if(ball->Top - (ball->Width/2) > paddleLeft->Top + (paddleLeft->Height/3)*2 &&
        ball->Top - (ball->Width/2) <= paddleLeft->Top + paddleLeft->Height +10){
         if(y <= 0) {
            y += 2;
            if(abs(x) > 4)x += 2;
          } else {
            if(abs(x) < 10) y -= 2;
            x += 2;
          }
        }
    x = -x;
    numberOfReflections++;
    numberOfReflectionsLabel->Caption = IntToStr(numberOfReflections);
    }

  // reflection form right paddle
  if((ball->Top - (ball->Width/2) >= paddleRight->Top -10) &&
     (ball->Top - (ball->Width/2) <= paddleRight->Top + paddleRight->Height +10) &&
     (ball->Left >= paddleRight->Left - ball->Width)){
    x = -x;
    numberOfReflections++;
    numberOfReflectionsLabel->Caption =  IntToStr(numberOfReflections);
    }

  //lose
  if((ball->Left < paddleLeft->Left + paddleLeft->Width -10) ||
     (ball->Left + ball->Width > paddleRight->Left +10)){
     TimerBall->Enabled = false;
     ball->Visible = false;


     if(ball->Left < table->Width/2) {
      pointsRightPlayer++;
      winerArrow->Caption = "Punkt zdoby³ gracz po prawej stronie   ->";
     } else {
      pointsLeftPlayer++;
      winerArrow->Caption = "<-  Punkt zdoby³ gracz po lewej stronie";
     }
     score->Caption =  IntToStr(pointsLeftPlayer) +
                       " : " + IntToStr(pointsRightPlayer);
     setsControle();

     winerArrow->Visible = true;
     nextRound->Visible = true;

  }
}
//---------------------------------------------------------------------------



void __fastcall TForm1::nextRoundClick(TObject *Sender)
{
  newService();
}
//---------------------------------------------------------------------------




void __fastcall TForm1::pauseGameClick(TObject *Sender)
{
 if(pause == false){
   pause = true;
   TimerBall->Enabled = false;
 } else {
   pause = false;
   TimerBall->Enabled = true;
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
  pauseGame->Caption = "Wstrzymaj grê \n (p)";
  nextRound->Caption = "Kolejny serw (spacja)";

}
//---------------------------------------------------------------------------

void __fastcall TForm1::newGameBtnClick(TObject *Sender)
{
 newGame1();

}
//---------------------------------------------------------------------------

void __fastcall TForm1::newGameClick(TObject *Sender)
{
 newGame1();
}
//---------------------------------------------------------------------------

