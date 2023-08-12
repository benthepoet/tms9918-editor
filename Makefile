CC = gcc
CFLAGS = -g -Wall
SDL2 = `sdl2-config --cflags --libs`
OUTDIR = bin

main: $(wildcard src/*.c)
	$(CC) $(CFLAGS) -o $(OUTDIR)/$@ $^ $(SDL2)