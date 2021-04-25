#include<iostream>
#include<stack>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

struct box{
	int a, b;
	box(int a, int b): a(a), b(b){}
};

bool can(box a, box b){
	return a.a <= b.a and a.b <= b.b;
}

stack<box> s;

void Push(string in){
	int a = 0, b = 0, ptr = 0;
	char ch;
	while(true){
		ch = in[ptr++];
		if(ch > '9' or ch < '0') break;
		a = a * 10 + (ch - '0');
	}
	while(true){
		ch = in[ptr++];
		if(ch > '9' or ch < '0') break;
		b = b * 10 + (ch - '0');
	}
	box t(a, b);
	while(s.size() and !can(t, s.top())) s.pop();
	s.push(t);
	return;
}

int main(){OW0
	string in;
	int cnt = 0;
	getline(cin, in);
	while(true){
		getline(cin, in);
		if(in == "End Stacking.") break;
		if(in == "") continue;
		if(in[0] == 'Q'){
			int ans = s.size();
			if(ans == 0) cout << "Query " << ++cnt << ": None.\n";
			else cout << "Query " << ++cnt << ": " << ans << " box" << (ans <= 1 ? "" : "es") << ".\n"; 
		}
		else{
			Push(in.substr(11));
		}
	}
	return 0;
}