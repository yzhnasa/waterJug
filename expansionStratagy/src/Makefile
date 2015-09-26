OBJS = Main.o StateExpansion.o Rule.o CompareState.o State.o
CC = g++
CFLAGS = -Wall -g

waterJugStateExpansion: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o waterJugStateExpansion
Main.o: Main.cpp Main.h 
	${CC} ${CFLAGS} -c Main.cpp
StateExpansion.o: StateExpansion.cpp StateExpansion.h State.h CompareState.h Rule.h
	${CC} ${CFLAGS} -c StateExpansion.cpp
Rule.o: Rule.cpp Rule.h State.h
	${CC} ${CFLAGS} -c Rule.cpp
CompareState.o: CompareState.cpp CompareState.h State.h
	${CC} ${CFLAGS} -c CompareState.cpp
State.o: State.cpp State.h
	${CC} ${CFLAGS} -c State.cpp

clean:
	/bin/rm ${OBJS}