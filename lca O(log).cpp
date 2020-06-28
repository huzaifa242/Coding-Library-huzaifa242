/**
 * Usage pre_lca(root) for precomputation and lca(u,v) for LCA
 * LCA O(log)
 */
const int lgs = 20;
vector <vector <int> > adjlst, up;
vector <int> in, out, lvl;
int ptr, n;
void lca_dfs(int u, int p, int lv) {
	lvl[u] = lv;
	in[u] = ++ptr;
	up[u][0] = p;
	for (int i = 1; i < lgs; ++i)
		up[u][i] = up[up[u][i - 1]][i - 1];
	for (auto &v : adjlst[u]) {
		if (v == p)
			continue;
		lca_dfs(v, u, lv + 1);
	}
	out[u] = ptr;
	return;
}
bool is_ancetor(int u, int v) {
	return in[u] <= in[v] && out[u] >= out[v];
}
int lca(int u, int v) {
	if (is_ancetor(u, v))
		return u;
	if (is_ancetor(v, u))
		return v;
	for(int i = lgs - 1; i >= 0; --i)
		if (!is_ancetor(up[u][i], v))
			u = up[u][i];
	return up[u][0];
}
void pre_lca(int root) {
	ptr = -1;
	lvl.resize(n + 1);
	in.resize(n + 1);
	out.resize(n + 1);
	up.assign(n + 1,vector <int>(lgs));
	lca_dfs(root, root,0);
}