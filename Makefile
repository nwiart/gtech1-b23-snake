CC=g++
# Adapt the variables below to your needs:
EXE=snake.out
CPP=main.cpp Renderer.cpp SnakeRenderer.cpp Texture.cpp Snake.cpp State.cpp StatePlaying.cpp StateGameOver.cpp StateMainMenu.cpp Utils.cpp
HPP=Fruit.hpp Renderer.h Snake.h SnakeRenderer.h State.h Texture.h Utils.h

# The default is build the executable file:
default: $(EXE)

# The executable file must be rebuilt if source files changed:
$(EXE): $(CPP) $(HPP)
	$(CC) $(CPP) -lSDL2 -lSDL2_image -o $(EXE)

# Run of the (always up-to-date) executable:
run: $(EXE)
	DISPLAY=:0 ./$(EXE)

# Build the UML diagram as a PNG image:
uml/classes.png: $(HPP)
	./uml/mk_uml.sh $@ $^

# Count the number of lines of code:
nblines:
	@wc -l $(CPP) $(HPP)
