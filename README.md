# gtech1-b23-snake
Snake game written in C++ with SDL2

# Authors
- [joachim-gabin](https://github.com/joachim-gabin)
- [nwiart](https://github.com/nwiart)



## Building

Install SDL2 dev tools and make :
```
sudo apt install libsdl2-dev libsdl2-image-dev make
```

To build the game, use the following command in the repository's root folder :
```
make snake.out
```



## Run the game

Run the following command in the repository's root folder to run the game.

**WARNING :** The window's size is locked to 1024x768. The game has not been tested on resolutions lower than 1600x900, and playing it on lower resolution monitors might result in graphical problems.
```
make run
```



## How to Play & Controls

The snake is moving through the game's grid at a constant rate. The player can change the direction using the arrow keys on the keyboard.

You must eat apples to make your snake grow more and more.
But you must pay attention to where the rest of the snake body is.
You are not allowed to hit the screen borders or one of the snake's segments.

Try to get the highest score possible without colliding into anything.
