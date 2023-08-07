CC="gcc"
ascii_art: $(wildcard src_files/*) src_files/art.h
	$(CC) $(wildcard src_files/*) src_files/art.h -g -std=gnu11 -o ascii_art -lm
install:
	cp -f ascii_art /usr/local/bin
clean:
	$(CC) $(wildcard src_files/*) src_files/art.h -g -std=gnu11 -o ascii_art -lm && rm vg*

src_files/art.h: asciiartdb-asciiarteu.json
	@echo xxd $@
	@echo "unsigned char arth_string[] = { " > $@
	@cat $^ | xxd -i - >> $@
	@echo ", 0x00};" >> $@
	@echo "unsigned int arth_len = `wc -c $^ | awk 'END{print $$1}'`;" >> $@
