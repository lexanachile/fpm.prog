#include <iostream>

using namespace std;

class AbstractIterator
{
public:
	virtual ~AbstractIterator() {};
	virtual bool InRange() const = 0;
	virtual void Reset() = 0;
	virtual int &operator*() const = 0;
	virtual void operator++() = 0;
};

class AbstractContainer
{
public:
	virtual ~AbstractContainer() {};
	virtual bool IsEmpty() const = 0;
	virtual void push(const int &n) = 0;
	virtual void pop() = 0;
	virtual int Size() const = 0;
	virtual void Show() const = 0;
};

class AbstractStack : public AbstractContainer
{
public:
	virtual ~AbstractStack() {};
	virtual int Top() const = 0;
};

class AbstractQueue : public AbstractContainer
{
public:
	virtual ~AbstractQueue() {};
	virtual int Front() const = 0;
	virtual int Back() const = 0;
};

class ArrayStackIterator;
class ArrayQueueIterator;
class ListStackIterator;
class ListQueueIterator;

struct node
{
	int info;
	node *next;
};

class ArrayStack : public AbstractStack
{
protected:
	int size;
	int *M;
	int top;
public:
	ArrayStack(int _size = 16)
	{
		size = _size;
		M = new int[size];
		top = -1;
	}
	ArrayStack(const ArrayStack &s)
	{
		size = s.size;
		M = new int[size];
		top = s.top;
		for (int i = 0; i <= top; ++i)
		{
			M[i] = s.M[i];
		}
	}
	ArrayStack(ArrayStack &&s)
	{
		M = s.M;
		size = s.size;
		top = s.top;

		s.M = nullptr;
		s.size = 0;
		s.top = 0;
	}
	~ArrayStack()
	{
		delete[] M;
	}

	void push(const int &n)
	{
		if (IsFull())
		{
			throw "stack is full";
		}
		M[top + 1] = n;
		top = top + 1;
	}
	void pop()
	{
		if (IsEmpty())
		{
			throw "stack is empty";
		}
		top = top - 1;
	}

	bool IsEmpty() const
	{
		return top == -1;
	}
	bool IsFull() const
	{
		return top == size - 1;
	}

	int Top() const
	{
		if (IsEmpty())
		{
			throw "stack is empty";
		}
		return M[top];
	}

	int Size() const
	{
		return top + 1;
	}

	ArrayStack operator=(const ArrayStack &s)
	{
		if (this != &s)
		{
			delete[] M;
			size = s.size;
			top = s.top;

			M = new int[size];
			for (int i = 0; i < size; i++)
            {
                M[i] = s.M[i];
            }
		}
		return *this;
	}
	ArrayStack operator=(ArrayStack &&s)
	{
		if (this != &s)
		{
			delete[] M;
			M = s.M;
			size = s.size;
			top = s.top;

			s.M = nullptr;
			s.size = 0;
			s.top = 0;
		}
		return *this;
	}

	void Show() const
	{
		if (IsEmpty())
		{
			throw "stack is empty";
		}
		int i = top;
		while (i != -1)
		{
			cout << M[i] << " ";
			i--;
		}
		cout << endl;
	}
	friend class ArrayStackIterator;
};

class ArrayQueue : public AbstractQueue
{
protected:
	int size;
	int *p;
	int head;
	int tail;
	int count;
public:
	ArrayQueue(int _size = 16)
	{
		size = _size;
		count = 0;
		p = new int[size];
		head = -1;
		tail = 0;
	}
	ArrayQueue(const ArrayQueue &q)
	{
		size = q.size;
		p = new int[size];
		count = q.count;
		head = q.head;
		tail = q.tail;
		for (int i = 0; i < size; ++i)
		{
			p[i] = q.p[i];
		}
	}
	ArrayQueue(ArrayQueue &&q)
	{
		p = q.p;
		size = q.size;
		head = q.head;
		tail = q.tail;
		count = q.count;

		q.p = nullptr;
		q.size = 0;
		q.head = 0;
		q.tail = 0;
		q.count = 0;
	}
	~ArrayQueue()
	{
		delete[] p;
	}

	void push(const int &n)
	{
		if (IsFull())
		{
			throw "queue is full";
		}
		p[tail] = n;
		tail = (tail + 1) % size;
		if (head == -1)
		{
			head = 0;
		}
		count++;
	}
	void pop()
	{
		if (IsEmpty())
		{
			throw "queue is empty";
		}
		head = (head + 1) % size;
		count--;
	}

