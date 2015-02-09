CC=`cat ../.compiler`
INCLUDEDIRS=-I../include
CCFLAGS=-fPIC -g -O2 -fstrict-aliasing -Wall -Werror
ECFLAGS=`cat ../.ecflags`
LDFLAGS=-shared -s
ELFLAGS=`cat ../.elflags`
ARCHFLAGS=`cat ../.archflags`
TARGET=libfsop.so

all:
	${CC} ${INCLUDEDIRS} ${CCFLAGS} ${ECFLAGS} ${ARCHFLAGS} -c dir.c
	${CC} ${INCLUDEDIRS} ${CCFLAGS} ${ECFLAGS} ${ARCHFLAGS} -c file.c
	${CC} ${INCLUDEDIRS} ${CCFLAGS} ${ECFLAGS} ${ARCHFLAGS} -c mm.c
	${CC} ${INCLUDEDIRS} ${CCFLAGS} ${ECFLAGS} ${ARCHFLAGS} -c path.c
	${CC} ${LDFLAGS} -o ${TARGET} dir.o file.o mm.o path.o ${ELFLAGS}

clean:
	rm -f *.o
	rm -f ${TARGET}

