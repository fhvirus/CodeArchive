#include<iostream>
#include<cmath>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

char b[100][100];

int main(){OW0
	string in;
	int T, l;
	cin>>T;
	cin.ignore();
	while(T--){
		getline(cin, in);
		l = ceil(sqrt(in.size()));
		while(in.size() < l*l)in.push_back('*');
		for(int i = 0; i < l; i++){
			for(int j = 0; j < l; j++){
				b[i][j] = in[i * l + j];
			}
		}
		for(int i = 0; i < l; i++){
			for(int j = l-1; j >= 0; j--){
				if(b[j][i] != '*')cout<<b[j][i];
			}
		}
		cout<<'\n';
	}
	return 0;
}