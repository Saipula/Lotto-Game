//---------------------------------------------------------------------------

#include <vcl.h>
#include <ctime>
#pragma hdrstop

#include "main.h"
#include "classes.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int counter = 0;
int Timer = 5000;
bool GameStart = 0;
Game game;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	int j = 0;
	for (int i = 0; i < Form1->ComponentCount; i++) {
		if (Form1->Components[i]->ClassNameIs("TSpeedButton")){
			game.arr[j] = (TSpeedButton*)Form1->Components[i];
			j++;
		}
	}

    game.Union();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormShow(TObject *Sender)
{
    Form1->Color = TColor(RGB(232, 224, 56));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StartClick(TObject *Sender) //Подгрузка визуальных компонентов и заполнение полей
{
	Button1->Visible = false;
	N1->Visible = true;
	N2->Visible = true;
	Label1->Visible = true;
	Label2->Visible = true;
	Label3->Visible = true;
	Timer1->Enabled = true;

	if (GameStart == 0) {
		N1Click(Sender);
		GameStart = 1;
		Label2->Caption = "5000";
	}
	else{
		game.ShowBut();
	}

	Label3->Caption = IntToStr(game.Game_arr[counter]);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N1Click(TObject *Sender)
{
	game.restart();

	counter = 0;
	Timer = 5000;
	Label3->Caption = IntToStr(game.Game_arr[counter]);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N2Click(TObject *Sender)
{
	Button1->Visible = true;    //Выключение визуальных компонентов
	N1->Visible = false;
	N2->Visible = false;
	Timer1->Enabled = false;
	Label1->Visible = false;
	Label2->Visible = false;
	Label3->Visible = false;

    game.clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender) //Таймер для ограничения времени на выбор правильного ответа
{
	Label2->Caption = FloatToStr(Timer/1000);
	Timer -= Timer1->Interval;

	if(StrToFloat(Label2->Caption) <= 0) {
		Timer = 1;           //Заменить на 1, для быстрой тестировки
		counter++;

		game.player2.II(game.Game_arr[counter]);//Бот противник
		if (game.player2.proverka()) {
			N1Click(Sender);
			N2Click(Sender);
			GameStart = 0;
			ShowMessage("Бот 2 Победил!");
		}

		if (counter > 99) {
			N1Click(Sender);
			N2Click(Sender);
			GameStart = 0;
			ShowMessage("Вы проиграли!");
		}
		Label3->Caption = IntToStr(game.Game_arr[counter]);
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Player1Click(TObject *Sender) //Проверка нажата ли игроком кнопка с цифрой равной с Label3
{
	if (StrToInt(((TSpeedButton*)(Sender))->Caption) == StrToInt(Label3->Caption)) {
		((TSpeedButton*)(Sender))->Font->Color = clGreen;

		if (game.player1.proverka()) {
			N1Click(Sender);
			N2Click(Sender);
			GameStart = 0;
			ShowMessage("Вы победитель!");
		}
	}
}

//----------------------------------------------------------------------------


