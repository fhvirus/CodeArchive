#include<iostream>
#include<sstream>
using namespace std;

#define owo ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int g[100001];
int cnt;

void init(int n){
	cnt = n;
	for(int i = 0; i <= n; i++)
		g[i] = i;
}

int Find(int v){
	if(v == g[v]) return v;
	return g[v] = Find(g[v]);
}

void Union(int a, int b){
	a = Find(a);
	b = Find(b);
	if(a != b){
		cnt--;
		g[b] = a;
	}
}

int main(){owo
	int T, n, a, b;
	stringstream ss;
	string in;
	cin >> T;
	while(T--){
		cin >> n;
		init(n);
		cin.ignore();
		while(getline(cin, in)){
			if(in.empty()) break;
			ss.str(""); ss.clear(); ss << in;
			while(ss >> a >> b) Union(a, b);
		}
		cout << cnt << '\n';
		if(T) cout << '\n';
	}
	return 0;
}