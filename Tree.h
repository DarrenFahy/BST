//Tree.h

#ifndef Tree_h
#define Tree_h

#include <string>
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

template <typename T>
class Node
{
public:
    Node(T info = T(), Node<T> *left = nullptr, Node<T> *right = nullptr);
    
    
    T info;
    Node<T> *left;
    Node<T> *right;
    
};

template <typename T>
class Tree
{
    
public:
    
    Tree();
    ~Tree();
    
    Node<T> *root;
    
    void insert(T info);
    void insert(T, Node<T> *&ptr);
    
    void remove(T info) { remove(info, root); }
    void remove(T info, Node<T> *&ptr);
    
    void empty(Node<T> *&ptr);
    void empty() { empty(root); }
    
    int treeHeight() { return treeHeight(root); }
    int treeHeight(Node<T> *&ptr);
    
    //const Node<T>* find(const T info)
    const Node<T>* find(const T info) { return find(info, root); }
    Node<T>* find(T info, Node<T> *ptr);
    
    int nodeHeight(const T& info); //{ return height(find(info)); }
    int height(const Node<T> *ptr);
    
    void printInOrder(Node<T> *ptr, ostream &os) const;
    void printInOrder(ostream &os) const { printInOrder(root, os); }
    
    void printPreOrder(Node<T> *ptr, ostream &os) const;
    void printPreOrder(ostream &os) const { printPreOrder(root, os); }
    
    void printPostOrder(Node<T> *ptr, ostream &os) const;
    void printPostOrder(ostream &os) const { printPostOrder(root, os); }
    
    void writeFilepi(string fname);
    void writeFilepp(string fname);
    void writeFilepe(string fname);
    void writeFileth(string name);
    
    
    //overloaded = operator
    Tree<T>& operator=(Tree<T> &rhsObj); //just call copy constructor
    
    //overloaded < operator
    //Tree<T>& operator<(Tree<T> &rhsObj);
    
    //overloaded == operator
    Tree<T>& operator==(Tree<T> &rhsObj);
    
    //copy constructor
    Tree(Tree<T> &otherTree);
    
    //copylist
    void copyList(Tree<T> &treeToCopy);
    
    
    
};

//Node implementation
template <typename T>
Node<T>::Node(T v, Node<T> *left, Node<T> *right)
{
    this->info = v;
    this->left = nullptr;
    this->right = nullptr;
    
}


//Default constructor
template <typename T>
Tree<T>::Tree()
{
    root = nullptr;
}

//Destructor
template <typename T>
Tree<T>::~Tree()
{

}


template <typename T>
int Tree<T>::nodeHeight(const T& info)
{
    if (root == NULL)
    {
        cout << "Tree is empty" << endl;
        return 0;
    }
    else
        return height( find(info) );
}

//const??
template <typename T>
int Tree<T>::height(const Node<T> *ptr)
{
    if (ptr == NULL)
    {
        return -1;
    }
    else
    {
        return 1 + max(height(ptr->left), height(ptr->right));
    }
    
    
}

//wraper function calling the root for the max height of the tree
template <typename T>
int Tree<T>::treeHeight(Node<T> *&ptr)
{
    if (root == NULL)
    {
        return 0;
    }
    else
        return height(root);
}


//returns the address of a node in the tree
template <typename T>
Node<T>* Tree<T>::find( T info, Node<T> *ptr)
{
    if (ptr == NULL)
    {
        //cout << "Value: " << info << " not found in tree" << endl;
        return ptr;
    }
    else if (strcmp(info, ptr->info) < 0)
    {
        return find(info, ptr->left);
    }
    else if( strcmp(ptr->info, info) < 0)
    {
        return find(info, ptr->right);
    }
    else
    {
        return ptr;
    }

    
}

template <typename T>
void Tree<T>::remove(T info, Node<T> *&ptr)
{
    //find the value, if the pointers right and left are null then delete the node
    
    //if there is a left pointer, go left once then right until null
    //replace the 'remove' value with that value
    
    //if that node has a left pointer, move the subtree up one spot
    
    //if value is not in tree (use find()?) then print
    
    if (ptr == nullptr)
    {
        return;
    }
    else if (strcmp(info, ptr->info) < 0)
    {
        remove(info, ptr->left);
    }
    else if (strcmp(ptr->info, info) < 0)
    {
        remove(info, ptr->right);
    }
    else
    {
        Node<T> *temp = ptr; //we delete this node
        Node<T> *attach;
        
        //only one child
        if (ptr->right == NULL)
        {
            ptr = ptr->left;
        }
        else if (ptr->left == NULL)
        {
            ptr = ptr->right;
        }
        else
        {
            //two children to move
            attach = ptr->right;
            
            while (attach->left != NULL)
            {
                attach = attach->left;
            }
            attach->left = ptr->left;
            ptr = ptr->right;
        }
        delete temp;
    }
}

