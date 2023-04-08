#pragma once

#include<iostream>
#include<string>
#include<stack>

template<typename T, typename D>
class RBTree {
	friend class iterator;
	enum Color {

		black = false,
		red = true,


	};
	struct Node {
		Node* left;
		Node* right;
		Node* parent;
		bool color;//0-black; 1-red

		T first;
		D second;
		bool is_fict;
		Node() {
			left = nullptr;
			right = nullptr;
			is_fict = true;
			parent = nullptr;
			color = Color::black;
		}
		Node(T first, D elem, Color c = Color::black, bool fict = false, Node* parent = nullptr) :first(first), parent(parent), second(elem), color(c) {
			is_fict = fict;
			left = nullptr;
			right = nullptr;

		};
		Node(const Node& n) :
			color(n.color),
			is_fict(n.is_fict),
			first(n.first),
			second(n.second),
			left(n.left), right(n.right),
			parent(n.parent) {};
		Node& operator=(const Node& n) {
			root = n.root;

			first = n.first;
			second = n.second;

			left = n.left;
			right = n.right;

			parent = n.parent;
			is_fict = n.is_fict;
			return *this;
		}
		friend std::ostream& operator<<(std::ostream& ostream, const Node* n) {
			if (n == nullptr) return ostream << "Empty";
			if (n->is_fict == false) {
				ostream << n->first << ":" << n->second
					<< ((!n->color) ? "(black) " : "(red) ") << "Kids:";
				if (n && n->left && n->left->is_fict == false) {
					ostream << n->left->first << ":" << n->left->second << " | ";
				}
				else if (n->left->is_fict) {
					ostream << "Fict:";
				}
				if (n && n->right && n->right->is_fict == false) {
					ostream << n->right->first << ":" << n->right->second;
				}
				else if (n->right->is_fict) {
					ostream << "Fict";
				}
				if (n->parent)
					ostream << " Parent:" << n->parent->first;
			}
			return ostream;
		}

	};

	Node* root;
	size_t _size;

	Node* copy(Node* n) {
		if (!n)return nullptr;

		Node* cur_node = new Node(n->first, n->second, (n->color) ? Color::black : Color::red, n->is_fict, n->parent);
		cur_node->left = copy(n->left);
		cur_node->right = copy(n->right);
		return cur_node;
	}
	void Tdestructor(Node* t) {
		if (!t) return;
		if (t->left)Tdestructor(t->left);
		if (t->right)Tdestructor(t->right);
		delete t;
	}

	void createFict(Node* t) {
		t->left = new Node();
		t->left->parent = t;

		t->right = new Node();
		t->right->parent = t;
	}

