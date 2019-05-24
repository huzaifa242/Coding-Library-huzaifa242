//Usage bellman_ford(). if return true, sssd success else negative cycle exist stored in negcyc
vector<pair<int,int> > adjlst[MAX],ssst[MAX];
vector<int> negcyc;
int dst[MAX],cnt[MAX],par[MAX],n,m;
bool inqueue[MAX];
void find_neg(int s)
{
	int i;
	for(i=1;i<=n;i++)
	s=par[s];
	for(i=s;;s=par[s])
	{
		negcyc.push_back(i);
		if(i==s && negcyc.size()>1)
		break;
	}
	revere(negcyc.begin(),negcyc.end());
	return 0;
}

bool bellman_ford(int s)
{
	int i,j,x;
	for(i=0;i<MAX;i++)
	{
		par[i]=i;
		dst[i]=LLONG_MAX;
		cnt[i]=0;
		inqueue[i]=false;
		ssst[i].clear();
	}
	queue<int> q;
	dst[s]=0;
	q.push(s);
	inqueue[s]=true;
	while(!q.empty())
	{
		int v=q.front();
		q.pop();
		inqueue[v]=false;
		for(auto uv:adjlst[v])
		{
			auto u=uv.y;
			auto ln=uv.x;
			if(dst[v]+ln <dst[u])
			{
				dst[u]=dst[v]+ln;
				par[u]=v;
				if(!inqueue[u])
				{
					q.push(u);
					inqueue[u]=true;
					cnt[u]++;
					if(cnt[u]>n)
					{
						find_neg(u);
						return false;
					}
				}
			}
		}
	}
	for(i=1;i<=n;i++)
	{
		if(par[i]!=i)
		{
			ssst[i].push_back({dst[i]-dst[par[i]],par[i]});
			ssst[par[i]].push_back({dst[i]-dst[par[i]],i});
		}
	}
	return 0;
}
