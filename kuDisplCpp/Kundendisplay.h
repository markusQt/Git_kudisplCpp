#ifndef KUNDENDISPLAY_H
#define KUNDENDISPLAY_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <thread>
#include <opencv.hpp>
#include <highgui/highgui.hpp>
#include "Texturemanager.h"



class Kundendisplay
{
    public:
        Kundendisplay();
        virtual ~Kundendisplay();

        bool gameIsRunning = true;
        bool videoPlay=false;
        void createTheDisplay(const char* title, int xPos, int yPos, int width,  int height, bool fullscreen);
        void run();
    private:
        std::vector<std::string>listeBilder;
        std::vector <std::string>listeFilme;
        int mDisplayWidth,mDisplayHeight;
        void clearAll_SDL();
        void threadPictureShow();
        static void doSlideShow(std::vector<std::string> listeBilder,SDL_Rect destRect, SDL_Renderer *renderer);
        static void doFilmShow(std::vector<std::string> listeFilme,SDL_Rect destRect, SDL_Renderer *renderer);
        void getMediaInfo();
        void handleEvents();
        void update();
        void render();
        int count = 0;
        char * exePath;
        float speedH=5.0;
        float speedV=5.0;
        SDL_Window *mWindow;
        SDL_Texture *mPlayerTex;
        SDL_Renderer *mRenderer;
        SDL_Rect mSrcRect,mDestRect;
};

#endif // KUNDENDISPLAY_H
