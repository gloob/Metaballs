TARGET = metaballs
OBJS = ../metaballs.o ../particle.o ../cube.o callbacks.o

INCDIR =
CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
LIBS = -lglut -lGLU -lGL -lm -lc -lpsputility -lpspdebug -lpspge -lpspdisplay -lpspctrl -lpspsdk -lpspvfpu -lpsplibc -lpspuser -lpspkernel -lpsprtc

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Metaballs [gloob/TsT]

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
