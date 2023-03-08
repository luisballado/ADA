TARGETS = problema_examen

CROSS_TOOL =
CC_CPP = $(CROSS_TOOL)g++
CC_C = $(CROSS_TOOK)gcc

CFLAGS = -std=c++11 

all: clean $(TARGETS)

$(TARGETS):
	$(CC_CPP) $(CFLAGS) $@.cpp -o $@

clean:
	rm -f $(TARGETS)
