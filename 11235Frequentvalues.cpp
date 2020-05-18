#include<bits/stdc++.h>
using namespace std;
#define dbg(a)  cerr << __LINE__ << ": " << #a << " = " << a << '\n'
typedef long long ll;
int sz = 0;
int seg[100010*4];

void add(int pos, int x, int nd = 1, int nl = 0, int nr = sz-1)
{
   if(nl==nr){
      seg[nd] += x;
      return;
   }
   int mid = (nl + nr) / 2;
   if(pos <= mid)add(pos, x, 2*nd, nl, mid);
   else add(pos, x, 2*nd + 1, mid+1, nr);

   seg[nd] = max(seg[2*nd], seg[2*nd+1]);
}

int query(int l, int r, int nd = 1, int nl = 0, int nr = sz-1)
{
   if(r < nl or nr < l) return 0;
   if(l <= nl and nr <= r){
      return seg[nd];
   }
   int mid = (nl + nr) / 2;
   int x = query(l, r, 2*nd, nl, mid);
   int y = query(l, r, 2*nd + 1, mid + 1, nr);
   return max(x, y);
}
int bSearch(vector<int>& vv, int val){
   int l = 0, r = sz-1;
   while(l < r){
      int mid = (l+r) / 2;
      if(val <= vv[mid]) r = mid;
      else l = mid + 1;
   }
   return l;
}

int main(){
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);
   #ifndef  ONLINE_JUDGE
   freopen("in", "r", stdin);
   freopen("out", "w", stdout);
   #endif
   while(true){
      int n, q; cin>>n>>q;
      if(n==0) break;
      map<int ,int>mp;
      for (int i = 0; i < n; ++i)
      {
         int a; cin>>a;
         mp[a]++;
      }
      int i = 0;
      memset(seg, 0, sizeof(seg));
      sz = mp.size();
      vector<int> vv(sz);
      for(auto aa: mp){
         if(i > 0)vv[i] = vv[i-1] + aa.second;
         else vv[i] = aa.second;
         add(i, aa.second);
         i++;
      }

      while(q--){
         int a, b; cin>>a>>b;
         int lidx = bSearch(vv, a);
         int ridx = bSearch(vv, b);
         int mx;
         if(lidx == ridx){
            mx = b - a + 1;
         }
         else if(lidx == ridx -1){
            mx = max(vv[lidx]-a+1, b-vv[ridx-1]);
         }
         else mx = max(query(lidx+1, ridx-1), max(vv[lidx]-a+1, b-vv[ridx-1]));
         cout<<mx<<endl;
      }

   }
   return 0;
}
