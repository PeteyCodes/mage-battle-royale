
src = $(wildcard src/*.c)
obj = $(src:.c=.o)

INCLUDES = -I/usr/local/include 
CFLAGS = -c -Wall -Wextra -Wpedantic -DHAVE_ASPRINTF -g -O0
LDFLAGS = -L/usr/local/lib -lSDL2 -lSDL2_image 

magebr: $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ $(CFLAGS) $(INCLUDES) $<

all: clean magebr
.PHONY: clean

clean:
	rm -rf $(obj) magebr
	clear

