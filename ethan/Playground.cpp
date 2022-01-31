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
    delete Fruits[0];
    delete Fruits[1];
}

void Playground::Update()
{


    segment* s = this->head;

    while (!victoire)
    {
        fruit_set(Fruits[0]);
        fruit_set(Fruits[1]);
    }



void Playground::fruit_set(Fruit* f)
{
    int posx_fruit = Utils::randomInt( 0, this->Sizex );
    int posy_fruit = Utils::randomInt( 0, this->Sizey ); 

    f->x = posx_fruit;
    f->y = posy_fruit;
    Segment* s = s->head;

    while (s)
    {

        if s->posX == f->x && s->posY == f->y
        { 
            posx_fruit = Utils::randomInt( 0, this->Sizex );
            posy_fruit = Utils::randomInt( 0, this->Sizey ); 
            s = s->head;

            continue;
        }
        s = s->next;
    }
    Fruit("GOOD",posx_fruit,posy_fruit)* pomme; 
}
