TARGET = metaballs
OBJS = metaballs.o particle.o cube.o vertex.o

INCDIR = 
CC=gcc
CFLAGS = -O2 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

FRAMEWORKS=-framework GLUT -framework OpenGL -framework Cocoa
LIBDIR = -L"/System/Library/Frameworks/OpenGL.framework/Libraries"
LDFLAGS =
LIBS = -lglut -lGLU -lGL -lm -l

$(TARGET): $(OBJS)
	$(CC) $(FRAMEWORKS) $(LDFLAGS) -o $@ $(OBJS)

%.o: ../%.c
	$(CC) -c $(CFLAGS) -o $@ $<

%.o: ../%.cpp
	$(CC) -c $(CXXFLAGS) -o $@ $<

clean:
	-rm -f $(TARGET) $(OBJS)

