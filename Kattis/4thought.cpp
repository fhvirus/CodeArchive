#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

#define FOR(i, j, n) for(int i = (j); i < ((int)n); ++i)

inline int op(int a, int b, char o){
    switch(o){
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
    }
    return -1;
}

int calc(vector<int> ans, vector<char> ops){
    int ptr = 0;
    for(int i = 0; i < ops.size();){
        if(ops[i] == '*' or ops[i] == '/'){
            ans[ptr] = op(ans[ptr], ans[ptr+1], ops[i]);
            ans.erase(ans.begin() + ptr + 1);
            ops.erase(ops.begin() + i);
        }
        else ++i, ++ptr;
    }
    for(int i = 0; i < ops.size(); ++i){
        ans[0] = op(ans[0], ans[1], ops[i]);
        ans.erase(ans.begin() + 1);
    }
    return ans[0];
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

    char c[4] = {'+', '-', '*', '/'};
    unordered_map<int, string> m;

    FOR(i, 0, 4) FOR(j, 0, 4) FOR(k, 0, 4){
        string s = "4   4   4   4 = ";
        s[2] = c[i];
        s[6] = c[j];
        s[10] = c[k];
        int res = calc(vector<int>(4, 4), {c[i], c[j], c[k]});
        if(!m.count(res)) m[res] = s;
    }

    int n, in;
    for(cin >> n; n; --n){
        cin >> in;
        if(m.count(in))
            cout << m[in] << in << '\n';
        else
            cout << "no solution\n";
    }
    return 0;
}