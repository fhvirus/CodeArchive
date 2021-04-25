#include<cstdio>
#include<deque>
char a[100001], b[100001];
int n, k, bptr;
std::deque<int> d;
int main(){
	while(scanf("%d%d%s", &n, &k, a) != EOF){
		d.clear();

		// find min a[i] where a[i] != '0' and 0 <= i <= k
		int head = 0;
		for(int i = 0; i <= k; ++i)
			if(a[i] != '0' and a[i] < a[head]) head = i;

		bptr = 1, b[0] = a[head];
		k = k - head;
		printf("%d %d\n", head, k);

		for(int i = head + 1; i <= head + k + 1; ++i){
			while(!d.empty() and a[d.back()] >= a[i]) d.pop_back();
			d.push_back(i);
		}
		for(int i: d) printf("%d ", i);
			puts("");

		for(int i = head + k; i < n; ++i){
			while(!d.empty() and k > 0 and a[d.back()] >= a[i]) d.pop_back(), --k;
			d.push_back(i);
			b[bptr++] = a[d.front()];
			d.pop_front();
		}

		b[bptr] = '\0';
		puts(b);
	}
}