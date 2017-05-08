#include "GR_HEAD.h"
/*-------------------------------------------------------------------------*/
void Coordinate::Display(flag f)                         // вывод на экран;
    { f? cout << y : cout << x; }
//--------------------------------------------------------------------------
float& Coordinate::getC(flag f)				// ввод координат;
    {
     if(f) return y;
     else return x;
    }
//--------------------------------------------------------------------------
void Start()               //                   Вывод меню на экран.
{
 textmode(C80);		textattr(0x1B); clrscr();   //         Смена цветов.
gotoxy(16, 3);   cout << "Задайте режим:";

gotoxy(21,7);   cout << "Ввод параметров                  - F2";
gotoxy(21,9);   cout << "Просмотр координат               - F3";
gotoxy(21,11);   cout << "Просмотр графика                 - F4";
gotoxy(21,13);   cout << "Редактирование координат         - F5";
gotoxy(21,15);   cout << "Сохранить координаты в файл      - F6";
gotoxy(21,17);   cout << "Считать координаты из файла      - F7";

gotoxy(21,20);   cout << "Завершение работы программы      - F12";

}
//---------------------------------------------------------------------------
void InputParameters(int &st)			// Ввод параметров функции.
{
	textmode(C80);	textattr(0x1B);		clrscr();

		     Pisk(20);
   gotoxy(21, 3); cout<< "Введите начальную координату Х... ";
				gotoxy(55, 3);  X0 = getF();
		     Pisk(30);
   gotoxy(21, 5); cout<< "Введите конечную координату Х... ";
				gotoxy(55, 5);	Xk = getF();
		     Pisk(40);
						// меняем местаи если кордината
      if(X0>Xk){ X0+=Xk; Xk=X0-Xk; X0-=Xk; }	// начала больше коорд. конца;

 do{
   gotoxy(21, 7); clreol(); cout<< "Введите шаг... ";
				gotoxy(55, 7);	dX = getF();
 }while(dX<0 || abs(Xk-X0)/dX>MAX);     //  Повтор ввода, если число недопустимо.

   gotoxy(10, 9); cout << "Задайте параметры(a1,b1,a2,b2,a3,b3) через запятую... ";
   gotoxy(15, 11); cin >> a1>>','>>b1>>','>>a2>>','>>b2>>','>>a3>>','>>b3;

 st = abs((Xk-X0)/dX)+2;			// количество строк в таблице;
}
//---------------------------------------------------------------------------
void DataCalc(Coordinate** CPrt, int st)	// Расчет данных;
{
 if(!st) { No_matr(); return; }  //              Контроль отсутствия матрицы.

 textmode(C4350);	  textattr(0x1B);	clrscr();   // Смена цветов.

 float x=X0;					// Координата начала;
 for(int i=0; i<st; i++)
  {
   CPrt[i]->getC(X)=x;					    // значение x;
   CPrt[i]->getC(Y)=a1*sin(b1*x)+a2*sin(b2*x)+a3*sin(b3*x); // значение f(x);
   x += dX;						    // Приращеение;
  }
}
//-------------------------------------------------------------------------
void ViewTable(Coordinate** CPrt, int st)	// простмотреть таблицу;
{
 if(!st) { No_matr(); return; }  	 // Контроль отсутствия таблицы;

 int n=0;					// номер верхней строки;
 char ch=0;

 for(;;)				// Цикл цикл обработки клавиш;
 {
  switch(ch)
  {
   case 0 : Display(CPrt,st,n); ch=42;	continue;
   case 42: ch = getch();		continue;
   case 72: ch=0; if(n)n--;		continue;
   case 80: ch=0; if(n<st-20)n++;	continue;
   case 13: clrscr();			return;
   case 27: clrscr();			return;
   default: Sound(4,150); ch =  0;	continue;
  }
 }

}
//-------------------------------------------------------------------------
void HeaderTable()
{
   textmode(C80); textattr(0x0A);	clrscr();
						// Шапка таблицы;
   gotoxy(25,2); cout << " Step        X               Y       ";
   gotoxy(25,3); cout << "-----T---------------T---------------";
}
//-------------------------------------------------------------------------
void Display(Coordinate** CPrt, int st, int n)	//
{
   HeaderTable();					// Шапка таблицы;
					// Цикл вывода таблицы в консоль;
   for (int i = n; (i<n+20) && i<st && i>-1;i++)
   {
    gotoxy(25,4+i-n); cout << '|'<< setw(4) << i<< "|";
    cout << setw(15) << CPrt[i]->getC(X) << "|";
    cout << setw(14) << CPrt[i]->getC(Y) << "|";
   }
}
//--------------------------------------------------------------------------
void Graphik(Coordinate** CPrt, int st)	 // Вывод графика функции в консоль;
{
 if(!st) { No_matr(); return; }		      // Контроль отсутствия таблицы

  textmode(C4350); textattr(0xf0);	clrscr();

 CSort(CPrt,st);		// Отсортируем по x перед выводом графика;
//			*** Подключение графики ***
 int gdriver = DETECT;
  int gmode;
  int errorcode;
  initgraph(&gdriver, &gmode, PATHTODRIVER);
  errorcode = graphresult();
  if (errorcode != grOk)
  {
   printf("ERROR!");
   exit(1);
  }

  int i;				// индекс элемента в массиве
  int x,y;				// координаты на графике;
  int scaleX = (570/abs(Xk-X0));        // коэффициет по x
		// Отрисовка координатных осей
  setcolor(0);
  lineto(20,225);
  setcolor(7);
  lineto(605,225);
  setcolor(0);
  lineto(600,220);
   setcolor(7);
  lineto(610,225);
   lineto(600,230);

  setcolor(0);
  lineto((30-(CPrt[0]->getC(X)*scaleX)),450);

  setcolor(7);
  lineto((30-(CPrt[0]->getC(X)*scaleX)),35);

  setcolor(0);
  lineto((25-(CPrt[0]->getC(X)*scaleX)),40);

  setcolor(7);
  lineto((30-(CPrt[0]->getC(X)*scaleX)),30);
  lineto((35-(CPrt[0]->getC(X)*scaleX)),40);

    setcolor(0);
    lineto((30),225-(CPrt[0]->getC(Y)*scaleX));

   for (i = 0; i<st; i++)		// Цикл отрисовки графика;
   {
    x=CPrt[i]->getC(X)*scaleX;
    y=225-(CPrt[i]->getC(Y)*scaleX);
    setcolor(10);
    lineto(x+30-(CPrt[0]->getC(X)*scaleX),y);
   }

getch();
closegraph();
}
//-------------------------------------------------------------------------
void Edit(Coordinate** CPrt, int st)
{
 if(!st) { No_matr(); return; }  //              Контроль отсутствия матрицы.

  textmode(C80); textattr(0x0A);	clrscr();

  int n=0;
  unsigned int id=0;
  flag f=X;
  char ch=0;
 for(;;)
 {
  switch(ch)
  {
   case  0: Display(CPrt,st,id,n,f); ch=42;	continue;
   case 42: ch = getch();			continue;
   case 72: ch=0; if(!id){ if(n)n--; }
		  else id--;    		continue;
   case 80: ch=0; if(id==19){if(n<st-20)n++;}
		  else id++;    		continue;
   case 75: if(f||!(n+id)){  f=X; ch=0; }
	    else { ch=72; f=Y; }		continue;
   case 77: if(!f||n+id==st-1){ f=Y; ch=0; }
	    else { ch=80; f=X; }		continue;
   case  9: ch=77;				continue;
   case  8: ch=0; EditEl(CPrt,id,n,f);		continue;
   case 13: clrscr();				return;
   case 27: clrscr();				return;
   default: Sound(4,150); ch = 0;		continue;
  }
 }
}
//-------------------------------------------------------------------------
void Display(Coordinate** CPrt, int st, int id,int n, flag f) // Вывод для
							// редактроваия;
{
   HeaderTable();					// Шапка таблицы;

   for (int i = n; (i<n+20) && i<st && i>-1;i++)  // Цикл вывода таблицы;
   {
    gotoxy(25,4+i-n); cout << '|'<< setw(4) << i<< "|";
    if(i==id+n && !f) textcolor(4);
    clreol(); cout << setw(15) << CPrt[i]->getC(X);
    textcolor(10); clreol(); cout << "|";
    if(i==id+n && f) textcolor(4);
    clreol(); cout << setw(15) << CPrt[i]->getC(Y);
    textcolor(10); clreol(); cout << "|";
   }
   gotoxy(45+f*16,4+id);
}
//-------------------------------------------------------------------------
void EditEl(Coordinate** CPrt,int id,int n, flag f) // редактровать эелемент;
{

 char s[20];                            // буферная строка
 for(int i=0; i<20; i++)
  s[i]='\0';

 i = 0;					// зануляем индекс массива;
 char ch;                               // код клавиши

 do{					// вывод текущих значений;
  gotoxy(32+f*15,4+id); textcolor(11); clreol(); cout << setw(13+f) << s;
			 textcolor(10); clreol(); cout << " |";
			 if(!f) cout << setw(15) << CPrt[id+n]->getC(Y) << "|";

  gotoxy(45+f*16,4+id);			// возврат каретки выделенному эл-ту;
  ch=getch();

  if(!i)				// если это нулевой элемент массива
   if(ch==45)				// проверяем знак;
    s[i++]=45;                          // если ввели '-'
   else s[i++]=43;			// знак '+' по умолчанию;

  if((ch>47 && ch<58) || ch==46)	// если нажали цифру
   s[i++]=ch;				// добавляем ее в массив;
  else
   if(ch==8 && i>0)			// если нажали backspase
   {
    s[--i]='\0';			// затираем предыдущее значение;
   }

 }while(ch!=13 && ch!=27 && i!=20);	// Выход по нажатию Exc или Enter;
 if(ch==13) { CPrt[id+n]->getC(f)=CIF(s); }	// Если Enter - сохраняем;

}
