#include <iostream>
#include <thread>
#include "Kundendisplay.h"


int main(){

    Kundendisplay mKundendisplay;
    mKundendisplay.createTheDisplay("Apotheke am Berg",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,810,530,false);
    mKundendisplay.run();

    return 0;
}
