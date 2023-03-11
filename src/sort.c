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

	// check if there's no flags indicating a file and check if there are too many files
	if(optind >= argc){
		file_flag = 0; 
	}
	else if (optind + 1 < argc) {
		fprintf(stderr, "Error: Too many files specified.\n");
		return EXIT_FAILURE; 
	}
	else {
		file_flag = 1; 
	}

	if(file_flag == 1){
		FILE *infile = fopen(argv[optind], "r");

			if(infile == NULL){
			fprintf(stderr, "Error: Cannot open '%s'. %s.\n", argv[optind], strerror(errno));
			return EXIT_FAILURE;
		}	 
	}

	//check if there are multiple valid flags
	if( i_flag == 1 && d_flag == 1){
		fprintf(stderr, "Error: Too many flags specified.\n");
		return EXIT_FAILURE; 
	
	}	

	fprintf(stdout, "i_flag = %d, d_flag = %d, str_flag = %d, file_flag = %d\n", i_flag, d_flag, str_flag, file_flag);

	// at this point, most errors have been checked. time to read in and sort.  

	void* arr = malloc(sizeof(void *) * MAX_ELEMENTS);
      	
	char buf[MAX_STRLEN]; 
	int count = 0; 
	
	if(file_flag == 1){

  		 FILE *infile = fopen(argv[optind], "r");

		 if(infile == NULL){
			 fprintf(stderr, "Error: Cannot open '%s'. %s.\n", argv[optind], strerror(errno)); 
			 return EXIT_FAILURE; 
		 }
	
		 while(fgets(buf, MAX_STRLEN, infile)){
			 char *eoln = strchr(buf, '\n');
			 if(eoln != NULL){
				*eoln = '\0';
			 }
			 
			 fprintf(stdout, "buf = %s\n", buf); 			 
			 //add to array.
			 if(i_flag == 1){
				int *int_ptr = malloc(sizeof(int)); 
				//((int **)arr)[count] = (int *)buf;
				*int_ptr = atoi(buf);
				arr[count] = (void *)int_ptr; 

			 }
			 else if(d_flag == 1){
				((double **)arr)[count] = (double *)buf;
			 }
			 else if(str_flag == 1){
				 ((char ***)arr)[count] = (char **)buf;
			 }
			 count++;
		}
		
	}
	
/*
	if(file_flag == 0){

		while(fgets(buf, MAX_STRLEN, stdin)){
			char *eoln = strchr(buf, '\n');
			if(eoln != NULL){
				*eoln = '\0';
			}
			//add to array.
			arr[count] = (int*)buf;
			count++; 
		}
	}

*/
	for(int i = 0; i < count; i++){
		fprintf(stdout, "%d\n", *((int*)arr + i));
	}


	//free(buf); 
	/*
	for(int i = 0; i < count; i++){
		if(i_flag == 1){
			int *p = (int *) arr[i]; 
			free(p); 
		}
		else if(d_flag == 1){
			float *p = (float *) arr[i];
			free(p); 
		}
		else {
			char *p = (char *) arr[i]; 
			free(p); 
		}
	}

	free(arr); 
	*/
	return EXIT_SUCCESS;
}
