#include "����˹����.h"
#include "queue.h"
char BlockSets[CONTAINER_HIGH*CONTAINER_WIDTH*BLOCK_SIZE] =
{
	/*	I	*/
	0, 1, 0, 0,
	0, 1, 0, 0,
	0, 1, 0, 0,
	0, 1, 0, 0,

	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	1, 1, 1, 1,

	0, 1, 0, 0,
	0, 1, 0, 0,
	0, 1, 0, 0,
	0, 1, 0, 0,

	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	1, 1, 1, 1,
	/*	J	*/
	0, 0, 0, 0,
	0, 0, 1, 0,
	0, 0, 1, 0,
	0, 1, 1, 0,

	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 1, 0, 0,
	0, 1, 1, 1,

	0, 0, 0, 0,
	0, 1, 1, 0,
	0, 1, 0, 0,
	0, 1, 0, 0,

	0, 0, 0, 0,
	0, 0, 0, 0,
	1, 1, 1, 0,
	0, 0, 1, 0,
	/*	L*/
	0, 0, 0, 0,
	0, 1, 0, 0,
	0, 1, 0, 0,
	0, 1, 1, 0,

	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 1, 1, 1,
	0, 1, 0, 0,

	0, 0, 0, 0,
	0, 1, 1, 0,
	0, 0, 1, 0,
	0, 0, 1, 0,

	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 1, 0,
	1, 1, 1, 0,
	/*	O	*/
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 1, 1, 0,
	0, 1, 1, 0,

	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 1, 1, 0,
	0, 1, 1, 0,

	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 1, 1, 0,
	0, 1, 1, 0,

	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 1, 1, 0,
	0, 1, 1, 0,
	/*	S	*/
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 1, 1, 0,
	1, 1, 0, 0,

	0, 0, 0, 0,
	0, 1, 0, 0,
	0, 1, 1, 0,
	0, 0, 1, 0,

	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 1, 1, 0,
	1, 1, 0, 0,

	0, 0, 0, 0,
	0, 1, 0, 0,
	0, 1, 1, 0,
	0, 0, 1, 0,
	/*	T	*/
	0, 0, 0, 0,
	0, 0, 0, 0,
	1, 1, 1, 0,
	0, 1, 0, 0,

	0, 0, 0, 0,
	0, 1, 0, 0,
	1, 1, 0, 0,
	0, 1, 0, 0,

	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 1, 0, 0,
	1, 1, 1, 0,

	0, 0, 0, 0,
	0, 1, 0, 0,
	0, 1, 1, 0,
	0, 1, 0, 0,
	/*	Z	*/
	0, 0, 0, 0,
	0, 0, 0, 0,
	1, 1, 0, 0,
	0, 1, 1, 0,

	0, 0, 0, 0,
	0, 0, 1, 0,
	0, 1, 1, 0,
	0, 1, 0, 0,

	0, 0, 0, 0,
	0, 0, 0, 0,
	1, 1, 0, 0,
	0, 1, 1, 0,

	0, 0, 0, 0,
	0, 0, 1, 0,
	0, 1, 1, 0,
	0, 1, 0, 0
};
void CheckGameOver()//�ж���Ϸ����
{
	int i, j;
	int lineblockflag = 0;/*0��ʾû�з���  1�з���*/
	int gameoverflag = 1;/*1����  0������*/
	for (i = 0; i < CONTAINER_HIGH; i++)
	{
		lineblockflag = 0;
		for (j = 0; j < CONTAINER_WIDTH; j++)
		{
			if (Container[i][j] == 1)
			{
				lineblockflag = 1;
			}
		}
		if (lineblockflag == 0)
		{
			gameoverflag = 0;
		}
	}
	tetris.GameState = (gameoverflag == 0) ? 1 : 0;
}
void CopyToConTainer()//���Ƶ�������
{
	int i, j;
	for (i = 0; i <= BLOCK_WIDTH - 1; ++i)
	{
		for (j = 0; j <= BLOCK_WIDTH - 1; ++j)
		{
			if (*(tetris.current_block + BLOCK_WIDTH*i + j) == 1)
			{
				Container[tetris.top + i][tetris.left + j] = 1;
			}
		}
	}
}
void CaculateScore()
{
	NODE *head = NULL;
	 int award = 0;
	int count = 0;
	int i = 0;
	int j = 0;
	int line=0;
	/* ��¼��Ҫ��ȥ����, ����һ�������ڷ����ľ���4�� */
	/* ֻ�����Ѿ���������Ϸ��������ķ��� */
	for (i = 0; i <= CONTAINER_WIDTH*CONTAINER_WIDTH; ++i)
	{
		count = 0;

		for (j = 0; j < CONTAINER_WIDTH; ++j)
		{
			count += Container[i][j];//��¼�������
		}

		if (count == CONTAINER_WIDTH)
		{
			
			queue_push(&head, i);//��ͬһ�н������
			++award;//����д���
		}
	}

	if (0 != award)
	{
		/* ���� */
		while (NULL != head)
		{

			//int line=0;// = 10;
			queue_pop(&head, &line);//������
			if (award == CONTAINER_WIDTH)
			{
				line = line + 1;
			}
			for (i = line - 1; i >= 0; --i) /* row high */
			{
				//�ӵ�9�п�ʼ����
				memcpy(&Container[i + 1][0], &Container[i][0], sizeof(unsigned char) * CONTAINER_WIDTH);
			}

		}

		
        /* �÷� */
		tetris.score = tetris.score + 10;
		/* �ٶ� */
		tetris.speed = tetris.initalSpeed;					
	}

}
void CaculateBlockBoundary()
{
	int i = 0;
	int j = 0;
	int isFounded = 0;

	//�ж��Ƿ񳬳���߽߱�
	isFounded = 0;
	for (j = 0; j < BLOCK_WIDTH && 0 == isFounded; ++j)
	{
		for (i = 0; i < BLOCK_WIDTH && 0 == isFounded; ++i)
		{
			if (1 == *(tetris.current_block + BLOCK_WIDTH * i + j))
			{
				tetris.min_left = j;
				isFounded = 1;
			}
		}
	}
	//�жϷ����Ƿ񳬳������Ϸ�
	isFounded = 0;
	for (i = 0; i < BLOCK_WIDTH && 0 == isFounded; ++i)
	{
		for (j = 0; j < BLOCK_WIDTH && 0 == isFounded; ++j)
		{
			if (1 == *(tetris.current_block + BLOCK_WIDTH * i + j))
			{
				tetris.min_top = i;
				isFounded = 1;
			}
		}
	}
	//�жϷ����Ƿ���������ұ�
	isFounded = 0;
	for (j = BLOCK_WIDTH - 1; j >= 0 && 0 == isFounded; --j)
	{
		for (i = BLOCK_WIDTH; i >=0 && 0 == isFounded; --i)
		{
			if (1 == *(tetris.current_block + BLOCK_WIDTH * i + j))
			{
				tetris.max_right = j;
				isFounded = 1;
			}
		}
	}

	
	//�жϷ����Ƿ������������
	isFounded = 0;
	for (i = BLOCK_WIDTH - 1; i >= 0 && 0 == isFounded; --i)
	{
		for (j = 0; j < BLOCK_WIDTH && 0 == isFounded; ++j)
		{
			if (1 == *(tetris.current_block + BLOCK_WIDTH * i + j))
			{
				tetris.max_bottom = i;
				isFounded = 1;
			}
		}
	}
}

