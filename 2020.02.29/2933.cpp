// 미네랄
/*
배열 자체를 문제와 같이 바닥의 index가 1이되도록 받고 시작
*/
#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

int R, C, N;
char map[102][102];
int mineral[101][101];
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };
int Group;
queue <pair<int, int>> q;

bool bfs()
{
	memset(mineral, 0, sizeof(mineral));
	int n = 1;

	for (int i = 1; i <= R; i++)
		for (int j = 1; j <= C; j++)
			if (mineral[i][j] == 0 && map[i][j] == 'x')
			{
				mineral[i][j] = n;
				q.push({ i,j });
				while (!q.empty())
				{
					pair<int, int> p = q.front();
					q.pop();

					for (int d = 0; d < 4; d++)
					{
						int xx = p.first + dx[d], yy = p.second + dy[d];
						if (xx<1 || xx>R || yy<1 || yy>C || mineral[xx][yy] != 0 || map[xx][yy] != 'x')
							continue;
						mineral[xx][yy] = n;
						q.push({ xx,yy });
					}
				}
				n++;
			}

	if (Group == n)
		return true;
	else
	{
		Group = n;
		return false;
	}
}

void dispatch() // 클러스터가 분리되어있고 공중에 있으면 떨어뜨리기
{
	int d = 100;
	int n = 0;
	for (int i = 1; i <= R; i++)
	{
		for (int j = 1; j <= C; j++)
		{
			if (mineral[i][j] == Group-1) // 가장 위에있는 클러스터 찾기
			{
				int x = i, y = j;
				while (1)
				{
					x--;
					if (mineral[x][y] == mineral[i][j]) // 클러스터중 가장 아래에 있는 미네랄만 검사
						break;

					
					if (map[x][y] == 'x' || x < 1)
					{
						if (i - x - 1 < d) // 거리가 가장 가까운 것 기준
						{
							d = i - x - 1;
						}
						break;
					}
				}
			}
		}
	}

	if (d == 0) // 떨어뜨릴 클러스터 x
		return;

	for(int i=1;i<=R;i++)
		for (int j = 1; j <= C; j++)
		{
			if (mineral[i][j] == Group - 1) // 떠있는 미네랄 이동
			{
				map[i][j] = '.'; 
				map[i - d][j] = 'x';
			}
		}

}

void stick(int dir, int loc) // 막대기를 던져 미네랄을 파괴
{
	int d = -1, start = C;
	if (dir % 2 == 0) // 순서에 따라 방향 결정
	{
		d = 1;
		start = 1;
	}

	for (int i = 0; i < C; i++)
	{
		if (map[loc][start] == 'x') // 미네랄 발견하면 파괴 후 클러스터 떨어뜨리기
		{
			map[loc][start] = '.';
			bfs(); // 클러스터 분리
			dispatch(); // 클러스터 떨어뜨리기
			break;
		}
		start += d;
	}

}

int main()
{
	scanf("%d %d", &R, &C);
	// input을 R부터 받아 문제와 유사하게 만들어 더 간단하게 푼듯
	for (int i = R; i > 0; i--)
		for (int j = 1; j <= C; j++)
			scanf(" %c", &map[i][j]);

	bfs();
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		int loc;
		scanf("%d", &loc);
		stick(i, loc);
	}

	for (int i = R; i > 0; i--)
	{
		for (int j = 1; j <= C; j++)
			printf("%c", map[i][j]);
		printf("\n");
	}
}