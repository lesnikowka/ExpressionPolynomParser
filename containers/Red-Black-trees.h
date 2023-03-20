#include<iostream>
#include<string>

template<typename T, typename D>
class RBTree {
	enum Color {
		black,
		red,
	};
	struct Node {
		Node* left;
		Node* right;
		Node* parent;
		bool color;//0-black; 1-red
		int height;
		int black_height;
		T key;
		D element;
		Node() {
			left = nullptr;
			right = nullptr;

			parent = nullptr;

			height = 0;
			black_height = 0;
			
			color = Color::black;
		}
		Node(T key, D elem, Color c, Node* parent=nullptr) :key(key),parent(parent) ,element(elem), color(c) { left = nullptr;
		right = nullptr;
		
		black_height = 0;
		height = 0; 
		};
		Node(const Node& n) :
			key(key), element(n.element), 
			left(n.left), right(n.right), 
			parent(n.parent),
			height(n.height),black_height(n.black_height) {};
		Node& operator=(const Node& n) {
			key = n.key;
			element = n.element;
			left = n.left;
			right = n.right;
			parent = n.parent;
			height = n.height;
			black_height = n.black_height;
			return *this;
		}
		bool operator<=(const Node& n)const { return key <= n.key; }
		bool operator<(const Node& n)const { return key < n.key; }
		bool operator>=(const Node& n)const { return key >= n.key; }
		bool operator>(const Node& n)const { return key > n.key; }
		friend std::ostream& operator<<(std::ostream& ostream, const Node* n) {
			if (n == nullptr) return ostream << "Empty";
			ostream << n->key << ":" << n->element;// << "\n" << "Kids:" << ((n->left) ? n->left->key : 0) << ":" << ((n->right) ? n->right->key : 0);
			return ostream;
		}
	};
	Node* root;
	void destructor(Node* t) {
		if (t == nullptr) return;
		//std::cout << t<<'\n';
		if (t->left)destructor(t->left);
		if (t->right)destructor(t->right);
		delete t;
	}



	void balanceInsert(Node* t) {
		if (!t) return;
		if (t->parent == nullptr) { t->color = Color::black; return; }
		if (t->parent->color == Color::black) return;
		if (U(t)&&U(t)->color == Color::black) {
			P(t)->color = Color::black;
			U(t)->color = Color::black;
			G(t)->color = Color::red;
			balanceInsert(G(t)); 
			return;
		}
		if ((P(t)&&G(t)&&G(t)->left)&&(P(t) == G(t)->left)) {
			if (t == P(t)->right)
				rotateLeft(P(t));
			rotateRight(G(t));
		}
		else if ((P(t) && G(t) && G(t)->right) &&P(t) == G(t)->right) {
			if (t == P(t)->left)
				rotateRight(P(t));
			rotateLeft(G(t));
		}
	}

	Node* pinsert(T key, D elem, Node* t,Node* pt=nullptr) {
		//insert
		bool flag = false;
		if (t == nullptr) {
			Node* tmp = new Node(key, elem, Color::red, pt);
			if (pt&&key > pt->key)pt->right = tmp;
			else if (pt&&key < pt->key)pt->left = tmp;
			//std::cout << "inserted" + std::to_string(key) + ")"<< "6)" << this->find(6) << '\n';
			//std::cout <<"inserted"+std::to_string(key)+")" << "7)" << this->find(7) << "\n\n";
			return tmp;
		}
		if (key == t->key)return t;


		if (key > t->key) {
			if (!t->right) flag = true;
			pinsert(key, elem, t->right, t);
			if (flag) {
				balanceInsert(t->right);
			}
			flag = false;
		}
		else if (key < t->key) {
			if (!t->left) flag = true;
			pinsert(key, elem, t->left, t);
			if (flag) {
				balanceInsert(t->left);
			}
			flag = false;
		}


		//height and black_height calculation
		int hl=0, hr=0,bhl=0,bhr=0;
		if (t->left) {
			hl = t->left->height;
			if (t->left->color == Color::black)
				bhl = t->left->black_height;
		}
		if (t->right) {
			hr = t->right->height;
			if (t->right->color == Color::black)
				bhr = t->right->black_height;
		}
		t->height = ((hl>hr) ? hl: hr)+1;
		t->black_height = ((bhl > bhr) ? bhl : bhr)+1;
		return t;
	}
	Node* pfind(T key,Node* t) {
		if (t == nullptr)return t;
		if (key > t->key) return pfind(key, t->right);
		if (key < t->key) return pfind(key, t->left);
		return t;
	}

	void rotateLeft(Node* t) {
		Node* new_t = t->right;
		t->right = new_t->left;
		if (new_t->left) new_t->left->parent = t;
		new_t->parent = t->parent;
		if (!new_t->parent)root = new_t;
		if (t->parent) {
			if (t->parent->left == t) t->parent->left = new_t;
			else t->parent->right = new_t;
		}
		new_t->left = t;
		t->parent = new_t;
	}
	void rotateRight(Node* t) {
		Node* new_t = t->left;
		t->left = new_t->right;
		if (new_t->right)
			new_t->right->parent = t;
		new_t->parent = t->parent;
		if (!new_t->parent)root = new_t;

		if (t->parent) {
			if (t->parent->right == t) t->parent->right= new_t;
			else t->parent->left = new_t;
		}
		new_t->right = t;
		t->parent = new_t;


	}
public:
	RBTree() { root = nullptr; }
	RBTree(T key, D elem) {
		height = 0;
		root = new Node(key, elem);
	}
	RBTree(const RBTree& t) { root = t.root; height = 0; }
	~RBTree() {
		destructor(root);
	}

	Node* insert(T key, D elem) {
		Node* tmp = pinsert(key, elem, root);
		if (root == nullptr) root = tmp;

		return tmp;
	}


	Node* P(Node* t) {
		return t->parent;
	}
	Node* G(Node* t) {
		return (t&&t->parent&&t->parent->parent)?t->parent->parent:nullptr;
	}
	Node* U(Node* t) {
		if (!t)return t;
		Node* u = (t->parent&&t->parent->parent)?t->parent->parent:nullptr;
		if (!u) return u;
		if (t->parent == u->left)return u->right;
		else return u->left;
	}
	Node* S(Node* t) {
		if (!t)return t;
		if (!t->parent)return nullptr;
		
		if (t->parent->left == t)return t->parent->right;
		else return t->parent->left;
	}




	Node* find(T key) {
		return pfind(key, root);
	}
	int getHeight(T key) {
		return find(key)->height;
	}
	int getBlackHeight(T key) {
		return find(key)->black_height;
	}
	bool getColor(Node* t) {
		return t->color;
	}
	Node* getParent(Node* t) {
		if (t == nullptr)return nullptr;
		return t->parent;
	}
	friend std::ostream& recOut(std::ostream& ostream, const Node* n) {
		for (int i = 0; i < n->height; i++)
			ostream << " ";
		ostream << n << "\n";
		if (n->left)recOut(ostream, n->left);
		if (n->right)recOut(ostream, n->right);

		return ostream;
	}
	friend std::ostream& operator<<(std::ostream& ostream, const RBTree& t) {
		recOut(ostream, t.root);

		return ostream;
	}
};