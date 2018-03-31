/*
 <<****  Developed by James George  ****>>
*/

// Uses Files to store High Score.

// Including the required header files in which the library functions are defined.

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

int exit_from_game = 0; // Keeps track of certain animations that should happen only if user plays the game atleast once.

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
void theEnd();

// Functions representing various phases of the game.

// Instructions Window.

void instructions()
{
  cleardevice();

  settextstyle(7, 0, 6);

  rectangle(0, 0, getmaxx(), getmaxy());

  outtextxy(80, 40, "INSTRUCTIONS");

  settextstyle(6, 0, 4);

  setcolor(3);

  outtextxy(7, 120, "1. Use A and D to move the basket either ways.");

  setcolor(random(15));

  outtextxy(7, 160, "2. Catch as many eggs as you can.");

  setcolor(4);

  outtextxy(7, 200, "3. Avoid black colored Eggs.");

  setcolor(5);

  outtextxy(7, 240, "4. There are overall 3 lives available.");

  setcolor(6);

  outtextxy(7, 280, "5. Press X to exit while on the game play.");

  setcolor(7);

  outtextxy(20, 360, "Press any key to return to the main menu.");

  repeat = 0;

  getch();

  main_menu();
}

// Retrieves and shows the current High Score from a text file.

void showHighScore()
{
  int score, i;

  char score_display[5];

  cleardevice();

  setcolor(random(15));

  file_read = fopen("score.txt","r");

  fscanf(file_read, "%d", &score);

  setcolor(15);

  for(i=0;i<=score;i++)
  {
  settextstyle(10, 0, 7);
  outtextxy(120, 60, "High Score");

  sprintf(score_display, "%d", i);
  settextstyle(9, 0, 4);
  outtextxy(getmaxx()/2-75, getmaxy()/2, score_display);

  delay(3);
  cleardevice();
  }

  fclose(file_read);

  settextstyle(10, 0, 7);

  repeat = 0;

  outtextxy(120, 60, "High Score");

  sprintf(score_display, "%d", score);
  settextstyle(9, 0, 4);

  outtextxy(getmaxx()/2-75, getmaxy()/2, score_display);

  settextstyle(6, 0, 4);
  outtextxy(60, 300, "Press any key to return to the Main Menu.");

  getch();

  main_menu();
}

// Sets new High Score.

void setHighScore(int current_score)
{
  int current_high_score;

  cleardevice();

  file_read = fopen("score.txt", "r");

  //current_high_score = (int) getc(file_read);

   fscanf(file_read, "%d", &current_high_score);

  if(current_score > current_high_score)
  {
	file_write = fopen("score.txt", "w");
	fprintf(file_write, "%d", current_score);
	fclose(file_write);
  }
  fclose(file_read);

}

// Game Play Mechanism.

void game_play()
{
  int i, speed = 5, k = 5, x, crashed = 0, life = 3, score = 0, random_color = 1, random_style = 1, basket_x = getmaxx()/2-80, basket_y = getmaxy()/2+80, egg_x = 50, egg_y = 45, pos = 0;
  char key, life_display[25], score_display[25], result[25];

  // Intro count-down.

  cleardevice();

  setbkcolor(random(14));

  setcolor(15);

  settextstyle(10, 0, 9);

  outtextxy(240, 100, "3");

  delay(1000);

  cleardevice();

  setbkcolor(random(14));

  settextstyle(10, 0, 9);

  outtextxy(240, 100, "2");

  delay(1000);

  cleardevice();

  setbkcolor(random(14));

  settextstyle(10, 0, 9);

  outtextxy(240, 100, "1");

  delay(1000);

  cleardevice();

  setbkcolor(15);

  setcolor(9);

  settextstyle(10, 0, 9);

  outtextxy(220, 100, "Go!");

  sound(2000);

  delay(2000);

  nosound();

  setcolor(15);

  setbkcolor(0);

  // Boundary

/*line(0, 30, getmaxx(), 30);
  line(getmaxx(), 30, getmaxx(), getmaxy()/2+170);
  line(0, 30, 0, getmaxy()/2+170);
  sector(basket_x, basket_y, 180, 360, 90, 90);
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

  outtextxy(getmaxx()-140, 0, score_display);
  outtextxy(20, 0, life_display);

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

	  case 'x':
		setHighScore(score);
		main_menu();
		break;
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
     setfillstyle(5, 4);

     sector(x, basket_y, 180, 360, 90, 90);

     // Checking whether egg falls within the basket.

     if(egg_x + 80 >= x && egg_x - 100 <= x && egg_y + 45 >= basket_y && egg_y - 23 <= basket_y + 45)
     {
	// Game play ends only when a black egg falls on the basket.

	if(random_color == 0)
	{
		life--;

	}

	if(life==0)
	{
			setHighScore(score);

			sprintf(result, "Your Score is %d.", score);
			settextstyle(10, 0, 6);
			setcolor(random(15));
			outtextxy(getmaxx()/2-240,getmaxy()/2-130, "GAME OVER");

			setcolor(3);
			settextstyle(6, 0, 6);
			outtextxy(getmaxx()/2-200, getmaxy()/2, result);

			delay(3000);

			crashed = 1;
			main_menu();
	}

	else
	{
		egg_y = getmaxy();

		if (random_color!=0)
		score += speed;
		else
		score -= speed;
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

     // Setting global variables accordingly to serve their purpose.
     repeat = 0;
     exit_from_game = 1;

     delay(40);
    cleardevice();
     }
  }

// The Game Ends here.

void theEnd()
{
  int i;

  cleardevice();

  setcolor(15);

  // Borders

  rectangle(0, 0, getmaxx(), getmaxy());

  settextstyle(10, 0, 7);

  setcolor(13);

  outtextxy(120, 140, "THE END");

  for(i=1;i<=800;i++)
  {
   putpixel(random(getmaxx()),random(getmaxy()), random(15));
   delay(25);
  }
  exit(0);

}

// Main Menu as the name suggests.


void main_menu()
{
     char option;

     int i;

     cleardevice();

     settextstyle(10, 0, 6);

  if(repeat == 1)
  {
  for(i=getmaxy()+30; i>=20; i--)
  {
  setcolor(random(15));
  outtextxy(getmaxx()/2 - 180, i, "Main Menu");
  delay(5);
  cleardevice();
  }
  }

  // Boundary.

  setcolor(WHITE);

  rectangle(0, 0, getmaxx(), getmaxy());

  outtextxy(getmaxx()/2 - 180, 20, "Main Menu");

  settextstyle(8, 0, 5);

  setcolor(12);

  outtextxy(30, getmaxy()/2 - 100, "1. Play Now");

  setcolor(10);

  outtextxy(30, getmaxy()/2 - 40, "2. Instructions");

  setcolor(6);

  outtextxy(30, getmaxy()/2 + 20, "3. High Score");

  setcolor(4);

  outtextxy(30, getmaxy()/2 + 80, "4. Exit");

  setcolor(2);

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

	 if (exit_from_game == 0)
	    exit(0);
	 else
	 theEnd();

	 break;

  /*  default:

	 settextstyle(8, 0, 5);

	 setfillstyle(0, BLACK);

	 bar(30, getmaxy()/2 + 80, getmaxx() - 60, getmaxy()/2 + 140);

	 line(50, getmaxy()/2 + 120, getmaxx() - 100, getmaxy()/2 + 120);
	 line(50, getmaxy()/2 + 120, 50, getmaxy() - 40);
	 outtextxy(50, getmaxy()/2 + 120, "Invalid option given");
	 line(getmaxx() - 100, getmaxy()/2 +120, getmaxx() - 100, getmaxy() - 40);
	 line(50, getmaxy() - 40, getmaxx() - 100, getmaxy() - 40);
    */
  }
  repeat = 0;
  delay(1000);
  main_menu();
}

