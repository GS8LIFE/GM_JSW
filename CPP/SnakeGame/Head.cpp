#include "Head.h"
#include <conio.h>
#include <ConsoleEngine/EngineCore.h>
#include "BodyManager.h"
#include "Body.h"
#include <vector> 
// 
// 1. ���� Ư�� �������� �����ߴٸ� ���� �Է¶��� �� �ݴ�������δ� ������ ����.
//    ���� �̵��ϴ� ������ �ݴ�������δ� ���� �ȵȴ�.
// 2. ���� �̵��� �ؼ� CurBody�� ȹ���ߴٸ� �� �������� �� �ٵ�� ���� ����;� �Ѵ�.


void Head::move(int _select,int _nowSelect)
{
	switch (_select)
	{
	case 'A':
	case 'a':
		if (nowSelect == 'D'|| nowSelect=='d')
		{
			AddPos(Right);
			break;
		}
		AddPos(Left);
		nowSelect = 'a';
		break;
	case 'S':
	case 's':
		if (nowSelect == 'W' || nowSelect == 'w')
		{
			AddPos(Up);
			break;
		}
		AddPos(Down);
		nowSelect = 's';
		break;
	case 'W':
	case 'w':
		if (nowSelect == 'S' || nowSelect == 's')
		{
			AddPos(Down);
			break;
		}
		AddPos(Up);
		nowSelect = 'w';
		break;
	case 'D':
	case 'd':
		if (nowSelect == 'A' || nowSelect == 'a')
		{
			AddPos(Left);
			break;
		}
		AddPos(Right);
		nowSelect = 'd';
		break;
	case '1':
		GetCore()->EngineEnd();
		break;
	default:
		break;
	}
	
}

void Head::Update()
{
	
	int2 whead = GetPos();
	nowHead = whead;

	bool InputCount = _kbhit();
	if (InputCount)
	{
		Select = _getch();
		return;
	}

	// InputCount = _kbhit();

	// X Y
	// 1 0

	move(Select,nowSelect);


	if (nullptr == BodyManager::GetCurBody())
	{
		MsgBoxAssert("������ �ִ� �ٵ� �������� �ʽ��ϴ�.");
		return;
	}

	Body* CurBody = BodyManager::GetCurBody();

	if (CurBody->GetPos() == GetPos())
	{
		Back = CurBody;
		BodyManager::ResetBody();
	}
	
}