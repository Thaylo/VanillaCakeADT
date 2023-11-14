all:
	gcc *.c -otest

run:
	./test

clean:
	rm test