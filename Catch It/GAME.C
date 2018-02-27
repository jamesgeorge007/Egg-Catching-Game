#include<stdio.h>
#include<graphics.h>
#include<dos.h>
#include<conio.h>
#include<stdlib.h>

void game_play()
{
  int i, speed = 5, x, crashed = 0, random_color = 1, random_style = 1, basket_x = getmaxx()/2-80, basket_y = getmaxy()/2+80, egg_x = 50, egg_y = 45, pos = 0;
  char key;

  setcolor(WHITE);

  // Boundary

/*  line(0, 30, getmaxx(), 30);
  line(getmaxx(), 30, getmaxx(), getmaxy()/2+170);
  line(0, 30, 0, getmaxy()/2+170);
  //sector(basket_x, basket_y, 180, 360, 90, 90);
  line(0, getmaxy()/2+170, getmaxx(), getmaxy()/2+170); */

  rectangle(0, 0, getmaxx(), getmaxy());

  // Main Game Loop.

   while(crashed == 0)
  {

  setfillstyle(random_style, random_color);

  fillellipse(egg_x, egg_y, 30, 45);

  line(0, 30, getmaxx(), 30);
  line(getmaxx(), 30, getmaxx(), getmaxy()/2+170);
  line(0, 30, 0, getmaxy()/2+170);
  line(0, getmaxy()/2+170, getmaxx(), getmaxy()/2+170);

	if(kbhit())
       {
	switch(getch())
	{
	  case 'a':
		pos-=5;
		break;
	  case 'd':
		 pos+=5;
		 break;
	  default:
		 crashed=1;
	}
       }

      x = basket_x + pos*2;

     // Restricting the basket within the space.

     if(x <= 90)
     {
       x = 90;
     }

     else if(x >= getmaxx()-90)
     {
       x = getmaxx() - 90;
     }
     setfillstyle(6, BROWN);

     sector(x, basket_y, 180, 360, 90, 90);
     //Checking whether the egg falls within the basket.

     if(egg_x >= x && egg_x <= x+90)
     {
	outtextxy(50, 80, "Crashed");
	delay(1000);
	crashed = 1;
     }

     egg_y += speed;

     // Placing egg to the initial position after crossing the border.

     if(egg_y >= getmaxy() - 90)
     {
	egg_x = random(getmaxx() - 30);

	if(egg_x <= 30)
	{
	  egg_x += 30;
	}

	egg_y = 45;

	if(speed >= 25)
	{
	  speed = 25;
	}
	else
	{
	  speed += 1;
	}

	random_color = random(15);
	random_style = random(12);

     }

     delay(40);
    cleardevice();
     }
  }

void intro()
{
  int gd=DETECT, gm, i, color=0;

  // Autodetect
  // Initializing the graphics driver as well as mode.

  initgraph(&gd, &gm, "../bgi");

  // Boundary

 /*   line(0, 30, getmaxx(), 30);
  line(getmaxx(), 30, getmaxx(), getmaxy()/2+170);
  line(0, 30, 0, getmaxy()/2+170);
  line(0, getmaxy()/2+170, getmaxx(), getmaxy()/2+170);

  settextstyle(7, 0, 8);

   for(i=-80; i<=80; i++)
   {
     setcolor(color);
     outtextxy(80, i, "Catch It");

     if(color>15)
	color=0;
     else
	color++;
     delay(35);
     cleardevice();
   }

   setcolor(getmaxcolor());

   outtextxy(80, 80, "Catch It");

  settextstyle(1, 0, 4);

  setcolor(RED);
  outtextxy(40, 300, "Press any key to continue...");

  getch();

  setfillstyle(0, BLACK);

  bar(40, 300, getmaxx(), 340);

  setcolor(GREEN);

  // Loading bar and text.

  outtextxy(40, 300, "Loading...");

  setfillstyle(5, BLUE);

  for(i=90; i<=getmaxx()-80; i++)
  {
   bar(80, 360, i, 390);
   delay(5);
  } */

  cleardevice();

  game_play();
}

void main()
{
  intro();
 // game_play();

}