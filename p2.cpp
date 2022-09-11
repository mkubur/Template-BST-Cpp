#include <iostream>
#include "BST.h"
#include <string>
#include <fstream>
using namespace std;
void welcomeMsg();
void stringBSTHeader();
void intBSTHeader();
string getIntegerFile();
string getStringFile();
template<typename T>
void insertValues(BST<T > &, string);
template<typename T>
void testTraversals(BST<T> &tree);
template<typename T>
void testLevelsAndAncestors(string fileName,BST<T> &tree);
template<typename T>
void testContains(T *, BST<T> &tree);
template<typename T>
void testRemove(T *, BST<T> &tree);
template<typename T>
void testInsertAgain(T *,BST<T> &tree);
template<typename T>
void printBSTDetails(BST<T> &tree);

/**
 * The main test the functionality of template BST class on both integers and strings,
 * calls functions to create, traverse in in/pre/post order, remove, insert and prints
 * the details of every step. it populates data by reading from file.
 **/

int main() {
    // numbers to test integer BST functionality
    int  testNums[] = {20, 40 , 10, 70 , 99,-2,59,43};
    // strings to test string BST functionality
    string testStrings[] = { "gene", "mary", "bea", "uma" ,"yan"
                             ,"amy" ,"ron" ,"opal"};
    welcomeMsg();     // prints welcome message
    intBSTHeader();   // prints header for int BST
    cout << "** CREATE BST **" << endl;
    BST<int> intTree;
    printBSTDetails(intTree);     // prints the details of BST
    string intFile = getIntegerFile();  // prompts the user for int file
    insertValues(intTree, intFile);  // populates data to BST
    printBSTDetails(intTree);
    testTraversals(intTree);         // traverse tree in pre/in/postorder
    //displays the level and ancestor of each element
    testLevelsAndAncestors(intFile,intTree);
    testContains(testNums,intTree);    // test if element exist in BST
    testRemove(testNums, intTree);  // removes elements from BST
    testInsertAgain(testNums, intTree);  // insert new values into BST

    // string tree function calls
    stringBSTHeader();
    cout << "** CREATE BST **" << endl;
    BST<string> stringTree;
    printBSTDetails(stringTree);
    string stringFile = getStringFile();
    insertValues(stringTree, stringFile);
    printBSTDetails(stringTree);
    testTraversals(stringTree);
    testLevelsAndAncestors(stringFile, stringTree);
    testContains(testStrings, stringTree);
    testRemove(testStrings, stringTree);
    testInsertAgain(testStrings, stringTree);

    cout << "\ngoodbye!";
    BST<string> bst = stringTree;
    stringTree.getLocation(stringTree);

    return 0;
}
/**
 * prints a welcome message and some info about the program.
 * */
void welcomeMsg(){
    cout << "Welcome to BST program, This program creates Binary search tree template\n"
    "with all its functionality; insert, delete, traverse, etc.." << endl << endl;

}
/**
 * prints a header for int BST to indicate the following
 * processes belongs to integer BST
 * */
void intBSTHeader(){
    cout << "******************************\n"
            "* INTEGER BINARY SEARCH TREE *\n"
            "******************************" << endl << endl;
}
/**
 * prints a header for string BST to indicate the following
 * processes belongs to string BST
 * */
void stringBSTHeader(){
    cout << "\n********************\n"
            "* test string BST  *\n"
            "********************" << endl << endl;
}
/**
 * print the details of the tree; # of nodes,leaves,height and
 * whether the tree is empty or not.
 * */
template<typename T>
void printBSTDetails(BST<T> &tree){
    stringstream ss;
    ss << "# of nodes:  " << tree.size() << endl;
    ss << "# of leaves: " << tree.getLeafCount() << endl;
    ss << "BST height:  " << tree.getHeight() << endl;
    ss << "BST empty?  ";
    if (tree.empty())
        ss << "true";
    else ss << "false";
    ss << endl;
    cout << ss.str();
}
/**
 * open the selected file, read and  insert values into the BST.
 * Also prints the values before inserting it.
 * */
