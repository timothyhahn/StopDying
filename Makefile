CC = g++
CFLAGS = -m

SFML= -lsfml-graphics -lsfml-window -lsfml-system

StopDying: main.cpp Game.cpp Game.h Entity.cpp Entity.h Enemy.cpp Enemy.h Player.cpp Player.h
	$(CC) -o StopDying main.cpp Game.cpp Entity.cpp Enemy.cpp Player.cpp $(SFML)

run: StopDying
	./StopDying

clean:
	rm -f StopDying
