CPP = g++
FLAGS = -o3 -std=c++17

_main.exe: story.o arrays.o location.o _main.o
	$(CPP) $(FLAGS) story.o arrays.o location.o _main.o -o _main.exe

story.o: story.hpp story.cpp
	$(CPP) $(FLAGS) story.cpp -c -o story.o

arrays.o: arrays.hpp arrays.cpp
	$(CPP) $(FLAGS) arrays.cpp -c -o arrays.o

location.o: location.hpp location.cpp story.hpp story.cpp
	$(CPP) $(FLAGS) location.cpp -c -o location.o

_main.o: _main.cpp story.hpp story.cpp arrays.hpp arrays.cpp location.hpp location.cpp
	$(CPP) $(FLAGS) _main.cpp -c -o _main.o
clean:
	rm -f *.o
