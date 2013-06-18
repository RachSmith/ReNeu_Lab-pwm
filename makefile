CC=gcc-4.4
LDFLAGS=-ldl -ggdb
OBJECTS=Example.o NiFpga.o
EXECUTABLE=Example

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)

Example.o: NiFpga_Math_Pid.h NiFpga.h

NiFpga.o: NiFpga.h

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)
