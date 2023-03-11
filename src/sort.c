#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quicksort.h"

#define MAX_STRLEN     64 // Not including '\0'
#define MAX_ELEMENTS 1024

void display_usage(char *basename) {
	char *usage = "Usage: %s [-i|-d] [filename]\n"
		      "   -i: Specifies the input contains ints.\n"
		      "   -d: Specifies the input contains doubles.\n"
		      "   filename: The file to sort. If no file is supplied, input is read from\n"
		      "             stdin.\n" 
		      "   No flags defaults to sorting strings.\n";
	fprintf(stderr, usage, basename);
}

int main(int argc, char **argv) {
	int i_flag = 0;
	int d_flag = 0;
	int file_flag = 0;
	int str_flag = 0;
	int option;
	while ((option = getopt(argc, argv, ":id")) != -1) {
		switch (option) {
			case 'i':
				i_flag = 1;
				break;
			case 'd':
				d_flag = 1;
				break;
			case '?': //this takes care of an invalid flag
				fprintf(stderr, "Error: Unknown option '-%c' received.\n", optopt);
				display_usage(argv[0]); //passes in the name of the program;
				return EXIT_FAILURE;
			default: 
				return EXIT_FAILURE; 
		}
	}

	//this is if there is no args/flags: set to string type and say that there is a file. 
	if (optind != 0 && optind < 2){
		str_flag = 1;
		file_flag = 1;
	}

	if(optind >= argc){
		file_flag = 0; 
	}
	else if (optind + 1 < argc) {
		fprintf(stderr, "Error: Too many files specified.\n");
	}
	else {
		file_flag = 1; 
	} 

	//char buf[BUFSIZE]; // set buffer 

	//this checks if there is a valid input file 
	if(file_flag == 1){

		FILE *infile = fopen(argv[2], "r"); 
		if(infile == NULL){
			fprintf(stderr, "Error: Cannot open '%s'. %s.\n", argv[2], strerror(errno));
	        	return EXIT_FAILURE;
		}
	}

	//check if there are multiple files
	if((optind >= 2 && i_flag == 0 && d_flag == 0) || (optind >= 3 && i_flag == 1) || (optind >= 3 && d_flag == 1)){
		fprintf(stderr, "Error: Too many files specified.\n");
		return EXIT_FAILURE; 
	}	

	//check if there are multiple valid flags
	if( i_flag == 1 && d_flag == 1){
		fprintf(stderr, "Error: Too many flags specified.\n");
		return EXIT_FAILURE; 
	}


	str_flag += 1; 

	return EXIT_SUCCESS;
}
