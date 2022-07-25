CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -g -Werror=vla
OBJECTS = main.o game.o character.o player.o enemy.o human.o vampire.o dragon.o troll.o merchant.o phoenix.o werewolf.o goblin.o item.o potion.o gold.o dragonhoard.o barriersuit.o buff.o atkbuff.o defbuff.o compass.o dwarf.o elf.o mapDetection.o orc.o randoms.o god.o magicarcher.o valkyrie.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = cc3k

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies
