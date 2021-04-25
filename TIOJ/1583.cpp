#include<cstdio>
#include<string>
#include<algorithm>
using namespace std;

const int N = 1e4;
int n;
struct person{
	char name[30];
	double bmi;
} p[N];

int main(){
	scanf("%d", &n);
	for(int i = 0, w, h; i < n; ++i){
		scanf("%s%d%d", p[i].name, &w, &h);
		p[i].bmi = (double)w / h / h;
	}
	sort(p, p + n, [](auto a, auto b){ return a.bmi > b.bmi;});
	for(int i = 0; i < n and i < 10; ++i)
		puts(p[i].name);
}