	void balanceInsert(Node* t) {
		if (!t) return;
		if (t->parent == nullptr) { t->color = Color::black; return; }
		if (t->parent->color == Color::black) return;
		if (U(t) && (U(t)->color == Color::red)) {
			P(t)->color = Color::black;
			U(t)->color = Color::black;
			G(t)->color = Color::red;
			balanceInsert(G(t));
			return;
		}
		if ((P(t) && G(t) && G(t)->left) && (P(t) == G(t)->left)) {
			Node* p = P(t),
				* g = G(t);
			if (P(t))
				P(t)->color = !P(t)->color;
			if (G(t))
				G(t)->color = !G(t)->color;
			if (t == P(t)->right) {
				rotateLeft(p);
			}
			rotateRight(g);

		}
		else if ((P(t) && G(t) && G(t)->right) && P(t) == G(t)->right) {
			Node* p = P(t), * g = G(t);

			if (P(t))P(t)->color = !P(t)->color;
			if (G(t))G(t)->color = !G(t)->color;
			if (t == P(t)->left)
				rotateRight(p);
			rotateLeft(g);
		}
	}
	void balanceDelete(Node* t) {

		//1
		if (!t->parent) return;
		Node* s = S(t), * p = P(t);

		//2
		if (s->color == Color::red) {
				p->color = Color::red;
				s->color = Color::black;
			if (t == p->left)
				rotateLeft(p);
			else
				rotateRight(p);
				s = S(t); p = P(t);

		}

		if (s->color == Color::black && p && p->color == Color::black && s->left && s->left->color == Color::black && s->right && s->right->color == Color::black) {
			s->color = Color::red;
			balanceDelete(p);
			return;
		}
		else if (s->color == Color::black && p && p->color == red && s->left && s->left->color == Color::black && s->right && s->right->color == Color::black) {
			s->color = Color::red;
			p->color = Color::black;
			return;
		}
		else if (t == p->left) {
			if ( s->left && s->left->color == Color::red && s->right && s->right->color == Color::black) {
				s->color = Color::red;
				s->left->color = Color::black;
				rotateRight(s);
				s = S(t); p = P(t);
			}
			s->color = p->color;
			p->color = Color::black;
			if (s && s->right)
				s->right->color = Color::black;
			rotateLeft(p);
		}

		else if (t == p->right) {
			if (s->right && s->right->color == Color::red && s->left && s->left->color == Color::black) {
				s->color = Color::red;
				s->right->color = Color::black;
				rotateLeft(s);
				s = S(t); p = P(t);

			}

			s->color = p->color;
			p->color = Color::black;
			if (s->left)
				s->left->color = Color::black;

			rotateRight(p);

		}
	}
	

	Node* pinsert(T first, D elem, Node* t, Node* pt = nullptr) {
		//insert
		bool flag = false;
		if (t->is_fict == true) {

			//Node* tmp = new Node(first, elem, Color::red, pt);
			t->first = first;
			t->second = elem;
			t->parent = pt;
			t->is_fict = false;
			if (t == root)t->color = Color::black;
			else t->color = Color::red;
			_size++;
			createFict(t);


			if (pt && first > pt->first)pt->right = t;
			else if (pt && first < pt->first)pt->left = t;
			balanceInsert(t);
			return t;
		}
		if (first == t->first)return t;


		if (first > t->first) {
			if (!t->right) flag = true;
			pinsert(first, elem, t->right, t);
			flag = false;
		}
		else if (first < t->first) {
			if (!t->left) flag = true;
			pinsert(first, elem, t->left, t);
			flag = false;
		}

		return t;
	}
	Node* pfind(T first, Node* t) {
		if (t->is_fict)return nullptr;
		if (first > t->first) return pfind(first, t->right);
		if (first < t->first) return pfind(first, t->left);
		return t;
	}


	void rotateLeft(Node* t) {
		if (!t)return;
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

		t->left = (new_t->right) ? new_t->right : new Node();
		if (new_t->right)
			new_t->right->parent = t;
		new_t->parent = t->parent;
		if (!new_t->parent)root = new_t;

		if (t->parent) {
			if (t->parent->right == t) t->parent->right = new_t;
			else t->parent->left = new_t;
		}
		new_t->right = t;
		t->parent = new_t;


	}

	Node* swap(Node* t, Node* prev) {
		//if (t->first == 1)
		//	std::cout << t<<'\n' << prev;
		bool flagForColors = true;
		Node* oldpos, * x = prev->left;
		if (t->parent)
			(t->parent->left == t) ? t->parent->left = prev : t->parent->right = prev;


		if (t == prev) {
			t->right->parent = t->parent;
			if (t->parent)
				(t->parent->left == t) ? t->parent->left = t->right : t->parent->right = t->right;
			delete t->left;
			oldpos = t->right;

		}
		else if (t->left != prev) {
			prev->left->parent = prev->parent;
			prev->parent->right = prev->left;
			prev->parent = t->parent;


			oldpos = prev->left;


			prev->left = t->left;
			t->left->parent = prev;
			delete prev->right;
			prev->right = t->right;
			t->right->parent = prev;



		}
		else if(t->left==prev) {
			oldpos = prev->left;
			prev->parent = t->parent;
			delete prev->right;
			prev->right = t->right;
			t->right->parent = prev;


		}
		if (t == root && t == prev) {
			root = prev->right;
		}
		else if (t == root)root = prev;

		if (flagForColors) {
			//x->color = prev->color;
			prev->color = t->color;
		}
		return oldpos;
	}

