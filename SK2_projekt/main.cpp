#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

#include "circle_functions.h"
#include "move.h"

#include <string>
#include <stdio.h>
#include <math.h>
#include <sstream>

#include <iostream>
#include <list>

#define PI 3.14159265
//The attributes of the screen

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 300;
const int SCREEN_BPP = 32;
const int FRAMES_PER_SECOND = 30;

const int radius=4;
double direction_angle = 0;
double speed = 2;
double base_turn_angle = 1;

SDL_Surface* screen = NULL;

struct xy
{
  double x;
  double y;};

std::list<xy> player_list;
std::list<xy> opponent_list;

int main( int argc, char* args[] )
{
  
SDL_Surface* lap = NULL;
SDL_Event event;
xy player,player_temp;

int lap_counter=0;
double x,y;
bool quit = false;
bool collide = false;
bool lap_updown= false;
bool host=true;
int time_start;
//Start SDL
SDL_Init(SDL_INIT_EVERYTHING);
//Set up screen
screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
SDL_WM_SetCaption("Speedway", "game");
//Load image
lap = SDL_LoadBMP("lap.bmp");

//Po podlazeniu zaleznie kto host kto guest
if(host==true)
{
  player.x = 294;
  player.y = 220;}
else
{
  player.x = 294;
  player.y = 250;}

while( quit == false || lap_count != 9)
    {  
	 
	time_start = SDL_GetTicks();
      
	if( SDL_PollEvent( &event ) )
        {           
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
	}

	//Apply image to screen  
	SDL_BlitSurface( lap, NULL, screen, NULL );
 	//Get the keystates	
	Uint8 *keystates = SDL_GetKeyState( NULL );
	//If left is pressed
	
        if( collide == false)
	{
	  if( keystates[ SDLK_LEFT ] )
	  {
	    speed-=0.05;
	    if(speed<1.5) speed=1.5;
	    base_turn_angle+=0.05;
	    if(base_turn_angle>1.5) base_turn_angle=1.5;
            direction_angle = change_angle(direction_angle,base_turn_angle);
	  }
	  else
	  {
	    speed+=0.05;
	    if(speed>2) speed=2;
	    base_turn_angle-=0.05;
	    if(base_turn_angle<1) base_turn_angle=1; 
	  }
	  x = speed*cos(direction_angle*PI/180);
	  player.x+=x;
	  y = speed*sin(direction_angle*PI/180);
	  player.y+=y;
	
	  if(lap_count((int)player.x,(int)player.y,lap_updown)==true)
	  {
	      lap_counter++;
	      lap_updown = (!lap_updown);
	      printf("%d\n", lap_counter);
	  }
	//Draw first_circle
	collide = fill_first_circle(screen, (int)player.x, (int)player.y, radius, 0xff008000);//to je zielony,
	player_list.push_front(player); 
	while(player_list.size()>75) player_list.pop_back();
	}
	
	for(int i = 0; i<player_list.size();i++)
	{
	  player_temp = player_list.front();
	  player_list.pop_front();
	  fill_circle(screen, (int)player_temp.x,(int)player_temp.y, radius, 0xff008000); 
	  player_list.push_back(player_temp);	  
	}
	 
	//Tu rysowanie linii przeciwnika
	
	fill_circle(screen, 294, 250, radius, 0xff0000ff);//to je niebieski
	/*
	 while(opponent_list.size()>75) opponent_list.pop_back();
	}
	 for(int i = 0; i<opponent_list.size();i++)
	{
	  player_temp = opponent_list.front();
	  opponent_list.pop_front();
	  fill_circle(screen, (int)player_temp.x,(int)player_temp.y, radius, 0xff008000); 
	  opponent_list.push_back(player_temp);	  
	}
	*/
	
	
	//Update Screen
	SDL_Flip(screen);
	
	if( SDL_GetTicks()-time_start < 1000 / FRAMES_PER_SECOND )
        {
            //Sleep the remaining frame time
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - SDL_GetTicks()+time_start );
        }
	
}

//Free the loaded image
SDL_FreeSurface(lap);

//Quit SDL
SDL_Quit();

return 0;
}

    