void GenerateBlock()
{
	/* �����Ϸ�Ƿ��Ѿ����� */
	CheckGameOver();
	if (0 == tetris.GameState)
	{
		return 0;
	}
	//��ǰλ��Ϊ����������飬���������һ����
	if (NULL == tetris.current_block)
	{
		/* ��һ�� */
		srand((unsigned int)time(0));
		tetris.kind = rand() % BLOCK_KINDS;
		tetris.rotate = rand() % BLOCK_ROTATES;
		tetris.current_block = BlockSets + tetris.kind * BLOCK_SIZE * BLOCK_ROTATES + tetris.rotate * BLOCK_SIZE;

		tetris.next_kind = rand() % BLOCK_KINDS;
		tetris.next_rotate = rand() % BLOCK_ROTATES;
	}
	else
	{
		tetris.kind = tetris.next_kind;
		tetris.rotate = tetris.next_rotate;
		tetris.current_block = tetris.next_block;

		srand((unsigned int)time(0));
		tetris.next_kind = rand() % BLOCK_KINDS;
		tetris.next_rotate = rand() % BLOCK_ROTATES;
	}
	tetris.next_block = BlockSets + tetris.next_kind * BLOCK_SIZE * BLOCK_ROTATES + tetris.next_rotate * BLOCK_SIZE;

	CaculateBlockBoundary();

	/* �·�����м����£�һ�������� */
	tetris.left = (CONTAINER_WIDTH - BLOCK_WIDTH) / 2 ; /* ��ԭʼ����ƫ����ߣ����Բ���1 */
	tetris.top = -tetris.max_bottom;
}
int DetectCollision(char *block, int left, int top)
{
	/* return 2�� ������ײ���»�ľ�������ڻ�ľ��ײ;1, ������ײ���������ҡ��±߿�; 0 û����ײ */
	 int state = 0;

	if (0 <= left + tetris.min_left /* ��߽��� */
		&& left + tetris.max_right <= CONTAINER_WIDTH - 1 /* �ұ߽��� */
														  /* �·�����������ϱ߽罻�� */														 
		&& top + tetris.max_bottom <= CONTAINER_HIGH - 1) /* �±߽��� */
	{
		int i = 0;
		int j = 0;

		for (i = 0; i <= BLOCK_WIDTH && 0 == state; ++i)
		{
			for (j = 0; j <= BLOCK_WIDTH-1 && 0 == state; ++j)
			{
				if (1 == *(block + BLOCK_WIDTH * i + j)
					&& 1 == Container[top + i][left + j])
				{					
						state = 2; /* 2�� ������ײ(�»�ľ�������ڻ�ľ��ײ) */				
				}
			}
		}
	}
	else
	{
		state = 1; /* 1, ������ײ(�������ҡ��±߿�) */
	}

	return state;
}
void StepLeft()
{
	//���Ͻ�����-1
	--tetris.left;
	if (DetectCollision(tetris.current_block, tetris.left, tetris.top))
	{
		//�������з��飬�����������
		++tetris.left;
	}
}
void StepRight()
{
	++tetris.left;
	if (DetectCollision(tetris.current_block, tetris.left, tetris.top))
	{
		--tetris.left;
	}
}
int StepDown()
{
	/* return 0,���� 1 ��������*/
	++tetris.top;
	if (DetectCollision(tetris.current_block, tetris.left, tetris.top))
	{
		--tetris.top;
		CopyToConTainer();
		CaculateScore();
		GenerateBlock();

		return 0;
	}

	return 1;
}
void UpdateCurrBlockDestinationPosition()
{
	int i, j;
	tetris.top_destinnation = tetris.top;
	for (i = 0; i < CONTAINER_WIDTH; i++)
	{
		for(j=0;j<CONTAINER_HIGH;j++)
		{
			//�·�û�з���������ߣ��о�ֹͣ
			if (DetectCollision(tetris.current_block, tetris.left, tetris.top_destinnation))
			{
				--tetris.top_destinnation;

				break;
			}

			++tetris.top_destinnation;
		}
	}
}
void StepRotate()
{
	++tetris.rotate;
	tetris.rotate %= BLOCK_ROTATES;
	tetris.current_block = BlockSets + tetris.kind * BLOCK_SIZE * BLOCK_ROTATES + tetris.rotate * BLOCK_SIZE;

	/* �����±߽� */
	CaculateBlockBoundary();
	
}