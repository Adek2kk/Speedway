#include "circle_functions.h"
void fill_circle(SDL_Surface *surface, int cx, int cy, int radius, Uint32 pixel)
{
   
    static const int BPP = 4;
 
    double r = (double)radius;
 
    for (double dy = 1; dy <= r; dy += 1.0)
    {
       
        double dx = floor(sqrt((2.0 * r * dy) - (dy * dy)));
        int x = cx - dx;
 
        Uint8 *target_pixel_a = (Uint8 *)surface->pixels + ((int)(cy + r - dy)) * surface->pitch + x * BPP;
        Uint8 *target_pixel_b = (Uint8 *)surface->pixels + ((int)(cy - r + dy)) * surface->pitch + x * BPP;
 
        for (; x <= cx + dx; x++)
        {
            *(Uint32 *)target_pixel_a = pixel;
            *(Uint32 *)target_pixel_b = pixel;
            target_pixel_a += BPP;
            target_pixel_b += BPP;
	   //printf("%d %d %d\n",get_color(1,1,surface), get_color(x,(int)(cy + r - dy),surface),get_color(x,(int)(cy - r + dy),surface));
        
	}
    }
}

bool fill_first_circle(SDL_Surface *surface, int cx, int cy, int radius, Uint32 pixel)
{
   
    static const int BPP = 4;
 
    double r = (double)radius;
    
    bool collision = false;
 
    for (double dy = 1; dy <= r; dy += 1.0)
    {
       
        double dx = floor(sqrt((2.0 * r * dy) - (dy * dy)));
        int x = cx - dx;
 
        Uint8 *target_pixel_a = (Uint8 *)surface->pixels + ((int)(cy + r - dy)) * surface->pitch + x * BPP;
        Uint8 *target_pixel_b = (Uint8 *)surface->pixels + ((int)(cy - r + dy)) * surface->pitch + x * BPP;
 
        for (; x <= cx + dx; x++)
        {
	    if(get_color(x,cy + r - dy,surface) == (Uint32)12829635) collision = true;
	    if(get_color(x,cy - r + dy,surface) == (Uint32)12829635) collision = true;
	    
            *(Uint32 *)target_pixel_a = pixel;
            *(Uint32 *)target_pixel_b = pixel;
            target_pixel_a += BPP;
            target_pixel_b += BPP;
	    
	    }
    }
	return collision;
}

Uint32 get_color(int x, int y, SDL_Surface *surface)
{
  unsigned int *ptr = (unsigned int*)screen->pixels;
  int lineoffset = y * (screen->pitch / 4); 
  return ptr[lineoffset + x];
  
}
