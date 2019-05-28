//Usage getsize(1,0)
//sack(1,0,0)
//col[] has the node values.
//sbsz[] has the subtree size
//cnt[] has the count of occurence of col[i] in subtree of u.
//O(nlogn)

vector<int> adjlst[MAX];
int n,cnt[MAX],big[MAX],sbsz[MAX]={0},col[MAX];

void getsize(int x,int p)
{
	sbsz[x]=1;
	for(auto u:adjlst[x])
	if(u!=p)
	{
		dfs(u,x);
		sbsz[x]+=sbsz[u];
	}
}

void add(int x,int p,int vl)
{
	cnt[col[x]]+=vl;
	for(auto u:adjlst[x])
	if(u!=p && !big[u])
	add(u,x,vl);
}

void sack(int x,int p,bool kp)
{
	int bigc=-1,mx=-1;
	for(auto u:adjlst[x])
	{
		if(u!=p && mx<sbsz[u])
		{
			mx=sbsz[u];
			bigc=u;
		}
	}
	for(auto u:adjlst[x])
	{
		if(u!=p && bigc!=u)
		sack(u,x,0);
	}
	if(bigc!=-1)
	{
		sack(bigc,x,1);
		big[bigc]=1;
	}
	add(x,p,1);
	
	//Now cnt has the value for subtree of x
	// so now compute answer

	if(bigc!=-1)
	big[bigc]=0;
	
	if(!kp)
	add(x,p,-1);
}