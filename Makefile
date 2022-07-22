CXX = g++
OBJECTS = main.o game.o character.o player.o human.o vampire.o posn.o dragon.o troll.o merchant.o phoenix.o werewolf.o goblin.o item.o potion.o gold.o dragonhoard.o barriersuit.o buff.o atkbuff.o defbuff.o compass.o dwarf.o elf.o mapDetection.o orc.o
CXX = g++
DEPENDS = ${OBJECTS:.o=.d}
EXEC = cc3k

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies
