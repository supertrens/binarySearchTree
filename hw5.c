/*This homework is to practice insertion and deletion 
 *in Binary search tree
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LIMIT 256

//Bst stands for Binary Search Tree Node
struct BstNode{
    int data;
    struct BstNode *leftChild;
    struct BstNode *rightChild;
};

//will keep track of the size of the input without comma
 int count = 0 ;


//check if the data is in the tree
bool SearchElement(struct BstNode* rootPointer , int data){
    if(rootPointer == NULL) 
        return false;
    else if(rootPointer->data == data) 
        return true;
    else if(data <= rootPointer->data)
        return SearchElement(rootPointer->leftChild , data);
    else return SearchElement(rootPointer->rightChild , data);
}

// function that retrieves the level count of your tree
int getLevelCount(struct BstNode *node)
{
    if (node == NULL)
    {
        return 0;
    }
    int leftMaxLevel = 1 + getLevelCount(node->leftChild);
    int rightMaxLevel = 1 + getLevelCount(node->rightChild);
    if (leftMaxLevel > rightMaxLevel)
    {
        return leftMaxLevel;
    }
    else
    {
        return rightMaxLevel;
    }
}

/**********
 * I was able to print the bst  credit to this thread
 * https://stackoverflow.com/questions/37062169/how-to-print-elements-from-binary-tree-by-level-in-c
 */
// function that prints a specific level of the tree:
void printLevel(struct BstNode* node, int level)
{
    if (node != NULL && level == 0)
    {
        printf("%d\t", node->data);
    }   
    else if (node != NULL)
    {
        printLevel(node->leftChild, level - 1);
        printLevel(node->rightChild, level - 1);
    } else{
        printf("*\t");
    }
}

//print every level of your tree (starting by the root node):
void printElements(struct BstNode *node)
{
    int i;
    int levelCount = getLevelCount(node);
    for (i = 0; i < levelCount; i++)
    {
        printLevel(node, i);
        printf("\n");
    }
}


//function to allocate space to new node
struct BstNode* createNewNode(int data){
    struct BstNode *newNode;
    newNode = (struct BstNode*)malloc(sizeof(struct BstNode));

    newNode->data = data;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    return newNode;
}


//function to add element to the root 
//and also keep track of the left and right siblings pointers
struct BstNode* InsertElement (struct BstNode *rootPointer , int data){
    

    // if the tree or substree is empty we create the first node
    if(rootPointer == NULL){        
        rootPointer = createNewNode(data);  
    }
    else if( data <= rootPointer->data){
        rootPointer->leftChild = InsertElement(rootPointer->leftChild , data);
    }
    else{
       
        rootPointer->rightChild = InsertElement(rootPointer->rightChild , data);

    }
    return rootPointer; 
}

struct BstNode * minValueNode(struct BstNode* node)
{
    struct BstNode* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->leftChild != NULL)
        current = current->leftChild;
 
    return current;
}

/* Given a binary search tree and a key, this function deletes the key
   and returns the new root */
struct BstNode* deleteNode(struct BstNode* rootPointer, int data)
{
    // base case
    if (rootPointer == NULL) return rootPointer;
 
    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (data < rootPointer->data)
        rootPointer->leftChild = deleteNode(rootPointer->leftChild, data);
 
    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (data > rootPointer->data)
        rootPointer->rightChild = deleteNode(rootPointer->rightChild, data);
 
    // if key is same as root's key, then This is the node
    // to be deleted
    else
    {
        // node with only one child or no child
        if (rootPointer->leftChild == NULL)
        {
            struct BstNode *temp = rootPointer->rightChild;
            free(rootPointer);
            return temp;
        }
        else if (rootPointer->rightChild == NULL)
        {
            struct BstNode *temp = rootPointer->leftChild;
            free(rootPointer);
            return temp;
        }
 
        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        struct BstNode* temp = minValueNode(rootPointer->rightChild);
 
        // Copy the inorder successor's content to this node
        rootPointer->data = temp->data;
 
        // Delete the inorder successor
        rootPointer->rightChild = deleteNode(rootPointer->rightChild, temp->data);
    }
    return rootPointer;
}

int* parseInputString(char * searchTreeInput){
 
    static int numArray[30];
    int num;

    const char *valueCopy = searchTreeInput;
    do {
        //Scans valueCopy for the occurrence of any comma,
        // returning the number of characters of str1 
        //read before this first occurrence.
        size_t field_len = strcspn(valueCopy,",");
        sscanf(valueCopy,"%d,",&num);
        numArray[count] = num;    
    
        valueCopy += field_len;
        count++;
    } while (*valueCopy++); 

    return numArray; 
}



int main(){

    struct BstNode *rootPointer , *head = NULL;
    
    //the program will store the element from stdin here
    // char searchTreeInput[MAX_LIMIT];
    char searchTreeInput[MAX_LIMIT];
    int data , i;
    int* numArray;


    printf("Please type in the data for the tree\n");
    fgets(searchTreeInput , MAX_LIMIT , stdin);  
    
    //I will get a pointer to all the value without comma
    numArray = parseInputString(searchTreeInput); 
    
    //calling insertElement for each of the value of the user input
    printf("Create Binary search tree \n");
    for(i = 0 ; i < count ; i ++){
        //take the value numArr[i];
        data = *(numArray+i);
        rootPointer = InsertElement(rootPointer , data);

        //keep the head adress for printing
        if( i = 0)
            head = rootPointer;
        
    }
    printf("\n");

    printElements(head);
    printf("\n");
    
    char myOption;
    
    int numberToDelete;
    bool stop = false;
    printf("Delete element? (Y/N): ");
    while(!stop){
        
        
        scanf("%c" , &myOption);
        fflush(stdin);

        if(myOption=='y' || myOption == 'Y'){
            printf("Choice element: ");
                scanf("%d", &numberToDelete);
                if(SearchElement(rootPointer , numberToDelete)){
                    //if the element exist in the BST , I perform the search
                    deleteNode(rootPointer, numberToDelete);
                    printf("New Binary search tres\n\n");
                    //and print the new BST
                    printElements(head);
                }
                else 
                    printf(" %d is not int the Tree\n\n" , numberToDelete);
                printf("Delete element? (Y/N): ");
        }
        if(myOption == 'n' || myOption =='N') 
            stop = true;

    }  
    printf("\n");
   
    return 0;
}