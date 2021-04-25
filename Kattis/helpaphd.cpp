#include<iostream>
using namespace std;

int main(){
	int n, a, b, ptr;
	string in;
	cin>>n;
	cin.ignore();
	while(n--){
		getline(cin, in);
		if(in == "P=NP"){
			cout<<"skipped\n";
			continue;
		}
		a = b = ptr = 0;
		while(in[ptr] != '+'){
			a *= 10;
			a += in[ptr++] - '0';
		}
		ptr++;
		while(ptr < in.size()){
			b *= 10;
			b += in[ptr++] - '0';
		}
		cout<< a + b <<'\n';
	}
	return 0;
}