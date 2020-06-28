/**
 * Usage floydwarshall()
 */
vector <vector <int> > dst(MAX, vector <int> (MAX, 0));
void floydwarshall() {
	for(int k = 1; k <= n; ++k)
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j)
				dst[i][j] = min(dst[i][j], dst[i][k] + dst[k][j]);
}