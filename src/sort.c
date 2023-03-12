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
		
		fclose(infile); 
	}

	//check if there are multiple valid flags
	if( i_flag == 1 && d_flag == 1){
		fprintf(stderr, "Error: Too many flags specified.\n");
		return EXIT_FAILURE; 
	
	}	

	//fprintf(stdout, "i_flag = %d, d_flag = %d, str_flag = %d, file_flag = %d\n", i_flag, d_flag, str_flag, file_flag);

	//execute for there being a file
	if(file_flag == 1){
		
		//check if the file is valid
		FILE *infile = fopen(argv[optind], "r"); 
		
		if(infile == NULL){
			fprintf(stderr, "Error: Cannot open '%s'. %s.\n", argv[optind], strerror(errno)); 
			return EXIT_FAILURE; 	
		}

	//start reading in data to array 

		char buf[MAX_STRLEN];
		void *arr[MAX_ELEMENTS];
		int count = 0; 

		while(fgets(buf, MAX_STRLEN, infile) && count < MAX_ELEMENTS){
	
		if(str_flag == 1){
			
			arr[count] = strdup(buf); 
		}
		else if (i_flag == 1){
			
			arr[count] = malloc(sizeof(int)); 
			sscanf(buf, "%d", (int *)arr[count]); 
		}
		else if(d_flag == 1){

			arr[count] = malloc(sizeof(double));
			sscanf(buf, "%lf", (double *)arr[count]); 
		}

		count++; 

		}

		fclose(infile);

		//put data in array and sort!

		if(i_flag == 1){ //ints
		
			int *array = malloc(sizeof(int) * count);

			for(int i = 0; i < count; i++){
				array[i] = *(int *)arr[i];
			}

			quicksort(array, count, sizeof(array[0]), int_cmp); 

			for(int i = 0; i < count; i++){
				fprintf(stdout, "%d\n", array[i]); 
			}

			free(array); 

			for(int i = 0; i < count; i++){
				free(arr[i]);
			}
		} else if (d_flag == 1){ //doubles
		
			double *array = malloc(sizeof(double) * count);

			for(int i = 0; i < count; i++){
				array[i] = *(double *)arr[i];	
			}

			quicksort(array, count, sizeof(arr[0]), dbl_cmp); 

			for(int i = 0; i < count; i++){
				fprintf(stderr, "%f\n", array[i]); 
			}

			free(array); 

			for(int i = 0; i < count; i++){
				free(arr[i]);
			}
		}
		else if (str_flag == 1){ //strings
		
			char **array = malloc(sizeof(char *) * count); 

			for(int i = 0; i < count; i++){
			
				array[i] = malloc(strlen((char *)arr[i]) + 1); 
				strcpy(array[i], (char *)arr[i]); 
			}

			quicksort(array, count, sizeof(arr[0]), str_cmp);

			for(int i = 0; i < count; i++){
				fprintf(stdout, "%s", array[i]); 
			}

			for(int i = 0; i < count; i++){
				free(array[i]);
			}

			free(array); 

			for(int i = 0; i < count; i++){
				free(arr[i]); 
			}	
		}
	
	} // end file_flag == 1 if statment (looking at reading from stdin now) 
	else {

		char buf[MAX_STRLEN];
		void *arr[MAX_ELEMENTS];
		int count = 0; 

		if(i_flag == 1){
			while(fgets(buf, MAX_STRLEN, stdin) && count < MAX_ELEMENTS){

				arr[count] = malloc(sizeof(int)); 
				sscanf(buf, "%d", (int *)arr[count]);
				count++;
			}

			int *array = malloc(sizeof(int) * count);

			for(int i = 0; i < count; i++){

				array[i] = *(int *)arr[i];
			}

			quicksort(array, count, sizeof(array[0]), int_cmp); 

			for(int i = 0; i < count; i++){
				fprintf(stdout, "%d\n", array[i]); 
			}

			free(array); 

			for(int i = 0; i < count; i++){
				free(arr[i]); 
			}

		}
		else if(d_flag == 1){
			
			while(fgets(buf, MAX_STRLEN, stdin) && count < MAX_ELEMENTS){

				arr[count] = malloc(sizeof(double));
				sscanf(buf, "%lf", (double *)arr[count]); 
				count++; 
			}

			double *array = malloc(sizeof(double) * count);

			for(int i = 0; i < count; i++){
				array[i] = *(double *)arr[i];
			}

			quicksort(array, count, sizeof(array[0]), dbl_cmp);

			for(int i = 0; i < count; i++){

				fprintf(stdout, "%lf\n", array[i]); 
			}

			free(array); 

			for(int i = 0; i < count; i++){
				free(arr[i]); 
			}

		}
		else if(str_flag == 1){

			while(fgets(buf, MAX_STRLEN, stdin) && count < MAX_ELEMENTS){
				
				arr[count] = malloc(sizeof(char) * MAX_STRLEN); 
				sscanf(buf, "%s", (char *)arr[count]);
				count++; 
			}

			char **array = malloc(sizeof(char *) * count);

			for(int i = 0; i < count; i++){

				array[i] = malloc(sizeof(char) * (strlen((char *)arr[i]) + 1));
				strcpy(array[i], (char *)arr[i]); 
			}

			quicksort(arr, count, sizeof(arr[0]), str_cmp);

			for(int i = 0; i < count; i++){
				fprintf(stdout, "%s\n", array[i]);
			}

			for(int i = 0; i < count; i++){
				free(array[i]);
			}

			free(array);

			for(int i = 0; i < count; i++){
				free(arr[i]);
			}

		}
		

	} // end file_flag != 1 	


	return EXIT_SUCCESS;
}
