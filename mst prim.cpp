/**
 * Usage prim(source). mst holds new tree
 * adjlst stores <weight,node>
 */
vector <vector <pair <int,int> > > adjlst, mst;
vector <int> par, vis, dst;
int n, m;
int prim(int u) {
	par.assign(n + 1, 0);
	vis.assign(n + 1, 0);
	dst.assign(n + 1, LLONG_MAX);
	mst.assign(n + 1, vector <pair <int,int> > (0));
	int sm = 0;
	priority_queue <pair <int,int>, vector <pair <int,int> >, greater <pair <int,int> > > pq;
	pq.push(make_pair(0ll, u));
	par[u] = u;
	dst[u] = 0;
	while (!pq.empty()) {
		auto pp = pq.top();
		pq.pop();
		if (!vis[pp.y]) {
			vis[pp.y] = 1;
			sm += pp.x;
			for (auto v : adjlst[pp.y]) {
				if (dst[v.y] > v.x && vis[v.y] == 0) {
					dst[v.y] = v.x;
					par[v.y] = pp.y;
					pq.push({dst[v.y], v.y});
				}
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		if (par[i] != i) {
			mst[i].push_back({dst[i], par[i]});
			mst[par[i]].push_back({dst[i], i});
		}
	}
	return sm;
}
