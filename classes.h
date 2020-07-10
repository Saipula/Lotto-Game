#include <vcl.h>
#include <ctime>

class Player{
public:
	TSpeedButton *arr[27]; //Массив кнопочек)

	void ShowButtons(){ //Разброс чисел по кнопкам (Возможны повторы)
		for (int i = 0; i < 27; i++){
			arr[i]->Visible = true;
		}
	}

	void restart() {
		for (int i = 0; i < 27; i++){
			arr[i]->Caption = "";
			arr[i]->Tag = 0;
			if (1+(rand()%10) < 6)
				arr[i]->Caption = 1+(rand()%99);
			else
				arr[i]->Tag = 1;

			arr[i]->Font->Color = clBlack;
		}
        ShowButtons();
    }

	void clear(){  //Выключение кнопочек
		for (int i = 0; i < 27; i++){
			arr[i]->Visible = false;
		}
	}

	bool proverka(){
		for (int i = 0; i < 27; i++){
			if (arr[i]->Tag != 1) {return false;}
		}
		return true;
	}

	void II(int Num){   // Бот противник
		for (int i = 0; i < 27; i++)
			if (arr[i]->Caption != "")
				if (Num == StrToInt(arr[i]->Caption)){
					arr[i]->Font->Color = clGreen;
					arr[i]->Tag = 1;
				}
	}
};

class Game{
public:
	TSpeedButton *arr[54];
	Player player1, player2;
	int Game_arr[99];

	void Union(){  //Переприсваивание кнопок на ворме к кнопкам в классе
		for (int i = 0; i < 54; i++) {
			if (i<54/2) player1.arr[i%27] = arr[i];
			else player2.arr[i%27] = arr[i];
		}
	}


	void Random_arr(){  //Рандомит и перездаёт массив с игровыми числами (Label3)
		srand(time(0));

		for (int i = 0; i < 100; i++)  //Очистка старих чисел
			Game_arr[i] = NULL;

		for (int i = 0; i < 99; i++)  //Заполняет массив от 1 до 100
			Game_arr[i] = i+1;

		for (int i = 0; i < 99; i++)  //Перемешивает массив
			std::swap(Game_arr[i], Game_arr[std::rand()%99]);
	}

	void ShowBut(){  //Отображает все кнопки
		player1.ShowButtons();
		player2.ShowButtons();
	}

	void restart(){  //Рестарт игры
        player1.restart();
		player2.restart();

		Random_arr();
	}

	void clear(){   //выключает все кнопки
        player1.clear();
		player2.clear();
	}

};
