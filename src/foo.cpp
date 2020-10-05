#include "odomdebug.h"

// need a setState callbacks

// reset callback

// intilization functional

// updateOdomDebug task to use display.setData()

// ok so firstly, fuck this shit
// now that we have that vital point out of the way lets explain why we do this

/**
odomDebug requires us to have a callback function for when a tile is pressed to
set the OdomState on our chassis to the OdomState of our debugger, now I dont
think this is neccesary, I belive its so you can correct the odom or just move
the odom position around through the GUI I may scrap this later and just feed it
a dummy callback function that does nothing but for now until I can actuall test
I will just do this. It was so fucking confusing trying to figure out why the
dude make OdomDebug:State instead of just using the OdomState object, they have
the same values just make another instance of the OdomState and store it for the
Debug state idk man it was very confusing. Also the word state looks very weird
now :(
*/

void setOdomState(OdomDebug::state_t state) {
  //
  OdomState newState = OdomState();
  newState.x = state.x;
  newState.y = state.y;
  newState.theta = state.theta;

  chassis->setState(newState);
}

void resetOdomState() {
  // foo
}
