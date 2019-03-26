//Usage kosaraju(). 
//lbl[i] has label of each node
//compo[i] has all the node that are strongly connected
vector<int> adjlst[MAX],iadj[MAX],compo[MAX];
int vis[MAX],lbl[MAX],n,m;
stack<int> scc;
void st_dfs(int x, int pr)
{
	vis[x]=1;
	for(int i=0;i<adjlst[x].size();i++)
	{
		if(!vis[adjlst[x][i]])
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
	if(vis[x])
	return;
	//cout<<x<<" "<<pr<<endl;
	vis[x]=1;
	compo[lb].push_back(x);
	lbl[x]=lb;
	for(int i=0;i<iadj[x].size();i++)
	{
		if(!vis[iadj[x][i]])
		scc_dfs(iadj[x][i],x,lb);
	}
}
int kosaraju()
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
	for(int i=1;i<=n;i++)
	{
		if(!vis[i])
		st_dfs(i,0);
	}
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
	return ptr;
}