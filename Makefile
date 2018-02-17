
target = magebr
src = $(wildcard src/*.c)
obj = $(src:.c=.o)

INCLUDES = -I/usr/local/include 
CFLAGS = -c -Wall -Wextra -Wpedantic -DHAVE_ASPRINTF -g -O0
LDFLAGS = -L/usr/local/lib -lSDL2 -lSDL2_image 

$(target): $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ $(CFLAGS) $(INCLUDES) $<

all: clean $(target)
.PHONY: clean

clean:
	rm -rf $(obj) $(target)
	clear

run: clean $(target)
	./$(target)


