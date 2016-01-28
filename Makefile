CC=g++
SRCS=$(wildcard *.cc)
DEPS=$(patsubst %.cc, %.d, $(SRCS))
OBJS=$(patsubst %.cc, %.o, $(SRCS))
CFLAGS_MKL=-I/opt/intel/mkl/include
CFLAGS=-Wall -O2 $(CFLAGS_MKL)
LIBS_MKL=-L/opt/intel/mkl/lib/intel64 -lmkl_intel_lp64 \
	-lmkl_sequential -lmkl_core -pthread
LIBS=$(LIBS_MKL)
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
