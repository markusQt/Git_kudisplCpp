#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <iostream>
#include "Kundendisplay.h"

class Texturemanager
{
    public:
        Texturemanager();
        virtual ~Texturemanager();

         static SDL_Texture *loadTexture(const char * filename, SDL_Renderer * rend);

};

#endif // TEXTUREMANAGER_H
