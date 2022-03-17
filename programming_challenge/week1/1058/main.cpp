#include <iostream>
#include <string>
#include <set>
#include <vector>
 
int main() {
 
	int count;
	std::vector<int> args;
	std::set<int> diffs;
	std::cin >> count;
	for(int i=0; i<count;i++){
		int n;
		std::cin >> n;
		args.push_back(n);
	}
	for(int i=0; i<count-1;i++){
		diffs.insert(abs(args[i] - args[i+1]));
	}
	if(count == 1){
		printf("Jolly");
	} else if ( diffs.size() == count -1){
		printf("Jolly");
	}else{
		printf("Not jolly");
	}
	printf("\n");
	return 0;
}
