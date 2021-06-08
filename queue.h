#pragma once
template<class T>
class queue 
{
private:
	class nodeQueue;
	nodeQueue* head;
	nodeQueue* tail;
	int sizee;
public:
	queue();
	~queue();
	T pop();
	void push(T value);
	int getSize();
	T front();
};
template <class T>
class queue<T>::nodeQueue {
private:
	T value;
	nodeQueue* _next;
public:
	nodeQueue() : _next(nullptr) {};
	nodeQueue(T value, nodeQueue* next)
	{
		queue<T>::nodeQueue::value = value;
		_next = next;
	}
	T getValue() {
		return value;
	}
	void setValue(T value) {
		queue<T>::nodeQueue::value = value;
	}
	nodeQueue* getNext() {
		return _next;
	}
	void setNext(nodeQueue* next) {
		_next = next;
	}
};
template <class T>
queue<T>::queue()
{
	head = nullptr;
	tail = nullptr;
	sizee = 0;
}
template<class T>
queue<T>::~queue()
{
	while (sizee > 0)
		this->pop();
}
template <class T>
T queue<T>::pop() 
{
	if (sizee == 0)
		throw "queue error";
	nodeQueue* temp = head;
	T t_value = head->getValue();
	head = head->getNext();
	delete temp;
	sizee--;
	if (head == nullptr)
		tail = head;
	return t_value;
}
template <class T>
void queue<T>::push(T value) 
{
	if (sizee == 0) {
		head = new nodeQueue(value, nullptr);
		tail = head;
		sizee++;
		return;
	}
	tail->setNext(new nodeQueue(value, nullptr));
	tail = tail->getNext();
	sizee++;
	return;
}
template <class T>
int queue<T>::getSize() 
{
	return sizee;
}
template <class T>
T queue<T>::front()
{
	return this->head->getValue();
}
