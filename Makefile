all: exec

exec:
	cd scr && $(MAKE)
	cd .. && cd tests && $(MAKE)

debug:
	cd scr && $(MAKE) debug

clean:
	cd scr && $(MAKE) clean
	cd .. && cd tests && $(MAKE) clean