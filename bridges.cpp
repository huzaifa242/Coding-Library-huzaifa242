//usage bridges(). 
//bridgpt is list of all edges that are bridges
vector<int> adjlst[MAX];
vector<pair<int,int> > bridgpt;
int n,vis[MAX],tin[MAX],low[MAX],ptr;
void brdgi_dfs(int x, int pr)
{
	vis[x]=1;
	tin[x]=ptr;
	low[x]=ptr;
	ptr++;
	for(int i=0;i<adjlst[x].size();i++)
	{
		int v=adjlst[x][i];
		if(v==pr)continue;
		else if(vis[v])
		low[x]=min(low[x],tin[v]);
		else
		{
			brdgi_dfs(v,x);
			low[x]=min(low[x],low[v]);
			if(low[v]>tin[x])
			{
				bridgpt.push_back({min(x,v),max(x,v)});
			}
		}
	}
}
void bridges()
{
	ptr=0;
	memset(vis,0,sizeof(vis));
	memset(tin,0,sizeof(tin));
	memset(low,0,sizeof(low));
	memset(arti,0,sizeof(arti));
	bridgpt.clear();
	for(int i=1;i<=n;i++)
	if(!vis[i])
	brdgi_dfs(i,0);
}