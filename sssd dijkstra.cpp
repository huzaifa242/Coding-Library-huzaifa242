/**
 * Usage dijkstra(source). get_path(source, any_node), ssst holds new tree
 * adjlst stores <weight,node>
 * for multi-source djikstra put all the sources in pq with dst=0
 */
vector <vector <pair <int,int> > > adjlst, ssst;
vector <int> par, vis, path;
vector <int> dst;
int n, m;
void dijkstra(int u) {
	par.assign(n + 1, 0);
	vis.assign(n + 1, 0);
	dst.assign(n + 1, LLONG_MAX);
	ssst.assign(n + 1, vector <pair <int,int> > (0));
	priority_queue <pair <int,int>, vector <pair <int,int> >, greater <pair <int,int> > > pq;
	pq.push({0ll, u});
	par[u] = u;
	dst[u] = 0;
	while (!pq.empty()) {
		auto pp = pq.top();
		pq.pop();
		if (!vis[pp.y]) {
			vis[pp.y] = 1;
			for (auto v : adjlst[pp.y]) {
				if (dst[v.y] > dst[pp.y] + v.x){
					dst[v.y] = dst[pp.y] + v.x;
					par[v.y] = pp.y;
					pq.push({dst[v.y], v.y});
				}
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		if (par[i] != i) {
			ssst[i].push_back({dst[i] - dst[par[i]], par[i]});
			ssst[par[i]].push_back({dst[i] - dst[par[i]], i});
		}
	}
}
//u must be source
void get_path(int u, int v) {
	debug(v, dst[v]);
	if (dst[v] == LLONG_MAX)
		cout << -1 << '\n';
	else {
		for (int i = v; par[i] != i; i = par[i])
			path.push_back(i);
		path.push_back(u);
		debug(path);
	}
}