#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

struct node{
    node* a[10];
    bool end;
    node(){
        for(int i = 0; i < 10; i++)
            a[i] = nullptr;
        end = false;
    }
} *root;

void Push(string s){
    node* ptr = root;
    for(int i = 0; i < s.size(); i++){
        if(!ptr->a[s[i]-'0']) ptr->a[s[i]-'0'] = new node();
        ptr = ptr->a[s[i]-'0'];
    }
    ptr->end = true;
    return;
}

bool Find(string s){
    node* ptr = root;
    for(int i = 0; i < s.size(); i++){
        if(!ptr->a[s[i]-'0']) return false;
        ptr = ptr->a[s[i]-'0'];
    }
    return true;
}

bool Check(string s){
    node* ptr = root;
    for(int i = 0; i < s.size(); i++){
        if(ptr->end) return true;
        if(!ptr->a[s[i]-'0']) return false;
        ptr = ptr->a[s[i]-'0'];
    }
    return false;
}

int main(){OW0
    int T, n;
    string s;
    bool can;
    cin >> T;
    while(T--){
        cin >> n;
        root = new node();
        can = true;
        for(int i = 0; i < n; i++){
            cin >> s;
            if(can){
                if(Find(s) || Check(s)){
                    can = false;
                }
                Push(s);
            }
        }
        if(can) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}