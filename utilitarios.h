
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <windows.h>


// FUNÇÃO SLEEP
void sleep(int a)
{
	time_t t1,t2;
	t1 = time(NULL);
                   t2 = time(NULL);
	while ((t2 - t1)*1000 < a)
	t2 = time(NULL);
}
//
// FUNÇÃO GOTOXY
text_info vActual = {0, 0, 79, 24, WHITE, WHITE, C80, 25, 80, 1, 1};
void gotoxy(int x, int y)
{
   COORD c;

   if(x < 1 || x > vActual.screenwidth ||
      y < 1 || y > vActual.screenheight) return;
   vActual.curx = x;
   vActual.cury = y;
   c.X = vActual.winleft + x - 1;
   c.Y = vActual.wintop + y - 1;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
//
// CORDEFUNDO
void textbackground(int newcolor)
{
   CONSOLE_SCREEN_BUFFER_INFO csbi;

   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
      (csbi.wAttributes & 0x0f) | (newcolor << 4));
   vActual.attribute = (csbi.wAttributes & 0x0f) | (newcolor << 4);
}
//
// CORDETEXTO
void textcolor(int newcolor)
{
   CONSOLE_SCREEN_BUFFER_INFO csbi;

   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
      (csbi.wAttributes & 0xf0) | newcolor);
   vActual.attribute = (csbi.wAttributes & 0xf0) | newcolor;
}