	bool IsEmpty() const
	{
		return count == 0;
	}
	bool IsFull() const
	{
		return count == size;
	}

	int Size() const
	{
		return count;
	}

	int Front() const
	{
		if (IsEmpty())
		{
			throw "queue is empty";
		}
		return p[head];
	}
	int Back() const
	{
		if (IsEmpty())
		{
			throw "queue is empty";
		}
		return p[(tail - 1 + size) % size];
	}

	ArrayQueue operator=(const ArrayQueue &q)
	{
		if (this != &q)
		{
			delete[] p;
			size = q.size;
			head = q.head;
			tail = q.tail;
			count = q.count;

			p = new int[size];
			for (int i = 0; i < size; i++)
            {
                p[i] = q.p[i];
            }
		}
		return *this;
	}
	ArrayQueue operator=(ArrayQueue &&q)
	{
		if (this != &q)
		{
			delete[] p;
			p = q.p;
			size = q.size;
			head = q.head;
			tail = q.tail;
			count = q.count;

			q.p = nullptr;
			q.size = 0;
			q.head = 0;
			q.tail = 0;
			q.count = 0;
		}
		return *this;
	}

	void Show() const
	{
		if (IsEmpty())
		{
			cout << "Queue is empty" << endl;
			return;
		}

		int current = head;
		for (int i = 0; i < count; ++i)
		{
			cout << p[current] << " ";
			current = (current + 1) % size;
		}
		cout << endl;
	}
	friend class ArrayQueueIterator;
};

class ListQueue : public AbstractQueue
{
protected:
	node *head;
	node *tail;

public:
	ListQueue() : head(nullptr), tail(nullptr)
	{
	}

	ListQueue(const ListQueue &el)
	{
		head = nullptr;
		tail = nullptr;
		for (auto i = el.head; i != nullptr; i = i->next)
		{
			push(i->info);
		}
	}

	ListQueue(ListQueue &&x)
	{
		head = x.head;
		tail = x.tail;
		x.head = nullptr;
		x.tail = nullptr;
	}

	~ListQueue()
	{
		while (head != nullptr)
		{
			node *temp = head;
			head = head->next;
			delete temp;
		}
		tail = nullptr;
	}

	void push(const int &info)
	{
		node *temp = new node;
		temp->info = info;
		temp->next = nullptr;
		if (tail == nullptr)
			head = temp;
		else
			tail->next = temp;
		tail = temp;
	}

	void pop()
	{
		if (head == nullptr)
		{
			throw "Queue is empty";
		}
		node *temp = head;
		head = head->next;
		delete temp;

		if (head == nullptr)
			tail = nullptr;
	}

	int Size() const
	{
		node *temp = head;
		int i = 0;
		while (temp != nullptr)
		{
			i++;
			temp = temp->next;
		}
		return i;
	}

	int Front() const
	{
		if (head == nullptr)
		{
			throw "Queue is empty";
		}
		return head->info;
	}

	int Back() const
	{
		if (tail == nullptr)
		{
			throw "Queue is empty";
		}
		return tail->info;
	}

	bool IsEmpty() const
	{
		return head == nullptr;
	}

	ListQueue &operator=(const ListQueue &x)
	{
		if (this != &x)
		{
			node *temp;
			while (head != nullptr)
			{
				pop();
			}
			tail = nullptr;

			temp = x.head;
			while (temp != nullptr)
			{
				push(temp->info);
				temp = temp->next;
			}
		}
		return *this;
	}

	ListQueue &operator=(ListQueue &&x)
	{
		if (this != &x)
		{
			head = x.head;
			tail = x.tail;
			x.head = nullptr;
			x.tail = nullptr;
		}
		return *this;
	}

	void Show() const
	{
		if (head == nullptr)
		{
			throw "Queue is empty";
		}

		node *current = head;
		while (current != nullptr)
		{
			cout << current->info << " ";
			current = current->next;
		}
		cout << endl;
	}

	friend class ListQueueIterator;
};

class ListStack : public AbstractStack
{
protected:
	node *head;

public:
	ListStack() : head(nullptr) {}

	ListStack(ListStack &&x)
	{
		head = x.head;
		x.head = nullptr;
	}

	ListStack(const ListStack &x)
	{
		head = nullptr;
		node *temp;
		ListStack y;
		temp = x.head;
		while (temp != nullptr)
		{
			y.push(temp->info);
			temp = temp->next;
		}
		temp = y.head;
		while (temp != nullptr)
		{
			push(temp->info);
			temp = temp->next;
		}
	}

