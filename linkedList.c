#include <stdio.h>
#include <stdlib.h>

// head 에 Dummy Node 를 추가하고, head 에 새 데이터를 추가하는 연결리스트 

#define TRUE 1
#define FALSE 0

typedef int LData;

typedef struct _node {
	LData data;
	struct _node *next;
}Node; 

typedef struct _linkedList{
	Node* head;
	Node* cur;
	Node* before; // Node remove 시 필요한 변수
	int numofData;
	// (*comp) 는 함수포인터 
	int (*comp) (LData D1, LData D2); 
}LinkedList;

typedef LinkedList List;

void ListInit(List* plist)
{
	// head 의 Dummy Node 만 추가된 상태
	plist->head = (Node*)malloc(sizeof(Node));
	plist->head->next = NULL;
	plist->comp = NULL;
	plist->numofData = 0;
}

void FInsert(List *plist, LData data)
{
	Node* newNode = (Node*)malloc(sizeof(Node)); // 여기에서 newNode 를 만드는구나!
	newNode->data = data;
	
	newNode->next = plist->head->next;
	plist->head->next = newNode;
	
	(plist->numofData)++;
}

void SInsert(List* plist, LData data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	Node* pred = plist->head;
	newNode->data = data;
	
	while (pred->next != NULL && plist->comp(data, pred->next->data) != 0)
	{
		pred = pred->next;
	}
	
	newNode->next = pred->next;
	pred->next = newNode;
	
	(plist->numofData)++;
}

void LInsert(List *plist, LData data)
{
	if (plist->comp == NULL) // 정렬기준이 마련되지 않았다면, head에 노드를 추가. 
	{
		FInsert(plist, data);
	}
	else // 정렬기준이 마련되었다면 정렬기준에 근거하여 노드를 추가. 
	{
		SInsert(plist, data);
	}
}

int LFirst(List* plist, LData* pdata)
{
	if ( plist->head->next == NULL ) 
	{
		return FALSE;
	}
	plist->before = plist->head;
	plist->cur = plist->head->next;
	
	*pdata = plist->cur->data;
	return TRUE;
}

int LNext(List* plist, LData* pdata)
{
	if (plist->cur->next == NULL)
	{
		return FALSE;
	}
	
	plist->before = plist->cur;
	plist->cur = plist->cur->next;
	
	*pdata = plist->cur->data;
	return TRUE;
}

LData LRemove(List* plist)
{
	Node* rpos = plist->cur;
	LData rdata = rpos->data;
	
	plist->before->next = plist->cur->next;
	plist->cur = plist->before;
	
	free(rpos);
	(plist->numofData)--;
	return rdata;
}

int WhoIsPrecede(LData D1, LData D2)
{
	if (D1 < D2)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void SetSortRule(List* plist, int (*comp) (LData D1, LData D2))
{
	plist->comp = comp;
}

int LCount(List* plist)
{
	return plist->numofData;
}

int main(void)
{ 
	List list;
	// LData data; 로 선언할 필요는 없는가? 애초에 가능한가? 
	int data; 
	ListInit(&list);
	
	SetSortRule(&list, WhoIsPrecede);
	
	LInsert(&list, 22);
	LInsert(&list, 33);
	LInsert(&list, 22);
	LInsert(&list, 44);
	LInsert(&list, 11);
	
	printf("현재 데이터의 수: %d\n\n", LCount(&list));
	
	if (LFirst(&list, &data))
	{
		printf("%d ", data);
		
		while(LNext(&list, &data))
		{
			printf("%d ", data);
		}
	}
	
	printf("\n\n");
	
	if (LFirst(&list, &data))
	{
		if(data == 22)
		{
			LRemove(&list);
		}
		
		while (LNext(&list, &data))
		{
			if (data == 22)
			{
				LRemove(&list);
			}
		}
	}
	
	if (LFirst(&list, &data))
	{
		printf("%d ", data);
		
		while(LNext(&list, &data))
		{
			printf("%d ", data);
		}
	}
	
	printf("\n\n");
	
	printf("현재 데이터의 수: %d\n\n", LCount(&list));
	
	return 0;
}
