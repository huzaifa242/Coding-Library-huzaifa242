//Usage prim(source). mst holds new tree
// adjlst stores <weight,node>
vector<pair<long long int,int> > adjlst[MAX],mst[MAX];
int par[MAX],vis[MAX],n,m;
long long int dst[MAX];
vector<int> path;
long long int prim(int u)
{
	int i;
	memset(par,0,sizeof(par));
	for(i=0;i<MAX;i++)
	{
		dst[i]=LLONG_MAX;
		mst[i].clear();
	}
	memset(vis,0,sizeof(vis));
	long long int sm=0;
	priority_queue<pair<long long int,int>, vector<pair<long long int,int> >, greater<pair<long long int,int> > > pq;
	pq.push(make_pair(0LL,u));
	par[u]=u;
	dst[u]=0;
	while(!pq.empty())
	{
		pair<int,int> pp=pq.top();
		pq.pop();
		if(!vis[pp.y])
		{
			vis[pp.y]=1;
			sm+=pp.x;
			for(i=0;i<adjlst[pp.y].size();i++)
			{
				pair<int,int> v=adjlst[pp.y][i];
				if(dst[v.y]>v.x && vis[v.y]==0)
				{
					dst[v.y]=v.x;
					par[v.y]=pp.y;
					pq.push(make_pair(dst[v.y],v.y));
				}
			}
		}
	}
	for(i=1;i<=n;i++)
	{
		if(par[i]!=i)
		{
			mst[i].push_back({dst[i],par[i]});
			mst[par[i]].push_back({dst[i],i});
		}
	}
	return sm;
}
