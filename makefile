CC=g++
CFLAGS = -g
num_thread=1
all:screensaver
screensaver:./code/src/main.cpp ./code/obj/shapes.o ./code/obj/collision.o ./code/obj/Grid.o ./code/obj/physics.o
	$(CC) -g ./code/src/main.cpp ./code/obj/collision.o ./code/obj/shapes.o ./code/obj/Grid.o ./code/obj/physics.o -o ss -lGL -lGLU -lglut -lpthread
./code/obj/shapes.o:./code/obj/shapes.cpp
	$(CC) -c ./code/obj/shapes.cpp -o ./code/obj/shapes.o

./code/obj/collision.o:./code/obj/collision.cpp
	$(CC) -c ./code/obj/collision.cpp -o ./code/obj/collision.o 

./code/obj/Grid.o:./code/obj/Grid.cpp
	$(CC) -c ./code/obj/Grid.cpp -o ./code/obj/Grid.o

./code/obj/physics.o:./code/obj/physics.cpp
	$(CC) -c ./code/obj/physics.cpp -o ./code/obj/physics.o

execute:screensaver 
	./ss $(num_thread)
clean:
	rm ss ./code/obj/shapes.o ./code/obj/collision.o ./code/obj/Grid.o ./code/obj/physics.o
