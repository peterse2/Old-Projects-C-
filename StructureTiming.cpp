//
//  main.cpp
//  StructureTiming: Collects data about the speed and structure of
//  5 different data strucutres (Vector, RedBlackTree, Treap,
//  LeftistHeap, and BinomialQueue)
//
//  Created by Emily Rose Peterson on 3/13/15.
//  Copyright (c) 2015 CIS 263. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <string>
#include <stack>
#include "Vector.cpp"
#include "RedBlackTree.cpp"
#include "Treap.cpp"
#include "LeftistHeap.cpp"
#include "BinomialQueue.cpp"

using namespace std;
class StructureTimming{
    Vector<string> vector;
	RedBlackTree<string> rbTree;
	Treap<string> treap;
	LeftistHeap<string> lheap;
    BinomialQueue<string> binQ;
    
    clock_t start;
    double duration;
    stack<double> time;
    
    
    /**
     * Reads in the file "filename" and inserts the file line by line
     * into the five data structure
     */
	void readIn(string filename){
        time.empty();
        string str;
		ifstream inFile(filename);
        start = clock();
        
		if (inFile.is_open()){
            
            //vector
			while (getline(inFile, str)){
				if (str.empty()) continue;
                vector.push_back(str);
            }
            duration = (clock() - start) / (double) CLOCKS_PER_SEC;
            time.push(duration);
            
            //RedBlackTree
            start = clock();
            while (getline(inFile, str)){
				if (str.empty()) continue;
                rbTree.insert(str);
            }
            duration = (clock() - start) / (double) CLOCKS_PER_SEC;
            time.push(duration);
            
            //Treap
            start = clock();
            while (getline(inFile, str)){
				if (str.empty()) continue;
                treap.insert(str);
            }
            duration = (clock() - start) / (double) CLOCKS_PER_SEC;
            time.push(duration);
            
            //LeftishHeap
            start = clock();
            while (getline(inFile, str)){
				if (str.empty()) continue;
                lheap.insert(str);
            }
            duration = (clock() - start) / (double) CLOCKS_PER_SEC;
            time.push(duration);
            
            //BinomialQueue
            start = clock();
            while (getline(inFile, str)){
				if (str.empty()) continue;
                binQ.insert(str);
            }
            duration = (clock() - start) / (double) CLOCKS_PER_SEC;
            time.push(duration);
		}
	}
    
    /**
     * Determines the size or length of a redBlackTree
     */
    int redBlackTreeLength(RedBlackNode *t) const
        {
            int count = 0;
            if( t != t->left ) {
                redBlackTreeLength( t->left );
                count++;
                redBlackTreeLength( t->right );
            }
            return count;
         }
    
    /**
     * Determines the size or length of a treap
     */
    int treapLength(TreapNode *t) const
    {
        int count = 0;
        if( t != nullNode )
        {
            treapLength( t->left );
            count++;
            treapLength( t->right );
        }
        return count;
    }
    
    /**
     * Determines the size or length of a leftistHeap
     */
    int leftistHeapLength(LeftistNode *t) const
    {
        int count = 0;
        if(t != nullNode)
        {
            leftistHeapLength( t->left );
            count++;
            leftistHeapLength( t->right );
        }
        return count;
    }
    
    /**
     * Seaches for a string in a vector
     */
    bool vectorSearch(Vector<string> * vec, string str){
            if(std::find(vec->begin(),vec->end(),str)!=vec->end())
                return true;
            return false;
    }
    
    /**
     * Seaches for a string in a leftistHeap
     */
    bool leftisHeapSearch(LeftisNode* top, string str)
    {
        if (top == NULL)
            return false;
        else {
            if (data == top->str)
                return true;
            else if (data < top->str)
                return contains(top->left, str);
            else if (data > top->data)
                return contains(top->right, str);
        }
    }
    
    /**
     * Seaches for a string in a BinomailNode
     */
    bool Search(BinomailNode* top, string str)
    {
        if (top == NULL)
            return false;
        else {
            if (data == top->str)
                return true;
            else if (data < top->str)
                return contains(top->left, str);
            else if (data > top->data)
                return contains(top->right, str);
        }
    }

    /**
     * Seaches for a string in a the five different data structures
     * recording the speed of each and storing the time into an 
     * stack
     */
    void find(string str){
        time.empty();
        
        start = clock();
        vectorSearch(vector, str);
        duration = (clock() - start) / (double) CLOCKS_PER_SEC;
        time.push(durration);
        
        start = clock();
        rbTree.contains(str);
        duration = (clock() - start) / (double) CLOCKS_PER_SEC;
        time.push(durration);
        
        start = clock();
        treap.contains(str);
        duration = (clock() - start) / (double) CLOCKS_PER_SEC;
        time.push(durration);
        
        start = clock();
        leftisHeapSearch(lheap->root, str);
        duration = (clock() - start) / (double) CLOCKS_PER_SEC;
        time.push(durration);
        
        start = clock();
        binnomialQueueSearch(binQ->root, str);
        duration = (clock() - start) / (double) CLOCKS_PER_SEC;
        time.push(durration);
    }
    
    

        
};

