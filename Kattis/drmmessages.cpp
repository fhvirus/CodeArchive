#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){OW0
	string in, a, b;
	int suma = 0, sumb = 0;
	cin>>in;
	int x = in.size();
	for(int i = 0; i * 2 < x; i++){
		suma += in[i] - 'A';
		sumb += in[i + x/2] - 'A';
	}
	for(int i = 0; i * 2 < x; i++){
		in[i] = ((in[i]-'A')+suma)%26 + 'A';
		in[i + x/2] = ((in[i + x/2]-'A')+sumb)%26 + 'A';
	}
	for(int i = 0; i * 2 < x; i++){
		in[i] = ((in[i]-'A')+(in[i+x/2]-'A'))%26 + 'A';
	}
	for(int i = 0; i * 2 < x; i++){
		cout<<in[i];
	}
	return 0;
}