// ĳ�����潺

/*
�Ÿ��� ������ ���� ���ʺ���
0���� �����Ѵٰ� ���� ������ �ƴϴ� 
	-> �Ÿ��� ������ y��ǥ�� Ȯ������
attack�� while�� ���� ������ ���� monster�� ����ģ monster�� ���� �Ѽ��϶����� ������
�� �� ������
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
vector <pair<int, int>> monster; // �� �ü��� ���� ��

void attack() // �ü��� ����
{
	int temp[15][15]; // map���� �ٷ� �ߴٰ� ��ȳ��� -> ���� �ȵǱ� ����
	memcpy(temp, map, sizeof(temp));
	int cnt = 0;
	int limit = N;
	pair< pair<int, int>, int> p = { {-1,-1},11 }; // ((��ġ),�Ÿ�)

	while (limit > 0) // N���� ��ĭ�� ������
	{
		monster.clear();
		for (int i = 0; i < 3; i++)
		{
			p = { {-1,-1},11 };
			int loc = v[i];
			
			for (int x = limit - 1; x >= limit - D; x--) // �ִ�Ÿ� limit-D���� ������
			{
				if (x < 0) // �����°� ���� ����� ���߱�
					break;
				for (int y = 0; y < M; y++)
				{
					if (temp[x][y] == 1)
					{
						int dis = abs(limit - x) + abs(loc - y);
						
						if (dis <= D && dis < p.second) // �������� �۰� ��������� ���� �ּҰŸ�
							p = { {x,y},abs(limit - x) + abs(loc - y) };
						if(dis==p.second) 
							if(p.first.second>y) // �Ÿ��� ���� ���� ���� ���ʿ� �ִ� �� Ȯ��
								p = { {x,y},abs(limit - x) + abs(loc - y) };
					}
				}
			}
			if (p.first.first != -1 && p.first.second != -1) // (-1,-1)���� ���� -> ���� ���Ѱ��
				monster.push_back(p.first);
		}

		for (int i = 0; i < monster.size(); i++) //���� ���Ѱ�찡 ���� -> 3�� �ƴ� size����
		{
			if (temp[monster[i].first][monster[i].second] == 1)
			{
				temp[monster[i].first][monster[i].second] = 0; //�ѹ� ���̸� �ǵ��� -> �ߺ�x
				cnt++;
			}
		}
		limit--; 
	}

	if (cnt > Max)
		Max = cnt;
}

void dfs(int index) // �ü� ��ġ ����
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

