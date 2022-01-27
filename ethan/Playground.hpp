#include "Fruit.hpp"

class Playground
{
    public:
        Playground(int Sizex, int Sizey);

        ~Playground();

        void Update();
        
    private:
        int Sizex;
        int Sizey;
        Fruit* Fruits[2];
        Snake* snake;

}