/*
 * Name: Naveen Mukundan Ravindran 
 * WSU: F496M359
 * Advanced Analysis of Algorithms
 * Programming Assignment
 * Description: This program can add nodes to Binary Search Tree, delete nodes to Binary Search tree and do more
operations. The program can take both positive and negative values as inputs. This program have count for all the 
nodes (how many times they occur in the tree). The program terminates when there are no successor or
predecessor value for a node.
*/


#include <iostream>
using namespace std;

//Building a BST by structure tree

struct tree
{
    int key,count,depth;
    struct tree *left,*right;
};

//Inserting a node in the tree. The function would not add duplicate nodes. But the count of how many times the 
//node appears in the tree is stored.

struct tree *insert(struct tree *root,int value)
{
    if(root==NULL)
    {
        root=(struct tree *)malloc(sizeof(struct tree));
        root->key=value;
        root->count=1;
        root->left=NULL;
        root->right=NULL;
        return root;
    }
    //Adding the count when found a duplicate node
    else if (value == root->key) 
    { 
        (root->count)++; 
        return root; 
    } 
    else
    {
        //Insert in right substree
        if(root->key < value)
            root->right=insert(root->right,value);
        else
        {
        //Insert in left subtree    
            if(root->key > value)
                root->left=insert(root->left,value);
        }    
    }
    return root;
}

//Deleting a node from tree
struct tree *deletion(struct tree *root,int value)
{
    if(root == NULL)
        return root;
    
    if(root->key < value)
    {
        //The node to be deleted is in right subtree
        root->right=deletion(root->right,value);
        return root;        
    }
    
    else if(root->key > value)
    {
        //The node to be deleted is in the left subtree
        root->left=deletion(root->left,value);
        return root;
    }
    
    else
    {
        //Decreasing the count of deleted node
        if (root->count > 1) 
        { 
               (root->count)--; 
               return root; 
        } 
            
        if(root->left == NULL)
        {
            struct tree *temp=root->right;
            delete root;
            return temp;
        }
     
        else if(root->right == NULL)
        {
            struct tree *temp=root->left;
            delete root;
            return temp;
        }
        
        //Finding the sucessor
        else
        {
            struct tree *succparent=root->right;
            struct tree *succ=root->right;
            while(succ->left != NULL)
            {
                succparent=succ;
                succ=succ->left;
            }
            succparent->left=succ->right;
            root->key=succ->key;
            delete succ;
            return root; 
        }
    }
    
}

//Minimum Value in the tree
struct tree *minimumval(struct tree *root)
{
    struct tree *current=root;
    while(current->left !=NULL)
        current=current->left;
    return current;
}

//Maximum Value in the tree
struct tree *maximumval(struct tree *root)
{
   struct tree *current=root;
    while(current->right !=NULL)
        current=current->right;
    return current;
}

//Inorder Traversal
void inorder(struct tree *root)
{
    if(root != NULL)
    {
        inorder(root->left);
        cout<<"\t"<<root->key<<"("<<root->count<<")";
        inorder(root->right);
    }
    return;
}

//Postorder Traversal
void postorder(struct tree *root)
{
    if(root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        cout<<"\t"<<root->key<<"("<<root->count<<")";
    }
    return;
}

//Preorder Traversal
void preorder(struct tree *root)
{
    if(root != NULL)
    { 
        cout<<"\t"<<root->key<<"("<<root->count<<")";
        preorder(root->left);
        preorder(root->right);
    }
    return;
}

//To find successor of a node
struct tree *successor(struct tree *root,struct tree *tofind)
{
    //Find minimum value in right subtree for successor
    
    if(tofind->right != NULL)
        return minimumval(tofind->right);
    
    struct tree *succ=NULL;
    while (root != NULL) 
    { 
        if (tofind->key < root->key) 
        { 
            succ = root; 
            root = root->left; 
        } 
        else if (tofind->key > root->key) 
            root = root->right; 
        else
            break; 
    } 
     return succ; 
    
}

struct tree *predecessor(struct tree *root,struct tree *tofind)
{
    //Find maximum value in left subtree
    
    if(tofind->left != NULL)
        return maximumval(tofind->left);
    
    struct tree *pred=NULL;
    while (root != NULL) 
    { 
        if (tofind->key < root->key) 
        { 
            pred = root; 
            root = root->left; 
        } 
        else if (tofind->key > root->key) 
            root = root->right; 
        else
            break; 
    } 
     return pred; 
    
}

//Searching a node in the tree
struct tree *search(struct tree *root, int value) 
{ 
    if (root == NULL || root->key == value) 
       return root; 
    
    //Search in right subtree
    
    if (root->key < value) 
       return search(root->right, value); 
    
    //Search in left subtree
    
    return search(root->left, value); 
} 

//Deleting all the nodes in the tree
struct tree *deleteall(struct tree *root)
{
    if(root == NULL)
        return root;
    
    deleteall(root->left);
    deleteall(root->right);
    delete root;
}

