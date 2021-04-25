#include<cstdio>
int readInt(){
	static bool minus = false;
	static int ans = 0;
	static char ch;
	ch = getchar();
	while(1){
		if(ch == '-') break;
		if(ch >= '0' or ch <= '9') break;
		ch = getchar();
	}
	if(ch == '-') minus = true;
	else ans = ch - '0';
	while(1){
		ch = getchar();
		if(ch < '0' or ch > '9') break;
		ans = ans * 10 + (ch - '0');
	}
	if(minus) return -ans;
	return ans;
}

int dsu[400001];
void init(int n){
	for(;n;--n) dsu[n] = n;
}

int Find(int a){
	return dsu[a] == a ? a : dsu[a] = Find(dsu[a]);
}

void Union(int a, int b){
	if(Find(a) == Find(b)) return;
	dsu[Find(b)] = Find(a);
}

int t, n, m, a, b, cnt, tmp, i;
int main(){
	t = readInt();
	for(;t;--t){
		n = readInt(); m = readInt();
		init(n<<1);
		for(;m;--m){
			a = readInt(); b = readInt();
			if(Find(a) != Find(b)){
				Union(a, b+n);
				Union(b, a+n);
			}
		}
		cnt = 0; tmp = Find(1);
		for(i = 1; i <= n; i++){
			if(Find(i) == tmp) cnt++;
		}
		if(cnt <= n/2){
			printf("%d\n", cnt);
			for(i = 1; i <= n; i++){
				if(Find(i) == tmp) printf("%d ", i);
			}
		} else {
			printf("%d\n", n-cnt);
			for(i = 1; i <= n; i++){
				if(Find(i) != tmp) printf("%d ", i);
			}
		}
		printf("\n");
	}
}