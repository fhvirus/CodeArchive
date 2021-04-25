#include<iostream>
#include<cctype>
using namespace std;

string a[26] = {
	"@", "8", "(", "|)", "3",
	"#", "6", "[-]", "|", "_|",
	"|<", "1", "[]\\/[]", "[]\\[]", "0",
	"|D", "(,)", "|Z", "$", "\'][\'",
	"|_|", "\\/", "\\/\\/", "}{", "`/", "2"
};

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	string in;
	getline(cin, in);
	for(auto i: in){
		if(isalpha(i)) cout << a[tolower(i)-'a'];
		else cout << i;
	}
	return 0;
}