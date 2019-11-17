#pragma once

#ifdef _DEBUG
	
	#include <ctime>
	#include <ratio>
	#include <chrono>

	/*
	*	If the Program is compiled in debug mode it will display more precise error messages.
	*   When compiled in release it will only display the error message and not the location where the error occured
	*/

	#define ERROR(FORMAT, ...) \
		printf("%s%s%s%s%s%s%s%i%s", "Error in ", __FILE__, "\n", "In function ", __FUNCTION__, "\n", "In line ", __LINE__, ": "); \
		printf(FORMAT, __VA_ARGS__); \
		printf("%s", "\n")

	#define DLOG(FORMAT, ...) \
		printf("%s", "[Debug] "); \
		printf(FORMAT, __VA_ARGS__); \
		printf("%s", "\n")

	/*
	*	Used to measure execution time at specific points.
	*	Prints passed time in seconds.
	*/

	#define BENCH_START \
		int StartLine = __LINE__; \
		chrono::high_resolution_clock::time_point Start = chrono::high_resolution_clock::now()

	#define BENCH_END \
		int EndLine = __LINE__; \
		chrono::high_resolution_clock::time_point End = chrono::high_resolution_clock::now(); \
		printf("%s%i%s%i%s%f%s", "Executing line ", StartLine, " - ", EndLine, " took ",  chrono::duration_cast<chrono::duration<float>>(End - Start).count(), " seconds")

#else

	#define ERROR(FORMAT, ...) \
		printf("%s", "[ERROR] "); \
		printf(FORMAT, __VA_ARGS__); \
		printf("%s", "\n")


	// No debug messages allowed in release.

	#define DLOG

	/*
	*	No benchmarks allowed in release build.
	*	Empty defines that code with BENCH_START and BENCH_END will still compile in release.
	*/

	#define BENCH_START
	#define BENCH_END


#endif




 