	bool perase(T first, Node* t) {
		bool flag=false;
		if (t == nullptr||t->is_fict) return false;
		if (t->first > first) {
			flag = perase(first, t->left);
		}
		else if (t->first < first) {
			flag = perase(first, t->right);
		}
		else {
			flag = true;
			Node* prev=findMax(t->left);

			Node* left = t->left, * right = t->right;
			Node* x = prev->left;
			bool c=prev->color;


			Node* oldpos = swap(t, prev);


			if (oldpos->color == Color::red) { oldpos->color = Color::black; }
			else if (oldpos->color == Color::black && c == Color::black) { balanceDelete(oldpos); }

			_size--;
			delete t;
			return flag;

		}
		if (!flag)
			throw std::exception("key is not founded");
		return flag;
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
		if (t->is_fict == true) return t->parent;
		else return findMax(t->right);
	}
	Node* findMin(Node* t)
	{
		if (t->is_fict == true) return t->parent;
		else return findMax(t->left);
	}

	friend std::ostream& recOut(std::ostream& ostream, const Node* n) {
		if (n->is_fict == false) {
			ostream << n << "\n";
			if (n->left)recOut(ostream, n->left);
			if (n->right)recOut(ostream, n->right);
		}
		return ostream;
	}
	Node* Nfind(T first) {
		return pfind(first,root);
	}
public:
	class iterator {
		std::stack<Node*> history;
		bool finish;
		iterator recPP(Node* last_node,bool up=false) {
			if (history.empty()) return iterator();
			Node* top = history.top();
			Node* parent = top->parent;

			if (up) {
				if (top->right!=last_node&&top->right->is_fict == false) { history.push(top->right); return *this; }
				history.pop();
				recPP(top,true);
			}
			else {
				if (top->left->is_fict == false) {
					history.push(top->left);
					return *this;
				}
				else if (top->right->is_fict == false) {
					history.push(top->right);
					return *this;
				}
				else {
					history.pop();
					recPP(top,true);
				}
			}
			return *this;
		}	
	public:
		iterator() { finish = true; }
		iterator(Node* node) {
			if (node && node->is_fict==false)
				history.push(node);
			finish = false;
		}
		Node operator*() {
			if (history.empty())throw "iterator points to the end";
			Node* tmp = history.top();

			return *(history.top());
		}
		iterator& operator=(const iterator& it) {
			history = it.history;
			return *this;
		}
		iterator operator++() {

			/*
			if (finish) return iterator();
			Node* top = history.top(), * parent = top->parent;
			
			if (top->left->is_fict == false) {
				history.push(top->left);
			}
			else if (top->right->is_fict == false) {
				history.push(top->right);
			}
			else if (parent && parent->left == top) {
				do {
					top = parent;
					parent = top->parent;
					history.pop();

				} while (parent && top->right->is_fict);
				if (top->right->is_fict) { finish = true; history.pop(); }
				else history.push(top->right);
			}
			else if (parent&&parent->right == top) {
				do {
					top = parent;
					parent = top->parent;
					history.pop();
				} while (parent && (parent->right == top || parent->right->is_fict));
				if (!parent) { finish = true; history.pop(); }
				else if (parent->right->is_fict == false) { history.pop(); history.push(parent->right); }
			}
			
			else {
				history.pop();
				finish = true;
			}

			return *this;
			*/
			return recPP(history.top());
		}
		bool operator!=(const iterator& it) const {
			return !operator==(it);
		}
		bool operator==(const iterator& it) const {
			if (history.empty() && it.history.empty())return true;
			else if (history.empty() == false || it.history.empty() == false) return false;
			return history.top() == it.history.top();
		}
		iterator operator++(int) {
			iterator tmp;
			operator++();
			return tmp;
		}
	};
	iterator begin()const {
		return iterator(root);
	}
	iterator end()const {
		return iterator();
	}


