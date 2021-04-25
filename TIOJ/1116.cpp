#include<cstdio>
#include<cstring>
char c[4];
bool can[4][3];
int main(){
	while(scanf("%s", c)==1){
		memset(can, false, sizeof(can));
		for(int i = 0; i < 4; ++i){
			if(c[i] == 'b' or c[i] == 'c'){
				can[(i+3)%4][0]=true;
				can[(i+2)%4][1]=true;
				can[(i+1)%4][2]=true;
			}
		}
		for(int i = 0; i < 4; ++i){
			if(c[i] == 'b') printf("X");
			else if(!can[i][0] and !can[i][1] and !can[i][2])
				printf("Y");
			else{
				if(can[i][2]) printf("A");
				if(can[i][0]) printf("B");
				if(can[i][1]) printf("C");
			}
			if(i < 3) printf(", ");
		}
		printf("\n");
	}
	return 0;
}