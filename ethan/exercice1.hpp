class MainSDLWindow
{
public:
    MainSDLWindow()
    {
        window = 0;
        renderer = 0;
    } 
    ~MainSDLWindow()
    {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
    }
    int Init(char* title, int longueur, int largeur)
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            printf("erreur");
            return EXIT_FAILURE;
        }

        else
        {
            window = SDL_CreateWindow(title, 20, 20, longueur, largeur, 0);
            return EXIT_SUCCESS;
        }
    }
    SDL_Renderer* GetRenderer(void)
    {
        return renderer;
    }
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

};