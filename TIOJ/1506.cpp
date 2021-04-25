#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>

int main(){
	double a1, a2, b1, b2;
	scanf("%lf%lf%lf%lf", &a1, &a2, &b1, &b2);
	double x = (b2-b1)/(a1-a2), y = a1*x + b1;
	x += (x < 0 ? -.001 : 0), y += (y < 0 ? -.001 : 0);
	printf("%.2lf\n%.2lf", x, y);
}