template<typename T>
void insertValues(BST<T > &tree, string fileName){
    fstream fs;
    fs.open(fileName);
    T value;
    if(fs){
        cout << endl;
        cout << "** TEST INSERT **" << endl;
        cout << "Inserting in this order: ";
        while(fs >> value){
            cout << value;
            cout << " ";
            tree.insert(value);
        }
        cout << endl;
    } else {
        cout << "invalid input file!";
    }
    fs.close();
}
/**
 * prompts the user for integer file name and validates
 * the file before returning the name of file.
 * */
string getIntegerFile(){
    fstream fs;
    string str;
    do {
        cout << "\nEnter Integer file: ";
        cin >> str;
        fs.open(str);
    } while (!fs);
    fs.close();
    return str;
}
/**
 * prompts the user for string file name and validates
 * the file before returning the name of file.
 * */
string getStringFile(){
    fstream fs;
    string str;
    do {
        cout << "\nEnter string file: ";
        cin >> str;
        fs.open(str);
    } while (!fs);
    fs.close();
    return str;
}
/**
 * print all the traversals of BST; pre/in/post order
 * */
template<typename T>
void testTraversals(BST<T> &tree){
    cout << endl;
    cout << "** TEST TRAVERSALS **" << endl;
    cout <<  "pre-order:  " + tree.getPreOrderTraversal() << endl;
    cout << "in-order:   " + tree.getInOrderTraversal() << endl;
    cout << "post-order: " + tree.getPostOrderTraversal() << endl;

}
/**
 * iterate throught all nodes of BST and prints the
 * level of node and its ancestors.
 * */
template<typename T>
void testLevelsAndAncestors(string fileName, BST<T> &tree){  // read about the difference between * and *&
    cout << endl;
    cout << "** TEST LEVEL & ANCESTORS **" << endl;
    fstream fs;
    fs.open(fileName);
    T value;
    if(fs){
        while(fs >> value){
            cout << "Level(" << (value) << "): " ;
            cout << tree.getLevel(value);
            cout << ", ancestors(" << value << "): ";
            cout << tree.getAncestors(value);
            cout << endl;
        }
    } else {
        cout << "invalid input file!";
    }
    fs.close();
}
/**
 * reads an array of values and test if these values exist
 * in the BST and prints the result of each value.
 * */
template<typename T>
void testContains(T * values, BST<T> &tree){

    int k = sizeof (values);
    cout << endl;
    cout << "** TEST CONTAINS **" << endl;
        for (int i = 0 ; i < k ; i++){
            cout << "contains(" << (values[i]) << "): " ;
            if (tree.contains(values[i]))
                cout << "true";
            else
                cout << "false";
            cout << endl;
        }
}
/**
 * reads an array of values and remove each value from the
 * BST if it does exists and prints the BST details after
 * removing values.
 * */
template<typename T>
void testRemove(T * testValues , BST<T> &tree){

    int k = sizeof (testValues);
    cout << endl;
    cout << "** TEST REMOVE **" << endl;
    cout << "Removing in this order: ";
    for (int i = 0 ; i < k ; i++){
        cout << testValues[i];
        cout << " ";
        tree.remove(testValues[i]);
    }
    cout << endl;
    printBSTDetails(tree);
    cout <<  "pre-order:  " + tree.getPreOrderTraversal() << endl;
    cout << "in-order:   " + tree.getInOrderTraversal() << endl;
    cout << "post-order: " + tree.getPostOrderTraversal() << endl;
}
/**
 * inserts an array of values into BST and prints the
 * details of BSt after insertion.
 * */
template<typename T>
void testInsertAgain(T * testValues, BST<T> &tree){

    int k = sizeof (testValues);
    cout << endl;
    cout << "** TEST INSERT (again) **" << endl;
    cout << "Inserting in this order: ";
    for (int i = 0 ; i < k ; i++){
        cout << testValues[i];
        cout << " ";
        tree.insert(testValues[i]);
    }
    cout << endl;
    printBSTDetails(tree);
    cout <<  "pre-order:  " + tree.getPreOrderTraversal() << endl;
    cout << "in-order:   " + tree.getInOrderTraversal() << endl;
    cout << "post-order: " + tree.getPostOrderTraversal() << endl;
}

