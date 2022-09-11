//
// Created by mhmdk on 5/13/2022.
//
/**
 * This template class of Binary search tree contains all the functionality
 * to insert,remove, traverse and get: leaf count, height of the tree and level, ancestor of
 * each node. this BST can hold any data type(string, int, char,etc..)
 * @author Mohamed Kubur
 * @version 1.0
 * */
#ifndef P2_BST_H
#define P2_BST_H
#include <string>
#include <sstream>
#include <iostream>
using namespace std;
template <typename T>
class BST {

public:
    BST();  //defaul constructor
    ~BST();  // destructor
    BST(BST<T> const &obj);  // copy constructor
    BST<T>& operator=(const BST<T> &obj); // overloaded assignment operator
    bool contains(T);       // test if value exist in BST
    void insert(T);         // insert element into BST
    void remove(T);         // remove element from BST
    bool empty(); // checks if BST is empty
    int size();  // gets the size of BST
    int getLeafCount();    // gets Leaf Count of BST
    int getHeight();    // gets the height of BST
    int getLevel(T);    // get the level of node
    string getInOrderTraversal();   // traverse BST inorder
    string getPreOrderTraversal();  // traverse BST in preorder
    string getPostOrderTraversal();  // traverse BST in postorder
    string getAncestors(T);         // gets the ancestors of node
    void getLocation(BST<T> &);
private:
    struct Node {
        T data;
        Node * left;
        Node * right;
    };
    Node * root;
    int size(Node *);    // overloaded helper function for size()
    int getLeafCount(Node * ptr); //overloaded helper function for getLeafCount
    int getHeight(Node *);    // overloaded helper function for getHeight
    int getLevel(Node * , T);  // overloaded helper function for getLevel
    string getInOrderTraversal(Node * ptr); //helper for getInOrderTraversal
    string getPreOrderTraversal(Node *);   //helper for getPreOrderTraversal
    string getPostOrderTraversal(Node *);  //helper for getPostOrderTraversal
    void insert(Node *&, Node *&);    //helper for insert()
    bool contains(Node *, T);         // helper function for contains
    void remove(Node *&, T);          // helper for remove
    void makeDeletion(Node *&, T);    // makes deletions of node
    void destroyTree(Node *&);        // destroys the tree
    void copy(Node *&newCopy, Node * objTemplate);  //helper for copying
};
template <typename T>
void BST<T>::getLocation(BST<T> &temp) {
    cout << "object location: " << this;
    cout << "object location: " << &temp;
    cout << "this root location: " << this->root;
    cout << "temp root location: " << temp.root;
}
// default constructor
template <typename T>
BST<T>::BST() {
    root = nullptr;
}
/**
 * @param obj BST to be copied from
 * overloaded copy constructor
 * */
template <typename T>
BST<T>::BST(BST<T> const &obj) {
    copy(this->root, obj.root);
}
/**
 * helper function for copying BST
 * @param newCopy BST to be copied to.
 * @param objTemplate BSt to be copied from
 * */
template <typename T>
void BST<T>::copy(Node *& newCopy, Node *objTemplate){
    if (objTemplate == nullptr) return;
    Node  * newNode = new Node();
    newNode->data = (objTemplate->data);
    newCopy = newNode;
    copy(newCopy->left, objTemplate->left);
    copy(newCopy->right, objTemplate->right);

}
/**
 * overloaded equal operator,
 * @param obj BST to be copied from(template)
 * */
template <typename T>
BST<T>& BST<T>::operator=(const BST<T> &obj){   // has segmentation error
    if (this->root != obj.root) {
        destroyTree(root);
        copy(this->root, obj.root);
    }
    return *this;
}
// deconstructor, calls destroytree
template <typename T>
BST<T>::~BST() {
    destroyTree(root);
}
/**
 * deletes all nodes by traversing BST
 * @param ptr pointer to the node to be deleted
 * */
template <typename T>
void BST<T>::destroyTree(Node *&ptr) {
    if (ptr != nullptr) {
        destroyTree(ptr->left);
        destroyTree(ptr->right);
        delete ptr;
    }
    ptr = nullptr;
}
/**
 * checks if the passed item exist in the BST
 * call an overloaded helper function passing the root.
 * @param item the value to searched for
 * @return boolean true if the value exist
 * */
