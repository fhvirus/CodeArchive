#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int sy, sx;
char board[5][5];

bool move(char i){
	if(i == '0') return true;
	if(i == 'A'){
		if(sy == 0) return false;
		board[sy][sx] = board[sy-1][sx];
		board[sy-1][sx] = ' ';
		sy--;
		return true;
	}
	if(i == 'B'){
		if(sy >= 4) return false;
		board[sy][sx] = board[sy+1][sx];
		board[sy+1][sx] = ' ';
		sy++;
		return true;
	}
	if(i == 'L'){
		if(sx == 0) return false;
		board[sy][sx] = board[sy][sx-1];
		board[sy][sx-1] = ' ';
		sx--;
		return true;
	}
	if(i == 'R'){
		if(sx >= 4) return false;
		board[sy][sx] = board[sy][sx+1];
		board[sy][sx+1] = ' ';
		sx++;
		return true;
	}
	return false;
}

int main(){OW0
	int T = 0;
	string in;
	char cmd;
	bool exit, valid;
	while(true){
		for(int i = 0; i < 5; i++){
			getline(cin, in);
			if(in == "Z") return 0;
			for(int j = 0; j < 5; j++){
				if(in.size() == j)
					board[i][j] = ' ';
				else
					board[i][j] = in[j];
				if(board[i][j] == ' ')
					sy = i, sx = j;
			}
		}

		exit = false;
		valid = true;

		while(true){
			getline(cin, in);
			if(in.back() == '0') exit = true;
			for(auto i: in){
				if(!move(i)){
					valid = false;
				}
			}
			if(exit) break;
		}
		if(T++) cout << '\n';
		cout << "Puzzle #" << T << ":\n";
		if(valid){
			for(int i = 0; i < 5; i++){
				for(int j = 0; j < 5; j++){
					cout << board[i][j];
					if(j < 4) cout << ' ';
				}
				cout << '\n';
			}
		} else {
			cout << "This puzzle has no final configuration.\n";
		}
	}
	return 0;
}