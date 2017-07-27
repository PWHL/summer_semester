#include <stdlib.h>
#include "queue.h"
int queue_push(NODE **head, int data)
{
	NODE *curnode = NULL;

	/* ����β�ڵ� */
	if (NULL == *head)
	{
		/* �����ֶ�����ͷ���δ���ֵ���� */
		*head = (NODE *)malloc(sizeof(NODE));
		curnode = *head;
	}
	else
	{
		curnode = *head;
		/* Ѱ��β�ڵ� */
		while (NULL != curnode->next)
		{
			curnode = (NODE *)curnode->next;
		}
		/* ������һ�ڵ㣬��ת����һ�ڵ� */
		{
			curnode->next = (NODE *)malloc(sizeof(NODE));
			curnode = (NODE *)curnode->next;
		}
	}

	/* β�ڵ㸳ֵ */
	curnode->data = data;
	curnode->next = NULL;

	return 1;
}
int queue_pop(NODE **head, int *data)
{
	NODE *temp = NULL;

	temp = (NODE *)(*head)->next;

	*data = (*head)->data;

	if (NULL != *head)
	{
		free(*head);
		*head = NULL;
	}

	*head = temp;

	return 1;
}