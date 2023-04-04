#pragma once

#include <stack>
#include <cmath>

template <class T, class Y>
class AVLTree {
public:
	struct Node {
		std::pair<T, Y> key_val;

		Node* left;
		Node* right;

		int height;

		Node() : left(nullptr), right(nullptr), height(1), key_val(T(), Y()) {}
		Node(const T& key_, const Y& value_, Node* left_ = nullptr, Node* right_ = nullptr) {
			key_val.first = key_; key_val.second = value_;
			left = left_; right = right_; height = 1;
		}
	};

	class iterator {
		friend class AVLTree;

		std::stack<std::pair<Node*, std::pair<bool, bool>>> history;

	public:
		iterator() = delete;
		iterator(Node* node) { history.push({ node, {true, true} }); }
		iterator(const iterator& it) : history(it.history) {}

		std::pair<T, Y> operator*() {
			return history.top().first->key_val;
		}

		bool operator==(const iterator& it) const {
			return history.top() == it.history.top();
		}

		bool operator!=(const iterator& it) {
			return !operator==(it);
		}

		iterator& operator++() {
			if (history.top().first->left && history.top().second.first) {
				history.push({ history.top().first->left, {true, true} });
			}
			else if (history.top().first->right && history.top().second.second) {
				history.push({history.top().first->right, { true, true }});
			}
			else {
				if (history.size() == 1) {
					history.pop();
					history.push({ nullptr, {true, true } });
				}
				else {
					Node* current = history.top().first;
					history.pop();
					if (history.top().first->left == current) {
						history.top().second.first = false;
					}
					else {
						history.top().second.second = false;
					}
					return operator++();
				}
			}
			return *this;
		}

		iterator operator++(int) {
			iterator tmp = *this;
			operator++();
			return tmp;
		}
	};

private:
	Node* root = nullptr;

	size_t _size = 0;

	Node* insert_(const T& key, const Y& value, Node* node) {
		if (!node) {
			return new Node(key, value);
		}
		else if (key > node->key_val.first) {
			node->right = insert_(key, value, node->right);
		}
		else {
			node->left = insert_(key, value, node->left);
		}

		change_height(node);

		return balance(node);
	}
	Node* erase_(const T& key, Node* node) {
		if (key < node->key_val.first) {
			node->left = erase_(key, node->left);
		}
		else if (key > node->key_val.first) {
			node->right = erase_(key, node->right);
		}
		else {
			T key = node->key_val.first;
			Node* prev = find_prev(node->key_val.first).history.top().first;


			if (prev) {
				node = detach_prev(prev, node);

				prev->left = node->left;
				prev->right = node->right;

				delete node;

				node = prev;
			}
			else {
				node = node->right;
			}
		}

		change_height(node);

		return balance(node);
	}

	Node* find_(const T& key, Node* node)const {
		if (!node) return nullptr;
		if (node->key_val.first == key) return node;
		if (key < node->key_val.first) {
			return find_(key, node->left);
		}
		else {
			return find_(key, node->right);
		}
	}
	Node* find_max_(Node* node)const {
		if (!node) return nullptr;
		if (!node->right) {
			return node;
		}
		else {
			return find_max_(node->right);
		}
	}
	Node* find_min_(Node* node)const {
		if (!node) return nullptr;
		if (!node->left) {
			return node;
		}
		else {
			return find_max_(node->left);
		}
	}

	Node* right_rotation(Node* node) {
		if (!node || !node->left) return node;

		int alpha_height = node->left->left ? node->left->left->height : 0;
		int beta_height = node->left->right ? node->left->right->height : 0;
		int gamma_height = node->right ? node->right->height : 0;

		node->height = std::max(gamma_height, beta_height) + 1;
		node->left->height = std::max(alpha_height, node->height) + 1;

		Node* left = node->left;
		node->left = left->right;
		left->right = node;
		return left;
	}
	Node* left_rotation(Node* node) {
		if (!node || !node->right) return node;

		int alpha_height = node->left ? node->left->height : 0;
		int beta_height = node->right->left ? node->right->left->height : 0;
		int gamma_height = node->right->right ? node->right->right->height : 0;

		node->height = std::max(alpha_height, beta_height) + 1;
		node->right->height = std::max(node->height, gamma_height) + 1;

		Node* right = node->right;
		node->right = right->left;
		right->left = node;
		return right;
	}
	Node* complex_right_rotation(Node* node) {
		if (!node) return node;
		node->left = left_rotation(node->left);
		return right_rotation(node);
	}
	Node* complex_left_rotation(Node* node) {
		if (!node) return node;
		node->right = right_rotation(node->right);
		return left_rotation(node);
	}

