

// Uses Files to store High Score.

// Including the required header files to use library functions.

#include<stdio.h>
#include<graphics.h>
#include<dos.h>
#include<conio.h>
#include<stdlib.h>

/*
	*-- Global Variables   --*
*/

/*  Global vaiables are declared here accessible within any functions.
    Changing their value locally within a function doesn't change this value assigned globally.
*/

int repeat = 1; // Prevents the Main Menu animation by changing the value locally when any other key other than the required one is being pressed.

FILE *file_read, *file_write; // File pointers

/*
	*-- Methods  --*
*/

// Function prototypes so that they can be accessed by any functions as per required.

void instructions();
void setHighScore(int);
void main_menu();
void showHighScore();
void game_play();

// Functions representing various phases of the game.

// Instructions Window.

void instructions()
{
  cleardevice();

  settextstyle(7, 0, 5);

  rectangle(0, 0, getmaxx(), getmaxy());

  outtextxy(160, 130, "INSTRUCTIONS");

  settextstyle(6, 0, 3);

  outtextxy(20, 180, "1. Use A and D to move the basket either ways.");

  outtextxy(20, 220, "2. Catch as many eggs as you can.");

  outtextxy(20, 260, "3. Avoid black Eggs which would decrease your life.");

  outtextxy(20, 300, "4. There are overall 3 lives available.");

  outtextxy(20, 340, "5. You can always view the current High Score from the Main Menu.");

  outtextxy(20, 380, "Press any key to return to the main menu.");

  getch();

  main_menu();
}

// Retrieves and shows the current High Score from a text file.

void showHighScore()
{
  int score;

  char score_text[5];

  cleardevice();

  settextstyle(7, 0, 6);

  outtextxy(180, 150, "High Score");

  file_read = fopen("score.txt","r");

  score = (int) getc(file_read);

  sprintf(score_text, "%d", score);

  settextstyle(4, 0, 6);

  outtextxy(getmaxx()/2-100, getmaxy()/2, score_text);

  fclose(file_read);

  settextstyle(6, 0, 4);

  outtextxy(80, 320, "Press any key to return to the Main Menu.");

  getch();

  main_menu();
}

// Sets new High Score.

void setHighScore(int current_score)
{
  int current_high_score;

  cleardevice();

  file_read = fopen("score.txt", "r");

  current_high_score = (int) getc(file_read);

  if(current_score > current_high_score)
  {
	file_write = fopen("score.txt", "w");
	putc(current_score, file_write);
	fclose(file_write);
  }
  fclose(file_read);

}

// Game Play Mechanism.

