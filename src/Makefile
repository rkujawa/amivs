CC=vc
RMRF=rm -rf

CFLAGS=
LDFLAGS=-lamiga

OBJECTS=amivs.o file.o clockport.o 
ADDHEADERS=

EXECUTABLE=amivs

all: $(EXECUTABLE) 

amivs : $(OBJECTS)
	$(CC) -o $(EXECUTABLE) $(LDFLAGS) $(OBJECTS)

%.o : %.c %.h $(ADDHEADERS)
	$(CC) $(CFLAGS) -c $<

clean :
	$(RMRF) $(OBJECTS) $(EXECUTABLE)  

