
client_target = magebr
client_src = $(wildcard src/client/*.c)
client_obj = $(client_src:.c=.o)

server_target = magebr-server
server_src = $(wildcard src/server/*.c)
server_obj = $(server_src:.c=.o)


INCLUDES = -I/usr/local/include 
CFLAGS = -c -Wall -Wextra -Wpedantic -DHAVE_ASPRINTF -g -O0
LDFLAGS = -L/usr/local/lib -lSDL2 -lSDL2_image 

$(client_target): $(client_obj)
	$(CC) -o $@ $^ $(LDFLAGS)

$(server_target): $(server_obj)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ $(CFLAGS) $(INCLUDES) $<

emcc:
	emcc $(client_src) $< $(INCLUDES) -O2 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png","jpeg"]' --preload-file assets -o $(client_target).html

all: clean $(client_target) $(server_target) emcc
.PHONY: clean

clean:
	rm -rf $(client_obj) $(client_target)
	rm -rf $(server_obj) $(server_target)
	rm -rf sdltest.dSYM
	rm -f magebr*
	clear

run-client: clean $(client_target)
	echo "Running client..."
	./$(client_target)

run-server: clean $(server_target)
	echo "Running server..."
	./$(server_target)


