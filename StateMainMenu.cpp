#include "State.h"

#include "Renderer.h"
#include "Texture.h"

#include <SDL2/SDL.h>

#include <iostream>


StateMainMenu::StateMainMenu()
{
	if ( !renderer ) {
		std::cout << "You haven't set a renderer in the State class. Specify a valid one before creating a State object.\n";
		return;
	}

	snakeTitleTex = renderer->createTexture( "res/title.png" );
	enterToPlayTex = renderer->createTexture( "res/text_play.png" );
}

StateMainMenu::~StateMainMenu()
{
	renderer->destroyTexture( snakeTitleTex );
	renderer->destroyTexture( enterToPlayTex );

}

State* StateMainMenu::update()
{
	const Uint8* keyStates = SDL_GetKeyboardState( 0 );
	if ( keyStates[SDL_SCANCODE_RETURN] )
	{
		return new StatePlaying();
	}

	return 0;
}

void StateMainMenu::render()
{
	// Render background.
	renderer->drawRect( 0x604020FF, (renderer->getWindowWidth() - 550) / 2, (renderer->getWindowHeight() - 700) / 2, 550, 700, 0 );

	// Title image.
	renderer->drawRect( snakeTitleTex, (renderer->getWindowWidth() - 416) / 2, renderer->getWindowHeight() / 2 - 100, 416, 130, 0 );

	// Instructions.
	renderer->drawRect( enterToPlayTex, (renderer->getWindowWidth() - 325) / 2, 680, 325, 30, 0 );
}