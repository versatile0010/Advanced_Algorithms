#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>

int main()
{
	LARGE_INTEGER freq, start, stop;
	double diff;

	QueryPerformanceFrequency(&freq);   // compute frequency
	QueryPerformanceCounter(&start);  // starting point

	/*
	something
	*/

	QueryPerformanceCounter(&stop);   // stopping point
	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;  // caculate time
	printf("%lf", diff);

	return 0;
}
