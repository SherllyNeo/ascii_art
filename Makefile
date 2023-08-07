.MAIN := ascii_art






CC="gcc"
ascii_art: $(wildcard src_files/*) src_files/art.h
	$(CC) $(wildcard src_files/*) src_files/art.h -g -std=gnu11 -o ascii_art -lm
install:
	cp -f ascii_art /usr/local/bin
clean:
	$(CC) $(wildcard src_files/*) src_files/art.h -g -std=gnu11 -o ascii_art -lm && rm vg*

