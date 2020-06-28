/**
 * Usage pre_lca(root) for precomputation and lca(u,v) for LCA
 * LCA O(1)
 */
const int lgs = 20;
vector <vector <int> > adjlst;
vector <int> euler, depth, foc, lvl, par;
int ptr, n;
//sparse table code with O(1) query
auto mrg = [&](int u, int v) {
	return depth[u] > depth[v]? v: u;
}
sparse_table <int> bld_sprs(mrg);
void lca_dfs(int u, int p, int lv) {
	lvl[u] = lv;
	par[u] = p;
	if(foc[u] == -1)
		foc[u] = ptr;
	euler.push_back(u);
	depth.push_back(lv);
	ptr++;
	for (auto &v : adjlst[u]) {
		if (p == v)
			continue;
		lca_dfs(v, u, lv + 1);
		euler.push_back(u);
		depth.push_back(lv);
		ptr++;
	}
	return;
}
void pre_lca(int root) {
	ptr = 0;
	foc.assign(n + 1, -1);
	lvl.resize(n + 1);
	par.resize(n + 1);
	euler.clear();
	depth.clear();
	lca_dfs(root, root, 0);
	bld_sprs.setsize(depth.size(), -1);
	bld_sprs.build();
}
int lca(int u, int v) {
	if (u == v)
		return u;
	else if (foc[u] > foc[v])
		swap(u,v);
	return euler[bld_sprs.query(foc[u], foc[v])];
}
int dist(int u, int v) {
	return lvl[u] + lvl[v] - 2 * lvl[lca(u, v)];
}