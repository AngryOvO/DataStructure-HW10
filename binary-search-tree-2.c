/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */






int main()
{
	char command;
	int key;
	Node* head = NULL;

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("--------------[201803805]------[���Ͽ�]-------------------------\n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			//printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node) // �ݺ��� ���� ��ȸ
{
	if (node == NULL) // ��Ʈ��尡 ����ִٸ�
	{
		printf("tree is empty!!\n"); // �������� ���
		return;
	}
	Node* n = node; // Ʈ���� ��ȸ�� ����ü ������ ����

	while(1) // ���� ����
	{
		while(n != NULL) // n�� NULL�� �ƴ� �� �ݺ�
		{
			push(n); // ���ÿ� n Ǫ��
			n = n->left; // n�� ���� �ڽ����� �̵�
		}
		n = pop(); // n�� ���� ������ �Ҵ�
		if(n != NULL) // ���ÿ��� �������� �����Ͱ� �����Ѵٸ�
		{
			printf(" [%d] ",n->key); // n�� key�� ���
			n = n->right; // n�� ������ �ڽ����� �̵�
		}
		else
			break;
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr) // �������� ��ȯ�Լ�
{
	if(ptr == NULL) // ��Ʈ�� ����ִ� ��� 
	{
		printf("tree is empty!!\n"); // �������� ��� �� ����
		return;
	}
	Node* n = ptr; // Ʈ���� ��ȸ�� ����ü ������ ����
	enQueue(n); // ť�� ������ ����
	while(1)
	{
		n = deQueue(n); // ť���� �� ������ n�� �Ҵ�
		if(n != NULL) // ť���� �� �����Ͱ� �����ϸ�
		{
			printf(" [%d] ",n->key); // n�� key�� ���
			if(n->left != NULL) // n�� ���� �ڽ��� �����ϸ�
				enQueue(n->left); // ���� �ڽ� ť�� ����
			if(n->right != NULL) // n�� ������ �ڽ��� �����ϸ�
				enQueue(n->right); // ������ �ڽ� ť�� ����
		}
		else
			break;
	}
	
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key) // ��� ���� �Լ�
{
	Node *n = head->left; // Ʈ���� �̵��� ����ü ������
	Node *p = NULL; // ��带 ������ ����ü ������
	Node *c = NULL;

	if(head == NULL) // ����尡 ����ִ°��
	{
		printf("tree is empty!\n"); // Ʈ���� �������
		return 0;
	}

	if(n == NULL) // ��Ʈ��尡 ����ִ� ���
	{
		printf("tree is empty!\n"); // Ʈ���� �������
		return 0;
	}

	while((n!= NULL) && (n->key != key)) // n�� NULL�� �ƴϰ� n�� key���� key���� �ٸ��� �ݺ�
	{
		if(n->key != key) // n�� key���� key���� �ٸ����
		{
			p = n; // p�� n�� ��ġ��

			if(n->key < key) // n�� key������ key���� ū ���
				n = n->right; //n�� n�� ������ �ڽ����� �̵�
			else
				n = n->left; //n�� n�� ���� �ڽ����� �̵�
		}	
	}

	if(n == NULL) // ������ �������� n�� NULL �ΰ��
	{
		printf("no exist key node in tree!\n"); // �Է¹��� key���� �ش��ϴ� ��尡 ����
		return 0;
	}
	

	if((n->left == NULL) && (n->right == NULL)) // ������ �������� n�� ��������ΰ��
	{
		if(p != NULL) // n�� �θ��尡 NULL�� �ƴѰ��
		{
			if(p->left == n) // n�� p�� ���� �ڽ��� ���
				p->left = NULL; // p�� �����ڽ� NULL
			else if(p->right == n) // n�� p�� ������ �ڽ��� ���
				p->right = NULL; // p�� ������ �ڽ� NULL
		}
		else // n�� �θ��尡 NULL�� ��� (n�� ��Ʈ����ΰ��)
			head->left = NULL; // ������� ���� ��尡 NULL
		free(n); // n �Ҵ� ����
		return 1;
	}

	if((n->left == NULL) || (n->right ==NULL)) // ������ �������� n�� �ϳ��� �ڽ��� ���� ���
	{
		if(n->left != NULL) // n�� �����ڽ��� �����ϴ� ���
			c = n->left; // c�� n�� ���� �ڽ�
		else // n�� �����ڽ��� �������� �ʴ°��
			c = n->right; //c�� n�� ������ �ڽ�
		
		if(p != NULL) // n�� �θ��尡 �����ϴ� ���
		{
			if(p->left == n) //p�� ���� �ڽ��� n�� ���
				p->left = c; //p�� �����ڽ��� c
			else // p�� ������ �ڽ��� n�� ���
				p->right = c; // p�� ������ �ڽ��� c
		}
		else // n�� ��Ʈ����� ���
			head->left = c; // c�� ��Ʈ���

		free(n); // n �Ҵ� ����
		return 1;
	}
	// n�� �ΰ��� �ڽ��� ���� ���
	c = n->right; // c�� n�� ������ �ڽ�
	p = n; // p�� n�� ��ġ��

	while(c->left != NULL) // c�� ���� �ڽ��� �����Ѵٸ�
	{
		p = c; // p�� c�� ��ġ��
		c = c->left; // c�� c�� �����ڽ�����
		// �� ������ �ݺ��ϸ� c�� n�� ������ �ڽ� �� ���� ���� ���� ���� ��忡 ��ġ��
	}

	if(p->left == c) // c�� p�� ���� �ڽ��� ���
		p->left = c->right; // p�� �����ڽ��� c�� ������ �ڽ�
	else if(p->right == c) // c�� p�� ������ �ڽ��� ���
		p->right = c->right; // p�� ������ �ڽ��� c�� ������ �ڽ�

	n->key = c->key; // n�� key���� c�� key������ �Ҵ�
	free(c); //c ����
	return 1;
}
void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()
{
	if(top == -1) // ������ ����ִ� ���
	{
		return NULL;
	}

	top = top - 1; // top�� 1 ����
	return stack[top + 1]; // ������ top + 1 ��° �ε����� ���� ����
}

void push(Node* aNode)
{
	if(top == MAX_STACK_SIZE-1) // ������ ���� ���ִ� ���
	{
		printf("stack is full!\n");
		return;
	}

	top = top + 1; // top�� 1 ����
	stack[top] = aNode; // ������ top ��° �ε����� ���ڷ� ���� ����� �ּ� �Ҵ�
}



Node* deQueue()
{
	if(rear == front) // ť�� ����ִ� ���
	{
		return NULL;
	}

	front = (front + 1) % MAX_QUEUE_SIZE; // front�� ���� ��ġ��
	return queue[front]; // ť�� front ��° �ε����� �ִ� �� ����
}

void enQueue(Node* aNode)
{
	if ((rear+1) % MAX_QUEUE_SIZE == front) // ť�� ���� ���ִ� ���
	{
		return;
	}

	rear = (rear+1) % MAX_QUEUE_SIZE; // rear�� ������ġ��
	queue[rear] = aNode; // ť�� rear �� ° �ε����� ���ڷ� ���� ����� �ּ� �Ҵ�
}

