#include"lib1044.h"

int main(){
	int l = 0, r = Initialize()+1;
	while(r > l){
		bool guess = Guess((r + l) / 2);
		if(guess){
			r = (r + l) / 2;
		} else {
			l = (r + l) / 2 + 1;
		}
	}
	Report(r);
	return 0;
}