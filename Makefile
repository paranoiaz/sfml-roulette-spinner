CC = g++
OUTPUT_NAME = spinner

all: compile link exec
compile:
	${CC} -c main.cpp windowmanager.cpp spinner.cpp player.cpp betmanager.cpp button.cpp -I ./include
link:
	${CC} main.o windowmanager.o spinner.o player.o betmanager.o button.o -o ${OUTPUT_NAME}.exe -L ./lib -l sfml-graphics -l sfml-window -l sfml-system
exec:
	${OUTPUT_NAME}.exe
clean:
	del ${OUTPUT_NAME}.exe main.o windowmanager.o spinner.o player.o betmanager.o button.o