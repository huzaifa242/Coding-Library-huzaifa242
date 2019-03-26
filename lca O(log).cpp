//Usage pre_lca(root) for precomputation and lca(u,v) for LCA
//LCA O(log)
#define lgs 20
vector<int> adjlst[MAX];
int lvl[MAX],tin[MAX],tout[MAX],up[MAX][lgs],ptr;
void lca_dfs(int x,int pr,int dep)
{
	lvl[x]=dep;
	tin[x]=++ptr;
	up[x][0]=pr;
	for (int i = 1; i <lgs; ++i)
	up[x][i] = up[up[x][i-1]][i-1];
	//cout<<x<<"$"<<par[x]<<" "<<lvl[x]<<"\n";
	for(int i=0;i<adjlst[x].size();i++)
	{
		//cout<<adjlst[x][i]<<"#\n";
		if(pr!=adjlst[x][i])
		{
			lca_dfs(adjlst[x][i],x,dep+1);
		}
	}
	tout[x]=++ptr;
	return;
}
bool is_ancetor(int u, int v)
{
	return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v)
{
	if (is_ancetor(u, v))
		return u;
	if (is_ancetor(v, u))
		return v;
	for (int i = lgs-1; i >= 0; --i) {
		if (!is_ancetor(up[u][i], v))
			u = up[u][i];
	}
	return up[u][0];
}
void pre_lca(int root) 
{
	ptr = 0;
	lca_dfs(root, root,0);
}