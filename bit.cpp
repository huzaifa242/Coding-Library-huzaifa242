/**
 * Distinct AND/OR of SUBARRAY
 * Usage init_fwd -> nxtchg_generator -> fwd_distinct
 * poss,pose will have position of range of distinct number and fdist will have actual numbers
 */
const int bts = 64;
vector <vector <int> > poss, pose, zbit, fdist, nxtchg;
void init_fwd(int n) {
	poss.assign(n, vector <int> (0));
	pose.assign(n, vector <int> (0));
	fdist.assign(n, vector <int> (0));
	nxtchg.assign(n, vector <int> (bts, n));
}
void nxtchg_generator(int n) {
	for (int j = 0; j < bts; ++j) {
		for (int i = n - 1; i >= 0; --i) {
			int k = a[i] & (1 << j);
			if (!zbit[j].empty() && k)//if(!zbit[j].empty() && !k) for OR
				nxtchg[i][j] = min(nxtchg[i][j], zbit[j].back());
			if (!k)// if(k) for OR
				zbit[j].push_back(i);
		}
	}
	for (auto &chg : nxtchg)
		sort(chg.begin(), chg.end());
	debug(zbit, nxtchg)
}
void fwd_distinct(int n) {
	init_fwd(n);
	nxtchg_generator(n);
	for (int i = 0; i < n; ++i) {
		int j, an = a[i];
		if (1) {//condition to include distinct
			j=nxtchg[i][0];
			fdist[i].push_back(an);
			poss[i].push_back(i);
		}
		for (int k = 0; k < bts; ++k) {
			j = nxtchg[i][k];
			if (an == 0){//if(an==(1<<bts)-1) for OR
				pose[i].push_back(n - 1);
				break;
			}
			if (j == n) {
				if(1)//condition to include distinct
					pose[i].push_back(n - 1);
				break;
			}
			if (k == 0 && j != i) {
				if (1)//condition to include distinct
					pose[i].push_back(j - 1);
				an &= a[j];//| for OR
				if (1) {//condition to include distinct
					debug(i, k, an);
					poss[i].push_back(j);
					fdist[i].push_back(an);
				}
			} else if (k == 0 && j == i) {

			} else if (nxtchg[i][k] != nxtchg[i][k - 1]) {
				if(1)//condition to include distinct
					pose[i].push_back(j - 1);
				an &= a[j];//| for OR
				if (1) {//condition to include distinct
					debug(i, k, an);
					poss[i].push_back(j);
					fdist[i].push_back(an);
				}
			}
		}
		// Pose[i] > Poss[i]
		debug(i, pose, poss, fdist);
	}
}
vector <vector <int> > rposs, rpose, rzbit, rdist, prvchg;
void init_rev(int n){
	rposs.assign(n, vector <int> (0));
	rpose.assign(n, vector <int> (0));
	rdist.assign(n, vector <int> (0));
	prvchg.assign(n, vector <int> (bts, -1));
}
void prvchg_generator(int n){
	int i,j,k;
	for (int j = 0; j < bts; ++j) {
		for (int i = 0; i < n; ++i) {
			int k = a[i] & (1 << j);
			if (!rzbit[j].empty() && k)
				prvchg[i][j] = max(prvchg[i][j], rzbit[j].back());
			if(!k)
				rzbit[j].push_back(i);
		}
	}
	for (auto &chg : prvchg) 
		sort(chg.rbegin(), chg.rend());
	debug(rzbit, prvchg);
}
void rev_distinct(int n) {
	int i,j,k,an;
	init_rev(n);
	prvchg_generator(n);
	for (int i = n - 1; i >= 0; --i) {
		int j, an = a[i];
		if (1) {//condition to include distinct
			j = prvchg[i][0];
			rposs[i].push_back(i);
			rdist[i].push_back(an);
		}
		for (int k = 0; k < bts; ++k) {
			j = prvchg[i][k];
			if (an == 0) {//if(an==(1<<bts)-1) for OR
				rpose[i].push_back(0);
				break;
			}
			if (j == -1) {
				if(1)//condition to include distinct
					rpose[i].push_back(0);
				break;
			}
			if (k == 0 && j != i) {
				if (1)//condition to include distinct
					rpose[i].push_back(j + 1);
				an &= a[j];//| for OR
				if(1){//condition to include distinct
					debug(i, k, an);
					rposs[i].push_back(j);
					rdist[i].push_back(an);
				}
			}else if( k==0 && j==i){

			}else if(prvchg[i][k]!=prvchg[i][k - 1]){
				if(1)//condition to include distinct
					rpose[i].push_back(j + 1);
				an&=a[j];//| for OR
				if(1){//condition to include distinct
					debug(i, k, an);
					rposs[i].push_back(j);
					rdist[i].push_back(an);
				}
			}
		}
		// rposs[i] > rpose[i]
		debug(i, rposs, rpose, rdist);
	}
}
