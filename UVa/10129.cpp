#include<iostream>
#include<cstring>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int deg[26], cnt;
int dsu[26], snum, sum;
bool vis[26];

void init(){
	memset(vis, 0, sizeof(vis));
	memset(deg, 0, sizeof(deg));
	snum = 26, sum = 0, cnt = 0;
	static int i = 25;
	for(;i;--i){
		dsu[i] = i;
	}
}

int Find(int a){
	return dsu[a] == a ? a : dsu[a] = Find(dsu[a]);
}

void Union(int a, int b){
	if(Find(a) == Find(b)) return;
	snum--;
	dsu[Find(b)] = Find(a);
}

int main(){OW0
	int T, n;
	string in;
	cin >> T;
	for(;T;--T){
		init();
		cin >> n;
		cin.ignore();
		for(int i = 0; i < n; i++){
			getline(cin, in);
			deg[int(in.front()-'a')]--;
			deg[int(in.back()-'a')]++;
			Union(in.front()-'a', in.back()-'a');
			vis[int(in.front()-'a')] = true;
			vis[int(in.back()-'a')] = true;
		}
		for(int i = 0; i < 26; i++)
			cout << deg[i] << ' ';
		cout << '\n';
		for(int i = 0; i < 26; i++){
			cout << vis[i];
			sum += vis[i];
			if(deg[i]) cnt ++;
		}
		cout << '\n' << snum << '\n';

		if(snum == 26 - sum + 1 and cnt <= 2) cout << "Ordering is possible.";
		else cout << "The door cannot be opened.";
		if(T) cout << '\n';
	}
	return 0;
}