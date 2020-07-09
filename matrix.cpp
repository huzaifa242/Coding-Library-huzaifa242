template <typename T>
class Matrix {
	public:
	int n,m;
	vector <vector <T> > a;
	
	Matrix(int sz) {
		n = sz;m = sz;
		a.assign(n, vector <T> (m, 0));
	}
	Matrix(int _n, int _m) {
		n = _n;m = _m;
		a.assign(n, vector <T> (m, 0));
	}
	vector <T>& operator [] (int i) {
		return a[i];
	}
	Matrix <T> operator * (Matrix<T> &b) {
		Matrix <T> c(n, b.m);
		if (m != b.n)
			return c;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j)
				for (int k = 0; k < b.m; ++k)
					c.a[i][j] = md(c.a[i][j] + md(a[i][k] * b.a[k][j]));
		return c;
	}
	friend ostream& operator << (ostream& out, const Matrix<T> &c) {
		for(auto i : c.a)
			out << i;
		return out << endl;
	}
};
template <typename T>
Matrix <T> matxpo(Matrix <T> &a, int n){
	if (n == 0) {
		Matrix <T> b(a.n);
		for (int i = 0; i < b.n; ++i)
			b[i][i] = 1;
		return b;
	} else if (n == 1)
		return a;
	Matrix <T> x = matxpo(a, n / 2);
	x = (x * x);
	if (n & 1)
		x = (x * a);
	return x;
}
//determinant from cp-algos/determinant-gauss
template <typename T>
T determinant(Matrix <T> a) {
	long double eps = 1e-9;
	T dt = 1;
	for (int i = 0; i < a.n; ++i) {
		int k = i;
		for (int j = i + 1; j < a.n; ++j)
			if (abs(a[j][i]) > abs(a[k][i]))
				k = j;
		if (a[k][i] == 0)//use a[k][i]<eps
			return 0;
		swap(a[i], a[k]);
		if (i != k)
			dt = md(-dt);
		dt = md(dt * a[i][i]);
		for (int j = i + 1; j < a.n; ++j)
			a[i][j] = md(a[i][j] * modinv(a[i][i]));
		for (int j = 0; j < a.n; ++j)
			if (j != i && abs(a[j][i]))//use abs(a[j][i])>eps
				for(k = i + 1; k < a.n; ++k)
					a[j][k] = md(a[j][k] - md(a[i][k] * a[j][i]));
	}
	return dt;
}