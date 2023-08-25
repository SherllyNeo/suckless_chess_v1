CFLAGS = -g -O -Wall -W -pedantic -std=c99 -O0 -I. -I/raylib/src -I../src -DPLATFORM_RPI

LDFLAGS = -L/raylib/src -L/opt/vc/lib
LDLIBS = -lraylib -lm 

chess: src_files/main.c
	gcc $(CFLAGS) $(LDFLAGS) src_files/main.c -o chess $(LDLIBS)
install: src_files/main.c
	gcc $(CFLAGS) $(LDFLAGS) src_files/main.c -o chess $(LDLIBS) && cp ./chess $(HOME)/.local/bin/