	~ListStack()
	{
		node *temp;
		while (head != nullptr)
		{
			temp = head;
			head = head->next;
			delete temp;
		}
	}

	void push(const int &x)
	{
		node *temp = new node;
		temp->info = x;
		temp->next = head;
		head = temp;
	}

	void pop()
	{
		if (head == nullptr)
		{
			throw "Stack is empty";
		}
		node *temp = head;
		head = head->next;
		delete temp;
	}

	int Size() const
	{
		node *temp = head;
		int i = 0;
		while (temp != nullptr)
		{
			i++;
			temp = temp->next;
		}
		return i;
	}

	int Top() const
	{
		if (head == nullptr)
		{
			throw "Stack is empty";
		}
		return head->info;
	}

	bool IsEmpty() const
	{
		return head == nullptr;
	}

	ListStack &operator=(const ListStack &x)
	{
		if (this != &x)
		{
			node *temp;
			while (head != nullptr)
			{
				pop();
			}

			ListStack y;
			temp = x.head;
			while (temp != nullptr)
			{
				y.push(temp->info);
				temp = temp->next;
			}

			temp = y.head;
			while (temp != nullptr)
			{
				push(temp->info);
				temp = temp->next;
			}
		}
		return *this;
	}

	ListStack &operator=(ListStack &x)
	{
		if (this != &x)
		{
			head = x.head;
			x.head = nullptr;
		}
		return *this;
	}

	void Show() const
	{
		if (head == nullptr)
		{
			throw "Stack is empty";
		}
		node *temp = head;
		while (temp != nullptr)
		{
			cout << temp->info << endl;
			temp = temp->next;
		}
	}

	friend class ListStackIterator;
};

class ArrayStackIterator : public AbstractIterator
{
	ArrayStack &a;
	int pos;
	ArrayStackIterator();

public:
	ArrayStackIterator(ArrayStack &_a) : a(_a), pos(_a.top) {}
	bool InRange() const
	{
		return pos > -1;
	}
	void Reset()
	{
		pos = a.top;
	}
	int &operator*() const
	{
		if (!InRange())
		{
			throw "Iterator out of range";
		}
		return a.M[pos];
	}
	void operator++()
	{
		if (!InRange())
		{
			throw "Iterator out of range";
		}
		--pos;
	}
};

class ArrayQueueIterator : public AbstractIterator
{
	ArrayQueue &a;
	int pos, passed;
	ArrayQueueIterator();

public:
	ArrayQueueIterator(ArrayQueue &_a) : a(_a)
	{
		pos = a.head;
		passed = a.count;
	}
	bool InRange() const
	{
		return passed != 0;
	}
	void Reset()
	{
		pos = a.head;
		passed = a.count;
	}
	int &operator*() const
	{
		if (!InRange())
		{
			throw "Iterator out of range";
		}
		return a.p[pos];
	}
	void operator++()
	{
		pos = (pos + 1) % a.size;
		passed--;
	}
};

class ListStackIterator : public AbstractIterator
{
	ListStack &a;
	node *current;
	ListStackIterator();

public:
	ListStackIterator(ListStack &_a) : a(_a)
	{
		current = a.head;
	}
	bool InRange() const
	{
		return current != nullptr;
	}
	void Reset()
	{
		current = a.head;
	}
	int &operator*() const
	{
		if (!InRange())
		{
			throw "Iterator out of range";
		}
		return current->info;
	}
	void operator++()
	{
		if (!InRange())
		{
			throw "Iterator out of range";
		}
		current = current->next;
	}
};

class ListQueueIterator : public AbstractIterator
{
	ListQueue &a;
	node *current;
	ListQueueIterator();

public:
	ListQueueIterator(ListQueue &_a) : a(_a)
	{
		current = a.head;
	}
	bool InRange() const
	{
		return current != nullptr;
	}
	void Reset()
	{
		current = a.head;
	}
	int &operator*() const
	{
		if (!InRange())
		{
			throw "Iterator out of range";
		}
		return current->info;
	}
	void operator++()
	{
		if (!InRange())
		{
			throw "Iterator out of range";
		}
		current = current->next;
	}
};

int main()
{
	ArrayQueue q1;
	AbstractQueue &q = q1;
	for (int i = 0; i < 5; i++)
	{
		q.push(i);
	}
	ArrayQueueIterator it1(q1);
	AbstractIterator &it = it1;
	while (it.InRange())
	{
		cout << *it << " ";
		++it;
	}
	return 0;
}