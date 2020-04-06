#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct n{
	char letter;
	int freq;
	struct n * next;
	struct n * left;
	struct n * right;
};
typedef struct n node;

//	Parameter: Head of linked list
void printList(node * head);

//	Parameters: Head * of linked list, string to be searched | Returns the adress of node which includes the string, if string is not found returns NULL.
node * searchList(node * head, char arg);

//	Parameter: String to be converted to linked list | Determines every letter and it's frequency in the text and stores them in a linked list. Returns head * of the list.
node * createList(char text[]);

//	Parameters: Head * of linked list, element to be inserted to head of the list | Unlinks the element from the list and inserts it to the head. Returns head * of the list.
node * insertFront(node * head, node * element);

//	Parameters: Head * of linked list, place to be inserted after, element to be inserted | Unlinks the element (3rd arg.) from the list and inserts it to place (2nd arg.).
void insertIn(node * head, node * place, node * element);

//	Parameter: Head * of linked list | Sorts the linked list in ascending order by using insertion sort algorithm.
node * sortList(node * head);

//	Parameter: Head * of linked list | Converts the linked list to Huffman Tree. Returns root of the tree.
node * createHuffman(node * head);

//	Parameter: Root of binary tree | Returns the height of a binary tree.
int treeHeight(node * root);

//	Parameters: Root of binary tree, level to be printed | Prints the determined level (2nd arg.) of the tree  
void printLevel(node * root, int level);

//	Parameter: Root of binary tree | Prints the binary tree by using treeHeight and printLevel functions.
void printTree(node * root);

int main(){
	char text[500];
	int i;
	node * head, * root;
	
	printf("Please enter the text that you would like to compress.\n");
	gets(text);
	
	head = createList(text);
	printf("\nGIVEN LIST:\n");
	printList(head);
	
	head = sortList(head);
	printf("\n\nLIST (SORTED):\n");
	printList(head);
	
	root = createHuffman(head);
	printf("\n\nHUFFMAN TREE:\n");
	printTree(root);
	
	free(root);

	return 0;
}

void printList(node * head){	
	node * tmp;
	tmp = head;
	while(tmp != NULL){
		printf("\nLetter: %c\nFrequency: %d\n",tmp->letter, tmp->freq);
		tmp = tmp->next;
	}
}

node * searchList(node * head, char arg){ 	
	node * tmp;
	tmp = head;
	while(tmp!=NULL){
		if(tmp->letter == arg)
			return tmp;
		tmp=tmp->next;
	}
	return NULL;
}

node * createList(char text[]){
	int i, length;
	node *head, *tmp;
	head = (node*)malloc(sizeof(node));
	head->letter = text[0];
	head->freq = 1;
	head->left = NULL;
	head->right = NULL;
	head->next = NULL;
	tmp = head;	
	length = strlen(text);	
	for(i=1; i<length; i++){
		if(searchList(head, text[i]) == NULL){
		tmp->next = (node*)malloc(sizeof(node));
		tmp = tmp->next;
		tmp->left = NULL;
		tmp->right = NULL;
		tmp->next = NULL;
		tmp->freq = 1;
		tmp->letter = text[i];
		}
		else{
			searchList(head, text[i])->freq++;
		}
	}
	return head;
}

node * insertFront(node * head, node * element){
	node * tmp;
	tmp = head;
	while(tmp->next != element){
		tmp = tmp->next;
	}
	tmp->next = element->next;
	element->next = head;
	head = element;
	return head;
}

void insertIn(node * head, node * place, node * element){
	node * tmp;
	tmp = head;
	while(tmp->next != element){
		tmp = tmp->next;
	}
	tmp->next = element->next;
	tmp = head;
	while(tmp->next != place){
		tmp = tmp->next;
	}
	tmp->next = element;
	element->next = place;
}

node * sortList(node * head){
	node *tmp, *tmp2;
	tmp = head;
	tmp2 = tmp->next;
	while(tmp2 != NULL){
		//	Finding the place to insert:
		while(tmp->next != tmp2 && tmp->freq <= tmp2->freq){
			tmp = tmp->next;
		}
		if(tmp->freq > tmp2->freq){
			if(tmp == head)
				head = insertFront(head, tmp2);
			else
				insertIn(head, tmp, tmp2);
		}
		tmp = head;
		tmp2 = tmp2->next;
	}
	return head;
}

node * createHuffman(node * head){
	node *tmp, *tmp2, *interval;
	//	Loops until there are 1 or 2 nodes exist in first level.
	while(head->next->next != NULL && head->next != NULL){
		tmp = head;
		tmp2 = head->next;
		head = tmp2->next;
		tmp->next = NULL;
		tmp2->next = NULL;
		interval = (node *)malloc(sizeof(node));
		interval->freq = tmp->freq + tmp2->freq;
		interval->left = tmp;
		interval->right = tmp2;
		interval->letter = NULL;
		//	Add to front:
		if(interval->freq < head->freq){
			interval->next = head;
			head = interval;
		}
		//	Add to tail or middle.
		else{
			node * tmp3 = head;
			//	Finding place to add:
			while(tmp3->next != NULL && tmp3->next->freq <= interval->freq){
				tmp3 = tmp3->next;
			}
			interval->next = tmp3->next;
			tmp3->next = interval;
		}
	}
	//	If there are 2 nodes in first level, links them in one parent root.
	if(head->next->next == NULL){
		interval = (node*)malloc(sizeof(node));
		interval->freq = head->freq + head->next->freq;
		interval->next = NULL;
		interval->letter = NULL;
		interval->left = head;
		interval->right = head->next;
		return interval;
	}
	else{
		return head;
	}	
}

int treeHeight(node * root){
	int left, right;
	if (root == NULL)
        return 0;
    else {
        left = treeHeight(root->left);
        right = treeHeight(root->right);
        if (left >= right)
            return left + 1;
        else
            return right + 1;
    }
}

void printLevel(node * root, int level){ 
    if (root == NULL){
    	printf(" ");
		return;
	}
    if (level == 1){
    	printf("%d", root->freq);
		if(root->letter != NULL)
				printf("%c", root->letter);
		printf(" ");
	}
    else if (level > 1) { 
        printLevel(root->left, level-1); 
        printLevel(root->right, level-1); 
    } 
}

void printTree(node * root){ 
    int i, h;
	h = treeHeight(root);  
    for (i=1; i<=h; i++) 
    { 
        printLevel(root, i); 
        printf("\n"); 
    } 
}
