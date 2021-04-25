#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

bool valid(string a, string b){
	bool ans = true;
	for(int i = 0; i < a.size(); i++){
		if(a[i] != b[i%b.size()]){
			ans = false;
			break;
		}
	}
	return ans;
}

int main(){OW0
	int T;
	string in;
	cin >> T;
	while(T--){
		cin >> in;
		int len = 1, minlen = 90;
		while(len * 2 <= in.size()){
			if(in.size() % len == 0 and valid(in, in.substr(0, len))){
				minlen = minlen < len ? minlen : len;
			}
			len++;
		}
		if(minlen == 90) cout << in.size();
		else cout << minlen;
		if(T) cout << "\n\n";
	}
	cout << '\n';
	return 0;
}