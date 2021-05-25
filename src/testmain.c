#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Assistant.h"
#include "BinarySearchTreeAPI.h"
#include <ctype.h>
#include <time.h>

int compare(const void* a, const void* b){
	if((int*)a>(int*)b) return 1;
	if((int*)a<(int*)b) return -1;
	return 0;
}
void deleteData(void *data){
	free(data);
	data=NULL;
}
void testmain_print(void *data){
	printf("%d ",*(int*)data);
}
int main(int argc, char *argv[]){
	srand(time(NULL));
	Tree *BST = createBinTree(&compare,&deleteData);
	int **array = malloc (sizeof(int*)*10);
	printf("Adding random Numbers to the Tree\n");
	for(int i=0;i<10;++i){
		array[i] = malloc(sizeof(int));
		*array[i] = rand();
		addToTree(BST,array[i]);
		
	}
	printf("Testing all 3 print Functions\nIn Order\n\n");
	printInOrder(BST,testmain_print);
	printf("\nPreOrder\n");
	printPreOrder(BST,testmain_print);
	printf("\nPostOrder\n");
	printPostOrder(BST,testmain_print);
	printf("\nDeleting all data");
	return 0;
}
