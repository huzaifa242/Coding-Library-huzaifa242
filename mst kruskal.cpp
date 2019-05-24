//Usage kruskal(). mst holds new tree
// adjlst stores <weight,node>
struct edg
{
	int u,v,w,id;
}edglst[MAX];
vector<pair<int,int> > adjlst[MAX],mst[MAX];
int dsu[MAX],sz[MAX],connected,n,m;
void clr_dsu()
{
	for(int i=0;i<MAX;i++)
	{
		dsu[i]=i;
		sz[i]=0;
		tree[i].clear();
	}
	connected=n;
}
void find_par(int k)
{
	if(dsu[dsu[k]]==k)
	return;
	find_par(dsu[k]);
	dsu[k]=dsu[dsu[k]];
}
void union_all(int u, int v)
{
	find_par(u);
	find_par(v);
	if(dsu[u]!=dsu[v])
	{
		connected--;
		sz[dsu[u]]+=sz[dsu[dsu[v]]];
		sz[dsu[dsu[v]]]=0;
	}
	dsu[dsu[v]]=dsu[u];
}
int krushkal()
{
	clr_dsu();
	int sm=0;
	sort(edglst,edglst+m,[&](edg a,edg b)-> bool {return a.w<b.w;});
	for(int i=0;i<m;i++)
	{
		int u=edglst[i].u,v=edglst[i].v;
		find_par(u);
		find_par(v);
		if(dsu[u]!=dsu[v])
		{
			sm+=edglst[i].w;
			mst[u].push_back({edglst[i].w,v});
			mst[v].push_back({edglst[i].w,u});
			union_all(dsu[u],dsu[v]);
		}
	}
	return sm;
}