#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <stack>
#include <map>
using namespace std;

#include "tree.h"
//Structure Which Allows Us to Store Strings and Associated Frequencies
struct probability{
    string c;       //String Symbol
    int freq;       //String Frequency
};

//Recursive Function Which Performs Huffman Encoding in O(logn) time. 
void Huff(int n, set<string> &S, map<string, string>& C, AVL_Tree& T){
    if(n == 1){
        return; 
    }

    else{
        probability p1;        //Stores smallest symbol and associated frequency
        probability p2;        //Stores next smallest symbol and its associated frequency

        probability merged;


        p1.c = T.minValueNode(T.root)->c;     //Returns String of MinValue in the Tree and Assigns it to p1
        p1.freq = T.minValueNode(T.root)->value;
        T.root = T.deleteNode(T.root, p1.freq);//Deletes Smallest From The Tree


        p2.c = T.minValueNode(T.root)->c; //Returns the next smallest freq node in the tree and subsequently deletes it
        p2.freq = T.minValueNode(T.root)->value;
        T.root = T.deleteNode(T.root, p2.freq);

        merged.c = "{" + p1.c + p2.c + "}"; //Merges Both Symbols
        merged.freq = p1.freq + p2.freq;    //Merges their frequencies

        TreeNode * node = new TreeNode;     //New Node Creation of new symbol and string to be inserted
        node->c = merged.c;
        node->value = merged.freq;

        T.root = T.insert(T.root, node);

        Huff(n-1, S, C, T);                //Recursive Call
        string enc_p;

        if(n==2){
            C.insert({p1.c, "0"});         //Assigns 0 to the associated symbol and inserts it into the map
            C.insert({p2.c, "1"});         //Assigns 1 to the associated symbol and inserts it into the map

        }
        //Assuming symbol which is merged already has an assigned encoding we have to assign 
        //Its Associated Encoded Value to its split symbols and concatenate them with either a 0 or 1
        else{
            enc_p = C.at(merged.c) ;
            C.erase(merged.c);

            
            C.insert({p1.c, enc_p + "0"});
            C.insert({p2.c, enc_p + "1"});
        }        
    }
}


int main(){ 
    string word = "aaaaaaaaaaaaaaabbbbbbbbcccccdddddddeeffff";           //Sample Symbol
    
    set<string> symbols; //Set of Symbols
    
    for(int i = 0; i < word.length(); i++){             //Inserting all symbols into the set.
        string letter;
        letter.append(1, word[i]);
        symbols.insert(letter);        

    }
    vector<probability> prob;
    probability temp;

    //Filling the probability Vector with symbols from the set
    for(auto i = symbols.begin(); i != symbols.end(); ++i){ 
        temp.c = *i;
        temp.freq = 0;

        prob.push_back(temp);
    }

    //Finding each symbols probability
    for(int i = 0; i < word.size(); i++){
        for(int j = 0; j < prob.size(); j++){
            if(word[i] == prob[j].c[0]){
                prob[j].freq++;
            }
        }
    }
   
    //Prints out symbol and frequency
    for(int i = 0; i < prob.size(); i++){
        cout << prob[i].c << " - " << prob[i].freq << endl;
    }

    map<string, string> coded; 
    AVL_Tree Tree;
    TreeNode * node;
    

    //Inserting Nodes Into AVL Tree
    for(int i = 0; i < prob.size(); i++){
        node = new TreeNode;
        node->c = prob[i].c;
        node->value = prob[i].freq;
        
        Tree.root = Tree.insert(Tree.root, node);
    }

    //Function Call
    Huff(symbols.size(), symbols, coded, Tree);

    cout << "------------------------------------------" << endl;

    //Printing Out Results
    for(auto i: coded ){
       cout << i.first << " " << i.second << endl;
    }
    
    return 0;
} 