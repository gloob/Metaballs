TARGET = metaballs
OBJS = metaballs.o particle.o cube.o

CC = gcc
INCDIR =
CFLAGS = -O2 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS = 
LIBS = -lglut -lGL -lGLU

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)

%.o: ../%.c
	$(CC) -c $(CFLAGS) -o $@ $<

%.o: ../%.cpp
	$(CC) -c $(CXXFLAGS) -o $@ $<

clean:
	-rm -f $(TARGET) $(OBJS)
