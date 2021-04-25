#include<cstdio>
#include<cstring>
char name[11], ans, len;
int main(){
	while(scanf("%s", name)!=-1){
		len = strlen(name);
		ans = 0;
		for(int i = 0; i < len; ++i)
			ans = (ans + (name[i] > 'Z' ? name[i] - 'a' : name[i] - 'A') + 1) % 17;
		puts(ans < 3 ? "D" : (ans < 6 ? "C" : (ans < 10 ? "B" : (ans < 13 ? "A" : "SA"))));
	}
}