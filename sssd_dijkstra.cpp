//Usage dijkstra(source). get_path(source, any_node)
// adjlst stores <weight,node>
vector<pair<int,int> > adjlst[MAX];
int par[MAX],vis[MAX],dst[MAX];
vector<int> path;
void dijkstra(int u)
{
	int i;
	memset(par,0,sizeof(par));
	for(i=0;i<MAX;i++)
	dst[i]=LLONG_MAX;
	memset(vis,0,sizeof(vis));
	priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > pq;
	pq.push(make_pair(0,u));
	par[u]=u;
	dst[u]=0;
	while(!pq.empty())
	{
		pair<int,int> pp=pq.top();
		pq.pop();
		if(!vis[pp.y])
		{
			vis[pp.y]=1;
			for(i=0;i<adjlst[pp.y].size();i++)
			{
				pair<int,int> v=adjlst[pp.y][i];
				if(dst[v.y]>dst[pp.y]+v.x)
				{
					dst[v.y]=dst[pp.y]+v.x;
					par[v.y]=pp.y;
					pq.push(make_pair(dst[v.y],v.y));
				}
			}
		}
	}
}
//u must be source
void get_path(int u, int v)
{
	//cout<<"Distance: "<<dst[v]<<endl;
	//cout<<"Path \n";
	if(dst[v]==LLONG_MAX)
	cout<<-1<<"\n";
	else
	{
		for(i=v;par[i]!=i;i=par[i])
		path.push_back(i);
		path.push_back(u);
		for(i=path.size()-1;i>=0;i--)
		cout<<path[i]<<" ";
		cout<<"\n";
	}
}