int main()
{
    //Collecting Data
    readIn("RomeoAndJuliet.txt");
    cout << "The Vector contains " << vector.size() << " lines";
    cout << "The RedBlackTree contains " << redBlackTreeLength(rbTree.header->right) << " lines";
    cout << "The Treap contains " << treapLength(treap.root) << " lines";
    cout << "The LeftistHeap contains " << leftistHeapLength(lheap.root) << " lines";
    cout << "The BinomialQueue contains " << binQ.size() << " lines";
    
    //Insert Timming
    readIn("RomeoAndJuliet.txt");
    cout<<"RomeoAndJuliet.txt BinomialQueue read in completed in: "<< time.pop() <<" seconds"<<'\n';
    cout<<"RomeoAndJuliet.txt LeftistHeap read in completed in: "<< time.pop() <<" seconds"<<'\n';
    cout<<"RomeoAndJuliet.txt Treap read in completed in: "<< time.pop() <<" seconds"<<'\n';
    cout<<"RomeoAndJuliet.txt RedBlackTree read in completed in: "<< time.pop() <<" seconds"<<'\n';
    cout<<"RomeoAndJuliet.txt Vector read in completed in: "<< time.pop() <<" seconds"<<'\n';
    
    readIn("RomeoAndJulietx10");
    cout<<"RomeoAndJulietx10 BinomialQueue read in completed in: "<< time.pop() <<" seconds"<<'\n';
    cout<<"RomeoAndJulietx10 LeftistHeap read in completed in: "<< time.pop() <<" seconds"<<'\n';
    cout<<"RomeoAndJulietx10 Treap read in completed in: "<< time.pop() <<" seconds"<<'\n';
    cout<<"RomeoAndJulietx10 RedBlackTree read in completed in: "<< time.pop() <<" seconds"<<'\n';
    cout<<"RomeoAndJulietx10 Vector read in completed in: "<< time.pop() <<" seconds"<<'\n';
    
    readIn("RomeoAndJulietx100");
    cout<<"RomeoAndJulietx100 BinomialQueue read in completed in: "<< time.pop() <<" seconds"<<'\n';
    cout<<"RomeoAndJulietx100 LeftistHeap read in completed in: "<< time.pop() <<" seconds"<<'\n';
    cout<<"RomeoAndJulietx100 Treap read in completed in: "<< time.pop() <<" seconds"<<'\n';
    cout<<"RomeoAndJulietx100 RedBlackTree read in completed in: "<< time.pop() <<" seconds"<<'\n';
    cout<<"RomeoAndJulietx100 Vector read in completed in: "<< time.pop() <<" seconds"<<'\n';
    
    //Find
    readIn("RomeoAndJulietx100");
    string str = "THE TRAGEDY OF ROMEO AND JULIET";
    find(str)
    cout<<"BinomialQueue search for" << str << "in RomeoAndJulietx100 " << '\n';
    cout<<"completed in: "<< time.pop() <<" seconds"<<'\n';
    
    cout<<"LeftishHeap search for" << str << "in RomeoAndJulietx100 " << '\n';
    cout<<"completed in: "<< time.pop() <<" seconds"<<'\n';
    
    cout<<"Treap search for" << str << "in RomeoAndJulietx100 " << '\n';
    cout<<"completed in: "<< time.pop() <<" seconds"<<'\n';
    
    cout<<"RedBlackTree search for" << str << "in RomeoAndJulietx100 " << '\n';
    cout<<"completed in: "<< time.pop() <<" seconds"<<'\n';
    
    cout<<"Vector search for" << str << "in RomeoAndJulietx100 " << '\n';
    cout<<"completed in: "<< time.pop() <<" seconds"<<'\n';
    
    
    string str = "Rom. Tush, thou art deceiv'd. ";
    find(str)
    cout<<"BinomialQueue search for" << str << "in RomeoAndJulietx100 " << '\n';
    cout<<"completed in: "<< time.pop() <<" seconds"<<'\n';
    
    cout<<"LeftishHeap search for" << str << "in RomeoAndJulietx100 " << '\n';
    cout<<"completed in: "<< time.pop() <<" seconds"<<'\n';
    
    cout<<"Treap search for" << str << "in RomeoAndJulietx100 " << '\n';
    cout<<"completed in: "<< time.pop() <<" seconds"<<'\n';
    
    cout<<"RedBlackTree search for" << str << "in RomeoAndJulietx100 " << '\n';
    cout<<"completed in: "<< time.pop() <<" seconds"<<'\n';
    
    cout<<"Vector search for" << str << "in RomeoAndJulietx100 " << '\n';
    cout<<"completed in: "<< time.pop() <<" seconds"<<'\n';
    
    string str = "THE END";
    find(str);
    cout<<"BinomialQueue search for" << str << "in RomeoAndJulietx100 " << '\n';
    cout<<"completed in: "<< time.pop() <<" seconds"<<'\n';
    
    cout<<"LeftishHeap search for" << str << "in RomeoAndJulietx100 " << '\n';
    cout<<"completed in: "<< time.pop() <<" seconds"<<'\n';
    
    cout<<"Treap search for" << str << "in RomeoAndJulietx100 " << '\n';
    cout<<"completed in: "<< time.pop() <<" seconds"<<'\n';
    
    cout<<"RedBlackTree search for" << str << "in RomeoAndJulietx100 " << '\n';
    cout<<"completed in: "<< time.pop() <<" seconds"<<'\n';
    
    cout<<"Vector search for" << str << "in RomeoAndJulietx100 " << '\n';
    cout<<"completed in: "<< time.pop() <<" seconds"<<'\n';
}

