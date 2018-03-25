//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TImage *table;
    TImage *ball;
    TImage *paddleLeft;
    TImage *paddleRight;
    TTimer *TimerLeftUp;
    TTimer *TimerLeftDown;
    TTimer *TimerRightUp;
    TTimer *TimerRightDown;
    TTimer *TimerBall;
    TButton *nextRound;
    TLabel *winerArrow;
    TLabel *score;
    TLabel *numberOfReflectionsLabel;
    TShape *Shape1;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *sets;
    TLabel *pauseGame;
    TLabel *newGame;
    TLabel *winerLabel;
    TButton *newGameBtn;
    void __fastcall TimerLeftUpTimer(TObject *Sender);
    void __fastcall TimerLeftDownTimer(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall TimerRightUpTimer(TObject *Sender);
    void __fastcall TimerRightDownTimer(TObject *Sender);
    void __fastcall TimerBallTimer(TObject *Sender);
    void __fastcall nextRoundClick(TObject *Sender);
    void __fastcall pauseGameClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall newGameBtnClick(TObject *Sender);
    void __fastcall newGameClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
