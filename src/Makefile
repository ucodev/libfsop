CC=`cat ../.compiler`
CCFLAGS=-fPIC -g -O2 -fstrict-aliasing -Wall -Werror
ECFLAGS=`cat ../.ecflags`
LDFLAGS=-shared -s
ELFLAGS=`cat ../.elflags`
TARGET=libfsop.so

all:
	${CC} ${CCFLAGS} ${ECFLAGS} -c dir.c
	${CC} ${CCFLAGS} ${ECFLAGS} -c file.c
	${CC} ${CCFLAGS} ${ECFLAGS} -c mm.c
	${CC} ${CCFLAGS} ${ECFLAGS} -c path.c
	${CC} ${LDFLAGS} -o ${TARGET} dir.o file.o mm.o path.o ${ELFLAGS}

clean:
	rm -f *.o
	rm -f ${TARGET}

