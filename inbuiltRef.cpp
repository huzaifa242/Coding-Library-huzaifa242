//Boost library for 128 bit int
#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;
#define ll int128_t
/*priority Queue Structure
priority_queue<T, vector<T>,decltype(pqcmp)> pq(pqcmp);*/
auto pqcmp=[&](T a,T b)
{//<-asc  >-desc};
//Double Ended Queue Structure
deque<T> dq;
dq.push_back();
dq.push_front();
dq.front();
dq.back();
dq.pop_front();
dq.pop_back();
//Comparator same as priority queue
//Set
set<T> s;
s.insert(10);
s.erase(10);
//Queue
queue<T> qu;
qu.push();
qu.front();
qu.back();
qu.pop();
//Stack
stack<T> st;
st.push();
st.top();
st.pop();
__gcd(a,b);
//C++ Lambda
sort(a,a+n,[&](int a, int b){return a>b });
__builtin_popcount(6); //returns 2. Number of set bits in binary of a number
__builtin_parity(x); //returns 1 for odd parity, 0 for even;
__builtin_clz(16); //returns 27. 32-pos(MSB 1) 64 for long long int
__builtin_ctz(16); //returns 4 position of (LSB 1) -1
