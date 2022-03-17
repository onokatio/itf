#include <stdio.h>

int abs(int a){
	return a >= 0 ? a : a * -1;
}

int max(int a, int b){
	return a > b ? a : b;
}

int main(){
	int scenarios;
	scanf("%d",&scenarios);
	for(int i=0;i<scenarios;i++){
		int bomb;
		int rats_count;
		int rats[20000][3] = {};
		scanf("%d",&bomb);
		scanf("%d",&rats_count);
		for(int j=0;j<rats_count;j++){
			scanf("%d",&rats[j][0]); //x
			scanf("%d",&rats[j][1]); //y
			scanf("%d",&rats[j][2]); //population
		}

		int result_x = 0;
		int result_y = 0;

		int best_population = -1;
		
		int max_x = 0;
		int max_y = 0;

		for(int k=0;rats[k][2] != 0;k++){
			if(rats[k][0] > max_x) max_x = rats[k][0];
			if(rats[k][1] > max_y) max_y = rats[k][1];
		}
		max_x += bomb+1;
		max_y += bomb+1;
		//printf("max: %d %d",max_x,max_y);
		for(int x=0;x<=max_x;x++){
			for(int y=0;y<=max_y;y++){
				int population = 0;
				for(int k=0;rats[k][2] != 0;k++){
					if(max( abs(rats[k][0]-x), abs(rats[k][1]-y) ) <= bomb){
						//printf("(%d %d) hit (%d,%d) %d\n",x,y,rats[k][0],rats[k][1],rats[k][2]);
						population += rats[k][2];
					}
				}
				if (population > best_population){
					result_x = x;
					result_y = y;
					best_population = population;
				}
			}
		}
		printf("%d %d %d\n",result_x,result_y,best_population);

	}

}
