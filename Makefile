ascii_art: main.c config.h mjson.h mjson.c
	$(CC) main.c mjson.c config.h mjson.h -g -std=gnu11 -o ascii_art -lm
install:
	cp -f ascii_art /usr/local/bin
clean:
	$(CC) main.c mjson.c mjson.h config.h -g -std=gnu11 -o ascii_art -lm && rm vg*
