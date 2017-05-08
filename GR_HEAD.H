#ifndef GRHEAD
#define GRHEAD
	//         Подключение библиотечных функций.
# include <conio.h>
# include <iostream.h>
# include <iomanip.h>
# include <dos.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <ctype.h>
# include <graphics.h>
#define PATHTODRIVER "c:\\BORLANDC\\bgi\\"

const int MAX = 2000;		        // максимальное количество строк
					// таблицы

enum flag {X,Y};			// флаги X и Y для удобства
					// обозначения координат;
float X0, Xk, dX;			// Начальная, конечная координаты
					// шаг смещения;
float a1,b1,a2,b2,a3,b3;		// Аргументы функции;

/*---------------------------- GR_INTRF.CPP --------------------------------*/
class Coordinate			// Класс координат
{
 private:
   float x;					// координата X;
   float y;					// координата Y;
 public:
   void Display(flag f);                         // вывод на экран;
   float& getC(flag f);				// ввод координат;
};

void Start();				// Вывод меню на экран.
void InputParameters(int &st);          // Ввод данных и параметров
void DataCalc(Coordinate** CPrt, int st);	// Расчет функции;
void ViewTable(Coordinate**, int);	// Обзор таблицы
void HeaderTable();			// Шапка таблицы;
void Display(Coordinate** CPrt, int st, int n); // Вывод таблици в консоль;
void Graphik(Coordinate** CPrt, int st);	// Вывод графика в консоль;
void Edit(Coordinate** CPrt, int st);		// Редактирование таблициы;
void Display(Coordinate** CPrt, int st,int id,int n, flag f); // вывод
			// таблицы для редактирования;
void EditEl(Coordinate** CPrt,int id,int n, flag f);	// Редактирование
			// элемента

/*------------------------------ GR_PROC.CPP -------------------------------*/
float getF();
float CIF(char s[]);
void CSort(Coordinate**, int);
void Order(Coordinate**, Coordinate**);
void Pisk(int n);
void Sound(int n, int dd);
void No_matr();
void Stop();                        //           Завершение работы программы.

/*------------------------------- GR_RW.CPP --------------------------------*/
void Write(Coordinate** CPrt,int st);      // Запись в файл.
void sizeSt(int &st, char name[40]);
void Read(Coordinate** CPrt,int st,char name[40]);   // Чтение из файла.
#endif