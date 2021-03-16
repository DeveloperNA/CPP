#include <iostream>

using namespace std;

class Node 
{
    public:
        int val;
        Node *left, *right;

        Node(){
            this->val = 0;
            this->left = NULL;
            this->right = NULL;
        }

        Node(int val){
            this->val = val;
            this->left = NULL;
            this->right = NULL;
        }
};

class AVL
{

    private:
    Node* leftRotate(Node* t);
    Node* rightRotate(Node* t);

    public:
    Node *root;

    AVL();
    AVL(int val);

    void insert(int val);
    Node* insert(Node* t, Node* newnode); 
    void remove(int val);
    Node* remove(Node* t, int val);

    int getHeight(Node* t);
    int getBalanceFactor(Node* t);
    Node* minNode(Node* t);    


    void inOrder(Node* t);

};

AVL::AVL()
{
    this->root = NULL;
}

AVL::AVL(int val)
{
    this->root = new Node(val);
}

Node* AVL::rightRotate(Node* t)
{
    Node *y = t->left;
    Node *z = y->right;

    y->right = t;
    t->left = z;

    return y;
}

Node* AVL::leftRotate(Node* t)
{
    Node *y = t->right;
    Node *z = y->left;

    y->left = t;
    t->right = z;

    return y;
}

void AVL::insert(int val)
{   
    Node *newnode = new Node(val);

    this->root = insert(this->root, newnode);
}

Node* AVL::insert(Node* t, Node* newnode)
{
    if(t == NULL){
        t = newnode;
        return t;
    }
    else if(newnode->val < t->val){
        t->left = insert(t->left, newnode);
    }
    else if(newnode->val > t->val){
        t->right = insert(t->right, newnode);
    }
    else{
        cout << "\n\t\t NO DUPLICATES ALLOWED\n";
        cout << "Cannot insert " << newnode->val << endl;
    }


    int bf = this->getBalanceFactor(t);

    if(bf > 1 && newnode->val < t->left->val){
        return rightRotate(t);
    }
    else if(bf >1 && newnode->val > t->left->val){
        t->left = leftRotate(t->left);
        return rightRotate(t);
    }
    else if(bf < -1 && newnode->val > t->right->val){
        return leftRotate(t);
    }
    else if(bf < -1 && newnode->val < t->right->val){
        t->right = rightRotate(t->right);
        return leftRotate(t);
    }

    return t;
}

Node* AVL::remove(Node *t, int val)
{
    if(t == NULL){
        cout << "ELement not present " << val << endl;
        return t;

    }
    else if(val < t->val){
        t->left = this->remove(t->left, val);
    }
    else if(val > t->val){
        t->right = this->remove(t->right, val);
    }
    else{
        if(t->left == NULL){
            Node* d = t->right;
            delete t;
            return d;
        }
        else if(t->right == NULL){
            Node* d = t->left;
            delete t;
            return d;
        }
        else{
            Node* min = minNode(t->right);
            t->val = min->val;
            t->right = this->remove(t->right, min->val);
        }
    }

    int bf = getBalanceFactor(t);

    if(bf > 1 && getBalanceFactor(t->left)>=0){
        return rightRotate(t);
    }
    else if(bf> 1 && getBalanceFactor(t->left)<0){
        t->left = leftRotate(t->left);
        return rightRotate(t);
    }
    else if(bf < -1 && getBalanceFactor(t->right) <=0){
        return leftRotate(t);
    }
    else if(bf < -1 && getBalanceFactor(t->right) > 0){
        t->right = rightRotate(t->right);
        return leftRotate(t);
    }

    return t;

}

void AVL::remove(int val)
{
    this->root = this->remove(this->root, val);
    // cout << endl<< "In void remove" << this->root->val << " " << endl;;

}

Node* AVL::minNode(Node* t)
{
    while(t->left != NULL){
        t=t->left;
    }

    return t;
}

int AVL::getHeight(Node* t)
{
    if(t == NULL)
        return -1;
    int leftHt = getHeight(t->left);
    int rightHt = getHeight(t->right);
    return ((leftHt>rightHt)? leftHt: rightHt) + 1;
}

int AVL::getBalanceFactor(Node *t)
{
    if(t == NULL)
        return -1;
    return (getHeight(t->left) - getHeight(t->right));
}

void AVL::inOrder(Node* t)
{
    if(t == NULL)
        return ;
    inOrder(t->left);
    cout << t->val << " ";
    inOrder(t->right);
}

int main()
{
    AVL myAvl;
    myAvl.insert(50);
    myAvl.insert(30);
    myAvl.insert(10);
    myAvl.insert(40);
    myAvl.insert(70);
    myAvl.insert(1);
    myAvl.insert(10);
    myAvl.insert(100);
    myAvl.insert(120);

    myAvl.inOrder(myAvl.root);
    cout << endl;

    cout << " Root: " << myAvl.root->val <<endl;
    myAvl.remove(30);

    myAvl.inOrder(myAvl.root);
    cout << endl;
    cout << " New Root: " << myAvl.root->val <<endl;

    return 0;

}