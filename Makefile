OBJS := Hero.o Json.o Player.o main.o
FILES := Hero.cpp Json.cpp Player.cpp main.cpp
CFLAGS := -std=c++17 -Wall -Wextra
CC := g++

VLGFLAGS := --error-exitcode=1 --leak-check=full
CHCKFLAGS:= --enable=warning,style,performance --error-exitcode=1 --output-file=styleAndPerformance.txt
TESTFLDR := test

rpg: $(OBJS)
	$(CC) $(CFLAGS) -o rpg $(OBJS)

Hero.o: Hero.cpp
	$(CC) $(CFLAGS) -c Hero.cpp
Json.o: Json.cpp
	$(CC) $(CFLAGS) -c Json.cpp
Player.o: Player.cpp
	$(CC) $(CFLAGS) -c Player.cpp
main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp
clean:
	rm -rf *.o rpg ./DOCS
docs:
	doxygen doxconf
valgrind: rpg
	valgrind $(VLGFLAGS)  ./rpg $(TESTFLDR)/units/1.json $(TESTFLDR)/units/2.json
cppcheck:
	cppcheck $(FILES)  $(CHCKFLAGS)

CreateTest:
	cmake $(TESTFLDR)/CMakeLists.txt
creategtest: CreateTest
	$ (cd $(TESTFLDR) && make)
gtest: creategtest
	$ (cd $(TESTFLDR) && ./runTests)

test: valgrind cppcheck gtest 
