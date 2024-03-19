#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
template <class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
template <class T> using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag,tree_order_statistics_node_update>;
long long int index(ordered_multiset<long long int> &st,long long int value){
    return st.order_of_key(value);
}
long long int value(ordered_multiset<long long int> &st,long long int index){
    return *st.find_by_order(index);
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin>>n;
    int mod=1e9+7;
    vector<long long int> a(n+1);
    for(int i=1;i<=n;i++){
        cin>>a[i];
        a[i]=a[i]*a[i];
    }
    vector<vector<int>> tree(n+1);
    for(int i=0;i+1<n;i++){
        int u,v;
        cin>>u>>v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    long long int ans=0;
    vector<ordered_multiset<long long int>> cnt(n+1);
    function<void(int,int)> dfs0=[&](int v,int p){
        for(auto u:tree[v]){
            if(u==p){
                continue;
            }
            dfs0(u,v);
            if(cnt[v].size()<cnt[u].size()){
                cnt[v].swap(cnt[u]);
            }
            for(auto i:cnt[u]){
                cnt[v].insert(i);
            }
        }
        cnt[v].insert(a[v]);
        long long int pos=index(cnt[v],a[v]+1);
        ans=(ans+pos*a[v])%mod;
    };
    dfs0(1,0);
    ordered_multiset<long long int> val;
    function<void(int,int)> dfs1=[&](int v,int p){
        val.insert(a[v]);
        long long int pos=index(val,a[v]);
        ans=(ans+pos*a[v])%mod;
        for(auto u:tree[v]){
            if(u==p){
                continue;
            }
            dfs1(u,v);
        }
        val.erase(val.find_by_order(index(val,a[v])));
    };
    dfs1(1,0);
    cout<<ans;
    return 0;
}
