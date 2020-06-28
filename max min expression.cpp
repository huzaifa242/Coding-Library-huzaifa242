/**
 * Usage max_min_expression()
 * put numbers in v
 * put operators in opr
 * mx[0][v.size()-1] has maximum value
 * mn[0][v.size()-1] has minimum value 
 */
void max_min_expression(vector <int> &v, vector <char> &opr) {
	int n = v.size();
	vector <vector <int> > mn(n, vector <int> (n));
	vector <vector <int> > mx(n, vector <int> (n));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			mn[i][j] = INT_MAX;
			mx[i][j] = INT_MIN;
			if (i == j)
				mn[i][j] = mx[i][j] = v[i];
		}
	}
	for (int len = 2; len <= n; ++len) {
		for (int i = 0; i < n - len + 1; ++i) {
			int j = i + len - 1;
			for (int k = i; k < j; ++k) {
				int mxtp,mxtp;
				if (opr[k] == '+') {
					mntp = mn[i][k] + mn[k + 1][j];
					mxtp = mx[i][k] + mx[k + 1][j];
				}
				//Similiar to '+' change operator
				//to do for any other operator
				mn[i][j] = min(mn[i][j], mntp);
				mx[i][j] = max(mx[i][j], mxtp);
			}
		}
	}
}