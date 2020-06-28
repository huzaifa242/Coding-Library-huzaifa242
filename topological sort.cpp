/**
 * usage topological_sort()
 * topo vector has sorted order
 */
int n, m;
vector <vector <int> > adjlst;
vector <int> topo, idgr;
bool topological_sort() {
	idgr.assign(n + 1, 0);
	priority_queue <int, vector <int>, greater <int> > pq;
	for (int i = 1; i <= n; ++i) {
		for (auto u : adjlst[i])
			idgr[u]++;
	}
	for (int i = 1; i <= n; ++i)
		if (!idgr[i])
			pq.push(i);
	while (!pq.empty()) {
		auto u = pq.top();
		pq.pop();
		topo.push_back(u);
		for (auto i : adjlst[u]){
			idgr[i]--;
			if (!idgr[i])
				pq.push(i);
		}
	}
	return topo.size() == n;
}