#pragma Os
#include<stdio.h>
char c;
inline char R(){
	c = getchar_unlocked();
	while(c<'-') c=getchar_unlocked();
	if(c=='-'){ getchar_unlocked(); return -1;}
	return (c > '1' ? c - '0' : (getchar_unlocked() == '0' ? 10 : 1));
}
#define N 10
char n, jizz, d = 0;
char head[N], to[N], prv[N];

char dfs(char u, char p){
	char h1 = 0, h2 = 0;
	for(char v = head[u]; v != -1; v = prv[v])
		if(to[v] != p){
			char h = dfs(to[v], u) + 1;
			if(h > h1) h2 = h1, h1 = h;
			else if(h > h2) h2 = h;
		}
	d = d > h1 + h2 ? d : h1 + h2;
	return h1;
}

int main(){
	n = R();
	for(char i = 0, j = 0; i < n; ++i){
		head[i] = -1;
		while((jizz = R()) != -1)
			to[j] = jizz, prv[j] = head[i], head[i] = j++;
	}
	dfs(0, 0);
	putchar_unlocked(d + '0');
	return 0;
}