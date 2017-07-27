#include "����˹����.h"
#include "queue.h"

RECT ContainerRect = { 1,1,240,482 };
//�洢��һ������ľ�������
RECT NextBlockRect= { 246,1,313,68 };
//���߽�
void OnDrawBorder(HDC hdc_mem)
{
	HPEN hPen;
	HPEN OldPen;
	/* ����һ��ʵ�߻��� */
	hPen = CreatePen(PS_SOLID, 5, RGB(139, 134, 130));
	/* ��ʵ�߻��ʷ����DC */
	OldPen = SelectObject(hdc_mem, hPen);
	/* �������� */
	Rectangle(hdc_mem, ContainerRect.left, ContainerRect.top, ContainerRect.right, ContainerRect.bottom);

	/* ��һ�����������߽� */
	Rectangle(hdc_mem, NextBlockRect.left, NextBlockRect.top, NextBlockRect.right, NextBlockRect.bottom);

	/* �ָ����� */
	SelectObject(hdc_mem, OldPen);
	DeleteObject(hPen);
	return ;
}

void OnDrawSpeedSelect(HDC hdc_mem)
{
	CHAR buffer[64] = { 0 };
	int size = 0;

	size = wsprintf(buffer, TEXT("��ʼ�ٶ����� = ��"));
    TextOut(hdc_mem, ContainerRect.left + CONTAINER_WIDTH, ContainerRect.top +  2 * CONTAINER_WIDTH, buffer, size);
	
	size = wsprintf(buffer, TEXT("��ʼ�ٶȼ��� = ��"));
	TextOut(hdc_mem, ContainerRect.left +  CONTAINER_WIDTH, ContainerRect.top + 4 * CONTAINER_WIDTH, buffer, size);
	
	size = wsprintf(buffer, TEXT("���ý�����ʼ��Ϸ = S"));
	TextOut(hdc_mem, ContainerRect.left +  CONTAINER_WIDTH, ContainerRect.top + 6 * CONTAINER_WIDTH, buffer, size);
	size = wsprintf(buffer, TEXT("��ǰ��ʼ�ٶ�Ϊ: %d"), tetris.initalSpeed + 1);
	TextOut(hdc_mem, ContainerRect.left + CONTAINER_WIDTH, ContainerRect.top + 8 * CONTAINER_WIDTH, buffer, size);
	
	return;
}

