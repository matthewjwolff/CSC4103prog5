#include <signal.h>
#include <unistd.h>

void handler(int sig) {
	fork();
}

void main() {
	// Install signal handlers
	signal(SIGINT, handler);
	signal(SIGSEGV, handler);
	signal(SIGKILL, handler);
	signal(SIGTERM, handler);
	while(1) {}
}
