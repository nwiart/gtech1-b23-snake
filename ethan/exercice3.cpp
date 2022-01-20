#include "SDL2/SDL.h"
#include "exercice3.hpp"


int main(void) {
    MainSDLWindow main_window;
    main_window.Init("Exo1",500,500);
    main_window.Getrender()

    int carrex = 0;
    int carrey = 0;

    SDL_Rect carre = {carrex, carrey, 50, 50};
    SDL_SetRenderDrawColor( renderer, 46, 107, 219, 255 );
    SDL_RenderFillRect(main_window.Getrender(), &carre );
    SDL_Delay(10000);


}
        

