/**
 * usage articulation_points(). 
 * arti[i] denotes wheather the node is AP 
 * artpt is list of all nodes that are AP
 */
vector <vector <int> > adjlst;
vector <int> artpt, vis, tin, low;
vector <bool> arti;
int n, ptr;
void arti_dfs(int u, int p) {
	vis[u] = 1;
	tin[u] = ptr;
	low[u] = ptr;
	ptr++;
	int kf = 0;
	for (auto v : adjlst[u]) {
		if (v == p)
			continue;
		else if (vis[v])
			low[u] = min(low[u], tin[v]);
		else {
			arti_dfs(v, u);
			low[u] = min(low[u], low[v]);
			if (low[v] >= tin[u] && p != 0) {
				if (!arti[u])
					artpt.push_back(u);
				arti[u] = true;
			}
			kf++;
		}
	}
	if (p == 0 && kf > 1) {
		if (!arti[u])
			artpt.push_back(u);
		arti[u] = true;
	}
}
void articulation_points() {
	ptr = 0;
	vis.assign(n + 1, 0);
	tin.assign(n + 1, 0);
	arti.assign(n + 1, 0);
	low.assign(n + 1, 0);
	artpt.clear();
	for (int i = 1; i <= n; ++i)
	if (!vis[i])
		arti_dfs(i, 0);
}