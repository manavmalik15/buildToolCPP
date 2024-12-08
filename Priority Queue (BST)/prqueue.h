/*-------------------------------------------
 Project 4 - Priority Queue (BST)
 Have created a templated binary search tree
 Designed a particular implementation of a priority queue
 Implemented multiple traversals through a binary search tree
 
System: xcode
------------------------------------------- */

#pragma once

#include <iostream>  // For debugging
#include <sstream>   // For as_string

using namespace std;

template <typename T>
class prqueue {
   private:
    struct NODE {
        int priority;
        T value;
        NODE* parent;
        NODE* left;
        NODE* right;
        NODE* link;  
    };

    NODE* root;
    size_t sz;

    // Utility pointers for begin and next.
    NODE* curr;
    NODE* temp; 

   public:
   
    /// Creates an empty `prqueue`.
    ///
    /// Runs in O(1).
    prqueue() : root(nullptr), sz(0) {}

    /// Empties the `prqueue`, freeing all memory it controls.
    ///
    void clearHelper(NODE*& node) {
        if (node != nullptr) {
            clearHelper(node->left);
            clearHelper(node->right);
            clearHelper(node->link);
            delete node;
            node = nullptr;
        }
    }
    
    /// Runs in O(N), where N is the number of values.
    void clear() {
        clearHelper(root);
        sz=0;
    }


    /// Destructor, cleans up all memory associated with `prqueue`.
     /// Runs in O(N), where N is the number of values.
    ~prqueue() {
        clear();
    }

    /// Adds `value` to the `prqueue` with the given `priority`.
    ///
    /// Uses the priority to determine the location in the underlying tree.
    ///
    ///
    NODE* enqueueHelper(NODE* node, T value, int priority, NODE* parent ) {
        if (node == nullptr) {
            node = new NODE{priority, value, parent, nullptr, nullptr, nullptr};
            sz++;
        } else if (priority < node->priority) {
            node->left = enqueueHelper(node->left, value, priority, node);
        } else if (priority > node->priority){
            node->right = enqueueHelper(node->right, value, priority, node);
        } else {
            node->link = enqueueHelper(node->link, value, priority, node);
        }
        return node;
    }

    /// Runs in O(H + M), where H is the height of the tree, and M is
    /// the number of duplicate priorities.
    void enqueue(T value, int priority) {
        root = enqueueHelper(root, value, priority, nullptr);
    }
    
    
    /// Returns the value with the smallest priority in the `prqueue`, but does
    /// not modify the `prqueue`.
    ///
    /// If the `prqueue` is empty, returns the default value for `T`.
    ///
    ///
    T peekHelper(NODE* node) const {
            if (node == nullptr) {
                return T{};
            }
            if (node->left == nullptr) {
                return node->value;
            }
            return peekHelper(node->left);
        }
    /// Runs in O(H + M), where H is the height of the tree, and M is
    /// the number of duplicate priorities.
    T peek() const {
            return peekHelper(root);
        }
    
    
    /// Returns the value with the smallest priority in the `prqueue` and
    /// removes it from the `prqueue`.
    ///

    NODE* dequeueHelper(NODE*& node) {
        
        if (node == nullptr) {
                return nullptr;
        };
        
        if (node->left == nullptr) {
            
                if (node->link == nullptr){
                    NODE* temp = node;
                    if (node->right != nullptr){
                        node->right->parent = node->parent;
                    };
                    node = node->right;
                    delete temp;
                    sz--;
                    
                }else{
                    node->link->right = node->right;
                    if (node->right != nullptr){
                        node->right->parent = node->link;
                    };
                     
                    
                    node->link->parent = node->parent;
                    
                    
                    NODE* temp = node;
                    node = node->link;
                    delete temp;
                    sz--;
                };
            
           } else {
               dequeueHelper(node->left);
           };
           return node;

        
    };

    
    /// If the `prqueue` is empty, returns the default value for `T`.
    ///
    /// Runs in O(H + M), where H is the height of the tree, and M is
    /// the number of duplicate priorities.
    T dequeue() {
        T value = peek();
        root = dequeueHelper(root);
        return value;
    }

    /// Returns the number of elements in the `prqueue`.
    ///
    /// Runs in O(1).
    size_t size() const {
        return sz;
    }

    void asStringHelper(NODE* node, ostringstream& oss) const {
           if (node != nullptr) {
               
               
               asStringHelper(node->left, oss);
               oss << node->priority << " value: " << node->value << endl;
               asStringHelper(node->link, oss);
               asStringHelper(node->right, oss);
           }
       }
    