	Node* balance(Node* node) {
		if (!node) return node;
		int right_height = node->right ? node->right->height : 0;
		int left_height = node->left ? node->left->height : 0;


		if (right_height - left_height == 2) {
			int right_right_height = node->right->right ? node->right->right->height : 0;
			int right_left_height = node->right->left ? node->right->left->height : 0;

			if (right_left_height <= right_right_height) {
				return left_rotation(node);
			}
			else {
				return complex_left_rotation(node);
			}
		}
		else if (left_height - right_height == 2) {
			int left_left_height = node->left->left ? node->left->left->height : 0;
			int left_right_height = node->left->right ? node->left->right->height : 0;

			if (left_right_height <= left_left_height) {
				return right_rotation(node);
			}
			else {
				return complex_right_rotation(node);
			}

			return complex_right_rotation(node);
		}

		return node;
	}

	void change_height(Node* node) {
		if (!node) return;
		int right_height = node->right ? node->right->height : 0;
		int left_height = node->left ? node->left->height : 0;

		node->height = std::max(right_height, left_height) + 1;
	}

	Node* detach_prev(Node* prev, Node* node) {
		if (!(prev && node)) return nullptr;

		if (node == prev) {
			return prev->left;
		}
		else if (node->key_val.first < prev->key_val.first) {
			node->right = detach_prev(prev, node->right);
		}
		else {
			node->left = detach_prev(prev, node->left);
		}

		change_height(node);

		return balance(node);
	}

	void delete_tree(Node* node) {
		if (!node) return;
		delete_tree(node->left);
		delete_tree(node->right);
		delete node;
	}

	Node* copy(Node* node_for_copying) {
		if (!node_for_copying) return nullptr;

		Node* current_node = new Node(node_for_copying->key_val.first, node_for_copying->key_val.second);
		current_node->height = node_for_copying->height;

		current_node->right = copy(node_for_copying->right);
		current_node->left = copy(node_for_copying->left);

		return current_node;
	}

public:
	iterator begin() {
		return iterator(root);
	}

	iterator end() {
		return iterator(nullptr);
	}

	AVLTree() = default;
	~AVLTree() {
		delete_tree(root);
	}
	AVLTree(const AVLTree& tree) {
		root = copy(tree.root);
		_size = tree._size;
	}
	AVLTree(AVLTree&& tree) {
		root = tree.root;
		tree.root = nullptr;
		_size = tree._size;
		tree._size = 0;
	}
	AVLTree& operator=(const AVLTree& tree) {
		delete_tree(root);
		copy(tree.root);

		_size = tree._size;

		return *this;
	}
	AVLTree& operator=(AVLTree&& tree) {
		std::swap(root, tree.root);

		std::swap(_size, tree._size);

		return *this;
	}

	size_t size() { return _size; }

	int height() {
		if (!root) return 0;
		return root->height;
	}

	void emplace(const T& key, const Y& value) {
		if (!root) {
			_size++;
			root = new Node(key, value);
		}
		else if (find(key) == end()) {
			_size++;
			root = insert_(key, value, root);
		}
	}
	void insert(const std::pair<T, Y>& pair) {
		emplace(pair.first, pair.second);
	}
	void erase(const T& key) {
		if (find(key) == end()) 
			throw std::exception("element was not founded");
		else {
			_size--;
			root = erase_(key, root);
		}

	}

	iterator find(const T& key) const {
		return iterator(find_(key, root));
	}
	iterator find_max() const {
		return iterator(find_max_(root));
	}
	iterator find_min() const {
		return iterator(find_min_(root));
	}
	iterator find_prev(const T& key) const {
		Node* node = find_(key, root);
		if (node) {
			if (node->left) {
				return iterator(find_max_(node->left));
			}
			else {
				return iterator(nullptr);
			}
		}
		return nullptr;
	}
	iterator find_next(const T& key) const {
		Node* node = find_(key, root);
		if (node) {
			if (node->right) {
				return iterator(find_min_(node->right));
			}
			else {
				return iterator(nullptr);
			}
		}
		return nullptr;
	}
	iterator find_most_similar(const T& key) const {
		Node* node = find_prev(key).history.top().first;
		if (node) {
			return iterator(node);
		}
		node = find_next(key).history.top().first;
		return iterator(node);
	}

	Y& operator[](const T& key) {
		Node* node = find_(key, root);
		if (!node) {
			emplace(key, Y());
			return find_(key, root)->key_val.second;
		}
		return node->key_val.second;
	}

	void out(std::ostream& o, Node* node) const {
		if (!node) return;
		out(o, node->left);
		o << node->key_val.first;
		o << ' ';
		out(o, node->right);
	}
	friend std::ostream& operator<<(std::ostream& o, const AVLTree& t) {
		t.out(o, t.root);
		return o;
	}

	bool is_balanced() {
		int right_height, left_height;

		for (auto it = begin(); it != end(); it++) {
			right_height = it.history.top().first->right ? it.history.top().first->right->height : 0;
			left_height = it.history.top().first->left ? it.history.top().first->left->height : 0;
			if (std::abs(right_height - left_height) > 1) return false;
		}
		
		return true;
	}
};

