CC=`cat ../compiler`
CCFLAGS=-O2 -fstrict-aliasing -Wall -Werror
LDFLAGS=-lfsop -s

all:
	${CC} ${CCFLAGS} -c cp.c
	${CC} -o cp cp.o ${LDFLAGS}
	${CC} ${CCFLAGS} -c mv.c
	${CC} -o mv mv.o ${LDFLAGS}
	${CC} ${CCFLAGS} -c cpdir.c
	${CC} -o cpdir cpdir.o ${LDFLAGS}
	${CC} ${CCFLAGS} -c mvdir.c
	${CC} -o mvdir mvdir.o ${LDFLAGS}

clean:
	rm -f *.o
	rm -f cp mv cpdir mvdir

