#include <stdlib.h>
#include "queue.h"
int queue_push(NODE **head, int data)
{
	NODE *curnode = NULL;

	/* 创建尾节点 */
	if (NULL == *head)
	{
		/* 考虑字段链表头结点未出现的情况 */
		*head = (NODE *)malloc(sizeof(NODE));
		curnode = *head;
	}
	else
	{
		curnode = *head;
		/* 寻找尾节点 */
		while (NULL != curnode->next)
		{
			curnode = (NODE *)curnode->next;
		}
		/* 创建下一节点，并转到下一节点 */
		{
			curnode->next = (NODE *)malloc(sizeof(NODE));
			curnode = (NODE *)curnode->next;
		}
	}

	/* 尾节点赋值 */
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