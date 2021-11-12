CXX = g++
CXXFLAGS = -Wall

proj2: Ship.o Game.o proj2.cpp
	$(CXX) $(CXXFLAGS) Ship.o Game.o proj2.cpp -o proj2

Game.o: Ship.o Game.cpp Game.h
	$(CXX) $(CXXFLAGS) -c Game.cpp

Ship.o: Ship.h Ship.cpp Material.h
	$(CXX) $(CXXFLAGS) -c Ship.cpp

clean:
	rm *.o*
	rm *~ 

run:
	./proj2
