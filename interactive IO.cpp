// I/O class for interactive question
// can't use integer literal or chars.
// use string for constant output
class Icout{
	public:
	template <typename T>
	Icout& operator<< (T &a){
		std::cerr<<a;
		std::cout<<a;
		return *this;
	}
	void tie(int a){
		std::cout.tie(0);
	}
	Icout& operator<< (std::ostream&(*p)(std::ostream&)){
		std::cerr<<*p;
		std::cout<<*p;
		return *this;
	}
}customcout;
// Put this in #define LOCAL
#define cout customcout
