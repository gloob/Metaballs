TARGET = metaballs
OBJS = metaballs.o particle.o cube.o

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


#particle.o: ../particle.c ../particle.h
#	$(CC) -c $(CFLAGS) -o $@ ../particle.c

#cube.o: ../cube.c
#	$(CC) -c $(CFLAGS) -o $@ ../cube.c

#metaballs.o: ../metaballs.c
#	$(CC) -c $(CFLAGS) -o $@ ../metaballs.c

clean:
	-rm -f $(TARGET) $(OBJS)

