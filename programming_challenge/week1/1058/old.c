#include <stdio.h>
 
int main() {
 
	/**
	 * Escreva a sua solução aqui
	 * Code your solution here
	 * Escriba su solución aquí
	 */
	int count;
	int args[3000];
	int diffs[3000] = {};
	int flag = 1;
	scanf("%d", &count);
	for(int i=0; i<count;i++){
		scanf("%d", args+i);
	}
	for(int i=0; i<count-1;i++){
		int diff = args[i] - args[i+1];
		if (diff < 0) diff *= -1;
		diffs[diff]++;
	}
	for(int i=1; i<count;i++){
		//printf("%d,",diffs[i]);
		if (diffs[i] != 1) flag = 0;
	}
	if(flag){
		printf("Jolly");
	}else if(count == 1){
		printf("Jolly");
	}else{
		printf("Not jolly");
	}
	printf("\n");
	return 0;
}
