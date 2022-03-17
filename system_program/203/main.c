#include <stdio.h>
#include <ctype.h>

int isDelimiter(char c){
	if(c == ' ' || c == '\n' || c == '\t'){
		return 1;
	}else{
		return 0;
	}
}

int wc(char *str)
{
	
	int count = 0;
	int i = 0;
	for(;isDelimiter(str[i]);i++){ } // 最初のホワイトスペースを読み飛ばす
	while(1){
		if(isDelimiter(str[i]) || str[i+1] == '\0'){
			for(;isDelimiter(str[i]);i++){ } // 連続するホワイトスペースやそれと連結する終端文字を読み飛ばす
			count++;
		}
		if(str[i] == '\0'){
			return count;
		}
		i++;
	}
}

int main(void)
{
  char *str;

  str = "University of Tsukuba"; // 3
  printf("%d\n", wc(str));

  str = "Hello\tworld!\nGood-bye\tworld!\n\n"; // 4
  printf("%d\n", wc(str));

  str = "    Ten little Indians standin' in a line;\n"
        "        One toddled home and then there were nine.\n"
        "    Nine little Indians swingin' on a gate;\n"
        "        One tumbled off and then there were eight.\n"; // 30
  printf("%d\n", wc(str));

  return 0;

}
