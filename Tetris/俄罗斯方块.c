#include "俄罗斯方块.h"
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
void CheckGameOver()//判断游戏结束
{
	int i, j;
	int lineblockflag = 0;/*0表示没有方块  1有方块*/
	int gameoverflag = 1;/*1结束  0不结束*/
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
void CopyToConTainer()//复制到容器中
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
	/* 记录需要消去的行, 消行一定发生在放入积木块的4行 */
	/* 只考虑已经出现在游戏容器里面的方块 */
	for (i = 0; i <= CONTAINER_WIDTH*CONTAINER_WIDTH; ++i)
	{
		count = 0;

		for (j = 0; j < CONTAINER_WIDTH; ++j)
		{
			count += Container[i][j];//记录方块个数
		}

		if (count == CONTAINER_WIDTH)
		{
			
			queue_push(&head, i);//将同一行进入队列
			++award;//入队列次数
		}
	}

	if (0 != award)
	{
		/* 消行 */
		while (NULL != head)
		{

			//int line=0;// = 10;
			queue_pop(&head, &line);//出队列
			if (award == CONTAINER_WIDTH)
			{
				line = line + 1;
			}
			for (i = line - 1; i >= 0; --i) /* row high */
			{
				//从第9行开始复制
				memcpy(&Container[i + 1][0], &Container[i][0], sizeof(unsigned char) * CONTAINER_WIDTH);
			}

		}

		
        /* 得分 */
		tetris.score = tetris.score + 10;
		/* 速度 */
		tetris.speed = tetris.initalSpeed;					
	}

}
void CaculateBlockBoundary()
{
	int i = 0;
	int j = 0;
	int isFounded = 0;

	//判断是否超出左边边界
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
	//判断方块是否超出界面上方
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
	//判断方块是否出到界面右边
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

	
	//判断方块是否出到界面以下
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
	/* 检查游戏是否已经结束 */
	CheckGameOver();
	if (0 == tetris.GameState)
	{
		return 0;
	}
	//当前位置为空则产生方块，否则产生下一方块
	if (NULL == tetris.current_block)
	{
		/* 第一次 */
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

	/* 新方块从中间落下，一行行下落 */
	tetris.left = (CONTAINER_WIDTH - BLOCK_WIDTH) / 2 ; /* 因原始数据偏向左边，所以补偿1 */
	tetris.top = -tetris.max_bottom;
}
int DetectCollision(char *block, int left, int top)
{
	/* return 2， 发生碰撞，新积木与容器内积木碰撞;1, 发生碰撞，超出左、右、下边框; 0 没有碰撞 */
	 int state = 0;

	if (0 <= left + tetris.min_left /* 左边界检测 */
		&& left + tetris.max_right <= CONTAINER_WIDTH - 1 /* 右边界检测 */
														  /* 新方块可以允许上边界交叉 */														 
		&& top + tetris.max_bottom <= CONTAINER_HIGH - 1) /* 下边界检测 */
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
						state = 2; /* 2， 发生碰撞(新积木与容器内积木碰撞) */				
				}
			}
		}
	}
	else
	{
		state = 1; /* 1, 发生碰撞(超出左、右、下边框) */
	}

	return state;
}
void StepLeft()
{
	//左上角坐标-1
	--tetris.left;
	if (DetectCollision(tetris.current_block, tetris.left, tetris.top))
	{
		//如果左边有方块，不能往左边走
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
	/* return 0,触底 1 正常下移*/
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
			//下方没有方块就往下走，有就停止
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

	/* 计算新边界 */
	CaculateBlockBoundary();
	
}