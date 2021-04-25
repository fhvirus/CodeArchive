#include<cstdio>
#include<cstring>
#include<algorithm>

char s[100001];
int n, id[100001];

int main(){
	scanf("%s", s);
	n = strlen(s);
	s[n++] = '\0';

	for(int i = 0; i < n; ++i) id[i] = i;
	std::sort(id, id+n, [](int a, int b){
		return strcmp(s+a, s+b) < 0;
	});
	for(int i = 0; i < n; ++i) printf("%d\n", id[i]);;
	return 0;
}