build: my_octave

my_octave: my_octave.c
	gcc -o my_octave my_octave.c -Wall -Wextra
	
clean:
	rm -f my_octave
	
.PHONY: pack clean