    /// Converts the `prqueue` to a string representation, with the values
    /// in-order by priority.
    ///
    /// Example:
    ///
    /// ```c++
    /// prqueue<string> names;
    /// names.enqueue("Gwen", 3);
    /// names.enqueue("Jen", 2);
    /// names.enqueue("Ben", 1);
    /// names.enqueue("Sven", 2);
    /// ```
    ///
    /// Calling `names.as_string()` would return the following multi-line
    /// string:
    ///
    /// ```text
    /// 1 value: Ben
    /// 2 value: Jen
    /// 2 value: Sven
    /// 3 value: Gwen
    /// ```
    ///
    /// Runs in O(N), where N is the number of values.
    string as_string() const {
        ostringstream oss;
        asStringHelper(root, oss);
        return oss.str();
    };
    
    
    /// Copy constructor.
    ///
    // Private helper function to copy the tree
    /// Copies the value-priority pairs from the provided `prqueue`.
    
    void copyTree(NODE* node) {
    if (node != nullptr) {
        enqueue(node->value, node->priority);
        
        copyTree(node->left);
        copyTree(node->link);
        copyTree(node->right);
        
    }
}

    /// The internal tree structure must be copied exactly.
    ///
    /// Runs in O(N), where N is the number of values in `other`.
    prqueue(const prqueue& other) {
        if (root == other.root){
            return;
        };
        root = nullptr;
        sz = 0;
        copyTree(other.root);
        // TODO_STUDENT
    }

    /// Assignment operator; `operator=`.
    ///
    /// Clears `this` tree, and copies the value-priority pairs from the
    /// provided `prqueue`. The internal tree structure must be copied exactly.
    ///
    /// Runs in O(N + O), where N is the number of values in `this`, and O is
    /// the number of values in `other`.
    prqueue& operator=(const prqueue& other) {
        if (root == other.root){
            return *this;
        };
        
        clear();

        copyTree(other.root);
        return *this;
         
    };
    

    /// Resets internal state for an iterative inorder traversal.
    ///
    /// See `next` for usage details.
    ///
    /// O(H), where H is the maximum height of the tree.

    void begin() {
        if (root == nullptr){
            curr = nullptr;
            return;
        }
        curr = root;
        
        while (curr && curr->left) {
            curr = curr->left;
        }
    }
    
    /// Uses the internal state to return the next in-order value and priority
    /// by reference, and advances the internal state. Returns true if the
    /// reference parameters were set, and false otherwise.
    ///
    /// Example usage:
    ///
    /// ```c++
    /// pq.begin();
    /// T value;
    /// int priority;
    /// while (pq.next(value, priority)) {
    ///   cout << priority << " value: " << value << endl;
    /// }
    /// ```
    ///
    /// Runs in worst-case O(H + M) or O(H), depending on implementation, where
    /// H is the height of the tree, and M is the number of duplicate
    /// priorities.
    bool next(T& value, int& priority) {
        if (curr == nullptr) {
            return false;
        }
        
        value = curr->value;
        priority = curr->priority;
        
        
        if (curr->link){
            
            curr=curr->link;
            
        }else if (curr->right ) {
            curr = curr->right;
            while (curr->left) {
                curr = curr->left;
            }
        } else if (curr->parent && curr == curr->parent->left ){
            curr = curr->parent;
            
        }else if(curr->parent && curr == curr->parent->right ) {
            
            while(curr->parent && curr == curr->parent->right){
                curr = curr->parent;
            };
            curr = curr->parent;
            
        }else if((curr->parent !=nullptr) && (curr == curr->parent->link) ) {
           
            
            while ((curr->parent !=nullptr) && curr == curr->parent->link){
                curr = curr->parent;
            }
            
            
            if (curr->right) {
                curr = curr->right;
                while (curr->left) {
                    curr = curr->left;
                };
                
            }else if(curr->parent && curr == curr->parent->right ) {
                
                while(curr->parent && curr == curr->parent->right){
                    curr = curr->parent;
                };
                curr = curr->parent;
                
            }else{
                curr = curr->parent;
            };
            
            
        }else{
            curr = curr->parent;
        };
         
        return true;
    }

    
    /// Checks if the contents of `this` and `other` are equivalent.
    ///
    ///
    bool equalsHelper(NODE* a, NODE* b) const {
        if (!a && !b) {
            return true;
        }
        if (!a || !b) {
            return false;
        }
    
        return ((a->value == b->value) && (a->priority == b->priority) && equalsHelper(a->left, b->left) && equalsHelper(a->link, b->link) && equalsHelper(a->right, b->right));
        
    };
    
 
    bool operator==(const prqueue& other) const {
        return equalsHelper(root, other.root);
    }

    void* getRoot() {
        return root;
    }
};
