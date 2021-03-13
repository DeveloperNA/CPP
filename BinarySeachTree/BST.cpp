#include <iostream>
#include <queue>

using namespace std;


class EmptyBstException:exception{};
class NodeNotFoundException:exception{};

class BST
{
    private:
        struct Node
        {
            int data;
            struct Node *left, *right;
        };

    public:
        struct Node *root;
        BST();
        BST(int data); 
        
        void insert(int data);
        void del(int data);
        
        void levelorder(struct Node *t);
        void preorder(struct Node *t);
        void inorder(struct Node *t);
        void postorder(struct Node *t);
      
};

BST::BST()
{
    this->root = NULL;
}

BST::BST(int data)
{
    this->root = new Node;
    this->root->data = data;
    this->root->left = NULL;
    this->root->right = NULL;
}

void BST::insert(int data)
{
    struct Node *temp, *p, *q;
    temp = new Node;
    p = NULL;
    q = this->root;

    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;

    if(q== NULL){
        this->root = temp;
    }
    else{
        while(q!= NULL){
            p = q;
            if(data < q->data){
                q = q->left;
            }
            else{
                q = q->right;
            }
        }

        if(data < p->data){
            p->left = temp;
        } 
        else{
            p->right = temp;
        }
        
    }
}

void BST::del(int data)
{
    struct Node *temp, *p, *q;

    p = NULL; 
    q = this->root;

    try{
        if(q == NULL)
            throw EmptyBstException();

        if(data == this->root->data){
            q = p = this->root;
        }

        while(q != NULL && q->data != data){
            p = q;
            if(data < q->data){
                q = q->left;
            }
            else{
                q = q->right;
            }
        }

    

        if(q == NULL)
            throw NodeNotFoundException();

        if(q->left == NULL){
            temp = q->right;
            delete q;
            p->left = temp;
        }
        else if(q->right == NULL){
            temp = q->left;
            delete q;
            p->right = temp;
        }
        else
        {
            struct Node *t = NULL;
            temp = q->right;

            while(temp->left != NULL){
                t = temp;
                temp = temp->left;

            }
            q->data = temp->data;   

            if(t != NULL){
                t->left = temp->right;
                delete temp;
            }
            else{
                q->right = temp->right;
            }

        }

        cout << "\nDeleted " << data << endl;
        
    }

    catch(EmptyBstException e){
        printf("\n\t\t////// Unable to delete a node(%d) in empty bst //////\n", data);
    }

    catch(NodeNotFoundException e){
        printf("\n\t\t///// Node(%d) Not found /////\n", data);
    }        

}

void BST::levelorder(struct Node *t)
{
    cout << "\nLevel order Traversal: ";

    queue<struct Node*> q;
    q.push(this->root);

    while(!q.empty()){
    
        struct Node *temp = q.front();

        if(temp!= NULL) cout << temp->data << " ";
        if(!q.empty()) q.pop();
        if(temp->left != NULL) q.push(temp->left);
        if(temp->right != NULL) q.push(temp->right);

    }

    cout << endl;

}

void BST::preorder(struct Node* t)
{
    if(t == NULL){
        return;
    }

    cout << t->data << " ";
    preorder(t->left);
    preorder(t->right);

}

void BST::inorder(struct Node* t)
{
    if(t == NULL){
        return;
    }

    inorder(t->left);
    cout << t->data  << " ";
    inorder(t->right);
}

void BST::postorder(struct Node* t)
{
    if(t == NULL){
        return;
    }

    postorder(t->left);
    postorder(t->right);
    cout << t->data << " ";
}

// struct Node* BST::maxOfBst(struct Node *t)
// {
//     struct Node *temp = t;
//     while(temp->right != NULL){
//         temp = temp->right;
//     }
//     return temp;
// }


int main()
{
    BST myBst;

    myBst.insert(30);
    myBst.insert(25);
    myBst.insert(60);
    myBst.insert(20);
    myBst.insert(10);
    myBst.insert(70);
    myBst.insert(15);
    myBst.insert(22);
    myBst.insert(50);

    myBst.del(10);
    myBst.del(100);
    myBst.del(30);


    cout << "\nPreorder Traversal : ";
    myBst.preorder(myBst.root); 
    cout << endl;

    cout << "\nInorder Traversal : ";
    myBst.inorder(myBst.root);
    cout << endl;
    
    cout << "\nPostorder Traversal : " ;
    myBst.postorder(myBst.root);
    cout << endl;

    myBst.levelorder(myBst.root);

    // cout << myBst.root->data;
    return 0;
}