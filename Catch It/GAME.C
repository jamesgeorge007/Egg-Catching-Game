#include<stdio.h>
#include<graphics.h>
#include<dos.h>

void game_play()
{
  int crashed = 0, basket_x = getmaxx()/2-80, basket_y = getmaxy()/2+80, pos;
  char key;

  line(0, 30, getmaxx(), 30);
  line(getmaxx(), 30, getmaxx(), getmaxy()/2+170);
  line(0, 30, 0, getmaxy()/2+170);
  sector(basket_x, basket_y, 180, 360, 90, 90);
  line(0, getmaxy()/2+170, getmaxx(), getmaxy()/2+170);

  while(crashed == 0)
  {
	key = getch();

	switch(key)
	{
	  case 'a':
		pos+=5;
		break;
	  case 'd':
		 pos-=5;
		 break;
	  default:
		 crashed=1;
	}

	sector(basket_x + pos, basket_y, 180, 360, 90, 90);
       //cleardevice();

  }

}

void intro()
{
  int gd=DETECT, gm;
  initgraph(&gd, &gm, "../bgi");
  game_play();
}

void main()
{
  intro();

}