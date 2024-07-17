
TOPDIR?=/home/et5341/source/repos

CC=g++
CFLAGS=	-Wall -fstack-protector-all -fpie  -fPIC -O0 -g \
		-I$(TOPDIR)/xmlsec-carillon/src/xmlsec1-1.2.38/include -DXMLSEC_STATIC=1 -DXMLSEC_CRYPTO_OPENSSL=1 -DXMLSEC_NO_SIZE_T \
		-I$(TOPDIR)/libxslt-carillon/src/libxslt-1.1.41 \
		-I$(TOPDIR)/libxml2-carillon/src/libxml2-2.13.1/include

LFLAGS=	-ldl -lpthread \
		$(TOPDIR)/xmlsec-carillon/src/xmlsec1-1.2.38/src/.libs/libxmlsec1.a \
		$(TOPDIR)/libxslt-carillon/src/libxslt-1.1.41/libxslt/.libs/libxslt.a \
		$(TOPDIR)/libxml2-carillon/src/libxml2-2.13.1/.libs/libxml2.a

%.o: %.cc
	$(CC) $(CFLAGS) -c -o $@ $<

main: main.o
	$(CC) -o $@ $^ $(LFLAGS)