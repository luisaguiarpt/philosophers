#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	struct timeval	start;
	struct timeval	tv;
	long int		elapsed;

	gettimeofday(&start, NULL);
	printf("seconds: %ld\n", start.tv_sec);
	printf("micro: %ld\n", start.tv_usec);
	sleep(2);
	gettimeofday(&tv, NULL);
	printf("seconds: %ld\n", tv.tv_sec);
	printf("micro: %ld\n", tv.tv_usec);
	elapsed = tv.tv_sec * 1000 + tv.tv_usec / 1000 - start.tv_sec * 1000 - start.tv_usec / 1000;
	printf("elapsed: %ld\n", elapsed);
}
