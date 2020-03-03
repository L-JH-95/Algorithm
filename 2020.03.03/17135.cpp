// 캐슬디펜스

/*
거리가 같으면 가장 왼쪽부터
0부터 시작한다고 가장 왼쪽이 아니다 
	-> 거리가 같으면 y좌표를 확인하자
attack의 while문 종료 조건을 잡은 monster와 지나친 monster의 합이 총수일때까지 돌리면
좀 더 빠를듯
*/

#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

int N, M, D;
int map[15][15];
int visit[15];
vector <int> v;
int Max;
int enamy;
vector <pair<int, int>> monster; // 각 궁수가 잡은 적

void attack() // 궁수가 공격
{
	int temp[15][15]; // map에서 바로 했다가 답안나옴 -> 복구 안되기 때문
	memcpy(temp, map, sizeof(temp));
	int cnt = 0;
	int limit = N;
	pair< pair<int, int>, int> p = { {-1,-1},11 }; // ((위치),거리)

	while (limit > 0) // N부터 한칸씩 내려옴
	{
		monster.clear();
		for (int i = 0; i < 3; i++)
		{
			p = { {-1,-1},11 };
			int loc = v[i];
			
			for (int x = limit - 1; x >= limit - D; x--) // 최대거리 limit-D까지 내려옴
			{
				if (x < 0) // 내려온게 범위 벗어나면 멈추기
					break;
				for (int y = 0; y < M; y++)
				{
					if (temp[x][y] == 1)
					{
						int dis = abs(limit - x) + abs(loc - y);
						
						if (dis <= D && dis < p.second) // 범위보다 작고 현재까지중 가장 최소거리
							p = { {x,y},abs(limit - x) + abs(loc - y) };
						if(dis==p.second) 
							if(p.first.second>y) // 거리가 같을 때는 가장 왼쪽에 있는 지 확인
								p = { {x,y},abs(limit - x) + abs(loc - y) };
					}
				}
			}
			if (p.first.first != -1 && p.first.second != -1) // (-1,-1)에서 시작 -> 선택 안한경우
				monster.push_back(p.first);
		}

		for (int i = 0; i < monster.size(); i++) //선택 안한경우가 존재 -> 3이 아닌 size까지
		{
			if (temp[monster[i].first][monster[i].second] == 1)
			{
				temp[monster[i].first][monster[i].second] = 0; //한번 죽이면 되돌릭 -> 중복x
				cnt++;
			}
		}
		limit--; 
	}

	if (cnt > Max)
		Max = cnt;
}

void dfs(int index) // 궁수 위치 선택
{
	if (v.size() == 3)
	{
		attack();
		return;
	}

	for(int i=index;i<M;i++)
		if (visit[i] == 0)
		{
			visit[i] = 1;
			v.push_back(i);
			dfs(i);
			v.pop_back();
			visit[i] = 0;
		}
}


int main()
{
	scanf("%d %d %d", &N, &M, &D);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
		{
			scanf("%d", &map[i][j]);
			if (map[i][j] == 1)
				enamy++;
		}

	dfs(0);
	printf("%d\n", Max);
}

