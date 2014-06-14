CXX = g++
CXXFLAGS = -Wall -std=c++0x -MMD
OBJECTS = Card.o Command.o launcher.o Game.o Player.o HumanPlayer.o CompPlayer.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}	# reads the .d files and reruns dependencies

