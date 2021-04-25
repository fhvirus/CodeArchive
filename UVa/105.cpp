#include<cstdio>

int main(){
	int skyline[10001] = {0};
	int L, R, H, rmax = 0;
	while(scanf("%d%d%d", &L, &H, &R) != EOF){
		for(int i = L < 0 ? 0 : L; i < R; i++)
			if(skyline[i] < H) skyline[i] = H;
		if(R > rmax) rmax = R;
	}
	bool space = false;
	for(int i = 1; i <= rmax; i++){
		if(skyline[i-1] != skyline[i]){
			if(space) putchar(' ');
			printf("%d %d", i, skyline[i]);
			space = true;
		}
	}
	putchar('\n');
	return 0;
}