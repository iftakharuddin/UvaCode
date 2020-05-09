#include<bits/stdc++.h>
using namespace std;

int tree[200010];
int n; 

void pointUpdate(int x, int y){
	//x++;
	while(x<=n){
		tree[x]+=y;
		x+=x&-x;
	}
}

int rangeQuery(int a){
	//a++;
	int sum=0;
	while(a>0){
		sum+=tree[a];
		a-=a&-a;
	}
	return sum;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int tc=1;
	while(true){
		cin>>n;
		if(n==0) break;
		if(tc!=1) printf("\n");
		printf("Case %d:\n", tc++);
		int ar[n];
		memset(tree, 0, sizeof(tree));

		for (int i = 0; i < n; ++i)
		{
			cin>>ar[i];
			pointUpdate(i+1, ar[i]);
		}
		while(true){
			string ss; cin>>ss;
			if(ss=="S"){
				int a, b; cin>>a>>b;
				pointUpdate(a, b-ar[a-1]);
				ar[a-1]=b;
			}
			else if(ss == "M"){
				int a, b; cin>>a>>b;
				int ans = rangeQuery(b)-rangeQuery(a-1);
				printf("%d\n", ans);
			}
			else break;
		}
		

	}
	return 0;
}