void OnDrawBlock(HDC hdc_mem)
{
	HBRUSH hBrush;
	HBRUSH hOldBrush ;

	/* ����һ��ʵ��ˢ��,ϵͳ��������Ҫ���ͼ�ε��ڲ������λͼ */
	hBrush = CreateSolidBrush(RGB(0, 245, 255)); 										   
	/* ��ʵ��ˢ�ӷ�����ڴ�DC */
	hOldBrush = SelectObject(hdc_mem, hBrush);
	
	/*DrawCurrentBlock*/
	{
		int i = 0;
		int j = 0;

		for (i = 0; i < BLOCK_WIDTH; ++i)
		{
			for (j = 0; j < BLOCK_WIDTH; ++j)
			{
				/* ֻ�������������ڵķ��� */
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

	/* �ָ����� */
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

	size = wsprintf(buffer, TEXT("��ʼ= S"));
	TextOut(hdc_mem, NextBlockRect.left, NextBlockRect.bottom + 6 * CONTAINER_WIDTH, buffer, size);

	size = wsprintf(buffer, TEXT("��ͣ= P"));
	TextOut(hdc_mem, NextBlockRect.left, NextBlockRect.bottom + 7 * CONTAINER_WIDTH, buffer, size);

	size = wsprintf(buffer, TEXT("�˳�= Esc"));
	TextOut(hdc_mem, NextBlockRect.left, NextBlockRect.bottom + 8 * CONTAINER_WIDTH, buffer, size);

	size = wsprintf(buffer, TEXT("��ת= ��"));
	TextOut(hdc_mem, NextBlockRect.left, NextBlockRect.bottom + 9 * CONTAINER_WIDTH, buffer, size);

	size = wsprintf(buffer, TEXT("����= ��"));
	TextOut(hdc_mem, NextBlockRect.left, NextBlockRect.bottom + 10 * CONTAINER_WIDTH, buffer, size);

	size = wsprintf(buffer, TEXT("����= ��"));
	TextOut(hdc_mem, NextBlockRect.left, NextBlockRect.bottom + 11 * CONTAINER_WIDTH, buffer, size);

	size = wsprintf(buffer, TEXT("����= ��"));
	TextOut(hdc_mem, NextBlockRect.left, NextBlockRect.bottom + 12 * CONTAINER_WIDTH, buffer, size);

	return 0;
}
void OnPaint(HDC hdc)
{
	HDC hdc_mem = { 0 };
	HBITMAP hBitmap = { 0 };
	HBITMAP hOldBitmap = { 0 };

	/* �����ڴ�DC */
	hdc_mem = CreateCompatibleDC(hdc);
	/* ����һ��bmp�ڴ�ռ� */
	hBitmap = CreateCompatibleBitmap(hdc, WINDOW_WIDTH, WINDOW_HIGH);
	/* ��bmp�ڴ�ռ������ڴ�DC */
	hOldBitmap = (HBITMAP)SelectObject(hdc_mem, hBitmap);
	/* ���ñ���ɫ��λͼ����ɾ��������õ��ǰ�ɫ��Ϊ���� */
	PatBlt(hdc_mem, 0, 0, WINDOW_WIDTH, WINDOW_HIGH, WHITENESS);

	OnDrawBorder(hdc_mem);

	if (tetris.GameState == 3)
	{
		/* �ٶ�ѡ�� */
		OnDrawSpeedSelect(hdc_mem);
	}
	else
	{
		/* ������Ϸ */
		UpdateCurrBlockDestinationPosition();
		OnDrawBlock(hdc_mem);
	}

	OnDrawResult(hdc_mem);

	/* ���ڴ�DC�����ݸ��Ƶ���Ļ��ʾDC��,�����ʾ */
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
			//�����½�ʱ����
			interval = 500 / (tetris.speed + 1);
			if ((timercounter * 20) >= interval)
			{
				if (1 == tetris.GameState)//��Ϸ��ʼ
				{
					StepDown();
				}

				timercounter = 0;
			}
			InvalidateRect(hWnd, NULL, 0);//ָ���Ĵ�������������һ������
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
				/* ��P����ͣ��Ϸ */
				tetris.GameState = 2;
			}
		}
		break;
		case 'S':
		{
			/* ��S���뿪��ͣ״̬ */
			if (2 == tetris.GameState)
			{
				tetris.GameState = 1;
			}
			/* ��S�����¿�ʼ��Ϸ */
			if ((0 == tetris.GameState) || (3 == tetris.GameState))
			{
				/* ������ʼ���ٶ� */
				unsigned int temp = tetris.initalSpeed;
				/* ��ʼ����Ϸ */
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
			/* ��Esc���˳���Ϸ */
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
	//�����ڱ������뱻����ʱ�ŷ���
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
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); /* ����ˢ */
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = TEXT("Tetris");

	RegisterClass(&wndClass);

	hWndDestop = GetDesktopWindow();
	GetClientRect(hWndDestop, &DestopRect);
	hinst = hInstance;
	hWnd = CreateWindow(
		TEXT("Tetris"),        /* �������� */
		TEXT("Tetris"),        /* ���� */
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, //WS_OVERLAPPEDWINDOW,   /* window style */
		(DestopRect.right - WINDOW_WIDTH) / 3,         /* initial x position default CW_USEDEFAULT */
		(DestopRect.bottom - WINDOW_HIGH) / 3,         /* initial y position default CW_USEDEFAULT */
		WINDOW_WIDTH,                  
		WINDOW_HIGH,                  
		(HWND)NULL,				// �����ھ�� no owner window 
		(HMENU)NULL,			// ���ڲ˵��ľ�� use class menu 
		hInstance,				// Ӧ�ó���ʵ����� handle to application instance 
		(LPVOID)NULL);			// ָ�򸽼����ݵ�ָ�� no window-creation data 
	

	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}


