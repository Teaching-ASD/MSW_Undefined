OBJS := Hero.o JSON.o Monster.o Character.o Map.o Game.o PreparedGame.o MarkedMap.o TextRenderer.o HeroTextRenderer.o main.o ObserverTextRenderer.o ObserverSVGRenderer.o CharacterSVGRenderer.o
FILES := Hero.cpp JSON.cpp Monster.cpp Character.cpp Map.cpp Game.cpp PreparedGame.cpp MarkedMap.cpp Render.cpp TextRenderer.cpp HeroTextRenderer.cpp ObserverTextRenderer.cpp ObserverSVGRenderer.cpp CharacterSVGRenderer.cpp
CFLAGS := -std=c++17 -Wall -Wextra
CC := g++-10
SHELL := /bin/bash

VLGFLAGS := --error-exitcode=1 --leak-check=full -s
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
Map.o: Map.cpp
	$(CC) $(CFLAGS) -c Map.cpp
MarkedMap.o: MarkedMap.cpp
		$(CC) $(CFLAGS) -c MarkedMap.cpp
Game.o: Game.cpp
	$(CC) $(CFLAGS) -c Game.cpp
PreparedGame.o: PreparedGame.cpp
		$(CC) $(CFLAGS) -c PreparedGame.cpp
TextRenderer.o: TextRenderer.cpp Renderer.h
		$(CC) $(CFLAGS) -c TextRenderer.cpp
HeroTextRenderer.o: HeroTextRenderer.cpp Renderer.h
		$(CC) $(CFLAGS) -c HeroTextRenderer.cpp
ObserverTextRenderer.o: ObserverTextRenderer.cpp Renderer.h
		$(CC) $(CFLAGS) -c ObserverTextRenderer.cpp
ObserverSVGRenderer.o: ObserverSVGRenderer.cpp Renderer.h
		$(CC) $(CFLAGS) -c ObserverSVGRenderer.cpp
CharacterSVGRenderer.o: CharacterSVGRenderer.cpp Renderer.h
		$(CC) $(CFLAGS) -c CharacterSVGRenderer.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp
clean:
	 rm -rf *.o rpg ./DOCS
docs:
	doxygen doxconf
leaktest: rpg
	$ (cp rpg $(TESTFLDR)/rpg && cd $(TESTFLDR) && (valgrind $(VLGFLAGS) ./rpg scenariomm.json) <<< "exit")  
cppcheck:
	cppcheck $(FILES)  $(CHCKFLAGS)


creategtest: 
	$ (cd $(TESTFLDR) && cmake CMakeLists.txt && make)
unittest: creategtest
	$ (cd $(TESTFLDR) && ./runTests)

test: leaktest cppcheck unittest

run: rpg
	$ (cp rpg $(TESTFLDR)/rpg && cd $(TESTFLDR) && ./rpg scenariomm.json)