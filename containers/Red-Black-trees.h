#include<iostream>
#include<string>

template<typename T, typename D>
class Tree {
	struct Node {
		Node* left;
		Node* right;
		int height;
		T key;
		D element;
		Node() { left = nullptr; right = nullptr; height = 0; }
		Node(T key, D elem) :key(key), element(elem) { left = nullptr; right = nullptr; height = 0; };
		Node(const Node& n) :key(key), element(n.element), left(n.left), right(n.right), height(n.height) {};
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

	Node* prinsert(T key, D elem, Node* t) {
		if (t == nullptr)
			return new Node(key, elem);
		if (t->key == key) return t;
		if (t->key > key) {
			t->left = prinsert(key, elem, t->left);
			balance(t);
		}
		if (t->key < key) {
			t->right = prinsert(key, elem, t->right);
		}

		return t;
	}
	Node* prfind(T key, Node* t) {
		if (t == nullptr)return t;
		if (t->key > key)return prfind(key, t->left);
		else if (t->key < key)return prfind(key, t->right);
		return t;
	}
	Node* preraseMax(Node* t) {
		if (t->right)t->right = preraseMax(t->right);
		else
			return t->left;
		return t;
	}
	Node* prerase(T key, Node* t) {
		if (t == nullptr) return t;
		if (t->key > key) {
			t->left = prerase(key, t->left);
			t->height--;
		}
		else if (t->key < key) {
			t->right = prerase(key, t->right);
			t->height--;
		}
		else {
			Node* max = findMax(t->left);
			Node* left = t->left, * right = t->right;
			delete t;
			max->right = right;
			max->left = preraseMax(left);
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
		int l = 0, r = 0;
		if (!n)return 0;
		if (n->left)l = prtakeHeight(n->left);
		if (n->right)r = prtakeHeight(n->right);
		return ((l > r) ? l : r) + 1;
	}
	Node* prfindNext(Node* cur_node, bool flag = false) {
		if (!flag && cur_node->right) cur_node = prfindNext(cur_node->right, true);
		else if (flag && cur_node->left)cur_node = prfindNext(cur_node->left, true);
		return cur_node;
	}
	Node* prfindPrev(Node* cur_node, bool flag = false) {
		if (!flag && cur_node->left) cur_node = prfindPrev(cur_node->left, true);
		else if (flag && cur_node->right)cur_node = prfindPrev(cur_node->right, true);
		return cur_node;
	}
	Node* balance(Node* t) {
		int balfunc = takeHeight(t->right) - takeHeight(t->left);
		if (balfunc == 2) {
			if (takeHeight(t->right->right) - takeHeight(t->right->left) < 0)
				rightRotate(t->right);
			leftRotate(t);
		}
		else if (balfunc == -2) {
			if (takeHeight(t->left->left) - takeHeight(t->left->right) < 0)
				leftRotate(t->left);
			rightRotate(t);
		}
		return t;
	}

	void rightRotate(Node* t) {

		Node* new_local_root = t->left;
		t->left = new_local_root->right;
		new_local_root->right = t;
	}
	void leftRotate(Node* t) {
		Node* new_local_root = t->right;
		t->right = new_local_root->left;
		new_local_root->left = t;
	}

public:
	Tree() { root = nullptr; }

	Tree(T key, D elem) {
		root = new Node(key, elem);
	}
	Tree(const Tree& t) { root = t.root; }
	int takeSize() const {
		int result = 0;
		result = prtakeSize(result, root);
		return result;
	}

	Tree& operator= (const Tree& t) { root = t.root; return*this; }

	int takeHeight(Node* t) const {
		return prtakeHeight(t);
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
	Node* find(T key) {
		return prfind(key, root);
	}
	void insert(T key, D elem) {
		this->root = prinsert(key, elem, root);
	}
	void erase(T key) {
		if (key != root->key)
			prerase(key, root);
		Node* right = root->right;
		Node* newleft = findMin(root->right);
		newleft->left = root->left;
		delete root;
		root = right;
	}

	Node* findNext(T key) {
		Node* node = find(key);
		return prfindNext(node);
	}
	Node* findPrev(T key) {
		Node* node = find(key);
		return prfindPrev(node);
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