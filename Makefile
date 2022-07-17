CXX = g++
CXXFLAGS = -std=c++14 -MMD
OBJECTS = main.o game.o character.o player.o human.o vampire.o posn.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = cc3k

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm ${DEPENDS} ${OBJECTS} cc3k.exe

-include ${DEPENDS} # reads the .d files and reruns dependencies
