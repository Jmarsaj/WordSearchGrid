
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions
void printPuzzle(char** arr, int n);
void searchPuzzle(char** arr, int n, char** list, int listSize);
void lowerCase(char** arr, int wordSize, int arrSize, int row, int col, int n);
int searchLtoR(char** arr, int n, char* word);
int searchVTtoB(char** arr, int n, char* word);
int searchVBtoT(char** arr, int n, char* word);
int searchDTLtoBR(char** arr, int n, char* word);
int searchDBLtoTR(char** arr, int n, char* word);

// Main function, DO NOT MODIFY!!!
int main(int argc, char **argv) {
	int bSize = 15;
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
		return 2;
	}
	int i, j;
	FILE *fptr;
	char **block = (char**)malloc(bSize * sizeof(char*));
	char **words = (char**)malloc(50 * sizeof(char*));

	// Open file for reading puzzle
	fptr = fopen(argv[1], "r");
	if (fptr == NULL) {
		printf("Cannot Open Puzzle File!\n");
		return 0;
	}

	// Read puzzle block into 2D arrays
	for(i=0; i<bSize; i++){
		*(block+i) = (char*)malloc(bSize * sizeof(char));

		fscanf(fptr, "%c %c %c %c %c %c %c %c %c %c %c %c %c %c %c\n", *(block+i), *(block+i)+1, *(block+i)+2, *(block+i)+3, *(block+i)+4, *(block+i)+5, *(block+i)+6, *(block+i)+7, *(block+i)+8, *(block+i)+9, *(block+i)+10, *(block+i)+11, *(block+i)+12, *(block+i)+13, *(block+i)+14 );
		}
	fclose(fptr);

	// Open file for reading word list
	fptr = fopen("states.txt", "r");
	if (fptr == NULL) {
		printf("Cannot Open Words File!\n");
		return 0;
	}
  
	// Save words into arrays
	for(i=0; i<50; i++){
		*(words+i) = (char*)malloc(20 * sizeof(char));
		fgets(*(words+i), 20, fptr);
	}
  
	// Remove newline characters from each word (except for the last word)
	for(i=0; i<49; i++){
		*(*(words+i) + strlen(*(words+i))-1) = '\0';
	}
  
	// Print out word list
	printf("Printing list of words:\n");
	for(i=0; i<50; i++){
		printf("%s\n", *(words + i));
	}
	printf("\n");
  
	// Print out original puzzle grid
	printf("Printing puzzle before search:\n");
	printPuzzle(block, bSize);
	printf("\n");

	// Call searchPuzzle to find all words in the puzzle
	searchPuzzle(block, bSize, words, 50);
	printf("\n");
  
	// Print out final puzzle grid with found words in lower case
	printf("Printing puzzle after search:\n");
	printPuzzle(block, bSize);
	printf("\n");
  
	return 0;
}

void lowerCase(char** arr, int wordSize, int arrSize, int row, int col, int n){
	int i;
	switch(n){
		case 1: 
		for (i = col; i < ((col + wordSize) - 1); i++){
			if (*(*(arr + row) + i) < 97)
				*(*(arr + row) + i) = (char)(*(*(arr + row) + i) + 32);
		 }
		break;
		case 2:
		for (i = row; i < ((row + wordSize) - 1); i++){
			if (*(*(arr + i) + col) < 97)
				*(*(arr + i) + col) = (char)(*(*(arr + i) + col) + 32);
		}
		break;
		case 3:
		for (i = row; i > ((row - wordSize) - 1); i--){
			if (*(*(arr + i) + col) < 97)
				*(*(arr + i) + col) = (char)(*(*(arr + i) + col) + 32);
		}
		break;
		case 4:
		for (i = 0; i < (wordSize - 1); i++){
			if (*(*(arr + i + row) + i + col) < 97)
				*(*(arr + i + row) + i + col) = (char)(*(*(arr + i + row) + i + col) + 32);
		}
		break;
		case 5:
		for (i = 0; i < (wordSize - 1); i++){
			if (*(*(arr - i + row) + i + col) < 97)
				*(*(arr - i + row) + i + col) = (char)(*(*(arr - i + row) + i + col) + 32);
		}
		break;
	}
}

void printPuzzle(char** arr, int n){
// This function will print out the complete puzzle grid (arr). It must produce the output in the SAME format as the samples in the instructions.
// Your implementation here
  
	for (int i = 0; i < n; i++){
		printf("%c %c %c %c %c %c %c %c %c %c %c %c %c %c %c\n", *(*(arr+i)), *(*(arr+i)+1), *(*(arr+i)+2), *(*(arr+i)+3), *(*(arr+i)+4), *(*(arr+i)+5), *(*(arr+i)+6), *(*(arr+i)+7), *(*(arr+i)+8), *(*(arr+i)+9), *(*(arr+i)+10), *(*(arr+i)+11), *(*(arr+i)+12), *(*(arr+i)+13), *(*(arr+i)+14));
	}

}

