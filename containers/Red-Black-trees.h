#include<iostream>
#include<string>
#include <iomanip> 
template<typename T, typename D>
class Tree {
	struct Node {
		Node* left;
		Node* right;
		T key;
		D element;
		Node() { left = nullptr; right = nullptr; }
		Node(T key, D elem) :key(key), element(elem) { left = nullptr; right = nullptr; };
		Node(const Node& n) :key(key), element(n.element), left(n.left), right(n.right) {};
		Node& operator=(const Node& n) {
			key = n.key;
			element = n.element;
			left = n.left;
			right = n.right;
			return *this;
		}
		bool operator<=(const Node& n)const { return key <= n.key; }
		bool operator<(const Node& n)const { return key < n.key; }
		bool operator>=(const Node& n)const { return key >= n.key; }
		bool operator>(const Node& n)const { return key > n.key; }
		friend std::ostream& operator<<(std::ostream& ostream, const Node* n) {
			if (n == nullptr) return ostream << "Empty";
			ostream << n->key << ":" << n->element;
			return ostream;
		}
	};
	Node* root;
	int height;


	Node* insert(T key, D elem, Node* t) {
		if (t == nullptr)
			return new Node(key, elem);
		if (t->key == key) return t;
		if (t->key > key) t->left = insert(key, elem, t->left);
		if (t->key < key) t->right = insert(key, elem, t->right);
		return t;
	}
	Node* find(T key, Node* t) {
		if (t == nullptr)return t;
		if (t->key > key)return find(key, t->left);
		else if (t->key < key)return find(key, t->right);
		return t;
	}

	Node* eraseMax(Node* t) {
		if (t->right)t->right = eraseMax(t->right);
		else
			return t->left;
		return t;
	}
	Node* erase(T key, Node* t) {
		if (t == nullptr) return t;
		if (t->key > key) t->left = erase(key, t->left);
		else if (t->key < key) t->right = erase(key, t->right);
		else {
			Node* max = findMax(t->left);
			Node* left = t->left; *right = t->right;
			delete t;
			max->right = right;
			max->left = eraseMax(left);
			return max;
		}
		return t;
	}

	int prtakeSize(int& res, Node* cur_node)const {
		res++;
		if (cur_node->right)
			prtakeSize(res, cur_node->right);
		if (cur_node->left)
			prtakeSize(res, cur_node->left);

		return res;
	};
	int prtakeHeight(Node* n) const {
		int h = 0, l = 0, r = 0;
		if (n->left)l = prtakeHeight(n->left);
		if (n->right)r = prtakeHeight(n->right);
		return h = ((l > r) ? l : r) + 1;
	}
public:

	Tree(T key, D elem) {
		height = 0;
		root = new Node(key, elem);
	}
	Tree(const Tree& t) { root = t.root; height = 0; }
	int takeSize() const {
		int result = 0;
		result = prtakeSize(result, root);
		return result;
	}

	Tree& operator= (const Tree& t) { root = t.root; return*this; }

	int takeHeight() const {
		return prtakeHeight(root);
	}

	Node* findMax(Node* t)
	{
		if (t == nullptr || t->right == nullptr) return t;
		else findMax(t->right);
	}
	Node* findMin(Node* t)
	{
		if (t == nullptr || t->left == nullptr) return t;
		else findMax(t->left);
	}
	bool find(T key) {
		return !(!find(key, root));
	}
	void insert(T key, D elem) {
		this->root = insert(key, elem, root);
	}


	friend std::ostream& recOut(std::ostream& ostream, const Node* n) {
		ostream << n << "\n";
		if (n->left)recOut(ostream, n->left);
		if (n->right)recOut(ostream, n->right);

		return ostream;
	}
	friend std::ostream& operator<<(std::ostream& ostream, const Tree& t) {
		recOut(ostream, t.root);

		return ostream;
	}
};