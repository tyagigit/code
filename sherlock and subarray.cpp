#include<bits/stdc++.h>
#define int long long
#define pib pair<int, bool>
#define X first
#define Y second
using namespace std;

vector<pib> st;
vector<int> a;
int n;

void build(int pos = 0, int l = 0, int r = n - 1){
    if(l == r){
        st[pos] = {a[l], true};
        return ;
    }
    int m = (l + r) / 2, c1 = (2 * pos) + 1, c2 = (2 * pos) + 2;
    build(c1, l, m);
    build(c2, m + 1, r);
    st[pos].Y = st[c1].X != st[c2].X;
    st[pos].X = max(st[c1].X, st[c2].X);
}
void init(){
    cin>>n;
    st.clear();
    st.resize(4 * n);
    a.clear();
    a.resize(n);
    for(auto &x: a)
        cin>>x;
}
pib oneMax(int pos, int ql, int qr,
                            int l = 0, int r = n - 1){
    if(ql > r || qr < l){
        return {0, true};
    }
    if(l >= ql && r <= qr){
        return st[pos];
    }
    int m = (l + r) / 2, c1 = (2 * pos) + 1, c2 = (2 * pos) + 2;
    pib p1 = oneMax(c1, ql, qr, l, m);
    pib p2 = oneMax(c2, ql, qr, m + 1, r);
    pib ret;
    ret.Y = p1.Y && p2.Y && (p1.X != p2.X);
    ret.X = max(p1.X, p2.X);
    return ret;
}
int bs(int ll, int rr){
    int l = ll, r = rr;
    while(l <= r){
        int m = (l + r) / 2;
        if(oneMax(0, ll, m).Y)
            l = m + 1;
        else
            r = m - 1;
    }
    return r;
}
int32_t main(){  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int t;
    cin>>t;
    while(t--){
        init();
        build();

        int ans = 0, r = 0;
        for(int l{0}; l < n; ++l){
            r = bs(l, n - 1);
            ans += (r - l + 1);
        }
        cout<<ans<<endl;
    }
    return 0;
}
