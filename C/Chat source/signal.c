#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void timeout(int sig)
{
	if(SIGALRM==sig)
		puts("Time Out!");
	alarm(2);
}

void keycontrol(int sig)
{
	if(SIGINT == sig)
		puts("CTRL+C pressed");
}

int main(int argc, char *argv[])
{
	int i;
	signal(SIGALRM, timeout);
	signal(SIGINT, keycontrol);
	alarm(2);

	for (;;)
	{
		puts("wait...");
		sleep(100);
	}

	return 0;
}