template <typename T>
bool BST<T>::contains(T item) {
    Node * ptr = root;
    return contains(ptr, item);
}
/**
 * this is an overloaded helper function
 * @param item the value to be searched.
 * @param n pointer to node to be checked if it
 * contain the value
 * @return boolean true if the node contain the value
 * */
template <typename T>
bool BST<T>::contains(Node * n, T item){
    if (n == nullptr) return false;

    if (n->data == item) return true;
    else if (n->data > item)
        return contains(n->left, item);
    else
        return contains(n->right, item);

    return false;
}
/**
 * inserts a value to the calling BST
 * by calling the helper function insert
 * @param item value to be inserted
 * */
template <typename T>
void BST<T>::insert(T item) {
    Node * newNode = new Node;
    newNode->data = item;
    newNode->left = newNode->right = nullptr;

    insert(root, newNode);
}
/**
 * overloaded helper function to insert a node into
 * the BST recursively
 * @param ptr pointer to node in BST
 * @param newNode the new node to be inserted
 * */
template <typename T>
void BST<T>::insert(Node *& ptr, Node *& newNode) {
    if (ptr == nullptr)
        ptr = newNode;
    else if (ptr->data > newNode->data)
        insert(ptr->left, newNode);
    else
        insert(ptr->right, newNode);
}
/**
 * removed a value from BST by calling
 * the helper function remove
 * @param item the value to be removed
 * */
template <typename T>
void BST<T>::remove(T item) {
    remove(root, item);
}
/**
 * removes a value from BST by calling itself recursively
 * @param item the value to be removed
 * @param ptr pointer to node in BST
 * */
template <typename T>
void BST<T>::remove(Node *& ptr, T item) {
    if (ptr != nullptr) {
        if (ptr->data > item)
            remove(ptr->left, item);
        else if (ptr->data < item)
            remove(ptr->right, item);
        else
            makeDeletion(ptr, item);
    }
}
/**
 * maked the deletion of the value
 * @param ptr pointer to node in BST
 * @param item value to be deleted
 * */
template <typename T>
void BST<T>::makeDeletion(Node *& ptr, T item) {
    Node * curr = nullptr;
    if (ptr != nullptr) {
        if (ptr->left == nullptr) {
            curr = ptr;
            ptr = ptr->right;
            delete curr;
        } else if (ptr->right == nullptr) {
            curr = ptr;
            ptr = ptr->left;
            delete curr;
        } else {
            curr = ptr->right;
            while (curr->left != nullptr)
                curr = curr->left;
            ptr->data = curr->data;
            remove(ptr->right, curr->data);
        }
    }
}
/**
 * checks if the BST is empty or not
 * @return boolean true if the tree is empty
 * */
template <typename T>
bool BST<T>::empty() {
    return root == nullptr;
}
/**
 * this function count the nodes of BST
 * @return int is the number of node in BST
 * */
template <typename T>
int BST<T>::size() {
    Node * ptr = root;
    return size(ptr);
}
/**
 * this function count the nodes of BST by calling
 * itself recursively
 * @param n pointer to a node in BST
 * @return int is the number of node in BST
 * */
template <typename T>
int BST<T>::size(Node * n) {
    int count = 0;
    if (n == nullptr) return count;
    else {
        count = 1 + size(n->right) + size(n->left);
    }
    return count;
}
/**
 * this function counts the number of leaves in BST
 * by calling the overloaded helper function
 * @return int is the number of leaves
 * */
template <typename T>
int BST<T>::getLeafCount(){
    Node * ptr = root;
    return getLeafCount(ptr);
}
/**
 * this is a helper function to count the number of leaves in BST
 * by itself recursively
 * @return int is the number of leaves
 * */
template <typename T>
int BST<T>::getLeafCount(Node * ptr){
    if (ptr == nullptr) return 0;
    if (ptr->right == nullptr && ptr->left == nullptr) return 1;
    int res = getLeafCount(ptr->left) + getLeafCount(ptr->right);
    return res;
}
/**
 * this function calculated the height of BST
 * @return int the height of BST
 * */
