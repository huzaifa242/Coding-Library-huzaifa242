/**
 * SquareRoot Decomposition
 * Usage sqrt_decomposition s1(size)
 */
struct bkt {
	//Node Structure of Bucket
};
class sqrt_decomposition {
	private:
	int bksz, tbk, n;
	vector <bkt> sqan;
	public:
	sqrt_decomposition(int size) {
		n = size;
		bksz = sqrt(n);
		tbk = (n % bksz == 0? n / bksz: (n / bksz) + 1);
		sqan.resize(tbk);
	}
	void sqan_init() {
		for(int i = 0; i < tbk; ++i) {
			//init bucket block
		}
		for(int i = 0; i < n; ++i) {
			//Array bucket relation
		}
	}
	int query(int l,int r) {
		int i, bs, be, ans, s, e;
		bs = l / bksz + 1;
		be = r / bksz;
		s = (l / bksz) * bksz;
		debug(s, bs * bksz);
		for (int i = s; i < bs * bksz; ++i) {
			if (i < l) {
				// start of this bucket to  l-1
			} else {
				// l to start of nearest bucket
			}
		}
		debug(bs, be);
		for (int i = bs; i < be; ++i) {
			// block/bucket traversal 
		}
		e = min((be + 1) * bksz, n);
		debug(be * bksz, e);
		for (int i = be * bksz; i < e; ++i) {
			if (i <= r) {
				// last bucket to r
			} else {
				// r+1 to end of that bucket
			}
		}        
	}
};