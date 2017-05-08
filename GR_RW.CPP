# include "GR_HEAD.h"
//---------------------------------------------------------------------------
void Write(Coordinate** CPrt,int st)      // Запись в файл.
{
if(!st) { No_matr(); return; }  //             Контроль отсутствия матрицы.

 textattr(0x71); clrscr();      char name[40];

  gotoxy(20, 2); cout << "Режим вывода таблицы в файл";

  gotoxy(20,12); cout << "Имя файла:   ";  cin >> name;

 FILE *fff;

 if((fff=fopen(name, "w+t"))==NULL)
 {
    gotoxy(20,16);   cout << "НЕ МОГУ создать файл "<< name;
    getch();     return;
 }

  for(int i=0; i<st; i++)
  {
   fprintf(fff, "%g;",CPrt[i]->getC(X));
   fprintf(fff, "%g\0",CPrt[i]->getC(Y));
   fputs("\n", fff);
  }
  fclose(fff);

  textattr(0x31); clrscr();
  gotoxy(23,12); cout << "З А П И С Ь   ЗАВЕРШЕНА !!!"; Sound(5,333);
}
//-----------------------------------------------------------------------
void sizeSt(int &st, char name[40])
{
 textattr(0x71); clrscr();   char sss[80];

  gotoxy(20, 2); cout << "Режим ввода матрицы из файла";

  gotoxy(20,12); cout << "Имя файла:   ";  cin >> name;

 FILE *fff;          st=0;

 if((fff=fopen(name, "r+t"))==NULL)
 {
    gotoxy(20,16);   cout << "НЕ МОГУ открыть файл "<< name;
    getch();     return;
 }
  for(;;)
  {
		fscanf(fff,"%s",sss );
   if(feof(fff))
     {
	  fclose(fff);
      return;
     }
	for(int i=0;i<80;i++)
	  if(sss[i]==';'){ st++; break; }
  }

}
//---------------------------------------------------------------------
void Read(Coordinate** CPrt,int st, char name[40])   // Чтение из файла.
{
     textattr(0x71); clrscr();
 char sss[80], sx[40], sy[40];
 FILE *fff;

 if((fff=fopen(name, "r+t"))==NULL)
 {
    gotoxy(20,16);   cout << "НЕ МОГУ открыть файл "<< name;
    getch();     return;
 }
			   clrscr();
cout << "Контроль ввода матрицы из файла\n\n";

 for(int i=0; i<st; i++)
   {
	fscanf(fff, "%s", sss);//  Считываем число как строку, а затем пере-
	for(int j=0,z=0,f=0;j<80;j++)
	 {
	  if(!f)
	   if(sss[j]!=';') sx[j]=sss[j];
	   else { sx[j]='\0'; f=1; }
	  else
	   if(sss[j]!='\0') sy[z++]=sss[j];
	   else { sy[z]='\0'; f=0; }
	 }
	CPrt[i]->getC(X) = atof(sx);   // водим в число, т.к., если считывать сразу:
	CPrt[i]->getC(Y) = atof(sy);   // водим в число, т.к., если считывать сразу:
  }

 X0=CPrt[0]->getC(X);
 Xk=CPrt[st-1]->getC(X);
 dX=fabs((X0-Xk))/st;

 fclose(fff);

  textattr(0x31); clrscr();
  gotoxy(23,12); cout << "Ч Т Е Н И Е  файла   ЗАВЕРШЕНО !!!";

	Sound(10,133);
}