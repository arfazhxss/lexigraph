#include <stdio.h>

int main() {
	FILE* inputfile = fopen("fruits.txt", "r");
	if (inputfile==NULL) {
		printf("INPUT FILE EXCEPTION\n");
		return 1;
	}
	FILE* outputfile = fopen("favfruits","w");
	if (outputfile==NULL) {
		printf("OUTPUT FILE EXCEPTION\n");
		fclose(inputfile);
		return 1;
	}
	
	int wordlim = 100;
	char word[wordlim];
	printf("with a limit on word of %d, we're getting:\n",wordlim);
	while (fscanf(inputfile,"%99s", word)==1) {
		printf("while loop passed\n");
		if (strcmp(word,"Pineapple")==0) {
			printf("Excluding the word to be excluded\n");
		} else {
			fprintf(outputfile,"%s\n", word);
		}
	}
	fclose(outputfile);	
}
