/**
 * while using address all the comments in the code
 * default implementation of key_to_string is for int->string
 * Query method is for actual logic
 * Usage trie <T> name(starting_char) (default value type is int)
 * Usage trie<T, G> name(starting_char) value type is G
 */
template <typename T, typename G = int>
class trie {
	private:
	// Look at this and change
	const static int alpha = 2;
	char start;
	bool conversion_required;
	struct node_t {
		G count = {0};
		bool is_leaf = false;
		array<node_t*, alpha> child;
	};
	node_t* head;
	// override this method for proper string conversion
	string key_to_string(T &key) {
		string new_key = "";
		int bits = 31;
		for (int i = bits; i >= 0; --i) 
			new_key += char(((key >> i) & 1) + '0');
		return new_key;
	}
	string get_key(T &key) {
		if (conversion_required) 
			return key_to_string(key);
		return to_string(key);
	}
	node_t* get_node() {
		return new node_t();
	}
	public:
	trie(char _start) {
		head = get_node();
		start = _start;
		conversion_required = typeid(T).name() != typeid(string).name();
	}
	// change based on value type
	void insert(T &key, G val = G(1)) {
		node_t* cur = head;
		string k = get_key(key);
		for (int i = 0; i < k.length(); ++i) {
			int id = k[i] - start;
			if (!cur->child[id]) 
				cur->child[id] = get_node();
			cur = cur->child[id];
			cur->count += val;
			//Do rest operation here
		}
		cur->is_leaf = true;
	}
	void remove(T &key) {
		node_t* cur = head;
		string k = get_key(key);
		G val = find(key);
		for (int i = 0; i < k.length(); ++i) {
			int id = k[i] - start;
			if (!cur->child[id]) { 
				// No child Handle
				assert(false);
			}
			cur = cur->child[id];
			cur->count -= val; //handle this carefully
			//Do rest operation here
		}
	}
	G find(T &key) {
		node_t* cur = head;
		string k = get_key(key);
		for (int i = 0; i < k.length(); ++i) {
			int id = k[i] - start;
			if (!cur->child[id]) { 
				// No child Handle
				assert(false);
			}
			cur = cur->child[id];
			//Do rest operation here
		}
		return cur->count;
	}
	// write logic in this method
	G query(T &key) {
		node_t* cur = head;
		string k = get_key(key);
		G val = {0};
		for (int i = 0; i < k.length(); ++i) {
			int id = k[i] - start;
			if (!cur->child[id]) { 
				// No child Handle
				assert(false);
			}
			cur = cur->child[id];
			//Do rest operation here
		}
		return val;
	}
};