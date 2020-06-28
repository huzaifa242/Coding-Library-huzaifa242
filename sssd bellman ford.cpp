/**
 * Usage bellman_ford(). if return true, sssd success 
 * else negative cycle exist stored in negcyc
 * name is bellman ford but it is spfa implementation
 */
vector <vector <pair <int,int> > > adjlst, ssst;
vector <int> negcyc, dst, par, cnt;
vector <bool> inqueue;
int n, m;
void find_neg(int s) {
	negcyc.clear();
	for (int i = 1; i <= n; ++i)
		s = par[s];
	for (int i = s;; s = par[s]) {
		negcyc.push_back(i);
		if (i == s && negcyc.size() > 1)
			break;
	}
	revere(negcyc.begin(), negcyc.end());
	return 0;
}

bool bellman_ford(int s) {
	int i, j, x;
	par.resize(n + 1);
	iota(par.begin(), par.end(), 0);
	dst.assign(n + 1, LLONG_MAX);
	cnt.assign(n + 1, 0);
	inqueue.assign(n + 1, false);
	ssst.assign(n + 1, vector <int> (0));
	queue <int> q;
	dst[s] = 0;
	q.push(s);
	inqueue[s] = true;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		inqueue[v] = false;
		for (auto uv :adjlst[v]) {
			auto u = uv.y;
			auto ln = uv.x;
			if (dst[v] + ln < dst[u]) {
				dst[u] = dst[v] + ln;
				par[u] = v;
				if (!inqueue[u]) {
					q.push(u);
					inqueue[u] = true;
					cnt[u]++;
					if (cnt[u] > n) {
						find_neg(u);
						return false;
					}
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
	return 0;
}
