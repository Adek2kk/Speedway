#include "SDL/SDL.h"

#include "circle_functions.h"
#include "move.h"

#include <string>
#include <stdio.h>
#include <math.h>
#include <sstream>

#include <iostream>
#include <list>

#include <cstdlib>
#include <strings.h>
#include <cstdio>
#include <unistd.h>
#include <netdb.h>
#include <cstdlib>
#include <cstring>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PI 3.14159265
//The attributes of the screen

const int BUFSIZE = 1000;

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 300;
const int SCREEN_BPP = 32;
const int FRAMES_PER_SECOND = 120;

const int radius=3;
double direction_angle = 0;
double speed = 2;
double base_turn_angle = 1;

SDL_Surface* screen = NULL;

int oponentSock;

struct xy{
  double x;
  double y;
};

std::list<xy> player_list;
std::list<xy> opponent_list;

int sck_in;

int server(){
    struct sockaddr_in sck_addr_in;
    memset(&sck_addr_in, 0, sizeof sck_addr_in);
    sck_addr_in.sin_family = AF_INET;
    sck_addr_in.sin_port = htons(6667);
    sck_addr_in.sin_addr.s_addr = htonl(INADDR_ANY); // "5.135.147.79"
    
    sck_in = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sck_in < 0){
        perror ("Can't create a socket");
        exit(EXIT_FAILURE);
    }
    
    int nFoo = 1;
    setsockopt(sck_in, SOL_SOCKET, SO_REUSEADDR, (char*)&nFoo, sizeof(nFoo));
    
    if(bind(sck_in, (struct sockaddr*)&sck_addr_in, sizeof(struct sockaddr)) < 0){
        perror("Can't bind a name to a socket");
        exit(EXIT_FAILURE);
    }
    
    if(listen(sck_in, 5) < 0){
        perror("Can't set queue size");
        exit(EXIT_FAILURE);
    }
    
    socklen_t slen = sizeof(sck_addr_in);
    
    printf("Czekam na klienta\n");
    int clientSocket = accept(sck_in, (struct sockaddr*)&sck_addr_in, &slen);
    
    if(clientSocket < 0){
        perror("Can't create a connetion socket");
        exit(EXIT_FAILURE);
    }
    oponentSock = clientSocket;
    
    return clientSocket;
}

