class Fruit
{
    public:

        enum FruitType
        {
            GOOD,
            BAD,
        };

        int x;
        int y;
        FruitType type;

        Fruit(FruitType type, int x, int y)
        {
            this->x = x;
            this->y = y;
            this->type = type;
        }

};