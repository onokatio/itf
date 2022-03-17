#include <stdio.h>
 
int main() {
	int count;
	int args[20][3];
	int diffs[3000] = {};
	int flag = 1;
	int max = 0;
	int min = 10000;
	scanf("%d", &count);
	for(int i=0; i<count;i++){
		scanf("%d %d %d", &args[i][0], &args[i][1], &args[i][2]);
	}
	for(int i=0; i<count;i++){
		printf("Case %d: ",i+1);
		max = 0;
		min = 10000;
		for(int j=0; j<3;j++) if(max < args[i][j]) max = args[i][j];
		for(int j=0; j<3;j++) if(min > args[i][j]) min = args[i][j];
		//printf("(%d %d)",min,max);
		for(int j=0; j<3;j++){
			if(min == args[i][j]) {
				args[i][j] = 0;
				break;
			}
		}
		for(int j=0; j<3;j++){
			if(max == args[i][j]){
				args[i][j] = 0;
				break;
			}
		}
		for(int j=0; j<3;j++){
			if(args[i][j] != 0){
				printf("%d\n",args[i][j]);
				break;
			}
		}
	}
	return 0;
}
