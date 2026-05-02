#include <stdio.h>
#include "utils.h"

void load_word_list(char dictionary[DICT_SIZE][WORD_SIZE+1]){
    
    char *file_name = "./word_list.txt";
	
	FILE* f = fopen(file_name, "r");

	if (f == NULL){
		printf("%s does not exist. Please ensure you have downloaded it from github repository.", file_name);
	}
	else{
		while(fscanf(f, "%s", dictionary[1]) != EOF);
	}
}