//uses post order traversal to delete the entire tree
template <typename T>
void Tree<T>::empty(Node<T> *&ptr)
{
    if (root == NULL)
    {
        cout << "Tree is empty" << endl;
        return;
    }
    if(ptr != NULL)
    {
        empty(ptr->left);
        empty(ptr->right);
        delete ptr;
        
        if(ptr->left != NULL)
        {
            ptr->left = NULL;
        }
        if(ptr->right != NULL)
        {
            ptr->right = NULL;
        }
        ptr = NULL;
    }
    
}


template <typename T>
void Tree<T>::insert(T info)
{
    if (root == nullptr)
    {
        root = new Node<T>(info);
        cout << "Inserted " << root->info << " into tree as root" << endl;
    }
    else
    {
        insert(info, root);
    }

}

template <typename T>
void Tree<T>::insert(T info, Node<T> *&ptr)
{
    
    if (ptr == nullptr)
    {
        ptr = new Node<T>(info);
        cout << "Inserted " << ptr->info << " into tree" << endl;
        return;
    }
    if (strcmp(ptr->info, info) == 0)
    {
        cout << "Warning, duplicate value, ignoring" << endl;
        return;
    }
    else if (strcmp(ptr->info, info) < 0)
    {
        insert(info, ptr->right);
    }
    else if (strcmp(ptr->info, info) > 0)
    {
        insert(info, ptr->left);
    }
}


//overloaded = operator
template <typename T>
Tree<T>& Tree<T>::operator=(Tree<T> &rhsObj)
{
    this->copyList(rhsObj);
}

//overloaded < operator
//template <typename T>
//Tree<T>& Tree<T>::operator<(Tree<T> &rhsObj)
//{
//    if (strcmp( this->info, rhsObj->info) < 0)//this->info lower than obj
//    {
//        return true;
//    }
//    else
//    {
//        return false;
//    }
//    
//    
//}

//template <typename T>
//Tree<T>& Tree<T>::operator==(Tree<T> &rhsObj)
//{
//    if (strcmp( this->info, rhsObj->info) == 0)
//    {
//        //object already exists in tree
//        return true;
//    }
//    else
//    {
//        return false;
//    }
//    
//}



template <typename T>
void Tree<T>::printInOrder(Node<T> *ptr, ostream &os) const
{
    if (root == NULL)
    {
        cout << "Tree is empty" << endl;
        return;
    }
    else if (ptr != NULL)
    {
        
        printInOrder(ptr->left, os);
        os << ptr->info << " ";
        printInOrder(ptr->right, os);
    }
}


template <typename T>
void Tree<T>::writeFilepi(string fname)
{
    ofstream os(fname);
    if (os.is_open())
    {
        printInOrder(os);
    }
    os.close();
    
}

template <typename T>
void Tree<T>::writeFilepp(string fname)
{
    ofstream os(fname);
    if (os.is_open())
    {
        printPostOrder(os);
    }
    os.close();
    
}

template <typename T>
void Tree<T>::writeFilepe(string fname)
{
    ofstream os(fname);
    if (os.is_open())
    {
        printPreOrder(os);
    }
    os.close();
    
}

template <typename T>
void Tree<T>::writeFileth(string fname)
{
    ofstream os(fname);
    if (os.is_open())
    {
        os << treeHeight();
    }
    os.close();
}



template <typename T>
void Tree<T>::printPreOrder(Node<T> *ptr, ostream &os) const
{
    if (root == NULL)
    {
        cout << "Tree is empty" << endl;
        return;
    }
    else if (ptr != NULL)
    {
        os << ptr->info << " ";
        printPreOrder(ptr->left, os);
        printPreOrder(ptr->right, os);
    }
}

template <typename T>
void Tree<T>::printPostOrder(Node<T> *ptr, ostream &os) const
{
    if (root == NULL)
    {
        cout << "Tree is empty" << endl;
        return;
    }
    else if (ptr != NULL)
    {
        printPostOrder(ptr->left, os);
        printPostOrder(ptr->right, os);
        os << ptr->info << " ";
    }

}



/****************************************************************************
 *                       Tree class copy constructor                        *
 ****************************************************************************/
template <typename T>
Tree<T>::Tree(Tree<T> &otherTree)
{
    this->copyList(otherTree);
    //creates a deep copy by calling copyList
}



/****************************************************************************
 *                        private function copyList                         *
 ****************************************************************************/

template <typename T>
void Tree<T>::copyList(Tree<T> &treeToCopy)
{
    if (this != &treeToCopy)
    {
        root = nullptr;
        this->clear();
        
        if (this->head == treeToCopy.head)
        {
            cout << "Trees same, no need to copy" << endl;
        }
        else
        {
            Node<T> *current = treeToCopy.head;
            
            while (current != NULL)
            {
                
                int value = current->info;
                this->insert(value);
                current = current->next;
            }//end while
            
        }//end else
    }
}//end void copyList




#endif /* Tree_h */
