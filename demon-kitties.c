#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <signal.h>

void handler(int sig) {
	//do nothing//
}

// copy self into another file with a random name of 8 lowercase characters
// make copy executable
// execute with exec (man 3 exec)
// make it terminate after 10 runs

int main(int argc, char** argv) {
	if(argc != 2) {
		printf("Usage: ./kitties n");
		return -1;
	}
	int num_copies = atoi(argv[1]);
	int armed = strcmp(argv[1], "-ARM-");
	// is also triggered for non-integers
	if(num_copies == 0 && armed!=0 ) {
		return 0;
	}
	// if we got a negative integer
	if(num_copies < 0) {
		printf("n must be a positive number");
		return -1;
	}

	// Register signals
	signal(SIGINT, handler);
	signal(SIGSEGV, handler);
	signal(SIGKILL, handler);
	signal(SIGTERM, handler);

	// fork
	fork();

	char file_name[9];
	// seed the rng (time returns time since unix epoch in seconds, clock returns number of millis since start of execution
	srand( time(NULL) + clock() );
	int i;
	for(i=0; i<8; i++) {
		long int rando = rand();
		//26 letters in the alphabet, shift up to ASCII value 61
		file_name[i] = (rando % 26) + 97;
	}
	// null terminate
	file_name[8] = 0;
	// could use the mode_t parameter in open to skip the chmod call, but we'll do it anyway
	int copy_fd = open(file_name, O_CREAT | O_WRONLY);
	int orig_fd = open("kitties", O_RDONLY);
	char buff[4096];
	int bytes_read = read(orig_fd, buff, 4096);
	while(bytes_read != 0) {
		write(copy_fd, buff, bytes_read);
		bytes_read = read(orig_fd, buff, 4096);
	}
	fchmod(copy_fd, 0755);
	close(copy_fd);
	close(orig_fd);

	char arg1[6];
	sprintf(arg1, "%d", num_copies-1);
	char *args[3];
	args[0] = file_name;
	if( armed== 0) {
		// copy 1st param, will never terminate
		args[1] = argv[1];
	} else
		args[1] = arg1;
	args[2] = NULL;
	execv(file_name, args);
}
