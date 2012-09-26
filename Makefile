CC = g++
CFLAGS = -m

SFML= -lsfml-graphics -lsfml-window -lsfml-system
SOURCE=src

StopDying: src/*.cpp src/*.h
	$(CC) -o StopDying src/main.cpp src/Game.cpp src/Entity.cpp src/Enemy.cpp src/Player.cpp $(SFML)

run: StopDying
	./StopDying
clean:
	rm -f StopDying
