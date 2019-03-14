//usage articulation_points(). 
//arti[i] denotes wheather the node is AP 
//artpt is list of all nodes that are AP
vector<int> adjlst[MAX],artpt;
int n,vis[MAX],tin[MAX],low[MAX],ptr;
bool arti[MAX];
void arti_dfs(int x, int pr)
{
	vis[x]=1;
	tin[x]=ptr;
	low[x]=ptr;
	ptr++;
	int kf=0;
	for(int i=0;i<adjlst[x].size();i++)
	{
		int v=adjlst[x][i];
		if(v==pr)continue;
		else if(vis[v])
		low[x]=min(low[x],tin[v]);
		else
		{
			arti_dfs(v,x);
			low[x]=min(low[x],low[v]);
			if(low[v]>=tin[x] && pr!=0)
			{
				if(!arti[x])
				artpt.push_back(x);
				arti[x]=true;
			}
			kf++;
		}
	}
	if(pr==0 && kf>1)
	{
		if(!arti[x])
		artpt.push_back(x);
		arti[x]=true;
	}
}
void articulation_points()
{
	ptr=0;
	memset(vis,0,sizeof(vis));
	memset(tin,0,sizeof(tin));
	memset(low,0,sizeof(low));
	memset(arti,0,sizeof(arti));
	artpt.clear();
	for(int i=1;i<=n;i++)
	if(!vis[i])
	arti_dfs(i,0);
}