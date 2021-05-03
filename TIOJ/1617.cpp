// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<algorithm>
using namespace std;

#ifdef OWO
#include<iostream>
int ball[10];
int Get_Box(){
	for(int i = 1; i <= 9; ++i) ball[i] = i;
	random_shuffle(ball + 1, ball + 10);
	return 9;
}
int Med3(int a, int b, int c){
	if(ball[a] > ball[b]) swap(a, b);
	if(ball[a] > ball[c]) swap(a, c);
	if(ball[b] > ball[c]) swap(b, c);
	return b;
}
void Report(int a){
	cout << a;
}
#else
#include "lib1617.h"
#endif

const int N = 1500;
int val[1500];
int main(){
	int n = Get_Box();

	int m1 = 1, m2 = 2;
	for(int i = 3; i <= n; ++i){
		int ret = Med3(m1, m2, i);
		if(ret == m1) m1 = i;
		if(ret == m2) m2 = i;
	}

	for(int i = 1, j = 0; i <= n; ++i)
		if(i != m1 and i != m2)
			val[j++] = i;

	nth_element(val, val + (n - 2) / 2, val + n - 2,
		[&](int a, int b){
			return Med3(m1, a, b) == a;
		}
	);

	Report(val[(n - 2) / 2]);

	return 0;
}