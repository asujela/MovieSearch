#pragma once
#include "LinkedList.h"
#include "Movie.h"

//FOR LinkedList.h
///*
// POST: void
// Prints all of the elements stored within the LinkedList
// starting from the top most element
// */
//template <class T>
//void LinkedList<T>::printAll()
//{
//    Node<T>* currentNode = first;
//
//    for (int i = 0; i < length; i++)
//    {
//        std::cout << currentNode->getData();
//        if (i+1 < length)
//        {
//            std::cout << "  -->  ";
//            currentNode = currentNode->getNext();
//        }
//    }
//
//}

//FOR LinkedList.h
//comment out         toReturn = new Node<T>(first->getData());

//FOR Movie.cpp
//Movie::Movie()
//{
//    title = "N/A";
//    releaseDate = "00/00/0000";
//    director = "N/A";
//    genre = "N/A";
//    length = "N/A";
//    castSize = 0;
//    budget = 0;
//    ticketsSold = 0;
//}

//FOR Main.cpp
//int main() {
//    Hash<Movie>* h = new Hash<Movie>(7);
//
//    Movie* m1 = new Movie("The Shawshank Redemption","s","d","a","1",4,5,6);
//    Movie* m2 = new Movie("The Godfather","s","d","a","1",4,5,6);
//    Movie* m3 = new Movie("The Dark Knight","s","d","a","1",4,5,69);
//    Movie* m4 = new Movie("The Godfather: Part II","s","d","a","1",4,5,6);
//    Movie* m5 = new Movie("The Lord of the Rings: The Return of the King","s","d","a","1",4,5,6);
//    Movie* m6 = new Movie("Pulp Fiction","s","d","a","1",4,5,6);
//    Movie* m7 = new Movie("fas sdsa sdadsa","a","s","s","5",6,4,3);
//
//    h->insert(m1);
//    h->insert(m2);
//    //    h->remove(m1);
//    h->insert(m3);
//    h->insert(m4);
//    h->insert(m5);
//    h->remove(m5);
//    h->insert(m6);
//    h->insert(m7);
//
//    h->printAll();
//
//    cout << h->exists(m3) << endl;
//
//    h->printElement(6);
//
//    //    LinkedList<int>* a = new LinkedList<int>[10];
//    //
//    //    cout << a[0].getLength() << endl;
//    //    int x = 7;
//    //    a[0].add(x);
//    //    cout << a[0].getLength() << endl;
//    //
//    //    delete[] a;
//
//    cout << "Collisions: " << h->getCollisions() << endl;
//
//
//    delete h;
//
//
//    //    Node<Movie>* m = new Node<Movie>;
//    //    cout << m->getData() << endl;
//
//    return 0;
//}

template <class T>
class Hash
{
private:
    int size;
    LinkedList<Movie>* arr;

public:
    Hash();
    Hash(int);
    int hashFunc(std::string);
    void insert(Movie*);
    void remove(Movie*);
    int exists(Movie*);
    void find(std::string);
    int getCollisions();
    
    void printElement(int);
    void printAll();
    std::ostream& printAllFile(std::ostream&);
    
    class InvalidSize {};
};

/*
 Constructor for Hash class given no parameters
 */
template <class T>
Hash<T>::Hash()
{
    this->size = 25; // defaults to a size of 25
    arr = new LinkedList<Movie>[size]; // creates array of linked lists
}

/*
 PRE: size of array
 Constructor for Hash class given one size parameter
 */
template <class T>
Hash<T>::Hash(int size)
{
    this->size = size; // sets the size
    
    if (size <= 0) // size can't be 0 or negative
        throw InvalidSize();
    
    arr = new LinkedList<Movie>[size]; // creates array of linked lists
    
}

/*
 PRE: key of Movie class
 POST: array index
 Takes a key from the Movie class and returns the index of the array
 where it will be stored
 */
template <class T>
int Hash<T>::hashFunc(std::string key)
{
    int index;
    index = (size - key.length()) % size;
    
    return index;
}

/*
 PRE: Movie object pointer
 POST: void
 Takes an object from the Movie class and adds it to its respective
 position in the hash map based on the index produced by the
 hash function
 */
template <class T>
void Hash<T>::insert(Movie* m)
{
    std::string key = m->getTitle(); // gets title ie the key
    int i = hashFunc(key); // index for the key
    int pos = arr[i].getLength(); // position for the linked list
    
    arr[i].add(*m,pos); // adds the object
}

/*
 PRE: Movie object
 POST: void
 Takes an object from the Movie class and removes it from the
 hash map if it is found
 */
template <class T>
void Hash<T>::remove(Movie* m)
{
    std::string key = m->getTitle(); // gets title ie the key
    int i = hashFunc(key); // index for the key
    int pos = arr[i].find(*m); // position for the linked list

    arr[i].remove(pos); // removes the object
}

/*
 PRE: Movie object
 POST: position if found
 Takes an object from the Movie class and finds it position
 if it is found in the hash map, returns -1 if not found
 */
template <class T>
int Hash<T>::exists(Movie* m)
{
    std::string key = m->getTitle(); // gets title ie the key
    int i = hashFunc(key); // index for the key
    int pos = arr[i].find(*m); // position for the linked list
    
    if (pos == -1)
        return -1;
    else
        return i;
}

/*
 POST: int
 Determines the number of collisions that have taken place
 in the hash map
 */
template <class T>
int Hash<T>::getCollisions()
{
    int col = 0;
    
    for (int i = 0; i < size; i++) // iterates through the hash map
    {
        if (arr[i].getLength() > 0) // if Movie object is stored at the index
            col += (arr[i].getLength() - 1); // added it if a collision has occured
    }
    
    return col;
}

/*
 PRE: int index
 POST: void
 Prints all of the objects in the hash map and
 all of their respective indices on a given index
 */
template <class T>
void Hash<T>::printElement(int i)
{
    std::cout << "[" << i << "]: ";
    arr[i].printList();
    std::cout << std::endl;
}

/*
 POST: void
 Prints all of the objects in the hash map and
 all of their respective indices
 */
template <class T>
void Hash<T>::printAll()
{
    for (int i = 0; i < size; i++)
    {
        std::cout << "[" << i << "]: ";
        
        if (arr[i].getLength() > 0)
            arr[i].printList();
        
        std::cout << std::endl;
    }
}

/*
 POST: void
 Prints all of the objects in the hash map and
 all of their respective indices into a said file
 */
template <class T>
std::ostream& Hash<T>::printAllFile(std::ostream& outS)
{
    for (int i = 0; i < size; i++)
    {
        outS << "[" << i << "]: ";
        
        if (arr[i].getLength() > 0)
            arr[i].printToFile(outS);
        
        outS << std::endl;
    }
    
    outS << "Collisions: " << getCollisions() << std::endl;
    
    return outS;
}
