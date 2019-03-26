//Usage bellman_ford(). if return true, sssd success else negative cycle exist stored in negcyc
struct edg
{
	long long int u,v,w,id;
}edglst[MAX];
vector<pair<long long int,int> > adjlst[MAX],ssst[MAX];
vector<int> negcyc;
long long int dst[MAX],par[MAX],n,m;
bool bellman_ford()
{
	int i,j,x;
	for(i=0;i<MAX;i++)
	{
		par[i]=i;
		dst[i]=LLONG_MAX;
	}
	for(i=1;i<=n;i++)
	{
		x=-1;
		for(j=0;j<m;j++)
		{
			if(d[edglst[j].v]> d[edglst[j].u]+edglst[j].w)
			{
				d[edglst[j].v]=d[edglst[j].u]+edglst[j].w;
				par[edglst[j].v]=edglst[j].u;
				x=edglst[j].v;
			}
		}
	}
	if(x==-1)
	return 1;
	for(i=1;i<=n;i++)
	x=par[x];
	for(i=x;;x=par[x])
	{
		negcyc.push_back(i);
		if(i==x && negcyc.size()>1)
		break;
	}
	revere(negcyc.begin(),negcyc.end());
	return 0;
}
