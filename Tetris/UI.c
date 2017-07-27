#include "俄罗斯方块.h"
#include "queue.h"

RECT ContainerRect = { 1,1,240,482 };
//存储下一个方块的矩形坐标
RECT NextBlockRect= { 246,1,313,68 };
//画边界
void OnDrawBorder(HDC hdc_mem)
{
	HPEN hPen;
	HPEN OldPen;
	/* 创建一个实线画笔 */
	hPen = CreatePen(PS_SOLID, 5, RGB(139, 134, 130));
	/* 将实线画笔分配给DC */
	OldPen = SelectObject(hdc_mem, hPen);
	/* 整个界面 */
	Rectangle(hdc_mem, ContainerRect.left, ContainerRect.top, ContainerRect.right, ContainerRect.bottom);

	/* 下一个方块容器边界 */
	Rectangle(hdc_mem, NextBlockRect.left, NextBlockRect.top, NextBlockRect.right, NextBlockRect.bottom);

	/* 恢复设置 */
	SelectObject(hdc_mem, OldPen);
	DeleteObject(hPen);
	return ;
}

void OnDrawSpeedSelect(HDC hdc_mem)
{
	CHAR buffer[64] = { 0 };
	int size = 0;

	size = wsprintf(buffer, TEXT("初始速度增加 = ↑"));
    TextOut(hdc_mem, ContainerRect.left + CONTAINER_WIDTH, ContainerRect.top +  2 * CONTAINER_WIDTH, buffer, size);
	
	size = wsprintf(buffer, TEXT("初始速度减少 = ↓"));
	TextOut(hdc_mem, ContainerRect.left +  CONTAINER_WIDTH, ContainerRect.top + 4 * CONTAINER_WIDTH, buffer, size);
	
	size = wsprintf(buffer, TEXT("设置结束开始游戏 = S"));
	TextOut(hdc_mem, ContainerRect.left +  CONTAINER_WIDTH, ContainerRect.top + 6 * CONTAINER_WIDTH, buffer, size);
	size = wsprintf(buffer, TEXT("当前初始速度为: %d"), tetris.initalSpeed + 1);
	TextOut(hdc_mem, ContainerRect.left + CONTAINER_WIDTH, ContainerRect.top + 8 * CONTAINER_WIDTH, buffer, size);
	
	return;
}

void OnDrawBlock(HDC hdc_mem)
{
	HBRUSH hBrush;
	HBRUSH hOldBrush ;

	/* 创建一个实心刷子,系统用来绘制要填充图形的内部区域的位图 */
	hBrush = CreateSolidBrush(RGB(0, 245, 255)); 										   
	/* 将实心刷子分配给内存DC */
	hOldBrush = SelectObject(hdc_mem, hBrush);
	
	/*DrawCurrentBlock*/
	{
		int i = 0;
		int j = 0;

		for (i = 0; i < BLOCK_WIDTH; ++i)
		{
			for (j = 0; j < BLOCK_WIDTH; ++j)
			{
				/* 只画出现在容器内的方块 */
				if (1 == *(tetris.current_block + BLOCK_WIDTH * i + j)
					&& 0 <= tetris.left + j && 0 <= tetris.top + i)
				{
					Rectangle(hdc_mem,
						ContainerRect.left + (tetris.left + j) * (CONTAINER_WIDTH + 1),
						ContainerRect.top + (tetris.top + i) * (CONTAINER_WIDTH + 1),
						ContainerRect.left + (tetris.left + j) * (CONTAINER_WIDTH + 1) + CONTAINER_WIDTH,
						ContainerRect.top + (tetris.top + i) * (CONTAINER_WIDTH + 1) + CONTAINER_WIDTH);
				}
			}
		}
	}

	/*DrawContainer*/
	{
		int i = 0;
		int j = 0;
		for (i = 0; i < CONTAINER_HIGH; ++i)
		{
			for (j = 0; j < CONTAINER_WIDTH; ++j)
			{
				if ( Container[i][j]==1 )
				{
					Rectangle(hdc_mem,
						ContainerRect.left + j * (CONTAINER_WIDTH + 1),
						ContainerRect.top + i * (CONTAINER_WIDTH + 1),
						ContainerRect.left + j * (CONTAINER_WIDTH + 1) + CONTAINER_WIDTH,
						ContainerRect.top + i * (CONTAINER_WIDTH + 1) + CONTAINER_WIDTH);
				}
			}
		}
	}

	/********************************************
	DrawNextBlock
	*********************************************/
	{
		int i = 0;
		int j = 0;

		for (i = 0; i < BLOCK_WIDTH; ++i)
		{
			for (j = 0; j < BLOCK_WIDTH; ++j)
			{
				if (1 == *(tetris.next_block + BLOCK_WIDTH * i + j))
				{
					Rectangle(hdc_mem,
						NextBlockRect.left + j * (CONTAINER_WIDTH + 1),
						NextBlockRect.top + i * (CONTAINER_WIDTH + 1),
						NextBlockRect.left + j * (CONTAINER_WIDTH + 1) + CONTAINER_WIDTH,
						NextBlockRect.top + i * (CONTAINER_WIDTH + 1) + CONTAINER_WIDTH);
				}
			}
		}
	}

	/* 恢复设置 */
	SelectObject(hdc_mem, hOldBrush);
	DeleteObject(hBrush);
	return;
}

