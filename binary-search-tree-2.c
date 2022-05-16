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
		printf("--------------[201803805]------[정하용]-------------------------\n");
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
void iterativeInorder(Node* node) // 반복적 중위 순회
{
	if (node == NULL) // 루트노드가 비어있다면
	{
		printf("tree is empty!!\n"); // 오류문장 출력
		return;
	}
	Node* n = node; // 트리를 순회할 구조체 포인터 생성

	while(1) // 루프 시작
	{
		while(n != NULL) // n이 NULL이 아닐 때 반복
		{
			push(n); // 스택에 n 푸시
			n = n->left; // n의 왼쪽 자식으로 이동
		}
		n = pop(); // n에 팝한 데이터 할당
		if(n != NULL) // 스택에서 빠져나온 데이터가 존재한다면
		{
			printf(" [%d] ",n->key); // n의 key값 출력
			n = n->right; // n의 오른쪽 자식으로 이동
		}
		else
			break;
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr) // 레벨단위 순환함수
{
	if(ptr == NULL) // 루트가 비어있는 경우 
	{
		printf("tree is empty!!\n"); // 오류문장 출력 후 종료
		return;
	}
	Node* n = ptr; // 트리를 순회할 구조체 포인터 생성
	enQueue(n); // 큐에 데이터 삽입
	while(1)
	{
		n = deQueue(n); // 큐에서 뺀 데이터 n에 할당
		if(n != NULL) // 큐에서 뺀 데이터가 존재하면
		{
			printf(" [%d] ",n->key); // n의 key값 출력
			if(n->left != NULL) // n의 왼쪽 자식이 존재하면
				enQueue(n->left); // 왼쪽 자식 큐에 삽입
			if(n->right != NULL) // n의 오른쪽 자식이 존재하면
				enQueue(n->right); // 오른쪽 자식 큐에 삽입
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


int deleteNode(Node* head, int key) // 노드 삭제 함수
{
	Node *n = head->left; // 트리를 이동할 구조체 포인터
	Node *p = NULL; // 노드를 삭제할 구조체 포인터
	Node *c = NULL;

	if(head == NULL) // 헤드노드가 비어있는경우
	{
		printf("tree is empty!\n"); // 트리가 비어있음
		return 0;
	}

	if(n == NULL) // 루트노드가 비어있는 경우
	{
		printf("tree is empty!\n"); // 트리가 비어있음
		return 0;
	}

	while((n!= NULL) && (n->key != key)) // n이 NULL이 아니고 n의 key값이 key값과 다를때 반복
	{
		if(n->key != key) // n의 key값이 key값과 다를경우
		{
			p = n; // p를 n의 위치로

			if(n->key < key) // n의 key값보다 key값이 큰 경우
				n = n->right; //n을 n의 오른쪽 자식으로 이동
			else
				n = n->left; //n을 n의 왼쪽 자식으로 이동
		}	
	}

	if(n == NULL) // 루프를 빠져나온 n이 NULL 인경우
	{
		printf("no exist key node in tree!\n"); // 입력받은 key값에 해당하는 노드가 없음
		return 0;
	}
	

	if((n->left == NULL) && (n->right == NULL)) // 루프를 빠져나온 n이 리프노드인경우
	{
		if(p != NULL) // n의 부모노드가 NULL이 아닌경우
		{
			if(p->left == n) // n이 p의 왼쪽 자식일 경우
				p->left = NULL; // p의 왼쪽자식 NULL
			else if(p->right == n) // n이 p의 오른쪽 자식일 경우
				p->right = NULL; // p의 오른쪽 자식 NULL
		}
		else // n의 부모노드가 NULL인 경우 (n이 루트노드인경우)
			head->left = NULL; // 헤드노드의 왼쪽 노드가 NULL
		free(n); // n 할당 해제
		return 1;
	}

	if((n->left == NULL) || (n->right ==NULL)) // 루프를 빠져나온 n이 하나의 자식을 가진 경우
	{
		if(n->left != NULL) // n의 왼쪽자식이 존재하는 경우
			c = n->left; // c가 n의 왼쪽 자식
		else // n의 왼쪽자식이 존재하지 않는경우
			c = n->right; //c가 n의 오른쪽 자식
		
		if(p != NULL) // n의 부모노드가 존재하는 경우
		{
			if(p->left == n) //p의 왼쪽 자식이 n인 경우
				p->left = c; //p의 왼쪽자식이 c
			else // p의 오른쪽 자식이 n인 경우
				p->right = c; // p의 오른쪽 자식이 c
		}
		else // n이 루트노드인 경우
			head->left = c; // c가 루트노드

		free(n); // n 할당 해제
		return 1;
	}
	// n이 두개의 자식을 가진 경우
	c = n->right; // c가 n의 오른쪽 자식
	p = n; // p를 n의 위치로

	while(c->left != NULL) // c의 왼쪽 자식이 존재한다면
	{
		p = c; // p를 c의 위치로
		c = c->left; // c를 c의 왼쪽자식으로
		// 위 과정을 반복하면 c는 n의 오른쪽 자식 중 가장 작은 값을 가진 노드에 위치함
	}

	if(p->left == c) // c가 p의 왼쪽 자식인 경우
		p->left = c->right; // p의 왼쪽자식은 c의 오른쪽 자식
	else if(p->right == c) // c가 p의 오른쪽 자식인 경우
		p->right = c->right; // p의 오른쪽 자식은 c의 오른쪽 자식

	n->key = c->key; // n의 key값을 c의 key값으로 할당
	free(c); //c 제거
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
	if(top == -1) // 스택이 비어있는 경우
	{
		return NULL;
	}

	top = top - 1; // top을 1 감소
	return stack[top + 1]; // 스택의 top + 1 번째 인덱스의 값을 리턴
}

void push(Node* aNode)
{
	if(top == MAX_STACK_SIZE-1) // 스택이 가득 차있는 경우
	{
		printf("stack is full!\n");
		return;
	}

	top = top + 1; // top을 1 증가
	stack[top] = aNode; // 스택의 top 번째 인덱스에 인자로 받은 노드의 주소 할당
}



Node* deQueue()
{
	if(rear == front) // 큐가 비어있는 경우
	{
		return NULL;
	}

	front = (front + 1) % MAX_QUEUE_SIZE; // front를 다음 위치로
	return queue[front]; // 큐의 front 번째 인덱스에 있는 값 리턴
}

void enQueue(Node* aNode)
{
	if ((rear+1) % MAX_QUEUE_SIZE == front) // 큐가 가득 차있는 경우
	{
		return;
	}

	rear = (rear+1) % MAX_QUEUE_SIZE; // rear을 다음위치로
	queue[rear] = aNode; // 큐의 rear 번 째 인덱스에 인자로 받은 노드의 주소 할당
}

