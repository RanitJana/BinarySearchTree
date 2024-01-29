#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    Node *left, *right;
    Node(int value) : data(value), left(NULL), right(NULL) {}
};

// insertion
Node *insertIterative(Node *root, int value)
{
    Node *newNode = new Node(value);
    if (!root)
        return newNode;
    Node *prev = NULL, *curr = root;
    while (curr)
    {
        prev = curr;
        if (value > curr->data)
            curr = curr->right;
        else if (value < curr->data)
            curr = curr->left;
        else
        {
            cout << value << " is already present.\n";
            return root;
        }
    }
    if (value > prev->data)
        prev->right = newNode;
    else
        prev->left = newNode;
    return root;
}
Node *insertRec(Node *root, int value)
{
    if (!root)
        return new Node(value);
    if (value > root->data)
        root->right = insertRec(root->right, value);
    else if (value < root->data)
        root->left = insertRec(root->left, value);
    else
    {
        cout << value << " is already present.\n";
    }
    return root;
}

// searching
Node *searchNodeIterative(Node *root, int value)
{
    while (root)
    {
        if (root->data == value)
            break;
        if (value > root->data)
            root = root->right;
        else
            root = root->left;
    }
    return root;
}

Node *searchNodeRec(Node *root, int value)
{
    if (!root)
        return NULL;
    if (value == root->data)
        return root;
    if (value > root->data)
        return searchNodeRec(root->right, value);
    return searchNodeRec(root->left, value);
}
// deletion
Node *singleChild(Node *root, Node *temp, Node *prev)
{
    Node *child = temp->left ? temp->left : temp->right;
    if (prev != NULL)
    {
        if (temp->data < prev->data)
        {
            prev->left = child;
        }
        else
            prev->right = child;
    }
    else
        root = child;
    delete temp;
    return root;
}
Node *doubleChild(Node *root, Node *temp, Node *prev)
{
    Node *store = temp;
    prev = temp;
    temp = temp->right;
    while (temp->left)
    {
        prev = temp;
        temp = temp->left;
    }
    store->data = temp->data;
    return singleChild(root, temp, prev);
}

Node *eraseNodeIterative(Node *root, int target)
{
    if (!root)
        return root;
    Node *temp = root, *prev = NULL;
    while (temp)
    {
        if (target > temp->data)
        {
            prev = temp;
            temp = temp->right;
        }
        else if (target < temp->data)
        {
            prev = temp;
            temp = temp->left;
        }
        else
        {
            if (temp->left == NULL || temp->right == NULL)
                return singleChild(root, temp, prev);
            return doubleChild(temp, temp, prev);
        }
    }
    return root;
}
Node *inorderSuccessor(Node *root)
{
    root = root->right;
    while (root->left)
    {
        root = root->left;
    }
    return root;
}
Node *eraseNodeRec(Node *root, int value)
{
    if (!root)
        return NULL;
    if (value > root->data)
        root->right = eraseNodeRec(root->right, value);
    else if (value < root->data)
        root->left = eraseNodeRec(root->left, value);
    else
    {
        if (root->left && root->right)
        {
            Node *succ = inorderSuccessor(root);
            root->data = succ->data;
            root->right = eraseNodeRec(root->right, root->data);
        }
        else
        {
            Node *child = root->left ? root->left : root->right;
            delete root;
            return child;
        }
    }
    return root;
}

// Traversal
void inorderRec(Node *root)
{
    if (!root)
        return;
    inorderRec(root->left);
    cout << root->data << " ";
    inorderRec(root->right);
}

void inorderIterative(Node *root)
{
    if (!root)
    {
        cout << "Empty tree." << endl;
        return;
    }
    stack<Node *> s;
    while (s.size() || root)
    {
        while (root)
        {
            s.push(root);
            root = root->left;
        }
        root = s.top();
        s.pop();
        cout << root->data << " ";
        root = root->right;
    }
    cout << endl;
}

void preorderRec(Node *root)
{
    if (!root)
        return;
    cout << root->data << " ";
    preorderRec(root->left);
    preorderRec(root->right);
}

void preorderIterative(Node *root)
{
    if (!root)
    {
        cout << "Empty tree." << endl;
        return;
    }
    stack<Node *> s;
    while (!s.empty() || root)
    {
        while (root)
        {
            cout << root->data << " ";
            s.push(root);
            root = root->left;
        }
        root = s.top();
        s.pop();
        root = root->right;
    }
    cout << endl;
}

void postorderRec(Node *root)
{
    if (!root)
        return;
    postorderRec(root->left);
    postorderRec(root->right);
    cout << root->data << " ";
}
void postorderIterative(Node *root)
{
    if (!root)
    {
        cout << "Empty tree." << endl;
        return;
    }
    stack<Node *> s;
    while (root || s.size())
    {
        while (root)
        {
            s.push(root);
            s.push(root);
            root = root->left;
        }
        root = s.top();
        s.pop();
        if (s.size() && s.top() == root)
            root = root->right;
        else
        {
            cout << root->data << " ";
            root = NULL;
        }
    }
    cout << endl;
}
void levelOrderTraversal(Node *root)
{
    if (!root)
        return;
    queue<Node *> q;
    q.push(root);
    while (q.size())
    {
        Node *temp = q.front();
        q.pop();
        cout << temp->data << " ";
        if (temp->left)
            q.push(temp->left);
        if (temp->right)
            q.push(temp->right);
    }
    cout << endl;
}
int main()
{
    Node *root = NULL;
    root = insertRec(root, 5);
    root = insertRec(root, 1);
    root = insertRec(root, 20);
    root = insertRec(root, 2);
    root = insertRec(root, 0);
    postorderIterative(root);
    postorderRec(root);
    return 0;
}