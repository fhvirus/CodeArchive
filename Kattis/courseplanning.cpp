#include<iostream>
#include<utility>
#include<algorithm>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
typedef long long ll;
const int MAXN = 2e5+1;
const ll INF = 8e7 * 8e7;

pair<string, int> course[MAXN];
ll dp1[MAXN], dp2[MAXN], dp3[MAXN];

int main(){OW0
    int n, k;
    cin >> n >> k;
    string name;
    for(int i = 1, diff; i <= n; i++){
        cin >> name >> diff;
        course[i] = {name, diff};
    }

    for(int i = 0; i <= n; i++){
        dp3[i] = INF;
    }

    sort(course + 1, course + n + 1);
    for(int j = 1; j <= k; j++){
        for(int i = 1; i <= n; i++){
            auto c = course[i];
            if(c.first.back() > '9'){
                dp3[i] = min(dp3[i-1], dp2[i-1] + c.second);
            } else {
                dp3[i] = min(dp3[i-1],
                         min(dp2[i-1] + c.second,
                             dp1[i-1] + c.second + course[i+1].second));
                ++i;
                dp1[i] = dp1[i-1];
                dp2[i] = dp2[i-1];
                dp3[i] = dp3[i-1];
            }
        }
        //swaps
        for(int i = 0; i <= n; i++){
            // cout << dp3[i] << ' ';
            dp1[i] = dp2[i];
            dp2[i] = dp3[i];
        }
        // cout << '\n';
    }
    cout << dp2[n];
    return 0;
}