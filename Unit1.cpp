//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdlib.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int x = -7;
int y = -7;
int pointsLeftPlayer = 0;
int pointsRightPlayer = 0;
int numberOfReflections = 0;

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
  if(Key == 0x41) TimerLeftUp->Enabled = true;
  if(Key == 0x5A) TimerLeftDown->Enabled = true;
  if(Key == VK_UP) TimerRightUp->Enabled = true;
  if(Key == VK_DOWN) TimerRightDown->Enabled = true;
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
    x = -x;
    numberOfReflections++;
    }

  // reflection form right paddle
  if((ball->Top - (ball->Width/2) >= paddleRight->Top -10) &&
     (ball->Top - (ball->Width/2) <= paddleRight->Top + paddleRight->Height +10) &&
     (ball->Left >= paddleRight->Left - ball->Width)){
    x = -x;
    numberOfReflections++;
    }

  //lose
  if((ball->Left < 10) || (ball->Left > table->Width - ball->Width -10 )){
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
     numberOfReflectionsLabel->Caption =  "Ilosc odbic: " +
                                       IntToStr(numberOfReflections);

     winerArrow->Visible = true;
     score->Visible = true;
     numberOfReflectionsLabel->Visible = true;
     nextRound->Visible = true;

  }
}
//---------------------------------------------------------------------------



void __fastcall TForm1::nextRoundClick(TObject *Sender)
{
  // set paddles in start position
  paddleLeft->Top = 197;
  paddleRight->Top = 197;
  numberOfReflections = 0;

  // set ball in postion
  // win left player
  if(ball->Left < table->Width/2) {
     ball->Left = paddleRight->Left;
     ball->Top = paddleRight->Top + paddleRight->Width/2;
     x = abs(x);
  // win right player
  } else {
     ball->Left = paddleLeft->Left + paddleLeft->Width;
     ball->Top = paddleLeft->Top + paddleLeft->Width/2;
     x = -abs(x);
  }

  ball->Visible = true;
  winerArrow->Visible = false;
  score->Visible = false;
  numberOfReflectionsLabel->Visible = false;
  nextRound->Visible = false;
  TimerBall->Enabled = true;


}
//---------------------------------------------------------------------------



