class Fruit
{
    public:

        enum FruitType
        {
            GOOD,
            BAD,
			GHOST
        };

        int x;
        int y;
        FruitType type;
        bool active;

        Fruit(FruitType type, int x, int y)
        {
            this->x = x;
            this->y = y;
            this->type = type;
            this->active = true;
        }

};

 