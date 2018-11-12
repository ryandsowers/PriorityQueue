// ---------------------------------------------------------------------
// Written by: Ryan Sowers
// Last edited on: December 11, 2017
// File name: Ryan_Sowers_priority_queue.cpp
// Description: this file creates objects of the type 'Priority_queue'.
//  These objects are priority queues or heaps that contain key and 
//  data-value pairs. A variety of functions are then called on these 
//  trees to add items to the queue, increase or decrease the value of 
//  an item, to show the heap, and finally a visual print to show the 
//  branching.
// Designed on MacOS.
// ---------------------------------------------------------------------
#include <iostream>
#include <cstdlib>		//for rand() use
#include <math.h>
using namespace std;

class Priority_queue {
    int size; // current size
    int max_size;
    int * elements;
    
    void max_heapify(int i){
        int l, r, largest;
        l = 2 * i;      // LEFT(i)
        r = 2 * i + 1;  // RIGHT(i)
        if(l <= size && elements[l] > elements[i]) 
                largest = l;
        else    largest = i;
        
        if(r <= size && elements[r] > elements[largest])
            largest = r;
        
        if(largest != i){
            // swap elements[i] with elements[largest]
            int temp = elements[i];
            elements[i] = elements[largest];
            elements[largest] = temp;
            max_heapify(largest); // recursion
        }
    }
    
public:
    // constructor
    Priority_queue(int n){
        if(n <= 0) max_size = 1; // default max_size == 1
        else max_size = n;
        size = 0; // creates empty queue
        elements = new int [max_size + 1];
        // indicies of stored elements start with 1
        elements[0] = -1; 
    }
    
    void enqueue(int key){
        if(size + 1 >= max_size){ 
            cout<< " queue overflow\n";
            return;
        }
        size++;
        elements[size] = key;
        // Walk backwards through the array from size/2 to 1, 
        // calling max_heapify() on each node => this is the same as constructing 
        // a heap from sub-heaps (bottom-up).
        // Order of processing guarantees that the children of node i 
        // are heaps when i is processed
        for(int i = size/2; i > 0; i--)
            max_heapify(i);
    }

    int maximum(){
        if(size == 0){
            cout<< " queue underflow\n";
            return -1;
        }
        return elements[1];
    }
    
    int dequeue(){
        if(size == 0){
            cout<< " queue underflow\n";
            return -1;
        }
        int root = elements[1];
        elements[1] = elements[size];
        size--;
        max_heapify(1);
        return root;
    }
    
    void increase_key(int position, int new_key){
        if(position > size) {
            cout << "Error, position " << position << " is out of bounds of the array." << endl;
            return;
        }
        if(new_key < elements[position]){
            cout<<" Error: new key "<< new_key << " is smaller than current key " 
                << elements[position]<<endl;
            return;
        }
        elements[position] = new_key;
        while(position > 1 && elements[position/2] < elements[position]){
            // swap element with its parent
            int temp = elements[position/2];
            elements[position/2] = elements[position];
            elements[position] = temp;
            position = position/2; // move upward
        }
    }
    
    void show(){
        // print the heap contents
        cout<< "the heap contents is: ";
        for(int i = 1; i <= size; i++)
            cout<< elements[i]<< ' ';
        if (size == 0) {
            cout << "Empty";
        }
        cout<<endl;
    }

    void clear() {
        for (int k = 1; k <= size; ++k) {
            elements[k] = 0;
        }
        size = 0;
        cout << "Heap cleared." << endl;
    }

    void decrease_key(int position, int new_key){
        if(position > size) {
            cout << "Error, position " << position << " is out of bounds of the array." << endl;
            return;
        }
        if(new_key > elements[position]){
            cout<<" Error: new key "<< new_key << " is greater than current key " 
                << elements[position]<<endl;
            return;
        }
        elements[position] = new_key;
        max_heapify(position);
    }

    void print_visual() {
        int maxL = log2(size) + 1;  // max number of layers
        int curLayer = 1;           // current layer number
        int layerIndex;     // index of first item of current layer
        // int layerIndexEnd = pow(2, curLayer) - 1;   // index of last item of current layer
        int numElts;   // number of elements in current layer

        for (int m = 1; m <= maxL; ++m) {
            layerIndex = pow(2, curLayer-1);
            numElts = pow(2, curLayer-1);
            // cout << "Layer index: " << layerIndex;
            // cout << " Num elts: " << numElts;
            for (int o = 0; o < numElts; ++o) {
                if (layerIndex == 1) {
                    for (int n = 0; n < (maxL - curLayer); ++n) {
                        cout << '\t';
                    }
                } else if (layerIndex%2==0) {
                    for (int p = 0; p < (maxL - curLayer); ++p) {
                        cout << '\t';
                    }
                } else if (layerIndex%2==1) {
                    cout << ' ';
                }
                if (layerIndex <= size) {
                    cout << elements[layerIndex];
                    layerIndex++; 
                }    
            }
            cout << endl;
            curLayer++; 
        }
    }
       
};

int main(){
    Priority_queue a(20);
    Priority_queue b(10);
    Priority_queue c(100);

    // show an empty queue
    cout << "\nEmpty queue: " << endl;
    a.show();
    a.print_visual();

    // fill the empty queue with one element and show
    a.enqueue(5);
    cout << "\nQueue with 1 element: " << endl;
    a.show();
    a.print_visual();

    // clear queue a and show
    a.clear();
    cout << "\nCleared queue a: " << endl;
    a.show();
    a.print_visual();

    // fill a new queue with five elements and show
    for (int n = 0; n < 5; ++n) {
        b.enqueue(rand() % 100);
    }
    cout << "\nQueue with small number of random elements: " << endl;
    b.show();
    b.print_visual();
    
    // fill a new queue with 65 random elements and show
    for(int j = 1; j <66; j++)
        c.enqueue(rand()% 100);
    cout << "\nQueue with 65 elements: " << endl;
    c.show();   
    c.print_visual();
    
    
    return 0;
}