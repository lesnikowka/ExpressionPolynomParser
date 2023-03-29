#pragma once
#include<initializer_list>
#include <iostream>


template<class T>
class List {
	struct Node{
		T elem;
		Node* next;
		Node(T elem=0, Node* ptr = nullptr) : elem(elem), next(ptr) {}
	};
	Node* first;

public:
	class Iterator {
		friend List;
		Node* ptr_elem;
	public:

		Iterator(Node* it=nullptr): ptr_elem(it) {};

		Iterator operator++(int) {//it++
			Iterator tmp(*this);
			ptr_elem = ptr_elem->next;
			return tmp;
		}; 
		Iterator& operator++() { //++it
			ptr_elem = ptr_elem->next; return *this;
		};

		T& operator*() { return ptr_elem->elem; }

		Iterator& operator+=(size_t c) { 
			for (size_t i = 0; i < c; i++) {
				if (ptr_elem == nullptr) 
					throw("Iterator out of range");
				ptr_elem = ptr_elem->next;
			}
			return *this; 
		};
		Iterator& operator=(const Iterator& it) { 
			if (this == &it)return* this;
			ptr_elem = it.ptr_elem;
			return *this; 
		};

		Iterator operator+(int c) { Iterator tmp(*this); return tmp += c; };

		bool operator!=(Iterator it) { return ptr_elem != it.ptr_elem; }
		bool operator==(Iterator it) { return !(ptr_elem != it.ptr_elem); }


	};

	Iterator begin() { 
		return Iterator(first); 
	}
	Iterator end(){ 
		return Iterator();
	}


	List() :first(nullptr) {};

	explicit List(const size_t count) {
		if (count == 0) {
			first = nullptr;
		}
		else{
			Node* tmp = new Node(0);
			first = tmp;
			for (size_t i = 1; i < count; i++) {
				tmp->next = new Node(0);
				tmp = tmp->next;
			}
		}
	}

	List(List& l) :List(1) {
		Node* tmp1=first;
		for (auto it = l.begin(); it != l.end(); it++) {
			tmp1->elem = *it;
			if(it+1!=l.end())
			tmp1->next = new Node();
			tmp1 = tmp1->next;
		}
	};

	List(List&& list)noexcept  :first()  {
		std::swap(first,list.first);
	};

	List(const std::initializer_list<T>& el) :List(el.size()) {
		Node* tmp = first;
		for (auto it:el) {
			tmp->elem = it;
			tmp=tmp->next;
		}
	}

	~List() {
		Node *tmp;
		if(first)
		while (first->next) {
			tmp = first->next;
			delete first;
			first = tmp;
		}
	};

	List& operator=(const List& l) {
		if (this == &l) return *this;
		Node* tmp1=first;
		Node* tmp2=l.first;
		Node* tail=nullptr;
		if (first == nullptr) {
			first = new Node();
			tmp1 = first;
		}

		while (tmp2 != nullptr) {
			tail = tmp1;
			if (tmp1->next == nullptr && tmp2->next!=nullptr)tmp1->next = new Node();
			tmp1->elem = tmp2->elem;
			tmp2 = tmp2->next;
			tmp1 = tmp1->next;
		}

		if (tail != nullptr) {
			tmp1 = tail->next;
			tail->next = nullptr;
			}
		while (tmp1 != nullptr) {
			tmp2 = tmp1->next;
			delete tmp1;
			tmp1 = tmp2;
		}
		return *this;
		
	};
	List& operator=(List&& l) {
		std::swap(first,l.first);
		return *this;
	}


	void assign(Iterator first, Iterator last) {
		clear();
		this->first = new Node();
		Node* tmp = this->first;
		for (first; first != last; first++) {
			tmp->next = new Node(*first);
			tmp = tmp->next;
		}
		pop_front();
	}
	bool empty() const { return !first; };
	size_t size() {
		size_t size=0;
		for (List::Iterator it = begin(); it != end(); it++, ++size);
		return size;
	};

	void clear() {
		Node* tmp1 = first;
		Node*tmp2 = first;
		while (tmp1 != nullptr) {
			tmp2 = tmp2->next;
			delete tmp1;
			tmp1 = tmp2;
		}
		first = nullptr;
	};

	void merge(List& l);
	void merge(List&& l);
	void sort();

	Iterator insert_after(Iterator prev, T value) {
		Node* tmp = new Node(value, (prev + 1).ptr_elem);
		prev.ptr_elem->next = tmp;
		return Iterator(tmp);
	};
	Iterator erase_after(Iterator prev) {
		Node* tmp = prev.ptr_elem;
		Node* tmp2 = prev.ptr_elem->next->next;
		delete tmp->next;
		tmp->next = tmp2;

		return Iterator(prev+1);
	};

	void push_front(T value) {
		Node* tmp = new Node(value);
		tmp->next = first;
		first = tmp;
	};
	void pop_front() {
		Node* tmp = first->next;
		delete first;
		first = tmp;
	}

	void invert(Iterator a=nullptr, Iterator b=nullptr) {
		Node* tmp1, *tmp2,*tmp3,*tmp4,* end;
		if (a == b&&a!=nullptr) return;
		if (b.ptr_elem == nullptr) {
			end = nullptr;
			tmp1 = nullptr;
		}
		else{
		end = b.ptr_elem->next;
		tmp1 = b.ptr_elem->next;
		}
		if (a == nullptr) {
			tmp2 = first;
		}
		else {
			tmp2 = a.ptr_elem->next;
		}
		tmp3 = tmp2->next;
		while(tmp2!=end) {
			tmp4 = tmp2;
			tmp2->next = tmp1;
			tmp2 = tmp3;
			tmp1 = tmp4;
			if(tmp3!=nullptr)
			tmp3 = tmp3->next;
		}
		if(a!=nullptr)
		a.ptr_elem->next = b.ptr_elem;
		else {
			first = tmp1;
		}
	}

	friend std::ostream& operator<<(std::ostream& ostr, List& l) {
		for (auto it = l.begin(); it != l.end();++it) {
			ostr << (*it)<<" ";
		}
		return ostr;
	};
};