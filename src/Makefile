CC=gcc

# Standar compilation
CFLAGS_STD=-c -Wall -Wextra 
LDFLAGS_STD=

# With O3 optimizations
CFLAGS_OPT=-c -O3 -Wall -Wextra 
LDFLAGS_OPT=

# With Ofast optimizations
CFLAGS_FAST=-c -Wall -Wextra -Ofast
LDFLAGS_FAST=

# Debug compilation
CFLAGS_DBG=-c -pg  -Wall -Wextra  
LDFLAGS_DBG=-lpthread

# With PThreads
CFLAGS_PT=-c -Wall -Wextra -Ofast
LDFLAGS_PT= -lpthread

# With OpenMP
CFLAGS_OMP=-c -fopenmp -Wall -Wextra 
LDFLAGS_OMP= -fopenmp 

# With Ofast optimizations and OpenMP
CFLAGS_FAST_OMP=-c -Ofast -fopenmp -Wall -Wextra 
LDFLAGS_FAST_OMP= -fopenmp 

# With 03 optimizations and OpenMP
CFLAGS_O3_OMP=-c -O3 -fopenmp -Wall -Wextra 
LDFLAGS_O3_OMP= -fopenmp 

COMP_TYPE=PT

CFLAGS  = ${CFLAGS_${COMP_TYPE}}
LDFLAGS = ${LDFLAGS_${COMP_TYPE}}

SOURCES=pcg_basic.c tools.c topology.c pdr_dsr.c edr_eed.c simulation.c input_output.c init.c 
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=simulate

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ -lm

.c.o:
	$(CC) $(CFLAGS) $< -o $@ 
	
clean:
	rm $(EXECUTABLE) -f
	rm *.o *.gch -f
