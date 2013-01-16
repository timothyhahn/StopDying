CC = g++
CFLAGS = -m

SFML= -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SOURCE=src
OUTPUT=StopDying
SOURCE_FILES=src/main.cpp src/Game.cpp src/Entity.cpp src/Enemy.cpp src/Player.cpp src/Bullet.cpp src/Sword.cpp 

StopDying: src/*.cpp src/*.h
	$(CC) -o $(OUTPUT) $(SOURCE_FILES) $(SFML)

run: StopDying
	./StopDying
clean:
	rm -f StopDying
debug: src/*.cpp src/*.h
	$(CC) -o $(OUTPUT) -ggdb $(SOURCE_FILES) $(SFML)
	gdb $(OUTPUT)