void searchPuzzle(char** arr, int n, char** list, int sizeofList){
// This function checks if arr contains words from list. If a word appears in arr, it will print out that word and then convert that word entry in arr into lower case.
// Your implementation here

	int i = 0;
	for(i = 0; i < sizeofList; i++){
		if(searchLtoR(arr, n, *(list+i)) || searchVTtoB(arr, n, *(list+i)) || searchVBtoT(arr, n, *(list+i)) || searchDTLtoBR(arr, n, *(list+i)) || searchDBLtoTR(arr, n, *(list+i))) {
			printf("Word found: %s\n", *(list+i));
   		}
	}
}

int searchLtoR(char** arr, int n, char* word){

	int size = strlen(word);
	int i = 0, j = 0, index;
	char a, b;
	for (i = 0; i < n; i++){
		for (j = 0; j <= (n - size); j++){
			index = 0;
			while(index < size){
				if (*(word + index) >= 97){
					a = *(word + index);
				} else {
					a = (char)(*(word + index) + 32);
				}
            			//printf("%c", a); 
				if (*(*(arr + i) + index + j) >= 97){
					b = *(*(arr + i) + index + j);
				} else {
					b = (char)(*(*(arr + i) + index + j) + 32);
				}
               			//printf("%c", b);
             	if(a==b){
                	//printf("index = %d", index); 
               		//printf("size = %d", size); 
					if (index == (size - 2)){
						lowerCase(arr, size, n, i, j, 1);
						//printf("return 1\n");
						return 1;
					} else {
						//printf("index++");
						index++;
					}
				} else {
					//printf("break\n");
					break;
				}
			}
		}
	}
	//printf("return 0");
	return 0;
}

int searchVTtoB(char** arr, int n, char* word){
  
   int size = strlen(word);
   int i = 0, j = 0, index;
   char a, b;
   for(i = 0; i < n; i++){
       for(j = 0; j <= (n-size); j++){
			index = 0;
       		while(index < size){
				if(*(word + index) >= 97){
					a = *(word + index);
				} else {
					a = (char)(*(word + index) + 32);
				}
				//printf("%c", a); 
				if (*(*(arr + index + j) + i) >= 97){
					b = *(*(arr + index + j) + i);
				} else {
					b = (char)(*(*(arr + index + j) + i) + 32);
				}
				//printf("%c\n", b); 
                if(a==b){
					//printf("index = %d", index); 
                	//printf("size = %d", size); 
               		if(index == (size-2)){
                   		lowerCase(arr, size, n, j, i, 2);
						//printf("return 1");
                   		return 1;
               	} else {
		   			index++;
					//printf("index++");
	       		}
			} else {
				//printf("break");
				break;
			}
       	}
      }
   }
   return 0;
}

int searchVBtoT(char** arr, int n, char* word){
  
   int size = strlen(word);
   int i = 0, j = 0, index;
   char a, b;
   for(i = 0; i < n; i++){
       for(j = (n-1); j >= (size-1); j--){
       		index = 0;
       		while(index < size){
				if (*(word + index) >= 97){
					a = *(word + index);
				} else {
					a = (char)(*(word + index) + 32);
				}
				if (*(*(arr + j - index) + i) >= 97){
					b = *(*(arr + j - index) + i);
				} else {
					b = (char)(*(*(arr + j - index) + i) + 32);
				}
               	if(a==b){
              	if(index == (size-2)){
                	lowerCase(arr, size, n, j, i, 3);
                	return 1;
               	} else {
		   			index++;
				}
           	}else{
            	break;
			}
       	}
      }
   }
  return 0;
}

int searchDTLtoBR(char** arr, int n, char* word){
  
   int size = strlen(word);
   int i = 0, j = 0, index;
   char a, b;
   for(i = 0; i < n; i++){
       for(j = 0; j <= n; j++){
      		index = 0;
       		while(index < size && ((i + index) < n) && ((j + index) < n)){
			if (*(word + index) >= 97){
				a = *(word + index);
			} else {
				a = (char)(*(word + index) + 32);
			}
			if (*(*(arr + index + i) + index + j) >= 97){
				b = *(*(arr + i + index) + j + index);
			} else {
				b = (char)(*(*(arr + i + index) + j + index) + 32);
			}
            if(a==b){
            	if(index == (size - 2)){
                	lowerCase(arr, size, n, i, j, 4);
                   	return 1;
               	} else {
		   			index++;
				}
           	} else {
            	break;
           	}
       	}
      }
  }
  return 0;
}

int searchDBLtoTR(char** arr, int n, char* word){
  
   int size = strlen(word);
   int i = 0, j = 0, index;
   char a, b;
   for(i = (n-1); i > 0; i--){
       for(j = 0; j <= n; j++){
       		index = 0;
       		while(index < size && ((i - index) > 0) && ((j + index) < n)){
				if (*(word + index) >= 97){
					a = *(word + index);
				} else {
					a = (char)(*(word + index) + 32);
				}
				if (*(*(arr + i - index) + j + index) >= 97){
					b = *(*(arr + i - index) + j + index);
				} else {
					b = (char)(*(*(arr + i - index) + j + index) + 32);
				}
               if(a==b){
               		if(index == (size - 2)){
              	    lowerCase(arr, size, n, i, j, 5);
                   	return 1;
               		} else {
						index++;
					}
			}else{
            	break;
           	}
       	}
      }
  }
  return 0;
}
