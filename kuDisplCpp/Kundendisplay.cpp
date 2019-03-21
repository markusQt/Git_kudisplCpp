#include "Kundendisplay.h"
 void Kundendisplay::doSlideShow(std::vector<std::string> listeBilder,SDL_Rect destRect, SDL_Renderer *renderer){

    std::cout << "Thread wird aufgerufen!!"<<std::endl;

    for (int i = 0 ; i <= listeBilder.size()-1;i++){
        std::cout << "Thread: "<<listeBilder.at(i)<<std::endl;
        SDL_Texture *tmpPlayerTex= Texturemanager::loadTexture(listeBilder.at(i).c_str(),renderer);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,tmpPlayerTex,NULL,&destRect);
        SDL_RenderPresent(renderer);
        SDL_Delay(3000);
        }


}




Kundendisplay::Kundendisplay()
{
    mWindow= nullptr;
    mRenderer=nullptr;
    exePath = SDL_GetBasePath();

    std::cout <<"Exe in Pfad:" << exePath<< std::endl;
    if (SDL_Init(SDL_INIT_EVERYTHING)){
        std::cout << "SDL initialisiert"<<std::endl;

    }else{
        std::cout<< "SDL Fehler :" << SDL_GetError()<<std::endl;
    }

    getMediaInfo();

}

Kundendisplay::~Kundendisplay()
{
    std::cout << "calling destructor Kundendisplay"<<std::endl;
}

void Kundendisplay::clearAll_SDL()
{
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Kundendisplay::handleEvents()
{
    SDL_Event myEvent;

    while(SDL_PollEvent(&myEvent)){

        if(myEvent.type ==  SDL_QUIT ){
            gameIsRunning=false;
            break;
        }

        if(myEvent.type == SDL_KEYDOWN ){
            std::cout << myEvent.key.keysym.sym<<std::endl;
            if(myEvent.key.keysym.sym == SDLK_ESCAPE){
                gameIsRunning=false;
                break;
            }
            if(myEvent.key.state == SDLK_w){
               mDestRect.y += -speedH;
            }
            if(myEvent.key.keysym.sym == SDLK_s){
               mDestRect.y += speedH;
            }
            if(myEvent.key.keysym.sym == SDLK_a){
               mDestRect.x += -speedV;
            }
            if(myEvent.key.keysym.sym == SDLK_d){
               mDestRect.x += speedV;
            }

        }

        if(myEvent.type ==  SDL_KEYUP ){

            if(myEvent.key.keysym.sym == SDLK_w){
               mDestRect.y += 0;
            }
            if(myEvent.key.keysym.sym == SDLK_s){
               mDestRect.y += 0;
            }
            if(myEvent.key.keysym.sym == SDLK_a){
               mDestRect.x += 0;
            }

            if(myEvent.key.keysym.sym == SDLK_a){
               mDestRect.x += 0;
            }
            if(myEvent.key.keysym.sym == SDLK_d){
               mDestRect.x += 0;
            }

        }
    }
}

void Kundendisplay::update()
{



}

void Kundendisplay::render()
{

}

void Kundendisplay::createTheDisplay(const char *title, int xPos, int yPos, int width, int height, bool fullscreen)
{
    Uint32 modus;
    if(fullscreen){
        modus = SDL_WINDOW_FULLSCREEN;
    }else{
        modus = SDL_WINDOW_SHOWN;
    }
    mDestRect.h=height;
    mDestRect.w=width;
    mDestRect.x=0;
    mDestRect.y=0;
    mWindow =  SDL_CreateWindow(title,xPos,yPos,width,height,modus);
    if(mWindow == NULL){
        std::cout << "error building window" << SDL_GetError()<<std::endl;
        return;
    }
    mRenderer= SDL_CreateRenderer(mWindow,-1,0);
    if(mRenderer == NULL){
        std::cout << "error building renderer" << SDL_GetError()<<std::endl;
        return;
     }else{
        SDL_SetRenderDrawColor(mRenderer,0,0,0,255);
     }

}

void Kundendisplay::run()
{
    const int FPS = 100;
    const int frameDelay = 1000/FPS;
    Uint32 frameStart;
    int frameTime=0;


    std::thread t1(doSlideShow,listeBilder,mDestRect,mRenderer);
    t1.detach();
    int cnt = 0;
    while (gameIsRunning){
    cnt ++;
    std::cout << "gameIsRunning :" << cnt << std::endl;
       frameStart = SDL_GetTicks();
       handleEvents();
       //update();
       //render();
       frameTime = SDL_GetTicks()-frameStart;
       if(videoPlay){
           if(frameDelay > frameTime){
           SDL_Delay(frameDelay-frameTime);
           }
       }

    }


    clearAll_SDL();
}

 void Kundendisplay::getMediaInfo()
{
    listeBilder.clear();
    listeFilme.clear();
    //Pfad zur playlist
    char* p;
    int num_chars = asprintf(&p, "%sassets/Playlist.txt",exePath);
    //header fuer Listeneintraege
    char* vectorHeader;
    int tmpChars = asprintf(&vectorHeader, "%sassets/",exePath);

    std::ifstream file(p);
    std::string line;
    std::stringstream ss;
    std::string label="";
    std::string tmpStr="";
    std::cout <<"While"<<std::endl;
    while(std::getline(file,line)){
        std::cout <<"Playlist: " <<line<< std::endl;
        ss.str("");
        tmpStr="";
        if(line.substr(0,4).compare("Pic@")==0){
            std::cout <<"Label Bilder gefunden " <<std::endl;
            ss << vectorHeader<< line.substr(4,line.length());;
            tmpStr= ss.str();
            listeBilder.push_back(tmpStr);
        }else if (line.substr(0,4).compare("Mov@")==0){
            std::cout <<"Label Filme gefunden " <<std::endl;
            ss << vectorHeader << line.substr(4,line.length());
            tmpStr= ss.str();
            listeFilme.push_back(tmpStr);
        }

    }

    for (int i = 0 ; i <= listeBilder.size()-1;i++){
        std::cout <<"Bilder: " <<listeBilder.at(i)<<std::endl;
    }

}




