template <typename T>
int BST<T>::getHeight(){
    Node * ptr = root;
    return getHeight(ptr);
}
/**
 * this is overloaded helper function to calculat the height of BST
 * @param ptr pointer to node in BST
 * @return int the height of BST
 * */
template <typename T>
int BST<T>::getHeight(Node * ptr){
    if (ptr == nullptr) return 0;
    return max(1 + getHeight(ptr->left), 1 + getHeight(ptr->right));
}
/**
 * this function calculates the level in which the node
 * exists by calling the helper overloaded function
 * @param data the value to be checked for level
 * @return int the number of level in the BST
 * */
template <typename T>
int BST<T>::getLevel(T data){
    Node * ptr = root;
    if (!contains(data)) return -1;
    return getLevel(ptr, data);
}
/**
 * this is an overloaded helper function to calculate the level in which the node
 * exists. by caling itself recursively
 * @param data the value to be checked for level
 * @return int the number of level in the BST
 * */
template <typename T>
int BST<T>::getLevel(Node * n, T data){
    if (n == nullptr) return -1;
    if (n->data == data) return 0;
    else if (n->data > data){
        return 1 + getLevel(n->left,data);
    }else {
        return 1 + getLevel(n->right, data);
    }
}
/**
 * this funciton traverse the BST in order(left, root, right)
 * by calling the overloaded helper function
 * @return string containing all the values of BST
 * */
template <typename T>
string BST<T>::getInOrderTraversal() {

    Node * ptr = root;
    return getInOrderTraversal(ptr);
}
/**
 * this is an overloaded helper funciton to
 * traverse the BST in order(left, root, right)
 * by calling itself recursively
 * @param ptr pointer to node in BST
 * @return string containing all the values of BST
 * */
template <typename T>
string BST<T>::getInOrderTraversal(Node * ptr) {
    stringstream ss;
    if (ptr == nullptr) return ss.str();

        ss << getInOrderTraversal(ptr->left) << (ptr->data) << " "
                << getInOrderTraversal(ptr->right);
    return ss.str();
}
/**
 * this function traverse the BST in preorder(root, left, right)
 * by calling the overloaded helper function
 * @return string containing all the values of BST
 * */
template <typename T>
string BST<T>::getPreOrderTraversal() {
    Node * ptr = root;
    return getPreOrderTraversal(ptr);
}
/**
 * this is an overloaded helper function to
 * traverse the BST in preorder(root, left, right)
 * by calling itself recursively
 * @param ptr pointer to node in BST
 * @return string containing all the values of BST
 * */
template <typename T>
string BST<T>::getPreOrderTraversal(Node * ptr) {
    stringstream ss;
    if (ptr == nullptr) return ss.str();

    ss << (ptr->data) << " " << getPreOrderTraversal(ptr->left)
            << getPreOrderTraversal(ptr->right);
    return ss.str();

}
/**
 * this function traverse the BST in postorder(left, right,root)
 * by calling the overloaded helper function
 * @return string containing all the values of BST
 * */
template <typename T>
string BST<T>::getPostOrderTraversal() {
    Node * ptr = root;
    return getPostOrderTraversal(ptr);
}
/**
 * this is an overloaded helper function to
 * traverse the BST in postorder(left, right,root)
 * by calling itself recursively
 * @param ptr pointer to node in BST
 * @return string containing all the values of BST
 * */
template <typename T>
string BST<T>::getPostOrderTraversal(Node * ptr) {
    stringstream ss;
    if (ptr == nullptr) return ss.str();

    ss << getPostOrderTraversal(ptr->left)
            << getPostOrderTraversal(ptr->right)
            << (ptr->data) << " ";
    return ss.str();

}
/**
 * this function returns a string containing all the
 * ancestor nodes for the passed element all the way to
 * the root.
 * @param item the value to get its ancestors
 * @return string contain the ancestors starting by the immediate
 * ancestor
 * */
template <typename T>
string BST<T>::getAncestors(T item){
    if (!contains(item))
        return "";

    Node * r = root;
    string temp;
    while (item != r->data) {
        stringstream ss;
        ss << (r->data) << " ";
        temp =  ss.str() + temp;
         if (r->data > item)
            r = r->left;
         else
             r = r->right;
    }
    return temp;
}

#endif //P2_BST_H
