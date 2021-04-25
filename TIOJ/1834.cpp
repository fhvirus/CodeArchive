#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<iostream>
#include<string>
#include<stack>
#include<queue>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

struct big{
	bool operator() (const string& a, const string& b){
		if(a.size() != b.size()) return a.size() > b.size();
		for(int i = 0; i < a.size(); ++i)
			if(a[i] != b[i]) return a[i] > b[i];
		return false;
	}
};
struct sml{
	bool operator() (const string& a, const string& b){
		if(a.size() != b.size()) return a.size() < b.size();
		for(int i = 0; i < a.size(); ++i)
			if(a[i] != b[i]) return a[i] < b[i];
		return false;
	}
};

int n, x, y;
bool flag;
string cmd, tmp;
stack<string> S;
queue<string> Q;
priority_queue<string, vector<string>, sml> M;
priority_queue<string, vector<string>, big> m;

inline void docmd(){
	cin >> cmd;
	if(cmd == "ダメよ～ダメダメ"){
		cin >> x >> tmp;
		if(x == 1) S.push(tmp);
		else if(x == 2) Q.push(tmp);
		else if(x == 3) M.push(tmp);
		else m.push(tmp);
	} else if(cmd == "しかしお兄ちゃんはわりと弱気だからなぁ……アタシの方からアプローチしないとダメかな"){
		cin >> x >> y;
		flag = true;
		if(x == 1){
			if(S.size() > 0){ tmp = S.top(); S.pop();}
			else flag = false;
		} else if(x == 2){
			if(Q.size() > 0){ tmp = Q.front(); Q.pop();}
			else flag = false;
		} else if(x == 3){
			if(M.size() > 0){ tmp = M.top(); M.pop();}
			else flag = false;
		} else {
			if(m.size() > 0){ tmp = m.top(); m.pop();}
			else flag = false;
		}
		if(!flag) return;
		if(y == 1) S.push(tmp);
		else if(y == 2) Q.push(tmp);
		else if(y == 3) M.push(tmp);
		else m.push(tmp);
	} else {
		cin >> x;
		if(x == 1){
			if(S.size() > 0){ tmp = S.top(); S.pop(); cout << tmp << '\n';}
			else cout << "イヤ...やめてよ...お兄ちゃん...壊れる\n";
		} else if(x == 2){
			if(Q.size() > 0){ tmp = Q.front(); Q.pop(); cout << tmp << '\n';}
			else cout << "イヤ...やめてよ...お兄ちゃん...壊れる\n";
		} else if(x == 3){
			if(M.size() > 0){ tmp = M.top(); M.pop(); cout << tmp << '\n';}
			else cout << "イヤ...やめてよ...お兄ちゃん...壊れる\n";
		} else {
			if(m.size() > 0){ tmp = m.top(); m.pop(); cout << tmp << '\n';}
			else cout << "イヤ...やめてよ...お兄ちゃん...壊れる\n";
		}
	}
}

int main(){OW0
	while(cin >> n){
		S = {};
		Q = {};
		M = {};
		m = {};
		for(; n; --n) docmd();
	}
	return 0;
}