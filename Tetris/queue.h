typedef struct NODE_T
{
	int data;
	struct NODE_T *next;
};
typedef struct NODE_T NODE;
int queue_push(NODE **head, int data);
int queue_pop(NODE **head, int *data);
