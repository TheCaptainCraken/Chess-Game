CC = gcc
CFLAGS = -O1 -Wall -Wno-missing-braces
LINKFLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm
LINKPATH = dependencies/lib
OUTPUTDIR = build
APPLICATIONNAME = app.exe
CFILES = src/main.c

all: $(CFILES)
	@mkdir $(OUTPUTDIR)
	$(CC) $(CFILES) -o $(OUTPUTDIR)/$(APPLICATIONNAME) $(CFLAGS) -L $(LINKPATH) $(LINKFLAGS)
	@echo created executable file in $(OUTPUTDIR)/$(APPLICATIONNAME)
