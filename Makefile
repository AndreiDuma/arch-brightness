build:
	gcc brightness.c -o build/brightness

clean:
	rm build/brightness

install: build
	cp build/brightness /usr/bin/brightness
	chown root:root /usr/bin/brightness
	chmod 4767 /usr/bin/brightness

.PHONY: build
