/**
 * Usage binlft_dfs(root,0) then getparent(node, distance_from_node)
 */
const int lgs = 20;
vector <vector <int> > adjlst, up(MAX, vector <int> (lgs));
void binlft_dfs(int u, int p) {
	up[u][0] = p;
	for (int i = 1; i < lgs; ++i)
		up[u][i] = up[up[u][i - 1]][i - 1];
	for (auto v : adjlst[u])
		if (v != p)
			binlift_dfs(v,u);
}
int getparent(int u, int lv) {
	if (lv < 0)
		return 0;
	for (int i = lgs - 1; i >= 0; --i)
		if ((1<<i) & lv)
			u = up[u][i];
	return u;
}