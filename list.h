#pragma once
#include <string>
using namespace std;
template<class T>
class list {
private:
	class nodeList;
	nodeList* Head;
	int Size;
public:
	list();
	~list();
	T pop();
	T pop(int);
	void push(T value);
	int getSize();
	void sort();
	string getString();
};
template <class T>
class list<T>::nodeList {
private:
	T Value;
	nodeList* Next;
public:
	nodeList()
	{
		Next = nullptr;
	}
	nodeList(T value, nodeList* next)
	{
		Value = value;
		Next = next;
	}
	T getValue() 
	{
		return Value;
	}
	void setValue(T value) 
	{
		Value = value;
	}
	nodeList* getNext() 
	{
		return Next;
	}
	void setNext(nodeList* next) 
	{
		Next = next;
	}
};
template <class T>
list<T>::list()
{
	Head = nullptr;
	Size = 0;
}
template<class T>
list<T>::~list()
{
	while (Size > 0)
		this->pop();
}
template <class T>
T list<T>::pop() 
{
	if (Size == 0)
		return 0;
	if (Size == 1) {
		T nxt_t_value = Head->getValue();
		delete Head;
		Head = nullptr;
		this->Size = 0;
		return nxt_t_value;
	}
	nodeList* temp = Head;
	while (temp->getNext()->getNext() != nullptr) temp = temp->getNext();
	T nxt_t_value = temp->getNext()->getValue();
	delete temp->getNext();
	Size--;
	temp->setNext(nullptr);
	return nxt_t_value;
}
template <class T>
T list<T>::pop(int index) 
{
	if (Size == 1 || Size == 0 || index == Size - 1) {
		return this->pop();
	}
	if (index == 0) {
		nodeList* temp = Head->getNext();
		T tempvalue = Head->getValue();
		Head = temp;
		Size--;
		return tempvalue;
	}
	nodeList* temp = Head;
	for (int i = 0; i < index - 1; i++)
		temp = temp->getNext();
	T nxt_t_value = temp->getNext()->getValue();
	nodeList* tempNext = temp->getNext()->getNext();
	Size--;
	temp->setNext(tempNext);
	return nxt_t_value;
}
template <class T>
void list<T>::push(T value) 
{
	if (Size == 0) {
		Head = new nodeList(value, nullptr);
		Size++;
		return;
	}
	nodeList* temp = Head;
	while (temp->getNext() != nullptr) temp = temp->getNext();
	temp->setNext(new nodeList(value, nullptr));
	Size++;
	return;
}
template <class T>
int list<T>::getSize() 
{
	return Size;
}
template <class T>
void list<T>::sort()
{
	if (Size == 1 || Size == 0)
		return;
	nodeList* temp = Head;
	bool f = false;
	for (int i = 0; i < Size - 1; i++) {
		temp = Head;
		f = false;
		for (int j = 0; j < Size - 1 - i; j++) {
			if (temp->getValue()->get_freq() > temp->getNext()->getValue()->get_freq()) {
				T t_value = temp->getValue();
				temp->setValue(temp->getNext()->getValue());
				temp->getNext()->setValue(t_value);
				f = true;
			}
			temp = temp->getNext();
		}
		if (!f)
			return;
	}
}
template <class T>
string list<T>::getString()
{
	nodeList* temp = Head;
	string _out = "";
	while (temp != NULL) {
		_out += temp->getValue() + '0';
		temp = temp->getNext();
	}
	return _out;
}