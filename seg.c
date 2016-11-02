#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char** argv) {
	if(argc!=2) {
		printf("Usage: seg [pid]\n");
		exit(1);
	}
	int pid = atoi(argv[1]);
	kill(pid, SIGSEGV);
}
