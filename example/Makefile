CC=`cat ../.compiler`
CCFLAGS=-O2 -fstrict-aliasing -Wall -Werror
LDFLAGS=-lfsop -s
ARCHFLAGS=`cat ../.archflags`

all:
	${CC} ${CCFLAGS} ${ARCHFLAGS} -c cp.c
	${CC} -o cp cp.o ${LDFLAGS}
	${CC} ${CCFLAGS} ${ARCHFLAGS} -c mv.c
	${CC} -o mv mv.o ${LDFLAGS}
	${CC} ${CCFLAGS} ${ARCHFLAGS} -c cpdir.c
	${CC} -o cpdir cpdir.o ${LDFLAGS}
	${CC} ${CCFLAGS} ${ARCHFLAGS} -c mvdir.c
	${CC} -o mvdir mvdir.o ${LDFLAGS}

clean:
	rm -f *.o
	rm -f cp mv cpdir mvdir

