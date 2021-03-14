#include <iostream>
#include <vector>

using namespace std;

class EmptyHeapException : exception{};

class MaxHeap
{
    private:
        vector<int> arr;
    
    public:
        int top;
        MaxHeap();
        MaxHeap(int data);

        void push(int data);
        void pop() throw(EmptyHeapException);

        bool empty();
        int getMaxChildIndex(int, int);
        void printHeap();
};

MaxHeap::MaxHeap()
{
    this->top = -999;
    this->arr.push_back(-999);
}   

MaxHeap::MaxHeap(int data)
{
    this->arr.push_back(0);
    this->arr.push_back(data);
    this->top = data;
}

bool MaxHeap::empty()
{
    if(this->arr.size() == 1)
        return true;
    else
        return false;
}

void MaxHeap::push(int data)
{
    this->arr.push_back(data);
    int i, parent;
    i=arr.size()-1;
    parent = i/2;
    
    while(i>1 && arr[parent] < arr[i]){
        
        swap(arr[parent], arr[i]);
        i = parent;
        parent = i/2;
    }
 
    this->top = arr[1];
}

void MaxHeap::pop() throw(EmptyHeapException)
{   
    int i, parentIndex, leftIndex, rightIndex, maxChildIndex;

    try{
        if(this->empty()){
            throw EmptyHeapException();
        }

        this->arr[1] = this->arr[this->arr.size()-1];
        this->arr.pop_back();

        parentIndex = 1;
        leftIndex = (2*parentIndex > this->arr.size())? 0 : 2*parentIndex;
        rightIndex = (2*parentIndex +1>this->arr.size())? 0 : 2*parentIndex+1;

        maxChildIndex = getMaxChildIndex(leftIndex, rightIndex);

        while(this->arr[parentIndex] < this->arr[maxChildIndex] && (leftIndex!=0 || rightIndex!=0)){
            
            swap(this->arr[parentIndex], this->arr[maxChildIndex]);
            
            parentIndex = maxChildIndex;
            leftIndex = (2*parentIndex > this->arr.size())? 0 : 2*parentIndex;
            rightIndex = (2*parentIndex+1 > this->arr.size())? 0 : 2*parentIndex+1;

            maxChildIndex = getMaxChildIndex(leftIndex, rightIndex);
        }
        this->top = this->arr[1];
    }   
    catch(EmptyHeapException e){
        cout << "\n\t\t/////Deletion cannot be perfomed on empty heap/////" << endl;
    }
}

int MaxHeap::getMaxChildIndex(int left, int right)
{
    return (this->arr[left] > this->arr[right])? left: right;
}

void swap(int *p, int *q)
{
    int temp = *p;
    *p = *q;
    *q = temp;
}

void MaxHeap::printHeap()
{
    cout << endl;
    for(int i=1; i<this->arr.size(); i++){
        cout << this->arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    MaxHeap myHeap;
    myHeap.push(10);
    myHeap.push(40);
    myHeap.push(20);
    myHeap.push(30);
    myHeap.printHeap();
    myHeap.push(50);
    myHeap.push(32);
    myHeap.push(70);

    myHeap.printHeap();

    cout << endl <<  myHeap.top << endl;

    myHeap.pop();

    cout << myHeap.top << endl;
    myHeap.pop();
    cout << myHeap.top << endl;
    myHeap.pop();
    cout << myHeap.top << endl;
    myHeap.pop();
    cout << myHeap.top << endl;
    myHeap.pop();
    cout << myHeap.top << endl;
    myHeap.pop();
    cout << myHeap.top << endl;
    myHeap.pop();
    myHeap.pop();

    return 0;
}