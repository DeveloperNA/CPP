#include <iostream>
#include <stdlib.h>

using namespace std;

class stack
{
	struct node {
		int data;
		node* next;
	};

	struct node* top;

public:
	stack();
	
	void push(int data);
	int pop();
	int peek(int pos);

	bool isEmpty();
	bool isFull();

	void display();
};

stack::stack()
{
	this->top = NULL;
}

void stack::push(int data)
{
	if (!isFull()) {
		struct node* temp = new node;

		temp->data = data;
		temp->next = this->top;
		this->top = temp;
	}
	else {
		cout << "STACK OVERFLOW" << endl;
	}
}

int stack::pop()
{
	if (!isEmpty()) {
		struct node* d = top;

		top = top->next;
		int data = d->data;

		free(d);
		return data;
	}
	else {
		cout << "STACK UNDERFLOW" << endl;
	}
}

int stack::peek(int pos)
{

	if (!isEmpty()) {
		struct node* temp = this->top;

		for (int i = 1; ((temp !=NULL) && (i < pos)); i++) {
			temp = temp->next;
		}

		if (temp == NULL) {
			return -1;
		}
		else {
			return temp->data;
		}
	}
	else {
		cout << "STACK IS EMPTY" << endl;
	}
}

bool stack::isEmpty()
{
	if (this->top == NULL) {
		return true;
	}
	else
		return false;
}

bool stack::isFull()
{
	struct node* t;
	t = new node;
	if (t == NULL) {
		return true;
	}
	else {
		free(t);
		return false;
	}
		
}

void stack::display()
{
	struct node* temp = top;

	while (temp != NULL) {
		cout << temp->data << " " ;
		temp = temp->next;
	}
	cout << endl;
}


int main()
{
	stack s;
	s.push(3);
	s.push(4);
	s.push(5);
	s.push(2);
	
	s.display();

	int a = s.pop();
	int b = s.peek(0);
	cout << a << " " << b; 

	return 0;
}