	RBTree() { root = new Node();_size = 0; }
	RBTree(T first, D elem) {
		_size = 1;
		root = new Node(first, elem);
	}

	RBTree(const RBTree& t) { root = copy(t.root); _size = t._size; }
	~RBTree() {
		Tdestructor(root);

	}

	void insert(std::pair<T, D> p) {
		return emplace(p.first, p.second);
	}
	void emplace(T first, D elem) {
		Node* tmp = pinsert(first, elem, root);
		if (tmp == root) {
			root->color = Color::black;
		}
	}

	void erase(T first) {
		size_t tmp = _size;
		perase(first, root);
		if (tmp == _size)
			throw std::exception("Can't delete");
	}
	
	iterator find(T first) {
		return iterator(pfind(first, root));
	}
	size_t getBlackHeight(iterator it) {
		return getBlackHeight(&(*it));
	}
	size_t getBlackHeight(Node* t) {
		size_t bhr = 0, bhl = 0;
		if (!t) return 0;
		if (t->is_fict) return 0;
		if (t->left)bhl = getBlackHeight(t->left);
		if (t->right)bhr = getBlackHeight(t->right);
		size_t h = ((bhr > bhl) ? bhr : bhl);
		if (t->color == Color::black) h++;
		return h;

	}
	D& operator[](const T& first) {
		Node* t = Nfind(first);
		if (t == nullptr)
			emplace(first, D());
		return Nfind(first)->second;
	}
	D& operator[](T&& first) {
		Node* t = Nfind(first);
		if (t == nullptr)emplace(first, D());
		else return t->second;
		return Nfind(first)->second;
	}



	//FOR TESTS |
	//FOR TESTS |
	//FOR TESTS V

	bool property_ColorsAreCorrect(iterator it) {
		if (it == end())return 1;

		return property_ColorsAreCorrect(&(*it));
	}
	bool property_ColorsAreCorrect(Node* t) {
		bool flag = true;
		if (t->is_fict) return true;
		if (t == root && t->color == Color::red) return false;

		if (t->color == Color::red && (t->left->color == Color::red || t->right->color == Color::red)) return false;

		if (t->left && t->right)flag = (property_ColorsAreCorrect(t->left) && property_ColorsAreCorrect(t->right));

		return flag;
	}
	bool property_BlackHeightsSimilar(iterator it) {
		if (it == end())return 1;
		return property_BlackHeightsSimilar(&(*it));
	}
	bool property_BlackHeightsSimilar(Node* t) {
		bool flag = true;

		if (getBlackHeight(t->left) != getBlackHeight(t->right)) 
			return false;

		if (t->left->is_fict==false && t->right->is_fict==false)flag = (property_BlackHeightsSimilar(t->left) && property_BlackHeightsSimilar(t->right));

		return flag;
	}
	bool property_ALL(iterator it) {
		if (it == end())return 1;
		return property_ALL(&(*it));
	}
	bool property_ALL(Node* t) {
		return property_BlackHeightsSimilar(t) && property_ColorsAreCorrect(t);
	}
	//FOR TESTS ^
	//FOR TESTS |
	//FOR TESTS |



	int getHeight(T first) {
		return find(first)->height;
	}
	int getBlackHeight(T first) {
		return find(first)->black_height;
	}
	bool getColor(Node* t) {
		return t->color;
	}
	Node* getParent(Node* t) {
		if (t == nullptr)return nullptr;
		return t->parent;
	}
	size_t size() { return _size; }

	friend std::ostream& operator<<(std::ostream& ostream, const RBTree& t) {
		recOut(ostream, t.root);
		return ostream;
	}
};