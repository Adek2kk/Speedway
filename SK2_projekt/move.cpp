#include "move.h"

int change_angle(int angle, int base_change)
{
	    angle -=base_change;
	    if(angle<0) angle=+360;
	    return angle;
}


bool lap_count(int x, int y, bool updown)
{
  bool ans;
  if(x>299 && x<321)
  {
      if(y>24 && y<96 && updown == true)
      {
	ans = true;
      }
      else if(y>206 && y<275 && updown == false)
      {
	ans = true;
      }
  }
  else ans = false;
  
  return ans;
}

