#ifndef TREE_H
#define TREE_H


#include <iostream>
using namespace std;

class TreeNode{
    public:
        int value;
        string c;
        string enc;
        TreeNode * left;
        TreeNode * right;
        TreeNode(){
            value = 0;
            left = nullptr;
            right = nullptr;
        }
};

class AVL_Tree{
    
    public:
    TreeNode * root;

    AVL_Tree(){
        root = nullptr;
    }

    bool isempty(){ return root == nullptr;}

    int height(TreeNode * n){
        if(n == nullptr){
            return -1;
        }

        else{
            int l_height = height(n->left);
            int r_height = height(n->right);
            
            if(l_height > r_height){
                return l_height + 1;                
            }
            else{
                return r_height + 1;
            }
        }
    }

    int getBalancedFactor(TreeNode * n){
        if (n == nullptr){
            return -1;
        }
        else{
            return height(n->left) - height(n->right);
        }
    }

    TreeNode * rightRotate(TreeNode * y){
        TreeNode * x = y -> left;
        TreeNode * T2 = x -> right;

        x->right = y;
        y->left = T2;

        return x;
    }

    TreeNode * leftRotate(TreeNode * x){
        TreeNode * y = x -> right;
        TreeNode * T2 = y -> left;

        y -> left = x;
        x -> right = T2;

        return y;

    }

    void print(TreeNode * r){
        if(r == nullptr){
            return; 
        }

        else{
            print(r->left);
            cout << r->c << " => " << r->enc << " " << r->value << endl;
            print(r->right);
        }
    }

    TreeNode * insert(TreeNode * r, TreeNode * new_node){
        if( r == nullptr){
            r = new_node;
            return r;
        }

        if(new_node -> value >= r -> value){
            r->right = insert(r->right, new_node); 
        }

        else if(new_node -> value < r -> value){
            r->left = insert(r->left, new_node); 
        }
        else{
            return r;
        }

        int bf = getBalancedFactor(r);

        if (bf > 1 && new_node -> value < r -> left -> value){
            return rightRotate(r);
        }

        if (bf < -1 && new_node -> value > r -> right -> value){
            return leftRotate(r);
        }

        if (bf > 1 && new_node -> value > r -> left -> value){
            r -> left = leftRotate(r-> left);
            return rightRotate(r);
        }
        if (bf < -1 && new_node -> value > r -> right -> value){
            r -> right = rightRotate(r -> right);
            return leftRotate(r);
        }

        return r;
    }
    TreeNode * minValueNode (TreeNode * node) {
        TreeNode * current = node;
        while (current -> left != nullptr) {
            current = current -> left;
        }
        return current;
    }
    TreeNode * deleteNode(TreeNode * r, int v){
        if (r == nullptr){
            return nullptr;
        }

        else if (v < r -> value){
            r -> left = deleteNode(r -> left, v);
        }

        else if (v > r -> value){
            r -> right = deleteNode(r -> right, v);
        }

        else{
            if( r -> left == nullptr) {
                TreeNode * temp = r -> right;
                delete r;
                return temp;
            }
            else if( r -> right == nullptr) {
                TreeNode * temp = r -> left;
                delete r;
                return temp;
            }
            else{
                TreeNode * temp = minValueNode(r -> right);
                r -> value = temp -> value;
                r -> right = deleteNode(r -> right, temp -> value);
            }

            int bf = getBalancedFactor(r);

            // LeftLeft
            if (bf == 2 && getBalancedFactor(r -> left) >= 0)
            return rightRotate(r);

            // LeftRight
            if (bf == 2 && getBalancedFactor(r -> left) == -1) {
            r -> left = leftRotate(r -> left); 
            return rightRotate(r);
            }

            // RightRight
            if (bf == -2 && getBalancedFactor(r -> right) <= 0){
            return leftRotate(r);
            }

            // RightLeft
            if (bf == -2 && getBalancedFactor(r -> right) == 1) {
            r -> right = rightRotate(r -> right);
            return leftRotate(r);
            }
            return r;
            

        }
        return r;
    };
};
#endif