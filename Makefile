all :
	make seg
	make demon-child
	make demon-kitties

seg : seg.c
	gcc -o seg seg.c

demon-child : demon-child.c
	gcc -o demon-child demon-child.c

demon-kitties : demon-kitties.c
	gcc -o demon-kitties demon-kitties.c
