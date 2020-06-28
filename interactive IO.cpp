/**
 * I/O class for interactive question
 * can't use integer literal or chars.
 * use string for constant output
 */
static char GLOBAL_STATE  = 'R';
class Icout {
	char STATE = 'O';
	public:
	template <typename T>
	Icout& operator << (T &a){
		if (GLOBAL_STATE != STATE) {
			std::cerr << endl << "  sol: ";
			GLOBAL_STATE = STATE;
		}
		std::cerr << a;
		std::cout << a;
		return *this;
	}
	void tie(int a) {
		std::cout.tie(0);
	}
	Icout& operator << (std::ostream&(*p)(std::ostream&)) {
		std::cerr << *p;
		std::cout << *p;
		return *this;
	}
} customcout;
class Icin {
	char STATE = 'I';
	public:
	template <typename T>
	Icin& operator >> (T &a){
		if (GLOBAL_STATE != STATE){
			std::cerr << endl << "judge: ";
			GLOBAL_STATE = STATE;
		}
		std::cin >> a;
		std::cerr << a << ' ';
		return *this;
	}
	void tie(int a) {
		std::cout.tie(0);
	}
}customcin;
// Put this in #define LOCAL
#define cout customcout
#define cin customcin
