#ifndef FQ_BASE
#define FQ_BASE
#endif 

typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long long u64;

enum VehicleType {TRUCK,BUS};

struct Vehicle {
	u64 id;
	VehicleType type;
	union {
		u32 weight;
		u32 number;
	};
};

template <typename T>
struct Node {
	Node<T>* pre;
	T val;
	Node<T>* next;
	Node(T Val) {
		val = Val;
	}
};

template <typename T>
struct LinkedQueue {
	Node<T>* front;
	Node<T>* rear;

	int size;

	bool empty();
	void clear();
	void push(T val);
	void pop();
	~LinkedQueue()
	{
		clear();
	}
};

struct Time {
	u8 hour;
	u8 min;
	Time(u8 hr, u8 m) {
		hour = hr;
		min = m;
	}
	Time operator+(int cnt) {
		min += cnt;
		int tAdd = min / 60;
		min = min % 60;
		hour = (hour + tAdd) % 24;
		return *this;
	};
	Time operator++(int) {
		return *this + 1;
	}
};


const int CAPACITY = 20;
const int LIMIT_COMMON = 20, LIMIT_BUSY = 10;
const int TIME_CROSSRIVER = 5;
const Time START = Time(6, 0), END = Time(18, 0);

template<typename T>
void swap(T*,T*);
template<typename T>
void swap(T&,T&);
void qsort(u64*, int, int);


template<typename T>
bool LinkedQueue<T>::empty() {
	if (this->front == nullptr) return true;
	return false;
}
template<typename T>
void LinkedQueue<T>::clear() {
	while(!empty()){
		pop();
	}
}
template<typename T>
void LinkedQueue<T>::pop() {
	if (empty()) return;
	if (this->rear == this->front) {
		delete this->rear;
		this->rear = this->front = nullptr;
		size = 0;
	}
	else {
		delete this->rear;
		this->front= this->front->pre;
		size--;
	}
}

template<typename T>
void LinkedQueue<T>::push(T Val) {
	Node<T>* node = new Node<T>(Val);
	if (empty()) this->front = this->rear = node;
	else {
		this->rear->pre = node;
		node->next = this->rear;
		this->rear = this->rear->pre;
	}
	size++;
}

template<typename T>
void swap(T* src,T* dest) {
	T temp = *src;
	*src = *dest;
	*dest = temp;
}

template<typename T>
void swap(T& src, T& dest) {
	T temp = src;
	src = dest;
	dest = temp;
}

void qsort(u64* tar, int start, int end) {
	if (start >= end) return;
	if (start - end == 1) {
		if (tar[start] > tar[end]) swap(tar + start, tar + end);
		return;
	}
	int p = tar[(start + end) / 2];
	int l = start, r = end;
	while (l < r) {
		while (tar[l] < p) l++;
		while (tar[r] > p) r--;
		if (l >= r) break;
		swap(tar + l, tar + r);
		if (tar[l] == tar[r]) {
			l++;
		}
	}
	if (l <= r) swap(l, r);
	qsort(tar, start, r - 1);
	qsort(tar, r + 1, end);
}