void OnDrawResult(HDC hdc_mem)
{
	CHAR buffer[64] = { 0 };
	int size = 0;

	size = wsprintf(buffer, TEXT("%d"), tetris.score);
	TextOut(hdc_mem, NextBlockRect.left, NextBlockRect.bottom+BLOCK_WIDTH, TEXT("Score:"), 6);
	TextOut(hdc_mem, NextBlockRect.left, NextBlockRect.bottom + 2 * CONTAINER_WIDTH, buffer, size);

	size = wsprintf(buffer, TEXT("%d"), tetris.speed + 1);
	TextOut(hdc_mem, NextBlockRect.left, NextBlockRect.bottom + 3 * CONTAINER_WIDTH, TEXT("Speed:"), 6);
	TextOut(hdc_mem, NextBlockRect.left, NextBlockRect.bottom + 4 * CONTAINER_WIDTH, buffer, size);

	switch (tetris.GameState)
	{
	case 0:
	{
		TextOut(hdc_mem, ContainerRect.left + 10*CONTAINER_WIDTH, ContainerRect.top + 5*CONTAINER_WIDTH, TEXT("Game Over!!!"), 12);
	}
	break;
	case 1:
	{
	}
	break;
	case 2:
	{
		TextOut(hdc_mem, NextBlockRect.left, NextBlockRect.bottom + 5 * CONTAINER_WIDTH, TEXT("Game Continue"), 10);
	}
	break;
	default:
	{
	}
	break;
	}

	size = wsprintf(buffer, TEXT("开始= S"));
	TextOut(hdc_mem, NextBlockRect.left, NextBlockRect.bottom + 6 * CONTAINER_WIDTH, buffer, size);

	size = wsprintf(buffer, TEXT("暂停= P"));
	TextOut(hdc_mem, NextBlockRect.left, NextBlockRect.bottom + 7 * CONTAINER_WIDTH, buffer, size);

	size = wsprintf(buffer, TEXT("退出= Esc"));
	TextOut(hdc_mem, NextBlockRect.left, NextBlockRect.bottom + 8 * CONTAINER_WIDTH, buffer, size);

	size = wsprintf(buffer, TEXT("旋转= ↑"));
	TextOut(hdc_mem, NextBlockRect.left, NextBlockRect.bottom + 9 * CONTAINER_WIDTH, buffer, size);

	size = wsprintf(buffer, TEXT("左移= ←"));
	TextOut(hdc_mem, NextBlockRect.left, NextBlockRect.bottom + 10 * CONTAINER_WIDTH, buffer, size);

	size = wsprintf(buffer, TEXT("右移= →"));
	TextOut(hdc_mem, NextBlockRect.left, NextBlockRect.bottom + 11 * CONTAINER_WIDTH, buffer, size);

	size = wsprintf(buffer, TEXT("下移= ↓"));
	TextOut(hdc_mem, NextBlockRect.left, NextBlockRect.bottom + 12 * CONTAINER_WIDTH, buffer, size);

	return 0;
}
void OnPaint(HDC hdc)
{
	HDC hdc_mem = { 0 };
	HBITMAP hBitmap = { 0 };
	HBITMAP hOldBitmap = { 0 };

	/* 创建内存DC */
	hdc_mem = CreateCompatibleDC(hdc);
	/* 创建一个bmp内存空间 */
	hBitmap = CreateCompatibleBitmap(hdc, WINDOW_WIDTH, WINDOW_HIGH);
	/* 将bmp内存空间分配给内存DC */
	hOldBitmap = (HBITMAP)SelectObject(hdc_mem, hBitmap);
	/* 先用背景色将位图清除干净，这里用的是白色作为背景 */
	PatBlt(hdc_mem, 0, 0, WINDOW_WIDTH, WINDOW_HIGH, WHITENESS);

	OnDrawBorder(hdc_mem);

	if (tetris.GameState == 3)
	{
		/* 速度选择 */
		OnDrawSpeedSelect(hdc_mem);
	}
	else
	{
		/* 正常游戏 */
		UpdateCurrBlockDestinationPosition();
		OnDrawBlock(hdc_mem);
	}

	OnDrawResult(hdc_mem);

	/* 将内存DC的内容复制到屏幕显示DC中,完成显示 */
	BitBlt(hdc, 0, 0, WINDOW_WIDTH, WINDOW_HIGH, hdc_mem, 0, 0, SRCCOPY);

	SelectObject(hdc_mem, hOldBitmap);
	DeleteObject(hBitmap);
	DeleteDC(hdc_mem);
}

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	int rs=0;

	switch (message)
	{
	case WM_CREATE:
	{
		tetris.GameState = 3;
		tetris.initalSpeed = 0;
		SetTimer(hWnd, tetris.TimerId, 10, (TIMERPROC)NULL);
	}
	break;
	case WM_TIMER:
	{
		if (3 != tetris.GameState)
		{
			static unsigned int timercounter = 0;
			static unsigned int interval = 0;
			++timercounter;
			//方块下降时间间隔
			interval = 500 / (tetris.speed + 1);
			if ((timercounter * 20) >= interval)
			{
				if (1 == tetris.GameState)//游戏开始
				{
					StepDown();
				}

				timercounter = 0;
			}
			InvalidateRect(hWnd, NULL, 0);//指定的窗体更新区域添加一个矩形
		}
	}
	break;
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_UP:
		{
			if (1 == tetris.GameState)
			{
				StepRotate();
			}
			if (3 == tetris.GameState)
			{
				++tetris.initalSpeed;
				tetris.initalSpeed = tetris.initalSpeed > 50 ? 0 : tetris.initalSpeed;
			}
		}
		break;
		case VK_LEFT:
		{
			if (1 == tetris.GameState)
			{
				StepLeft();
			}
		}
		break;
		case VK_RIGHT:
		{
			if (1 == tetris.GameState)
			{
				StepRight();
			}
		}
		break;
		case VK_DOWN:
		{
			if (1 == tetris.GameState)
			{
				StepDown();
			}
		}
		break;
		case 'P':
		{
			if ( tetris.GameState==1)
			{
				/* 按P键暂停游戏 */
				tetris.GameState = 2;
			}
		}
		break;
		case 'S':
		{
			/* 按S键离开暂停状态 */
			if (2 == tetris.GameState)
			{
				tetris.GameState = 1;
			}
			/* 按S键重新开始游戏 */
			if ((0 == tetris.GameState) || (3 == tetris.GameState))
			{
				/* 保留初始化速度 */
				unsigned int temp = tetris.initalSpeed;
				/* 初始化游戏 */
				memset((void *)Container, 0, sizeof(unsigned char) * CONTAINER_HIGH * CONTAINER_WIDTH);
				memset((void *)&tetris, 0, sizeof(struct Tetris));
				tetris.GameState = 1;
				tetris.score = 0;
				tetris.initalSpeed = temp;
				tetris.speed = 0 + tetris.initalSpeed;
				GenerateBlock();
			}
		}
		break;
		case VK_ESCAPE:
		{
			/* 按Esc键退出游戏 */
			PostMessage(hWnd, WM_DESTROY, (WPARAM)NULL, (LPARAM)NULL);
		}
		break;
		default:
		{
			rs = DefWindowProc(hWnd, message, wParam, lParam); /* default windows proc */
		}
		break;
		}
		InvalidateRect(hWnd, NULL, 0);
	}
	break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		OnPaint(hdc);
		EndPaint(hWnd, &ps);
	}
	break;
	//当窗口背景必须被擦除时才发送
	case WM_ERASEBKGND:
	{
		
	}
	break;
	case WM_DESTROY:
	{
		KillTimer(hWnd, tetris.TimerId);
		PostQuitMessage(0);
	}
	break;
	default:
	{
		rs = DefWindowProc(hWnd, message, wParam, lParam); /* default windows proc */
	}
	break;
	}

	return rs;
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevlnstance, PSTR lpCmdLine, INT iCmdShow)
{
	HWND hWnd;
	MSG msg ;
	HWND hWndDestop;
	RECT DestopRect;
	WNDCLASS wndClass;

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = MainWndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); /* 背景刷 */
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = TEXT("Tetris");

	RegisterClass(&wndClass);

	hWndDestop = GetDesktopWindow();
	GetClientRect(hWndDestop, &DestopRect);
	hinst = hInstance;
	hWnd = CreateWindow(
		TEXT("Tetris"),        /* 窗口名字 */
		TEXT("Tetris"),        /* 标题 */
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, //WS_OVERLAPPEDWINDOW,   /* window style */
		(DestopRect.right - WINDOW_WIDTH) / 3,         /* initial x position default CW_USEDEFAULT */
		(DestopRect.bottom - WINDOW_HIGH) / 3,         /* initial y position default CW_USEDEFAULT */
		WINDOW_WIDTH,                  
		WINDOW_HIGH,                  
		(HWND)NULL,				// 父窗口句柄 no owner window 
		(HMENU)NULL,			// 窗口菜单的句柄 use class menu 
		hInstance,				// 应用程序实例句柄 handle to application instance 
		(LPVOID)NULL);			// 指向附加数据的指针 no window-creation data 
	

	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}


