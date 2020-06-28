/**
 * usage bridges(). 
 * bridgpt is list of all edges that are bridges
 */
vector <vector<int> > adjlst;
vector <int> vis, tin, low;
vector <pair <int,int> > bridgpt;
int n, m, ptr;
void brdgi_dfs(int u, int p) {
	vis[u] = 1;
	tin[u] = ptr;
	low[u] = ptr;
	ptr++;
	for (auto v : adjlst[u]) {
		if (v == p)
			continue;
		else if (vis[v])
			low[u] = min(low[u], tin[v]);
		else {
			brdgi_dfs(v, u);
			low[u] = min(low[u], low[v]);
			if (low[v] > tin[u])
				bridgpt.push_back({min(u, v), max(u, v)});
		}
	}
}
void bridges() {
	ptr = 0;
	vis.assign(n + 1, 0);
	tin.assign(n + 1, 0);
	low.assign(n + 1, 0);
	bridgpt.clear();
	for (int i = 1; i <= n; ++i)
		if (!vis[i])
			brdgi_dfs(i, 0);
}