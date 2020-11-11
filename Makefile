OBJS := Hero.o JSON.o Monster.o main.o Character.o
FILES := Hero.cpp JSON.cpp Monster.cpp Character.cpp
CFLAGS := -std=c++17 -Wall -Wextra
CC := g++

VLGFLAGS := --error-exitcode=1 --leak-check=full -s --show-leak-kinds=all
CHCKFLAGS:= --enable=warning,style,performance --error-exitcode=1 --output-file=styleAndPerformance.txt
TESTFLDR := test

rpg: $(OBJS)
	$(CC) $(CFLAGS) -o rpg $(OBJS)
Character.o: Character.cpp
	$(CC) $(CFLAGS) -c Character.cpp
Hero.o: Hero.cpp
	$(CC) $(CFLAGS) -c Hero.cpp
JSON.o: JSON.cpp
	$(CC) $(CFLAGS) -c JSON.cpp
Monster.o: Monster.cpp
	$(CC) $(CFLAGS) -c Monster.cpp
main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp
clean:
	 rm -rf *.o rpg ./DOCS
docs:
	doxygen doxconf
leaktest: rpg
	$ (cp rpg $(TESTFLDR)/rpg && cd $(TESTFLDR) && valgrind $(VLGFLAGS) ./rpg scenario1.json)
cppcheck:
	cppcheck $(FILES)  $(CHCKFLAGS)


creategtest: 
	$ (cd $(TESTFLDR) && cmake CMakeLists.txt && make)
unittest: creategtest
	$ (cd $(TESTFLDR) && ./runTests)

test: leaktest cppcheck unittest 
