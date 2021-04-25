#include<iostream>
#include<set>
#include<cctype>
using namespace std;

int main(){
	int T,a[26],cnt=0;
	cin>>T;
	cin.ignore();
	string in;
	while(T--){
		getline(cin,in);
		for(auto &i:a)i=0;
		cnt=0;
		for(int i=0;i<in.size();i++){
			if(isalpha(in[i]))
			if(a[tolower(in[i])-'a']==0){
				a[tolower(in[i])-'a']=1;
				cnt++;
			}
		}
		if(cnt==26){
			cout<<"pangram\n";
		}else{
			cout<<"missing ";
			for(int i=0;i<26;i++){
				if(a[i]==0){
					cout<<(char)('a'+i);
				}
			}
			cout<<endl;
		}
	}

	return 0;
}