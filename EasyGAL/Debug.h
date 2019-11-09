#pragma once

#ifdef _DEBUG
	#define ERROR(FORMAT, ...) \
		printf("%s%s%s%s%s%s%s%i%s", "Error in ", __FILE__, "\n", "In function ", __FUNCTION__, "\n", "In line ", __LINE__, ": "); \
		printf(FORMAT, __VA_ARGS__); \
		printf("%s", "\n")
#else
	#define ERROR(FORMAT, ...) \
		printf("%s", "[ERROR] "); \
		printf(FORMAT, __VA_ARGS__); \
		printf("%s", "\n")
#endif
 
