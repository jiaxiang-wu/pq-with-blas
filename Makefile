CC=g++
SRCS=$(wildcard *.cc)
DEPS=$(patsubst %.cc, %.d, $(SRCS))
OBJS=$(patsubst %.cc, %.o, $(SRCS))
CFLAGS_OPENBLAS=-I./OpenBLAS-build/include
CFLAGS=-Wall -std=c++11 -O2 $(CFLAGS_OPENBLAS)
LIBS_OPENBLAS=-L./OpenBLAS-build/lib -pthread -lopenblas
LIBS=$(LIBS_OPENBLAS)
DFLAGS=
TARGET=PQwithBLAS

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)
sinclude $(SRCS:.cc=.d)
%d: %cc
	$(CC) -MM $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ ,g' < $@.$$$$ > $@; \
	$(RM) $@.$$$$
%o: %cc
	$(CC) -c -o $@ $< $(CFLAGS) $(DFLAGS)

clean:
	$(RM) $(DEPS) $(OBJS) $(TARGET)
