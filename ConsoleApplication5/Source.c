# define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

typedef int COLOR;
# define BLUE 1
# define WHITE 0

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
	COLOR color;
	List listComp;
}Comp;

void sortList(List *lst);
int cmpfunc(const void * a, const void * b);
int *strToArr(char *string);
void linkedList(int *arr, int arrSize, Comp *compNet);
Comp *makeCompNet(int n);
List creatEmptyList();
int isEmptyList(List lst);
ListNode* createNode(void * data, ListNode* next);
void insertNodeToHead(List* lst, ListNode* newHead);
void insertNodeToTail(List* lst, ListNode* newTail);
Comp *createComp(int data, List *listComp);
void createGroup(Comp *comp, List *nagishList, Comp xComp);
//void createGroup(Comp **comp, List *nagishList, Comp *xComp);
void makeAllCompWhiteAgain(Comp *comp, int compSize);
void printCompNet(Comp *compNet, int numOfComp);
void printCompNetNagish(Comp *compNetNagish, int numOfComp);
void sortCompNet(Comp *compNet, int numOfComp);
void createCompNagishList(Comp *compNet, Comp *compNetNagish, int numOfComp);

/*void createCompNagishList(Comp *compNet, Comp *compNetNagish, int numOfComp)
{
	int i = 0;
	for (i = 0; i < numOfComp; i++)
	{
		createGroup(compNet, &compNetNagish[i].listComp, compNet[i]);
		//makeAllCompWhiteAgain(compNet, numOfComp);
	}
}*/
void sortCompNet(Comp *compNet, int numOfComp)
{
	int i = 0;
	for (i = 0; i < numOfComp; i++)
	{
		sortList(&compNet[i].listComp);
	}
}
void printCompNetNagish(Comp *compNetNagish, int numOfComp)
{
	int i = 0;
	ListNode *tmpForPrint;

	for (i = 0; i < numOfComp; ++i)
	{
		tmpForPrint = compNetNagish[i].listComp.head;
		printf("\n Negishim For comp num %d are:", compNetNagish[i].compNum);
		while (tmpForPrint != NULL)
		{
			printf(" %d, ", tmpForPrint->compNum);
			tmpForPrint = tmpForPrint->next;
		}

	}
}
void printCompNet(Comp *compNet, int numOfComp)
{
	int i = 0;
	ListNode *tmpForPrint;

	for (i = 0; i < numOfComp; ++i)
	{
		tmpForPrint = compNet[i].listComp.head;
		while (tmpForPrint != NULL)
		{
			printf(" %d -> %d , \n", compNet[i].compNum, tmpForPrint->compNum);
			tmpForPrint = tmpForPrint->next;
		}

	}
}
void makeAllCompWhiteAgain(Comp *comp, int compSize)
{
	int i = 0;
	for (i = 0; i < compSize; i++)
	{
		comp[i].color = WHITE;
	}
}
void createGroup(Comp *comp, List *nagishList, Comp xComp)
{
	//variables declaration
	ListNode *tmpNode, *tmpPtr;
	printf("The color is %d (1=BLUE, 0=WHITE)\n", xComp.color);

	//stopping condition
	if (comp[xComp.compNum -1].color == BLUE )
	{
		printf("@@@stop condition@@@\n");
		return 0;
	}
	else
	{
		
		//changes xComp to color BLUE
		comp[xComp.compNum -1].color = BLUE;
		printf("NEW!!! color is %d (1=BLUE, 0=WHITE)\n", xComp.color);
		//creates new node (with the xComp Number) and colores it in BLUE
		tmpNode = createNode(xComp.compNum, NULL);
		//insert the new node to the tail of the input list
		insertNodeToTail(nagishList, tmpNode);
		
		//points to the head of the input list (the first ListNode of the relevant comp)
		tmpPtr = xComp.listComp.head;

		//runs on the relevant list
		while (tmpPtr != NULL)
		{
			if (comp[tmpPtr->compNum-1].color == WHITE)
			{
				createGroup(comp, nagishList, comp[tmpPtr->compNum-1]);
			}
			tmpPtr = tmpPtr->next;
		}
	}
}
Comp *createComp(int data, List *listComp)//DELETE-ME
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
	{
		lst->head = lst->tail = newTail;
	}
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
	Comp *compArr;
	int i = 0;

	compArr = (Comp*)malloc(n*sizeof(Comp));

	for (i = 0; i < n; i++)
	{
		compArr[i].compNum = i + 1;
		compArr[i].listComp = creatEmptyList();
		compArr[i].color = WHITE;
		
	}

	return compArr;
}
void linkedList(int *arr, int arrSize, Comp *compNet)
{
	int i = 0;
	ListNode *tmpNode;
	for (i = 0; i < arrSize; i += 2)
	{
		tmpNode = createNode(arr[i + 1], NULL);
		insertNodeToTail(&compNet[arr[i]-1].listComp , tmpNode);
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
int cmpfunc(const void * a, const void * b)
{
	return (*(int*)a - *(int*)b);
}
void sortList (List *lst)
{
	ListNode *ptrToLst;
	ListNode *ptrHeadLst;
	ptrToLst = ptrHeadLst = lst->head;
	
	int arr[10000];
	int i = 0;
	int arrSize;
	//gos on all 
	while (ptrToLst != NULL)
	{
		arr[i] = ptrToLst->compNum;
		i++;
		ptrToLst = ptrToLst->next;
	}

	//keeps the array size
	arrSize = i;

	//sorting the array with qsort
	qsort(arr, arrSize, sizeof(int), cmpfunc);

	//puts the data from the sorted array back into the list
	for (i = 0; i < arrSize; i++)
	{
		ptrHeadLst->compNum = arr[i];
		ptrHeadLst = ptrHeadLst->next;
	}
}


void main()
{
	int numOfComp, i;

	//need to ask Iris how to create string with no limit and use gets
	char inputString[10000];
	int *arrOfLinkedComp;
	int stringLen;
	Comp *compNet;
	Comp *compNetNagish;

	printf("Typethe number of computers in the network\n");
	scanf("%d", &numOfComp);

	printf("Type the conections between the computers\n");

	fflush(stdin);
	gets(inputString);
	stringLen = strlen(inputString);

	arrOfLinkedComp = strToArr(inputString);
	compNet = makeCompNet(numOfComp);
	
	linkedList(arrOfLinkedComp, stringLen, compNet);

	//sorts compNet
	for (i = 0; i < numOfComp; i++)
	{
		sortList(&compNet[i].listComp);
	}

	//tries from function - need to fix
	//sortCompNet(compNet, numOfComp);

	//prints the network - compNet
	printCompNet(compNet, numOfComp);
	
	
	//creates emptycompNetNagish array
	compNetNagish = makeCompNet(numOfComp);
	
	//goes over compNet and create the Negishim Group for each comp in compNetNagish
	for (i = 0; i < numOfComp; i++)
	{
		printf("####### - line num %d\n", i);
		createGroup(compNet, &compNetNagish[i].listComp, compNet[i]);
		makeAllCompWhiteAgain(compNet, numOfComp);
	}
	//tryies from function - need to fix
	//createCompNagishList(compNet, compNetNagish, numOfComp);

	//sort the compNetNagish
	/*for (i = 0; i < numOfComp; i++)
	{
		sortList(&compNetNagish[i].listComp);
	}*/

	//prints the Negishim group of each comp
	printCompNetNagish(compNetNagish, numOfComp);


}