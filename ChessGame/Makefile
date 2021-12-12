CC = gcc
CFLAGS = -O1 -Wall -Wno-missing-braces
LINKFLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm
LINKPATH = dependencies/lib
OUTPUTDIR = debug_build
APPLICATIONNAME = app.exe
CFILES = src/main.c src/libraries/board.c src/libraries/loader.c src/libraries/events.c 

all: $(CFILES)
	@mkdir $(OUTPUTDIR)
	$(CC) $(CFILES) -o $(OUTPUTDIR)/$(APPLICATIONNAME) $(CFLAGS) -L $(LINKPATH) $(LINKFLAGS)
	@echo created executable file in $(OUTPUTDIR)/$(APPLICATIONNAME)

clean:
	del $(OUTPUTDIR)\$(APPLICATIONNAME) 
	rmdir $(OUTPUTDIR)
