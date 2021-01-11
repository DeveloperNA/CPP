#include <iostream>
using namespace std;

class stack
{
private:
	int top;
	int size;
	int* arr;

public:
	stack(int);

	void push(int data);
	void pop();
	int peek(int index);

	int getTop();
	int getSize();
	
	void display();

	bool isEmpty();
	bool isFull();

	
};


stack::stack(int size)
{
	this->top = -1;
	this->size = size;
	this->arr = new int[this->size];
}

int stack::getTop()
{
	return this->top;
}

int stack::getSize()
{
	return this->size;
}

void stack::push(int data)
{
	if (!isFull()) {
		this->arr[++top] = data;
	}
	else {
		cout << "STACK OVERFLOW" << endl;
	}
}

void stack::pop()
{
	if (!isEmpty()) {
		this->arr[top--] = 0;
	}
	else {
		cout << "STACK UNDERFLOW" << endl;
	}
}

int stack::peek(int pos)
{
	if (!isEmpty() && (pos!= 0 && pos <= this->top)) {
		return this->arr[top - pos + 1];
	}
	else
		return -1;
}

bool stack::isEmpty()
{
	if (this->top == -1)
		return true;
	else
		return false;
}

bool stack::isFull()
{
	if (this->top == this->size - 1)
		return true;
	else
		return false;
}

void stack::display()
{
	
	for (int i = this->top; i >= 0; i--) {
		cout << this->arr[i] << " ";
	}
	cout << endl;
}

int main()
{
	stack s(6);

	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);
	s.push(5);

	s.display();
	cout << "Element at position 2 is :" << s.peek(2) << endl;

	s.pop();
	s.pop();
	s.pop();

	s.display();
	cout <<"Element at position 3 is :" << s.peek(3) << endl;


	
	return 0;

}

