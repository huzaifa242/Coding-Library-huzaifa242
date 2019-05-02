//usage topological_sort()
//topo vector has sorted ordef
int idgr[MAX],n,m;
vector<int> topo,adjlst[MAX];
bool topological_sort()
{
	int i;
	memset(idgr,0,sizeof(idgr));
	priority_queue<int, vector<int>, greater<int> > pq;
	for(i=1;i<=n;i++)
	{
		for(auto u:adjlst[i])
		idgr[u]++;
	}
	for(i=1;i<=n;i++)
	if(!idgr[i])
	pq.push(i);
	while(!pq.empty())
	{
		auto u=pq.top();
		pq.pop();
		topo.push_back(u);
		for(auto i:adjlst[u])
		{
			idgr[i]--;
			if(!idgr[i])
			pq.push(i);
		}
	}
	return topo.size()==n;
}