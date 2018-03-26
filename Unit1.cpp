//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdlib.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

 // [speed][angle][x,y]
int movement[6][6][2] = {{{7, 0},{7, 2},{6, 3},{5, 5},{3, 6},{2, 7}},
                         {{9, 0},{8, 3},{7, 5},{6, 6},{5, 7},{3, 8}},
                         {{10,0},{9, 3},{8, 6},{7, 7},{6, 8},{3, 9}},
                         {{11,0},{10,5},{9, 7},{8, 8},{7, 9},{5,10}},
                         {{12,0},{11,6},{10,8},{9, 9},{8,10},{6,11}},
                         {{14,0},{12,7},{11,9},{10,10},{9,11},{7,12}}};
int x = movement[0][1][0];
int y = movement[0][1][1];
int ballSpeed = 0;
int ballAngle = 3;
int pointsLeftPlayer = 0;
int pointsRightPlayer = 0;
int setsLeftPlayer = 0;
int setsRightPlayer = 0;
int numberOfReflections = 0;
bool pause = false;


void accelerateBall(int ballDirectionY){
  int ballDirectionX = 1;
  if(Form1->ball->Left > Form1->table->Width/2) ballDirectionX = -1;
  ballSpeed += 2;
  ballAngle--;
  if(ballAngle < 0) ballAngle = 0;
  if(ballSpeed > 5) ballSpeed = 5;
  x = movement[ballSpeed][ballAngle][0] * ballDirectionX;
  y = movement[ballSpeed][ballAngle][1] * ballDirectionY;
  Form1->speedLabel->Caption = ballSpeed +1;
  Form1->angleLabel->Caption = ballAngle;
}

void increaseAngle(int ballDirectionY){
  int ballDirectionX = 1;
  if(Form1->ball->Left > Form1->table->Width/2) ballDirectionX = -1;
  ballAngle += 2;
  //ballSpeed--;
  if(ballAngle > 5) ballAngle = 5;
  if(ballSpeed < 0) ballSpeed = 0;
  x = movement[ballSpeed][ballAngle][0] * ballDirectionX;
  y = movement[ballSpeed][ballAngle][1] * ballDirectionY;
  Form1->speedLabel->Caption = ballSpeed +1;
  Form1->angleLabel->Caption = ballAngle;
}

void reduceAngle(int ballDirectionY){
  int ballDirectionX = 1;
  if(Form1->ball->Left > Form1->table->Width/2) ballDirectionX = -1;
  ballAngle -= 2;
  //ballSpeed--;
  if(ballAngle < 0) {
     ballAngle = 1;
     ballDirectionY *= -1;
  }
  if(ballSpeed < 0) ballSpeed = 0;
  x = movement[ballSpeed][ballAngle][0] * ballDirectionX;
  y = movement[ballSpeed][ballAngle][1] * ballDirectionY;
  Form1->speedLabel->Caption = ballSpeed +1;
  Form1->angleLabel->Caption = ballAngle;
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

  // win left player
  } else {
     Form1->ball->Left = (Form1->paddleLeft->Left + Form1->paddleLeft->Width + 10);
     Form1->ball->Top = Form1->paddleLeft->Top + Form1->paddleLeft->Width/2;
  }

  Form1->ball->Visible = true;
  Form1->winerArrow->Visible = false;
  Form1->nextRound->Visible = false;
  Form1->winerLabel->Visible = false;
  Form1->TimerBall->Enabled = true;
  x = movement[0][3][0];
  y = movement[0][3][1];
  ballSpeed = 5;
  ballAngle = 3;
  Form1->speedLabel->Caption = ballSpeed +1;
  Form1->angleLabel->Caption = ballAngle;
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
         if(y < 0) {
            reduceAngle(-1);
          } else {
            increaseAngle(1);
          }

        }
     //middle part of paddle
     if(ball->Top - (ball->Width/2) > paddleLeft->Top + paddleLeft->Height/3 &&
        ball->Top - (ball->Width/2) <= paddleLeft->Top + (paddleLeft->Height/3)*2){
        if(y < 0) {
           accelerateBall(-1);
          } else {
           accelerateBall(1);
          }

        }
     //bottom parto of paddle
     if(ball->Top - (ball->Width/2) > paddleLeft->Top + (paddleLeft->Height/3)*2 &&
        ball->Top - (ball->Width/2) <= paddleLeft->Top + paddleLeft->Height +10){
         if(y < 0) {
           increaseAngle(-1);
          } else {
           reduceAngle(1);
          }
        }
      numberOfReflections++;
      numberOfReflectionsLabel->Caption =  IntToStr(numberOfReflections);
    }

  // reflection form right paddle
  if((ball->Top - (ball->Width/2) >= paddleRight->Top -10) &&
     (ball->Top - (ball->Width/2) <= paddleRight->Top + paddleRight->Height +10) &&
     (ball->Left >= paddleRight->Left - ball->Width)){
     //top part of paddle
     if(ball->Top - (ball->Width/2) >= paddleRight->Top-10 &&
        ball->Top - (ball->Width/2) <= paddleRight->Top + paddleRight->Height/3){
         if(y < 0) {
            reduceAngle(-1);
          } else {
            increaseAngle(1);
          }

        }
     //middle part of paddle
     if(ball->Top - (ball->Width/2) > paddleRight->Top + paddleRight->Height/3 &&
        ball->Top - (ball->Width/2) <= paddleRight->Top + (paddleRight->Height/3)*2){
        if(y < 0) {
           accelerateBall(-1);
          } else {
           accelerateBall(1);
          }

        }
     //bottom parto of paddle
     if(ball->Top - (ball->Width/2) > paddleRight->Top + (paddleRight->Height/3)*2 &&
        ball->Top - (ball->Width/2) <= paddleRight->Top + paddleRight->Height +10){
         if(y < 0) {
           increaseAngle(-1);
          } else {
           reduceAngle(1);
          }
        }
      numberOfReflections++;
      numberOfReflectionsLabel->Caption =  IntToStr(numberOfReflections);
    }


  //lose
  if((ball->Left < paddleLeft->Left - paddleLeft->Width) ||
     (ball->Left + ball->Width > paddleRight->Left + paddleRight->Width)){
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



