#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

// Verification if is Windows or Linux

#ifdef _WIN32
	#include <windows.h>
#else
	#include <unistd.h>
#endif

void my_wait(){
	#ifdef _WIN32
		Sleep(100);
	#else
		usleep(100000);
	#endif
}

void print_progress(size_t count, size_t max) {
	const char prefix[] = "Loading Game: [";
	const char suffix[] = "]";
	const size_t prefix_length = sizeof(prefix) - 1;
	const size_t suffix_length = sizeof(suffix) - 1;
	char *buffer = calloc(max + prefix_length + suffix_length + 1, 1); // +1 for \0
	size_t i = 0;

	strcpy(buffer, prefix);
	for (; i < max; ++i)
	{
		buffer[prefix_length + i] = i < count ? '*' : ' ';
	}

	strcpy(&buffer[prefix_length + i], suffix);
	printf("\b%c[2K\r%s", 27, buffer);
	fflush(stdout);
	free(buffer);
}

#define NUM_SECS 20

void loadingBar()
{
	size_t num_secs = 1, max_secs = NUM_SECS;
	printf("%s\n", "");
	print_progress(0, max_secs);
	for (; num_secs <= max_secs; ++num_secs)
	{
		print_progress(num_secs, max_secs);
        my_wait();
	}
}
