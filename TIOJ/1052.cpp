#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#include<cstring>
int main(){
	int n, linecnt, wordcnt, charcnt;
	char eek[1030], jizz;
	scanf("%d", &n);
	scanf("%[^\n]", eek);
	scanf("%c", &jizz);
	for(; n; --n){
		linecnt = wordcnt = charcnt = 0;
		while(true){
			int res = scanf("%[^\n]", eek);

			if(res == EOF) break;

			if(eek[0] == '=' and eek[1] == '=' and eek[2] == '=' and eek[3] == '=' and eek[4] == '='){
				scanf("%c", &jizz);
				break;
			}

			linecnt++;
			if(res != 0){
				int len = strlen(eek);
				charcnt += len;
				for(int i = 1; i < len; ++i){
					if((eek[i] == ' ' or eek[i] == '\t') and (eek[i-1] != ' ' and eek[i-1] != '\t'))
						wordcnt++;
				}
				if(eek[len-1] != ' ' and eek[len-1] != '\t') wordcnt++;
			}

			if(scanf("%c", &jizz) == EOF) break;
		}
		printf("%d %d %d\n", linecnt, wordcnt, charcnt);
	}
}