int client(char* ip){
    
    char *server = ip;	/* adres IP pętli zwrotnej */
    char const *protocol = "tcp";
    short service_port = 6667;	/* port usługi daytime */
    
    struct sockaddr_in sck_addr;
    
    int sck;
    
    printf ("Usługa %d na %s z serwera %s :\n", service_port, protocol, server);
    
    memset (&sck_addr, 0, sizeof sck_addr);
    sck_addr.sin_family = AF_INET;
    inet_aton (server, &sck_addr.sin_addr);
    sck_addr.sin_port = htons (service_port);
    
    if ((sck = socket (PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        perror ("Nie można utworzyć gniazdka");
        exit (EXIT_FAILURE);
    }
    
    if (connect (sck, (struct sockaddr*) &sck_addr, sizeof sck_addr) < 0) {
        perror ("Brak połączenia");
        exit (EXIT_FAILURE);
    }
    
    return sck;
}


int main( int argc, char** argv ){
 
	int clientSocket;
	int sck; 
    	if(argv[1][0] == '1'){
		 clientSocket = server();
		printf("Polaczono !\n");
    	}else{
		 sck = client(argv[2]);
		printf("Polaczono z serwerem ! \n");
	}
    
	SDL_Surface* lap0 = NULL,*lap1 = NULL,*lap2 = NULL,*lap3 = NULL,*lap4 = NULL,*lapr = NULL,*lapy = NULL,*winner = NULL, *loser = NULL;
	SDL_Event event;
	xy player,player_temp;
	
	int lap_counter=0;
	double x,y;
	bool quit = false;
	bool collide = false;
	bool lap_updown= false;
	int time_start;
	bool win = true;
	//Start SDL
        SDL_Init(SDL_INIT_EVERYTHING);
        //Set up screen
        screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
        SDL_WM_SetCaption("Speedway", "game");
        //Load image
        lap0 = SDL_LoadBMP("pics/lap0.bmp");
	lap1 = SDL_LoadBMP("pics/lap1.bmp");
	lap2 = SDL_LoadBMP("pics/lap2.bmp");
	lap3 = SDL_LoadBMP("pics/lap3.bmp");
	lap4 = SDL_LoadBMP("pics/lap4.bmp");
	lapr = SDL_LoadBMP("pics/lapred.bmp");
	lapy = SDL_LoadBMP("pics/lapyel.bmp");
	loser = SDL_LoadBMP("pics/lose.bmp");
	winner = SDL_LoadBMP("pics/win.bmp");
        
	//Po podlaczeniu zaleznie kto host kto guest
        if(argv[1][0] == '1'){
                player.x = 294;
                player.y = 230;}
        else{
                player.x = 294;
                player.y = 250;
        }
	int z = 3;
	while(z>0){
		
		if(z == 1) SDL_BlitSurface( lapy, NULL, screen, NULL ); 
		else SDL_BlitSurface( lapr, NULL, screen, NULL ); 
		fill_circle(screen, (int)player.x,(int)player.y, radius, 0xff008000); 
		if(player.y == 230) fill_circle(screen, 294, 250, radius, 0xff0000ff);
		else fill_circle(screen, 294, 230, radius, 0xff0000ff);
		SDL_Flip(screen);
		sleep(1);
		z = z - 1;
	}	
        while( quit == false && lap_counter != 9){
       		 time_start = SDL_GetTicks();
       		 if( SDL_PollEvent( &event ) ){
            		//If the user has Xed out the window
            		if( event.type == SDL_QUIT ){
                	//Quit the program
                	quit = true;
            		}
		  }

        	//Apply image to screen  
        	if(lap_counter < 1) SDL_BlitSurface( lap0, NULL, screen, NULL );     
        	else if(lap_counter < 3) SDL_BlitSurface( lap1, NULL, screen, NULL );     
        	else if(lap_counter < 5) SDL_BlitSurface( lap2, NULL, screen, NULL );     
        	else if(lap_counter < 7) SDL_BlitSurface( lap3, NULL, screen, NULL );     
        	else if(lap_counter < 9) SDL_BlitSurface( lap4, NULL, screen, NULL );     
        	
		Uint8 *keystates = SDL_GetKeyState( NULL );//Get the keystates. If left is pressed
		
		if( collide == false){
	  		//Ustalenie wartosci predkosci i kat skrecenia w zaleznosci czy klawisz jest wcisniety czy nie.
			if( keystates[ SDLK_LEFT ] ){
	    			speed-=0.05;
	    			if(speed<1.5) speed=1.5;
	    			base_turn_angle+=0.05;
	    			if(base_turn_angle>1.5) base_turn_angle=1.5;
            			direction_angle = change_angle(direction_angle,base_turn_angle);
	  		}
	  		else{
	    			speed+=0.05;
	    			if(speed>2) speed=2;
	    			base_turn_angle-=0.05;
	    			if(base_turn_angle<1) base_turn_angle=1; 
	  		}
	  		//Ustalenie nowej pozycji
	  		x = speed*cos(direction_angle*PI/180);
	  		player.x+=x;
	  		y = speed*sin(direction_angle*PI/180);
	  		player.y+=y;
	
	  		if(lap_count((int)player.x,(int)player.y,lap_updown)==true){
	      			lap_counter++;
	      			lap_updown = (!lap_updown);
	  		}
			//Rysowanie pierwszego kola + sprawdzenie czy wystapila kolizja
			collide = fill_first_circle(screen, (int)player.x, (int)player.y, radius, 0xff008000);//to je zielony,
			player_list.push_front(player); 
			//Usuwanie elementu z listy jesli rysowana linia z kol jest za dlugi
			while(player_list.size()>75) player_list.pop_back();
		}
		//Rysowanie linii
		for(unsigned int i = 0; i<player_list.size();i++){
	  		player_temp = player_list.front();
	  		player_list.pop_front();
	  		fill_circle(screen, (int)player_temp.x,(int)player_temp.y, radius, 0xff008000); 
	  		player_list.push_back(player_temp);	  
		}
	 
        	if(argv[1][0] == '1') {
            		char rcvx[sizeof(double)];
            		char rcvy[sizeof(double)];
            
            		xy rcv;
            
            		read(clientSocket, &rcvx, 8);
            		rcv.x = atof(rcvx);
            		read(clientSocket, &rcvy, 8);
            		rcv.y = atof(rcvy);
            		//printf("serwer odebral x = %f oraz y = %f\n", rcv.x, rcv.y);
            		
            		if(rcv.x == 1 && rcv.y == 1) quit = true;
			else if (rcv.x == 2 && rcv.y == 2) collide = true; 
            		else opponent_list.push_front(rcv);
			
	    		if(collide == true){
			      player.x = 1;
			      player.y = 1;
			}
			else if(lap_counter == 9){
			      player.x = 2;
			      player.y = 2;
			}
	    		
			char x[sizeof(player.x)];
            		char y[sizeof(player.y)];
			 
            		sprintf(x ,"%lf",player.x);
            		sprintf(y ,"%lf",player.y);

            		write(clientSocket,x,8);
            		write(clientSocket,y,8);
       
 		}else{
            		if(collide == true){
			      player.x = 1;
			      player.y = 1;
			}
			else if(lap_counter == 9){
			      player.x = 2;
			      player.y = 2;
			}
		  
			char x[sizeof(player.x)];
            		char y[sizeof(player.y)];
            
            		sprintf(x ,"%lf",player.x);
            		sprintf(y ,"%lf",player.y);
            
            		write(sck,x,8);
            		write(sck,y,8);
            		oponentSock = sck;

	    		char rcvx[sizeof(double)];
           		char rcvy[sizeof(double)];

            		xy rcv;

            		read(sck, &rcvx, 8);
            		rcv.x = atof(rcvx);
            		read(sck, &rcvy, 8);
            		rcv.y = atof(rcvy);
            		//printf("client odebral x = %f oraz y = %f\n", rcv.x, rcv.y);
                        if(rcv.x == 1 && rcv.y == 1) quit = true;
			else if (rcv.x == 2 && rcv.y == 2) collide = true; 
            		else opponent_list.push_front(rcv);
                 
		};
	
		
	 	while(opponent_list.size()>75){
			opponent_list.pop_back();
		}

	 	for(unsigned int i = 0; i<opponent_list.size();i++){
	  		player_temp = opponent_list.front();
	  		opponent_list.pop_front();
	  		fill_circle(screen, (int)player_temp.x,(int)player_temp.y, radius, 0xff0000ff); 
	  		opponent_list.push_back(player_temp);	  
		}
	
		//Update Screen
		SDL_Flip(screen);
	
		if( SDL_GetTicks()-time_start < 1000 / FRAMES_PER_SECOND ){
            		//Sleep the remaining frame time
            		SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - SDL_GetTicks()+time_start );
        	}
		
		if(collide == true){

			quit = true;
			win = false;
		}
	}
	
	if(win == true){
		SDL_BlitSurface( winner, NULL, screen, NULL );
		SDL_Flip(screen);
		sleep(10);
	}else{
		SDL_BlitSurface( loser, NULL, screen, NULL );
		SDL_Flip(screen);
		sleep(10);
	}

	if(argv[1][0] == '1') {
                close(clientSocket);
                close(sck_in);
        }


	//Free the loaded image
	SDL_FreeSurface(lap0);
	SDL_FreeSurface(lap1);
	SDL_FreeSurface(lap2);
	SDL_FreeSurface(lap3);
	SDL_FreeSurface(lap4);
	SDL_FreeSurface(lapr);
	SDL_FreeSurface(lapy);
	SDL_FreeSurface(winner);
	SDL_FreeSurface(loser);
	//Quit SDL
	SDL_Quit();

	return 0;
}

    
