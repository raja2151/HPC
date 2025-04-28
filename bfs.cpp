#include <iostream>
#include <queue>
using namespace std;

// Define the node structure
struct node {
    int data;
    node *left, *right;
    node(int val) {
        data = val;
        left = right = NULL;
    }
};

// Function to insert data into the binary tree
node* insert(node* root, int data) {
    if (root == NULL) {
        return new node(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    return root;
}

// Function to perform BFS (Breadth-First Search) and print the tree level by level
void bfs(node* root) {
    if (root == NULL) {
        cout << "Tree is empty!" << endl;
        return;
    }
    
    queue<node*> q;
    q.push(root);
    
    while (!q.empty()) {
        node* current = q.front();
        q.pop();
        cout << current->data << " ";
        
        if (current->left != NULL) {
            q.push(current->left);
        }
        if (current->right != NULL) {
            q.push(current->right);
        }
    }
    cout << endl;
}

int main() {
    node *root = NULL;
    int data;
    char ans;

    do {
        cout << "\nEnter data => ";
        cin >> data;
        root = insert(root, data);

        cout << "Do you want to insert one more node? (y/n): ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');

    cout << "BFS of the tree: ";
    bfs(root);

    return 0;
}

