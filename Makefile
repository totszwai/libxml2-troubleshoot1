
TOPDIR?=/home/et5341/source/repos

CC=g++
CFLAGS=	-Wall -fstack-protector-all -fpie  -fPIC -O0 -g \
		-I$(TOPDIR)/libxml2-carillon/src/libxml2-2.13.1/include

LFLAGS=	$(TOPDIR)/libxml2-carillon/src/libxml2-2.13.1/.libs/libxml2.a

%.o: %.cc
	$(CC) $(CFLAGS) -c -o $@ $<

main1: main1.o
	$(CC) -o $@ $^ $(LFLAGS)

main2: main2.o
	$(CC) -o $@ $^ $(LFLAGS)
