#include<bits/stdc++.h>
using namespace std;
const int N = 1000;
int n;
string s[N];
char mp[128];
inline bool cmp(string a, string b){
    for(int i = 0; i < a.size() and i < b.size(); ++i){
        if(mp[a[i]] != mp[b[i]]) return mp[a[i]] < mp[b[i]];
    }
    return a.size() < b.size();
}
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    for(int i = 'a', l = 'a', r = 'z'; i <= 'z';) mp[l++] = i++, mp[r--] = i++;
    cin >> n;
    for(int i = 0; i < n; ++i) cin >> s[i];
    sort(s, s + n, cmp);
    for(int i = 0; i < n; ++i) cout << s[i] << '\n';
    return 0;
}
