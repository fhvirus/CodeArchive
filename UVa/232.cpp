#include<iostream>
#include<iomanip>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int r, c;
char b[10][10];
int  n[10][10];

int main(){OW0
	int T = 0, cnt;
	string in;
	while(cin >> r >> c){
		if(r == 0) break;
		if(T++) cout << '\n';
		cin.ignore();
		for(int i = 0; i < r; i++){
			getline(cin, in);
			for(int j = 0; j < c; j++){
				b[i][j] = in[j];
			}
		}
		cnt = 1;
		for(int i = 0; i < r; i++){
			for(int j = 0; j < c; j++){
				if( b[i][j] != '*' and
				   ((i == 0) or
					(j == 0) or
					(i > 0 and b[i-1][j] == '*') or
					(j > 0 and b[i][j-1] == '*'))){
					n[i][j] = cnt++;
				} else n[i][j] = 0;
			}
		}
		cout << "puzzle #" << T << ":\nAcross\n";
		for(int i = 0; i < r; i++){
			for(int j = 0; j < c; j++){
				if( b[i][j] != '*' and
				  ((j == 0) or
				   (j > 0 and b[i][j-1] == '*'))){
					cout << setw(3) << setfill(' ')
						 << n[i][j] << '.';
					for(int k = j; k < c and b[i][k] != '*'; k++)
						cout << b[i][k];
					cout << '\n';
				}
			}
		}
		cout << "Down\n";
		for(int i = 0; i < r; i++){
			for(int j = 0; j < c; j++){
				if( b[i][j] != '*' and
				  ((i == 0) or
				   (i > 0 and b[i-1][j] == '*'))){
					cout << setw(3) << setfill(' ')
						 << n[i][j] << '.';
					for(int k = i; k < r and b[k][j] != '*'; k++)
						cout << b[k][j];
					cout << '\n';
				}
			}
		}
	}
	return 0;
}