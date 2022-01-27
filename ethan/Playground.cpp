#include <Snake.h>
#include <Fruit.hpp>
#include <Utils.h>
#include <Playground.hpp>

Playground::Playground(int Sizex, int Sizey)
{
    Fruits[0] = new Fruit();
    Fruits[1] = new Fruit();
}

~Playground()
{
    delete Fruits[0]
    delete Fruits[1]
}

void Playground::Update()
{
    int posx_fruit = Utils::randomInt( 0, this->Sizex )
    int posy_fruit = Utils::randomInt( 0, this->Sizey )
    Fruit("GOOD",posx_fruit,posy_fruit)* pomme;

    while victory != 0
    {
        segment* s = this->head->next

        for (s,s->tail,s->next)
        {
            if s->posX == fr->x and s->posY == fr->posY
            {
                int posx_fruit = Utils::randomInt( 0, tab_size->Sizex )
                int posy_fruit = Utils::randomInt( 0, tab_size->Sizey )
                pomme = Fruit("GOOD",posx_fruit,posy_fruit)
            }
        }


    }
}




