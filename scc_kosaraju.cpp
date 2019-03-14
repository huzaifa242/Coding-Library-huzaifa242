vector<int> adjlst[MAX],iadj[MAX],compo[MAX];
int vis[MAX],lbl[MAX]n,m;
stack<int> scc;
void st_dfs(int x, int pr)
{
	vis[x]=1;
	for(int i=0;i<adjlst[x].size();i++)
	{
		if(adjlst[x][i]!=pr)
		st_dfs(adjlst[x][i],x);
	}
	scc.push(x);
}
void i_graph()
{
	for(int i=1;i<=n;i++)
	{
		for(auto j:adjlst[i])
		iadj[j].push_back(i);
	}
}
void scc_dfs(int x,int pr, int lb)
{
	vis[x]=1;
	compo[lb].push_back(x);
	lbl[x]=lb;
	for(int i=0;i<iadj[x][i];i++)
	{
		if(x!=pr)
		scc_dfs(iadj[x][i],x,lb);
	}
}
void kosaraju()
{
	int ptr=1;
	memset(vis,0,sizeof(vis));
	memset(lbl,0,sizeof(lbl));
	while(!scc.empty())
	scc.pop();
	for(int i=0;i<MAX;i++)
	{
		iadj[i].clear();
		compo[i].clear();
	}
	st_dfs(1,0);
	i_graph();
	memset(vis,0,sizeof(vis));
	while(!scc.empty())
	{
		auto u=scc.top();
		scc.pop();
		if(!vis[u])
		{
			scc_dfs(u,0,ptr);
			ptr++;
		}
	}
}