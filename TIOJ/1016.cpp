#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>

/*
代表三振的 K (Strikeout)
代表保送的 W (Walk)
以及一壘安打 S (Single）
二壘安打 D (Double)
三壘安打 T (Three bases?)
全壘打 H (Home Run)
以及其他的出局狀況 O (Out,例如滾地球、飛球、刺殺、觸殺等等)
*/

int a, b, out;
char eek;
bool first, second, third, turn;
int main(){
	while(true){
		eek = getchar_unlocked();
		if(eek == EOF) break;
		a = 0, b = 0;
		first = second = third = false;
		out = 0;
		turn = 0; // 0 -> a, 1 -> b
		while(eek != '\n' and eek != EOF){
			if(eek == 'K' or eek == 'O'){
				++out;
				if(out == 3){
					first = second = third = false;
					out = 0;
					turn = !turn;
				}
			} else if(eek == 'W'){
				if(first and second and third) ++(turn ? b : a);
				else if(first and second) third = true;
				else if(first) second = true;
				else first = true;
			} else if(eek == 'S'){
				if(third) ++(turn ? b : a);
				third = second;
				second = first;
				first = true;
			} else if(eek == 'D'){
				if(third) ++(turn ? b : a);
				if(second) ++(turn ? b : a);
				third = first;
				second = true;
				first = false;
			} else if(eek == 'T'){
				if(third) ++(turn ? b : a);
				if(second) ++(turn ? b : a);
				if(first) ++(turn ? b : a);
				third = true;
				second = false;
				first = false;
			} else if(eek == 'H'){
				if(third) ++(turn ? b : a);
				if(second) ++(turn ? b : a);
				if(first) ++(turn ? b : a);
				++(turn ? b : a);
				first = second = third = false;
			}
			eek = getchar_unlocked();
		}
		if(a >= 1000) putchar_unlocked(a/1000 + '0');
		if(a >= 100) putchar_unlocked(a%1000/100 + '0');
		if(a >= 10) putchar_unlocked(a%100/10 + '0');
		putchar_unlocked(a%10 + '0');
		putchar_unlocked(' ');
		if(b >= 1000) putchar_unlocked(b/1000 + '0');
		if(b >= 100) putchar_unlocked(b%1000/100 + '0');
		if(b >= 10) putchar_unlocked(b%100/10 + '0');
		putchar_unlocked(b%10 + '0');
		putchar_unlocked('\n');
	}
	return 0;
}