void game_play()
{
  int i, speed = 5, k = 5, x, crashed = 0, life = 3, score = 0, random_color = 1, random_style = 1, basket_x = getmaxx()/2-80, basket_y = getmaxy()/2+80, egg_x = 50, egg_y = 45, pos = 0;
  char key, life_display[10], score_display[10];

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

  // Random fill styles and colors for eggs.

  setfillstyle(random_style, random_color);

  // Ccnstructs eggs and fills it with the fill pattern provided.

  fillellipse(egg_x, egg_y, 30, 45);

  line(0, 30, getmaxx(), 30);
  line(getmaxx(), 30, getmaxx(), getmaxy()/2+170);
  line(0, 30, 0, getmaxy()/2+170);
  line(0, getmaxy()/2+170, getmaxx(), getmaxy()/2+170);

  sprintf(life_display, "Life: %d", life);
  sprintf(score_display, "Score: %d", score);

  settextstyle(8, 0, 3);

  outtextxy(getmaxx()-120, 0, score_display);
  outtextxy(0, 0, life_display);

	if(kbhit())
       {
	switch(getch())
	{
	  case 'a':
		pos -= k;
		break;
	  case 'd':
		 pos += k;
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

     // Checking whether egg falls within the basket.

     if(egg_x + 80 >= x && egg_x - 100 <= x && egg_y + 45 >= basket_y && egg_y - 45 <= basket_y + 90)
     {
	// Game play ends only when a black egg falls on the basket.

	if(random_color == 0)
	{
		life--;

	}

	if(life==0)
	{
			setHighScore(score);
			outtextxy(50, 80, "Crashed");
			delay(1000);
			crashed = 1;
	}

	else
	{
		egg_y = getmaxy();
		score += 1;
	}
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

	if(k <= 10)
	{
	  k += 1;
	}
	else
	{
	  k = 10;
	}

	random_color = random(15);
	random_style = random(12);

     }

     delay(40);
    cleardevice();
     }
  }

// Main Menu as the name suggests.


void main_menu()
{
     char option;

     int i;

     cleardevice();

     setcolor(6);


  settextstyle(7, 0, 7);



  if(repeat == 1)
  {
  for(i=getmaxy()+30; i>=20; i--)
  {
  outtextxy(getmaxx()/2 - 160, i, "Main Menu");
  delay(1);
  cleardevice();
  }
  }

  // Boundary.

  setcolor(WHITE);

  rectangle(0, 0, getmaxx(), getmaxy());

  outtextxy(getmaxx()/2 - 160, 20, "Main Menu");

  settextstyle(8, 0, 5);

  outtextxy(30, getmaxy()/2 - 100, "1. Play Now");

  outtextxy(30, getmaxy()/2 - 40, "2. Instructions");

  outtextxy(30, getmaxy()/2 + 20, "3. High Score");

  outtextxy(30, getmaxy()/2 + 80, "4. Exit");

  outtextxy(30, getmaxy()/2 + 140, "Enter your option:");

  option = getche();

  switch(option)
  {

    case '1':

	 game_play();
	 break;

    case '2':

	 instructions();
	 break;

    case '3':

	 showHighScore();
	 break;

    case '4':

	 exit(0);

    default:

	 settextstyle(8, 0, 5);

	 setfillstyle(0, BLACK);

	 bar(30, getmaxy()/2 + 80, getmaxx() - 60, getmaxy()/2 + 140);

	 line(50, getmaxy()/2 + 120, getmaxx() - 100, getmaxy()/2 + 120);
	 line(50, getmaxy()/2 + 120, 50, getmaxy() - 40);
	 outtextxy(50, getmaxy()/2 + 120, "Invalid option given");
	 line(getmaxx() - 100, getmaxy()/2 +120, getmaxx() - 100, getmaxy() - 40);
	 line(50, getmaxy() - 40, getmaxx() - 100, getmaxy() - 40);

	 repeat = 0;
	 delay(1000);
	 main_menu();
  }
}

// Intro window.

void intro()
{
  int gd=DETECT, gm, i, j, color=0;

  // Autodetect
  // Initializing the graphics driver as well as mode.

  initgraph(&gd, &gm, "../bgi");

  cleardevice();

  // Boundary

   line(0, 30, getmaxx(), 30);
   line(getmaxx(), 30, getmaxx(), getmaxy()/2+170);
   line(0, 30, 0, getmaxy()/2+170);
   line(0, getmaxy()/2+170, getmaxx(), getmaxy()/2+170);



  settextstyle(10, 0, 5);

  setcolor(5);

  for(i=-180,j=getmaxx()+30;i<=getmaxx()+40;i++,j--)
  {
	setcolor(color);

	color = random(15);

	outtextxy(i, getmaxy()/2-80, "Welcome");

	outtextxy(j, getmaxy()/2, "To");

	if(i>=getmaxx()/2-150 && i<=getmaxx()/2-50)
	delay(30);

	else
	delay(2);
	cleardevice();
  }
  settextstyle(7, 0, 8);

/*  color=0;

   for(i=-80; i<=80; i++)
   {
     setcolor(color);
     outtextxy(140, i, "Catch It");

     if(color>15)
	color=0;
     else
	color++;
     delay(35);
     cleardevice();
   }

   */

   for(i=-120, j=getmaxy()+50; i<=160; i++, j--)
   {
       color = random(15);
       setcolor(color);
       outtextxy(140, i, "Catch");
       outtextxy(400, j, "It");

       delay(10);
       cleardevice();
   }

   setcolor(getmaxcolor());

   outtextxy(140, 80, "Catch It");

   settextstyle(1, 0, 4);

   setcolor(RED);
   outtextxy(40, 300, "Press any key to continue...");

  getch();

  setfillstyle(0, BLACK);

  bar(40, 300, getmaxx(), 340);

  setcolor(GREEN);

  // Loading bar and text.

  outtextxy(40, 300, "Loading...");

  setfillstyle(4, BLUE);

  for(i=90; i<=getmaxx()-80; i++)
  {
   bar(80, 360, i, 390);
   delay(5);
  }

 // cleardevice();

  main_menu();

  //game_play();
}

void main()
{
  intro();
 // game_play();

}