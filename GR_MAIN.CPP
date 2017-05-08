#include "GR_HEAD.h"
#include "GR_INTRF.CPP"
#include "GR_PROC.CPP"
#include "GR_RW.CPP"
/////////////////////////////////////////////////////////////////////////////
void main()
{
 int st=0;
 int i; char ch=0;
 Coordinate* CPrt[MAX];
 for(;;)
  switch(ch)
  {
   case  0: Start();				ch = getch();	continue;
   case 60: if(st)delete []CPrt; InputParameters(st);
	    for(i=0; i<st; i++) CPrt[i] = new Coordinate;
	    DataCalc(CPrt,st);			ch = 61;	continue;
   case 61: ViewTable(CPrt, st);		ch = 62;	continue;
   case 62: Graphik(CPrt,st);			ch =  0;	continue;
   case 63: Edit(CPrt,st);                      ch = 62;        continue;
   case 64: Write(CPrt,st);			ch =  0;	continue;
   case 65: delete []CPrt; char name[40]; sizeSt(st,name);
	    for(i=0; i<st; i++) CPrt[i] = new Coordinate;
	    Read(CPrt,st,name);			ch = 61;	continue;
   case -122: if(st)delete []CPrt; 				return;
   default: Sound(4,150);			ch =  0;	continue;
  }

}
