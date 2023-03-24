#include<iostream>
#include<string>

template<typename T, typename D>
class RBTree {
	enum Color {
		black=false,
		red=true,
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
		bool is_fict;
		Node() {
			left = nullptr;
			right = nullptr;

			parent = nullptr;

			height = 0;
			black_height = 0;
			is_fict = 0;
			color = Color::black;
		}
		Node(T key, D elem, Color c, Node* parent = nullptr) :key(key), parent(parent), element(elem), color(c) {
			is_fict = 0;
			left = nullptr;
			right = nullptr;

			black_height = 0;
			height = 0;
		};
		Node(const Node& n) :
			is_fict(n.is_fict),
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
		friend std::ostream& operator<<(std::ostream& ostream, const Node* n) {
			if (n == nullptr) return ostream << "Empty";
			ostream << n->key << ":" << n->element << ((!n->color) ? "(black) " : "(red) ") << "Kids:" 
				<< ((n&&n->left) ? n->left->key : 0) << ":" 
				<< ((n&&n->right) ? n->right->key : 0);
			ostream<<"  Parent:" << ((n && n->parent) ? n->parent->key : 0);
			return ostream;
		}

	};
	Node* root;

	void destructor(Node* t) {
		if (t == nullptr) return;
		if (t->left)destructor(t->left);
		if (t->right)destructor(t->right);
		delete t;
	}


	//HORROR
	void balanceInsert(Node* t) {
		if (!t) return;
		if (t->parent == nullptr) { t->color = Color::black; return; }
		if (t->parent->color == Color::black) return;
		if (U(t)&&(U(t)->color == Color::red)) {
			P(t)->color = Color::black;
			U(t)->color = Color::black;
			G(t)->color = Color::red;
			balanceInsert(G(t)); 
			return;
		}
		if ((P(t)&&G(t)&&G(t)->left)&&(P(t) == G(t)->left)) {
			Node* p = P(t),
				*g=G(t);
			if(P(t))
				P(t)->color = !P(t)->color;
			if (G(t))
				G(t)->color = !G(t)->color;
			if (t == P(t)->right) {
				rotateLeft(p);
			}
			rotateRight(g);

		}
		else if ((P(t) && G(t) && G(t)->right) &&P(t) == G(t)->right) {
			Node* p = P(t), *g = G(t);

			if (P(t))P(t)->color = !P(t)->color;
			if (G(t))G(t)->color = !G(t)->color;
			if (t == P(t)->left)
				rotateRight(p);
			rotateLeft(g);
		}
	}
	void balanceDelete(Node* t) {
		if (!t->parent) return;
		Node* s = S(t), * p = P(t);
		if (s && s->color == Color::red) {
			p->color = Color::red;
			p->color = Color::black;
			if (t == p->left)
				rotateLeft(p);
			else 
				rotateRight(p);
		}

		else if (s && s->color == Color::black && p && p->color == Color::black && s->left && s->left->color == Color::black && s->right && s->right->color == Color::black) {
			s->color = Color::red;
			balanceDelete(p);
			return;
		}
		else if (s && s->color == Color::black && p && p->color == red && s->left && s->left->color == Color::black && s->right && s->right->color == Color::black) {
			s->color = Color::red;
			s->color = Color::black;
			return;
		}
		else if (t == p->left) {
			if (s&&s->left && s->left->color == Color::red && s->right && s->right->color == Color::black) {
				s->color = Color::red;
				s->left->color = Color::black;
				rotateRight(s);
			}
			if(s)s->color = p->color;
			p->color = Color::black;
			if(s&&s->right)
			s->right->color = Color::black;
			rotateLeft(p);
		}

		else if (t == p->right) {
			if (s&&s->right && s->right->color == Color::red && s->left && s->left->color == Color::black) {
				s->color = Color::red;
				s->right->color = Color::black;
				rotateLeft(s);
			}

			if(s)s->color = p->color;
			p->color = Color::black;
			if (s && s->left)
			s->left->color = Color::black;
			
			rotateRight(p);
			
		}
	}
	//HORROR

	Node* pinsert(T key, D elem, Node* t,Node* pt=nullptr) {
		//insert
		bool flag = false;
		if (t == nullptr) {
			Node* tmp = new Node(key, elem, Color::red, pt);

			if (pt&&key > pt->key)pt->right = tmp;
			else if (pt&&key < pt->key)pt->left = tmp;
			balanceInsert(tmp);
			return tmp;
		}
		if (key == t->key)return t;


		if (key > t->key) {
			if (!t->right) flag = true;
			pinsert(key, elem, t->right, t);
			flag = false;
		}
		else if (key < t->key) {
			if (!t->left) flag = true;
			pinsert(key, elem, t->left, t);
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
		if (!t)return ;
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
		if (!t)return;
		Node* new_t = t->left;

		t->left = (new_t->right)?new_t->right:new Node();
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


	void perase(T key, Node* t) {
		if (t == nullptr) return ;
		if (t->key > key) perase(key, t->left);
		else if (t->key < key) perase(key, t->right);
		else {
			/*
			bool is_balanced = false;
			Node* prev = findMax(t->left);
			Node* left = t->left, *right = t->right;
			Node* tmp;
			if (t == root) {
				root = prev;
			}
			if (prev) {
				if (prev != left) {
					prev->parent = t->parent; 

					if (prev->left) {
						prev->left->parent = prev->parent;
						prev->parent->right = prev->left;
					}
					else {
						left->right = nullptr;
					}
						prev->left = left;
						left->parent = prev;
					
					prev->right = right;
					right->parent = prev->right;
					
				}
				else {
					prev->parent = t->parent;
					prev->right = t->right;
					t->right->parent = prev;
					t->parent->left = prev;
				}
				
				//
				if (!left->right) {
					left->right = new Node();
					left->right->parent = left;
					left->right->is_fict = 1;
				}
				//
				prev->color = t->color;
				delete t;
				t = prev;
			}
			else {
				if (t->right) {
					t->right->parent = t->parent;

					t->parent->right = t->right;
					right->color = t->color;
					delete t;
					t = right;
				}
				else {
					balanceDelete(t);
					is_balanced = true;
					tmp = t->parent->left;
					t->parent->right = nullptr;
					delete t;
					return ;
				}
			}
			if (prev == root) {
				balanceDelete(left->right);
				is_balanced = true;
				delete left->right;
				left->right = nullptr;
				return;
			}
			
			if (prev&& prev != root && prev->left&& prev->left->color == Color::red) {
				prev->left->color = Color::black;
			}
			else if (prev && prev->left && prev->left->color == Color::black && prev->color == Color::black&&!is_balanced) {
				balanceDelete(t->left);
			}
			
			return ;
			*/

		}
		return ;
	}
	

	Node* P(Node* t) {
		return t->parent;
	}
	Node* G(Node* t) {
		return (t && t->parent && t->parent->parent) ? t->parent->parent : nullptr;
	}
	Node* U(Node* t) {
		if (!t)return t;
		Node* u = (t->parent && t->parent->parent) ? t->parent->parent : nullptr;
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

	friend std::ostream& recOut(std::ostream& ostream, const Node* n) {
		for (int i = 0; i < n->height; i++)
			ostream << " ";
		ostream << n << "\n";
		if (n->left)recOut(ostream, n->left);
		if (n->right)recOut(ostream, n->right);

		return ostream;
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
		if (root == nullptr) { root = tmp; root->color = Color::black; }

		return tmp;
	}

	void erase(T key) {
		perase(key, root);
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


	friend std::ostream& operator<<(std::ostream& ostream, const RBTree& t) {
		recOut(ostream, t.root);

		return ostream;
	}
};