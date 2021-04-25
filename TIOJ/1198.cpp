#include<cstdio>
#include<algorithm>
using namespace std;
#define INF 33
int s[9], t[9],
	dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1},
	rev[4] = {1, 0, 3, 2};
int h(){
	int ans = 0;
	for(int i = 0; i < 9; ++i)
		if(s[i]!=t[i]) ++ans;
	return ans;
}
int in(int x, int y){
	return x<3 and x>=0 and y<3 and y>=0;
}

int ida(int x, int y, int cnt, int prev, int bound){
	if(cnt + h() > bound) return INF;
	if(h() == 0) return cnt;
	int ans = INF;
	for(int i = 0; i < 4; ++i){
		if(rev[i] != prev and in(x+dx[i], y+dy[i])){
			swap(s[x*3+y], s[(x+dx[i])*3+y+dy[i]]);
			ans = min(ans, ida(x+dx[i], y+dy[i], cnt+1, i, bound));
			swap(s[x*3+y], s[(x+dx[i])*3+y+dy[i]]);
		}
	}
	return ans;
}

int main(){
	int i, ans;
	for(i = 0; i < 9; ++i) scanf("%d", &s[i]);
	for(i = 0; i < 9; ++i) scanf("%d", &t[i]);
	for(i = 0; i < 9; ++i) if(s[i]==0) break;
	for(int bound = 1; bound < INF; bound<<=1){
		ans = ida(i/3, i%3, 0, -1, bound);
		if(ans != INF){
			printf("%d\n", ans);
			return 0;
		}
	}
	return 0;
}