#include<cstdio>
int readInt () {
	bool minus = false;
	int result = 0;
	char ch;
	ch = getchar();
	while (true) {
		if (ch == '-') break;
		if (ch >= '0' && ch <= '9') break;
		ch = getchar();
	}
	if (ch == '-') minus = true; else result = ch-'0';
	while (true) {
		ch = getchar();
		if (ch < '0' || ch > '9') break;
		result = result*10 + (ch - '0');
	}
	if (minus)
		return -result;
	else
		return result;
}

struct DSU{
	int n, *dsu;
	DSU(int n): n(n), dsu(new int[n+1]){
		for(int i = n; i; --i){
			dsu[i] = i;
		}
	}
	int Find(int a){
		return dsu[a] == a ? a : dsu[a] = Find(dsu[a]);
	}
	void Union(int a, int b){
		if(Find(a) == Find(b)) return;
		dsu[Find(b)] = Find(a);
	}
};

int main(){
	int n, m, a, b;
	n = readInt(); m = readInt();
	DSU color(n<<1), group(n);
	for(;m;--m){
		a = readInt(); b = readInt();
		color.Union(a, b+n);
		color.Union(b, a+n);
		group.Union(a, b);
	}
	for(int i = 1; i <= n; i++){
		if(color.dsu[i] == color.dsu[i+n]){
			printf("-1");
			return 0;
		}
	}
	int s=0, t=0;
	for(int i = 1; i <= n; i++){
		if(color.Find(i) == color.Find(group.Find(i))) s++;
		else t++;
	}
	printf("%d %d\n", s, t);
	for(int i = 1; i <= n; i++){
		if(color.Find(i) == color.Find(group.Find(i)))
			printf("%d ", i);
	}
	printf("\n");
	for(int i = 1; i <= n; i++){
		if(color.Find(i) != color.Find(group.Find(i)))
			printf("%d ", i);
	}
	return 0;
}