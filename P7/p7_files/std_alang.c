#include "stdio.h"
#include "stdlib.h"
#include <inttypes.h>
#include <time.h>

void printBool(int64_t c){
	if (c == 0){
		printf("false");
	} else{
		printf("true");
	}
	fflush(stdout);
}

int64_t magic(){
	static int init = 0;
	if (init == 0){
		srand(time(NULL));
		init = 1;
	}
        // Get a random number, mask it to 1 bit
	return rand() & 0x1;
}

//Note: there is no exit function in the 
// standard library, but you could add one
// or call exit directly from your assembly code
// for the exit quad

void printInt(long int num){
	printf("%ld", num);
	fflush(stdout);
}

void printString(const char * str){
	fprintf(stdout, "%s", str);
	fflush(stdout);
}

int64_t getBool(){
	char c;
	fscanf(stdin, "%c", &c);
	getchar(); // Consume trailing newline
	if (c == '0'){
		return 0;
	} else {
		return 1;
	}
}

int64_t getInt(){
	char buffer[32];
	for (int i = 0 ; i < 32; i++){
		buffer[i] = 0;
	}
	fgets(buffer, 32, stdin);
	long int res = atol(buffer);
	return res;
}
