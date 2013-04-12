default: example

example:
	gcc example.c -o example `pkg-config clutter-1.0 --cflags --libs`
	gcc -lm example.cairo.c -o example.cairo `pkg-config clutter-1.0 --cflags --libs`
	gcc -lm ctests.c -o ctests `pkg-config clutter-1.0 --cflags --libs`
	gcc -lm exampletex.c -o exampletex `pkg-config clutter-1.0 --cflags --libs`
clean:
	-rm -f example example.cairo ctests
