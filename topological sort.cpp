//usage topological_sort()
//topo vector has sorted ordef
int n,m;
vector<int> topo,adjlst[MAX],idgr;
bool topological_sort(){
	int i;
	idgr.assign(n+1,0);
	priority_queue<int, vector<int>, greater<int> > pq;
	for(i=1;i<=n;i++){
		for(auto u:adjlst[i])
			idgr[u]++;
	}
	for(i=1;i<=n;i++)
		if(!idgr[i])
			pq.push(i);
	while(!pq.empty()){
		auto u=pq.top();
		pq.pop();
		topo.push_back(u);
		for(auto i:adjlst[u]){
			idgr[i]--;
			if(!idgr[i])
				pq.push(i);
		}
	}
	return topo.size()==n;
}