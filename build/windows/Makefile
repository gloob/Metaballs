# cygwin
TARGET = metaballs.exe
OBJS = metaballs.o particle.o cube.o

CC = gcc
INCDIR =
CFLAGS = -O2 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
LIBS = -lglut32 -lglu32 -lopengl32 -lm

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)

%.o: ../../src/%.c
	$(CC) -c $(CFLAGS) -o $@ $<

%.o: ../../src/%.cpp
	$(CC) -c $(CXXFLAGS) -o $@ $<

clean:
	-rm -f $(TARGET) $(OBJS)
