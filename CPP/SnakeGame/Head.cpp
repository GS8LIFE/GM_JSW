#include "Head.h"
#include <conio.h>
#include <ConsoleEngine/EngineCore.h>
#include "BodyManager.h"
#include "Body.h"
#include <vector> 
// 
// 1. 내가 특정 방향으로 진행했다면 다음 입력때는 그 반대방향으로는 갈수가 없다.
//    내가 이동하는 방향의 반대방향으로는 가면 안된다.
// 2. 내가 이동을 해서 CurBody를 획득했다면 그 다음부터 그 바디는 나를 따라와야 한다.


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
	std::vector<int2> snake;
	int2 whead = GetPos();
	nowHead = whead;

	std::vector<int2> MyBodyPositionVector;
	Part* CurPart = this->Back;
	while (CurPart)
	{
		//프론트의 이전위치를 기억해서 이동
		Part* FrontPart = CurPart->Front;
		CurPart->nowHead = CurPart->GetPos();
		CurPart->SetPos(FrontPart->nowHead);

		//바디들을 바디벡터에 넣음
		int2 CurPosition = CurPart->GetPos();
		MyBodyPositionVector.push_back(CurPosition);

		CurPart = CurPart->Back;
	}

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
		MsgBoxAssert("먹을수 있는 바디가 존재하지 않습니다.");
		return;
	}

	Body* CurBody = BodyManager::GetCurBody();

	if (CurBody->GetPos() == GetPos())
	{
		Part* CurNode = this;
		while (CurNode->Back)
		{
			CurNode = CurNode->Back;
		}
		CurBody->Front = CurNode;
		CurNode->Back = CurBody;
		CurBody->SetPos(CurNode->nowHead);

		BodyManager::ResetBody();
	}
	
}