#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int n, q;
int dsu[1000001];

void init(){
	for(int i = 0; i <= n; i++)
		dsu[i] = i;
}

int Find(int a){
	if(dsu[a] == a) return a;
	return dsu[a] = Find(dsu[a]);
}

void Union(int a, int b){
	if(Find(a) == Find(b)) return;
	dsu[Find(a)] = dsu[b];
}

bool Query(int a, int b){
	return Find(a) == Find(b);
}

int main(){OW0
	cin >> n >> q;
	init();
	char cmd;
	int a, b;
	while(q--){
		cin >> cmd >> a >> b;
		if(cmd == '=')
			Union(a, b);
		else
			cout << (Query(a, b) ? "yes" : "no") << '\n';
	}
	return 0;
}