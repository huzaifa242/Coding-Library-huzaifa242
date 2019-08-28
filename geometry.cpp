// Usage point<int/double> p1;
// To know cw or ccw of vector AB and CD
// (B-A).cross(D-C)
// if cross < 0 then AB has more theta with positive x axis than CD
// if cross > 0 then AB has less theta with positive x axis than CD
// if cross == 0 then AB and CD are collinear
template<typename T>
class point
{
	private:
	T eps=1e-15;
	public:
	T x,y;
	point()
	{}
	point(T _x, T _y)
	{
		x=_x;
		y=_y;
	}
	bool operator == (const point &a)
	{
		return abs(x-a.x)<=eps && abs(y-a.y)<=eps;
	}
	bool operator < (const point &a)
	{
		return (abs(x-a.x)<eps)?y<a.y:x<a.x;
	}
	bool operator <= (const point &a)
	{
		return (*this==a)||(*this<a);	
	}
	void operator =(const point &a)
	{
		x=a.x,y=a.y;
	}
	point operator +(const point &a)
	{
		return point(x+a.x,y+a.y);
	}
	point operator -(const point &a)
	{
		return point(x-a.x,y-a.y);
	}
	T dot(const point &a)
	{
		return x*a.x + y*a.y;
	}
	T cross(const point &a)
	{
		T crs=x*a.y - y*a.x;
		return (abs(crs)<=eps)?0:crs;
	}
	T mag()
	{
		return x*x + y*y;
	}
};
template<typename T>
class line
{
	private:
	T eps=1e-15;
	public:
	T a,b,c;
	line()
	{}
	line(T _a, T _b,T _c)
	{
		a=_a,b=_b,c=_c;
	}
	line(point<T> p,point<T> q)
	{
		if(abs(p.x-q.x)<=eps)
		{
			a=1;b=0;c=p.x;
		}
		else
		{
			a=q.y-p.y;
			b=p.x-q.x;
			c=a*p.x+b*p.y;
		}
	}
	line(T _m, T _c)
	{
		a=-_m;b=1;c=_c;
	}
	bool is_parallel(const line &l)
	{
		return abs(a*l.b-l.a*b)<=eps;
	}
	point<T> intersect(const line &l)
	{
		if(is_parallel(l))
			return point<T>(-eps,eps);
		if(abs(b)<=eps)
			return point<T>(c,(l.c-l.a*c)/l.b);
		else if(abs(l.b)<=eps)
			return point<T>(l.c,(c-a*l.c)/b);
		T x,y;
		x=(c*l.b-b*l.c)/(a*l.b-l.a*b);
		y=(c*l.a-a*l.c)/(l.a*b-a*l.b);
		return point<T>(x,y);
	}
	line<T> normal_at(const point<T> &p)
	{
		return line<T>(-b,a,a*p.y-b*p.x);
	}
	T dist(const point<T> &p)
	{
		T dst=abs(a*p.x+b*p.y+c)/sqrt(a*a + b*b);
		return dst<eps?0:dst;
	}
};
template<typename T>
class l_segment
{
	private:
	T eps=1e-15;
	public:
	line<T> l;
	point<T> a,b;
	l_segment(point<T> _a, point<T> _b)
	{
		l=line<T>(_a,_b);
		a=_a,b=_b;
	}
	bool on_segment(const point<T> &p)
	{
		bool on=true;
		on&=min(a.x,b.x)<=p.x+eps && p.x<=max(a.x,b.x)+eps;
		on&=min(a.y,b.y)<=p.y+eps && p.y<=max(a.y,b.y)+eps;
		return on;
	}
	point<T> intersect(l_segment &ls)
	{
		point<T> insec=l.intersect(ls.l);
		return on_segment(insec)?insec:point<T>(-eps,eps);
	}
	point<T> intersect(const line<T> &ls)
	{
		point<T> insec=l.intersect(ls);
		return on_segment(insec)?insec:point<T>(-eps,eps);
	}
	bool is_parallel(l_segment &ls)
	{
		return l.is_parallel(ls.l);
	}
	bool is_parallel(const line<T> &ls)
	{
		return l.is_parallel(ls);
	}
	T dist(const point<T> &p)
	{
		if((b-a).dot(p-b)>0)
			return sqrt((b-p).mag());
		if((b-a).dot(p-a)>0	)
			return sqrt((b-p).mag());
		return l.dist(p);
	}
};