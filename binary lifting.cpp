//Usage binlft_dfs(root,0) then getparent(node, distance_from_node)
#define lgs 20
vector<int> adjlst[MAX];
int up[MAX][lgs];
void binlft_dfs(int x, int pr)
{
	up[x][0]=p;
	for(int i=1;i<lgs;i++)
	{
		up[x][i]=up[up[x][i-1]][i-1];
	}
	for(auto vv:adjlst[x])
	{
		if(vv!=pr)
		binlift_dfs(vv,x);
	}
}
int getparent(int u, int lv)
{
	if(lv<0)
	return 0;
	for(int i=lgs-1;i>=0;i--)
	{
		if((1<<i)&lv)
		{
			u=up[u][i];
		}
	}
	return u;
}