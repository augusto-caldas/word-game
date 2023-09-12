#include <stdio.h>
#include "utils.h"

void load_word_list(char dictionary[DICT_SIZE][WORD_SIZE+1]){
    
    char *file_name = "./word_list";
	
	FILE* f = fopen(file_name, "r");
	int idx = 0;

	if (f == NULL){
		printf("%s does not exist. Please ensure you have downloaded it from Canvas.", file_name);
	}
	else{
		while(fscanf(f, "%s", dictionary[idx++]) != EOF);
	}
}