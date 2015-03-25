SYSBINDIR=`cat .dirbin`
SYSCACHEDIR=`cat .dircache`
SYSCONFDIR=`cat .dirconf`
SYSDOCDIR=`cat .dirdoc`
SYSINCLUDEDIR=`cat .dirinclude`
SYSLIBDIR=`cat .dirlib`
SYSMANDIR=`cat .dirman`
SYSRUNDIR=`cat .dirrun`
SYSSBINDIR=`cat .dirsbin`
SYSSHAREDIR=`cat .dirshare`
SYSTMPDIR=`cat .dirtmp`

all:
	cd src && make && cd ..

install_all:
	mkdir -p ${SYSLIBDIR}
	mkdir -p ${SYSINCLUDEDIR}/fsop
	cp src/libfsop.* ${SYSLIBDIR}/
	cp include/*.h ${SYSINCLUDEDIR}/fsop/

clean:
	cd src && make clean && cd ..