//Finding depth of a node
int depth(struct tree *root,int value, int level)
{
     
    if(root == NULL)
        return 0;
    
    if(root->key == value)
        return level;
    int temp = depth(root->left,value,level+1); 
    if(temp != 0)
        return temp;
    
    temp=depth(root->right,value,level+1);
    return temp;
}

int main()
{
        int choice=0,value=0,value1=0;
        struct tree *root=NULL,*searchh=NULL,*position=NULL;
    do
    {
        //Menu for selecting the operation to perform
        cout<<"\n\n";
        cout<<"\n Binary Search Tree !!!!";
        cout<<"\n [1] Insertion ";
        cout<<"\n [2] Deletion ";
        cout<<"\n [3] Search ";
        cout<<"\n [4] Minimum Value ";
        cout<<"\n [5] Maximum Value ";
        cout<<"\n [6] Successor ";
        cout<<"\n [7] Predecessor ";
        cout<<"\n [8] Traversals ";
        cout<<"\n [9] Delete All ";
        cout<<"\n [0] Exit ";
        
        cout<<"\n Enter the choice: ";
        cin>>choice;
        
        switch(choice)
        {
            case 1:
                    cout<<"\n Insertion..!";
                    cout<<"\n Enter the element to be inserted: ";
                    cin>>value;
                    root=insert(root,value);
                    root->depth=depth(root,value,0);
                    cout<<"\n Depth of node "<<value<<" is: "<<root->depth;
                    break;
            case 2: 
                    cout<<"\n Deletion..!";
                    cout<<"\n Enter the element to be deleted: ";
                    cin>>value;
                    if(search(root,value) == NULL)
                        cout<<"\n Deletion Unsuccessful. Value does not exists in the tree!";
                    else
                    {
                        root->depth=depth(root,value,0);
                        cout<<"\n Depth of node "<<value<<" is: "<<root->depth;
                        root=deletion(root,value);
                        cout<<"\n Inorder Traversal: ";
                        inorder(root);
                    }
                    break;
            case 3:
                    cout<<"\n Search..!";
                    cout<<"\n Enter the element to be searched: ";
                    cin>>value;
                    searchh=search(root,value);
                    if(searchh == NULL)
                        cout<<"\n Key not found!";
                    else
                    {
                        root->depth=depth(root,value,0);
                        cout<<"\n"<<" Key "<<searchh->key<<" Found!";
                        cout<<"\n Depth of node "<<value<<" is: "<<root->depth;
                    }
                    break;
            case 4:
                    cout<<"\n Minimum Value..!";
                    if(root == NULL)
                        cout<<"\n No minimum values in empty tree";
                    else
                    {
                        value=minimumval(root)->key;
                        root->depth=depth(root,value,0);
                        cout<<"\n Smallest value in the tree: "<<value;
                        cout<<"\n Depth of node "<<value<<" is: "<<root->depth;
                    }
                    break;
            case 5:
                    cout<<"\n Maximum Value..!";
                    if(root == NULL)
                        cout<<"\n No maximum values in empty tree";
                    else
                    {
                        value=maximumval(root)->key;
                        root->depth=depth(root,value,0);
                        cout<<"\n Largest value in the tree: "<<value;
                        cout<<"\n Depth of node "<<value<<" is: "<<root->depth;
                    }
                        
                    break;
            case 6:
                    cout<<"\n Successor..!";
                    cout<<"\n Enter the node to find successor: ";
                    cin>>value1;
                    position=search(root,value1);
                    if(position == NULL)
                        cout<<"\n No Successor values in tree / empty tree";
                    else
                    {
                        value=successor(root,position)->key;
                        root->depth=depth(root,value,0);
                        cout<<"\n Successor of "<<value1<<" is: "<<value;
                        cout<<"\n Depth of node "<<value<<" is: "<<root->depth;
                       
                    }
                        break;
            case 7:
                    cout<<"\n Predecessor..!";
                    cout<<"\n Enter the node to find predecessor: ";
                    cin>>value1;
                    position=search(root,value1);
                    if(position == NULL)
                        cout<<"\n No Predecessor values in tree / empty tree";
                    else
                    {
                        value=predecessor(root,position)->key;
                        root->depth=depth(root,value,0);
                        cout<<"\n Predecessor of "<<value1<<" is: "<<value;
                        cout<<"\n Depth of node "<<value<<" is: "<<root->depth;
                    }
                        
                    break;
            case 8:
                    cout<<"\n Traversals..!";
                    cout<<"\n Inorder: ";
                    inorder(root);
                    cout<<"\n Preorder: ";
                    preorder(root);
                    cout<<"\n Postorder: ";
                    postorder(root);
                    break;
            case 9:
                    cout<<"\n Delete All..!";
                    if(deleteall(root) == NULL)
                        cout<<"\n Tree is Empty";
                    root=NULL;
                    break;
            case 0:
                    cout<<"\n Exiting..!";
                    break;
            default:
                    cout<<"\n Invalid Choice!";
                    break;
        }
        
    }while(choice!=0);

    return 0;
}


