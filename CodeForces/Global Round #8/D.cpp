#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define MAXN 200000

int n, cnt[20], a;

int main(){OW0
	cin >> n;
	for(int i = 0; i < n; i++){
		cin >> a;
		cnt[0] += ((a&1) ? 1 : 0);
		cnt[1] += ((a&2) ? 1 : 0);
		cnt[2] += ((a&4) ? 1 : 0);
		cnt[3] += ((a&8) ? 1 : 0);
		cnt[4] += ((a&16) ? 1 : 0);
		cnt[5] += ((a&32) ? 1 : 0);
		cnt[6] += ((a&64) ? 1 : 0);
		cnt[7] += ((a&128) ? 1 : 0);
		cnt[8] += ((a&256) ? 1 : 0);
		cnt[9] += ((a&512) ? 1 : 0);
		cnt[10] += ((a&1024) ? 1 : 0);
		cnt[11] += ((a&2048) ? 1 : 0);
		cnt[12] += ((a&4096) ? 1 : 0);
		cnt[13] += ((a&8192) ? 1 : 0);
		cnt[14] += ((a&16384) ? 1 : 0);
		cnt[15] += ((a&32768) ? 1 : 0);
		cnt[16] += ((a&65536) ? 1 : 0);
		cnt[17] += ((a&131072) ? 1 : 0);
		cnt[18] += ((a&262144) ? 1 : 0);
		cnt[19] += ((a&524288) ? 1 : 0);

	}
	// for(int i = 0; i < 20; i++){
	// 	cout << cnt[i] << '\n';
	// }
	long long ans = 0, tmp;
	do{
		tmp = 0;
		for(int i = 0; i < 20; i++){
			if(cnt[i]){
				cnt[i]--;
				tmp |= (1<<i);
			}
		}
		ans += tmp * tmp;
	}while(tmp);
	cout << ans;
	return 0;
}