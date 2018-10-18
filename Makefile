all: exec

exec:
	cd scr && $(MAKE) clean && $(MAKE)

clean:
	cd scr && $(MAKE) clean