// Intro window.

void intro()
{
  int gd=DETECT, gm, i, j, k,color=15;

  char score[25];

  // Autodetect
  // Initializing the graphics driver as well as mode.

  initgraph(&gd, &gm, "../bgi");

  cleardevice();

  /* Boundary

   setcolor(random(15));
   line(0, 30, getmaxx(), 30);

   setcolor(random(15));
   line(getmaxx(), 30, getmaxx(), getmaxy()/2+170);

   setcolor(random(15));
   line(0, 30, 0, getmaxy()/2+170);

   setcolor(random(15));
   line(0, getmaxy()/2+170, getmaxx(), getmaxy()/2+170); */

   settextstyle(10, 0, 5);

  for(i=-180,j=getmaxx()+30;i<=getmaxx()+40;i++,j--)
  {

	setcolor(color);

	color = 15;

	outtextxy(i, getmaxy()/2-80, "Welcome");

	outtextxy(j, getmaxy()/2, "To");

	if(i>=getmaxx()/2-150 && i<=getmaxx()/2-50)
	{
	color = random(15);
	delay(40);
	}

	else
	delay(1);

	cleardevice();
  }

   for(i=-60;i<=getmaxy()/2+15;i+=3)
   {
    setfillstyle(1, 7);
    fillellipse(getmaxx()/2+60, i, 30, 45);
    setfillstyle(1, 5);
    sector(getmaxx()/2+15, getmaxy()/2+45, 180, 360, 90, 90);
    delay(5);
    cleardevice();
   }
   setcolor(15);

   settextstyle(7, 0, 7);
   outtextxy(getmaxx()/2, getmaxy()/2-100, "Life: 3");
   delay(700);
   cleardevice();

   settextstyle(7, 1, 7);
   outtextxy(getmaxx()/2, getmaxy()/2-100, "Crashed");
   delay(700);
   cleardevice();

   settextstyle(10, 0, 4);

   for(i=0;i<=500;i++)
   {
   sprintf(score, "Score: %d", i);
   setcolor(random(15));
   outtextxy(getmaxx()/2-120, getmaxy()/2-80, score);
   delay(5);
   cleardevice();
   }

   settextstyle(7, 0, 8);

   for(i=-120, j=getmaxy()+50; i<=160; i++, j--)
   {
       color = random(15);
       setcolor(color);
       outtextxy(140, i, "Catch");
       outtextxy(400, j, "It");

       delay(10);
       cleardevice();
   }

   setcolor(9);

   outtextxy(140, 160, "Catch It");

   settextstyle(1, 0, 4);

   setcolor(GREEN);
   outtextxy(40, 300, "Press any key to continue...");

  getch();

  setfillstyle(0, BLACK);

  bar(40, 300, getmaxx(), 340);

  setcolor(GREEN);

  // Loading bar and text.

  outtextxy(40, 300, "Loading...");

  setfillstyle(8, RED);

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