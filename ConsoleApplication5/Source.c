# define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

typedef struct listNode{
	int compNum;
	struct listNode* next;
	//struct listNode* priv;
}ListNode;
typedef struct list
{
	ListNode *head;
	ListNode *tail;
}List;
typedef struct  comp
{
	int compNum;
	List listComp;
}Comp;

int *strToArr(char *string);
void linkedList(int compNum, int *inputString, List *compList);
Comp *makeCompNet();
List creatEmptyList();
int isEmptyList(List lst);
ListNode* createNode(void * data, ListNode* next);
void insertNodeToHead(List* lst, ListNode* newHead);
void insertNodeToTail(List* lst, ListNode* newTail);
Comp *createComp(int data, List *listComp);

Comp *createComp(int data, List *listComp)
{
	Comp *result;
	result = (Comp*)malloc(sizeof(Comp));
	result->compNum = data;
	result->listComp = *listComp;

	return result;



}
void insertNodeToTail(List* lst, ListNode* newTail)
{
	newTail->next = NULL;

	if (isEmptyList(*lst))
		lst->head = lst->tail = newTail;
	else
	{
		lst->tail->next = newTail;
		lst->tail = newTail;
	}
}
void insertNodeToHead(List* lst, ListNode* newHead)
{
	newHead->next = lst->head;
	if (lst->tail == NULL)
		lst->tail = newHead;
	lst->head = newHead;
}
ListNode* createNode(int data, ListNode* next)
{
	ListNode *result;

	result = (ListNode *)malloc(sizeof(ListNode));

	result->compNum = data;
	result->next = next;

	return result;
}
int isEmptyList(List lst)
{
	return (lst.head == NULL);
}
List creatEmptyList()
{
	List result;
	result.head = result.tail = NULL;
	return result;
}
Comp *makeCompNet(int n)
{
	Comp *comp;
	List *tmpList;
	int i = 0;

	for (i = 0; i < n; i++)
	{
		*tmpList = creatEmptyList();
		comp[i] = *createComp(i, tmpList);
	}
}
void linkedList(int compNum, int *inputString,int inputStringLen, List *compList)
{
	int i = 0;
	ListNode *tmpNode;
	for (i = 0; i < inputStringLen; i+=2)
	{
		if (compNum == inputString[i])
		{
			tmpNode = createNode(i + 1, NULL);
			insertNodeToTail(compList, tmpNode);
		}
	}
}
int *strToArr(char *string)
{
	int len = strlen(string);
	int *intArr, i;
	intArr = (int*)malloc(len*sizeof(int));
	for (i = 0; i < len; i++)
	{
		intArr[i] = string[i]-'0';
	}

	return intArr;
}
void inputFromUser()
{
	int numOfComp, i;
	char *inputString;
	int *arrOfLinkedComp;
	Comp *compNet;
	int stringLen;

	printf("Typethe number of computers in the network\n");
	scanf("%d", &numOfComp);

	printf("Type the conections between the computers\n");

	fflush(stdin);
	gets(inputString);
	stringLen = strlen(inputString);

	arrOfLinkedComp = strToArr(inputString);
	compNet = makeCompNet(numOfComp);

	for (i = 0; i < numOfComp; i++)
	{
		linkedList(compNet[i].compNum, arrOfLinkedComp, stringLen ,&compNet->listComp);
	}





}
void qSortListd