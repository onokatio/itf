#include <stdio.h>

int main(){
	int numbers[10];
	
	for(int i=0;i<10;i++){
		numbers[i] = i;
	}

	for(int i=0;i<10;i++){
		printf("numbers[%d] = %d\n",i,numbers[i]);
	}
}
