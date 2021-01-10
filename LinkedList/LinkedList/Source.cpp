#include <iostream>
#include <stdlib.h>

using namespace std;

class List
{
private:
	struct Node {
		int data;
		Node* next;
	};
	
	
	Node* temp;
	int size=0;

public: 
	Node* head;
	List();
	int getSize();

	void append(int data);
	void insertFirst(int data);
	void insert(int pos, int data);
	void removeFirst();
	void removeLast();
	int RcountSize(struct Node* temp);
	int Rsum(struct Node* temp);
	void printInReverse(struct Node* temp);
	void display();
};


List::List()
{
	this->head = NULL;
	this->temp = NULL;
}

void List::append(int data)
{
	Node* n;
	n = new Node;
	n->data = data;
	n->next = NULL;

	if (head != NULL)
	{
		temp = head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = n;
	}
	else {
		head = n;
	}
}

void List::insertFirst(int data)
{
	Node* n = new Node;
	n->data = data;
	n->next = NULL;

	if (head == NULL) {
		head = n;
	}
	else {
		n->next = head;
		head = n;
	}
}

void List::insert(int pos, int data)
{
	Node* n = new Node;
	n->data = data;
	n->next = NULL;

	if (pos == 1)
		this->insertFirst(data);

	else if (pos < this->getSize() && pos > 0) {
		temp = head;

		for (int i = 1; i < pos - 1; i++) {
			temp = temp->next;
		}
		n->next = temp->next;
		temp->next = n;
	}
	else {
		cout << "Position out of bound";
	}
}

void List::removeFirst()
{
	if (head == NULL)
		cout << "No elements present in the list";
	else{
		temp = head;
		head = head->next;
		free(temp);
	}
}

void List::removeLast()
{
	struct Node* d;
	if (head == NULL)
		cout << "No elements present in the list";
	else {

		if (this->getSize() == 1) {
			head = NULL;
		}
		else
		{
			temp = head;
			while (temp->next->next != NULL) {
				temp = temp->next;
			}
			d = temp->next;
			temp->next = NULL;
			free(d);
		}
		
	}
}

int List::RcountSize(struct Node* temp)
{
	/// returning a count of elements in  linked list using recursion
	///	Time complexity: O(n) 
	/// Space complexity: O(n) Since  recursion uses stack to store function calls
	if (temp == NULL)
		return 0;
	else
		return 1 + RcountSize(temp->next);
}

int List::Rsum(struct Node* temp)
{
	// returning a sum of elements in linked list using recursion
	// Time complexity : O(n)
	// Space complexity : O(n) Since recursion uses stack to store function calls

	if (temp)
		return temp->data + Rsum(temp->next);
	else
		return 0;
}

void List::printInReverse(struct Node* temp)
{
	/// reversing a linked list using recursion
	///	Time complexity: O(n) 
	/// Space complexity: O(n) Since recursion uses stack to store function calls

	if (temp != NULL) {
		printInReverse(temp->next);
		cout << temp->data << endl;
	}
	else {
		cout << "Reversed List:" << endl;
	}
}

int List::getSize()
{
	this->size = 0;
	for (temp = head; temp != NULL; temp = temp->next) {
		this->size++;
	}
	return this->size;
}

void List::display()
{
	cout << "List:" << endl;
	for (temp = head; temp != NULL; temp = temp->next) {
		cout << temp->data << "\n";
	}
}

int main() 
{
	List mylist;
	mylist.append(4);
	mylist.append(6);
	mylist.append(3);
	mylist.insert(1, 10);

	mylist.insertFirst(1);

	mylist.removeFirst();
	mylist.removeLast();


	mylist.display();
	mylist.printInReverse(mylist.head);
	cout <<"Total elements in list:"<< mylist.RcountSize(mylist.head) << endl;

	cout << "Sum of elements in list: " << mylist.Rsum(mylist.head) << endl;
	return 0;
}