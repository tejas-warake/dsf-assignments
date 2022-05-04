//      Name: Tejas Shekhar Warake
//      Batch: C3   Roll No: 233059
//      PRN No: 22020218


#include <iostream>
using namespace std;

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};


Node *Insert(Node *root, int data)
{
    if (root == NULL)
    {
        root = new Node();
        root->data = data;
        root->left = root->right = NULL;
    }
    else if (data <= root->data)
        root->left = Insert(root->left, data);
    else
        root->right = Insert(root->right, data);
    return root;
}


Node *FindMin(Node *root)
{
    while (root->left != NULL)
        root = root->left;
    return root;
}

Node *Delete(struct Node *root, int data)
{
    if (root == NULL)
        return root;
    else if (data < root->data)
        root->left = Delete(root->left, data);
    else if (data > root->data)
        root->right = Delete(root->right, data);
    else
    {
        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            root = NULL;
        }
        else if (root->left == NULL)
        {
            Node *temp = root;
            root = root->right;
            delete temp;
        }
        else if (root->right == NULL)
        {
            Node *temp = root;
            root = root->left;
            delete temp;
        }
        else
        {
            Node *temp = FindMin(root->right);
            root->data = temp->data;
            root->right = Delete(root->right, temp->data);
        }
    }
    return root;
}


void Inorder(Node *root)
{
    if (root == NULL)
        return;

    Inorder(root->left);
    cout << root->data << " ";
    Inorder(root->right);
}


Node *Update(Node *root, int data, int val)
{
    root = Delete(root, data);
    root = Insert(root, val);
    return root;
}


int main()
{
    Node *root = NULL;
    int data;
    int ch;
    
    do {
        cout<<"\n1.Insert\n2.Update\n3.Delete\n4.Display(Inorder)\n5.Exit\n";
        cout<<"Enter you choice: ";
        cin>>ch;
        switch(ch) {
        case 1:
            cout<<"\nEnter data: ";
            cin>>data;
            root = Insert(root, data);
            break;
        case 2:
            cout<<"\nEnter older data: ";
            cin>>data;
            cout<<"Enter newer data: ";
            int val;
            cin>>val;
            root = Update(root, data, val);
            break;
        case 3:
            cout<<"\nEnter data to delete: ";
            cin>>data;
            root = Delete(root, data);
            break;
        case 4:
            Inorder(root);
            cout<<"\n";
            break;
        case 5:
            exit(0);
        }

    }while(ch < 5);
    cout << "\n";
}
