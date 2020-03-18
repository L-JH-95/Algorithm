// 15906 
/*
bfs + ���ͽ�Ʈ�� (dp)
cost���� ��� �ٲ�� ������ ���� ����Ǿ��ִ� ���� �ƴ� st�� ����Ǿ��ִ� time�� �̿��Ͽ� ��
*/
/*
���ͽ�Ʈ��
- Ư�� �������� Ư�� �������� ������ �ִ� ���
- BFS�� �⺻
- �����϶��� ���x
*/

#define _CRT_SECURE_NO_WARNINGS
#define INF 2147000000;

#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;
int N, T, R, C;
int cost[2][501][501]; // (1,1) ���� (x,y)������ �ּұ��� : cost[mode][x][y]
char map[502][502];
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };
int Min;

struct st {
	int x, y;
	int mode;
	int time;
};

queue <st> q;

void Dijk() // bfs + ���ͽ�Ʈ��
{
	cost[0][1][1] = 0;
	q.push({ 1,1,0,0 });

	while (!q.empty())
	{
		st s = q.front();
		q.pop();

		if (s.mode == 0) // �Ϲݸ��
		{
			for (int d = 0; d < 4; d++) // 4�������� 1ĭ��
			{
				int xx = s.x + dx[d], yy = s.y + dy[d];
				if (xx<1 || xx>N || yy<1 || yy>N)
					continue;
				if (s.time + 1 < cost[s.mode][xx][yy])
				{
					cost[s.mode][xx][yy] = s.time + 1;
					q.push({ xx,yy,s.mode,cost[s.mode][xx][yy] });
				}
			}
			int mode = (s.mode + 1) % 2; // �Ϲݸ��

			if (s.time + T < cost[mode][s.x][s.y])
			{
				cost[mode][s.x][s.y] = s.time + T; // �Ϲ� -> ���� : ����ġ T
				q.push({ s.x,s.y,mode,cost[mode][s.x][s.y] });
			}
			
		}
		else {
			for (int d = 0; d < 4; d++) // 4����
			{ 
				int xx = s.x, yy = s.y;
				while (1) // #ã��
				{
					xx += dx[d], yy += dy[d];
					if (xx<1 || xx>N || yy<1 || yy>N) // ������ ����� �׹������� ����x
						break;
					if (map[xx][yy] == '#')
					{
						if (s.time + 1 < cost[s.mode][xx][yy]) // ������ �ִ��� ���簪+����ġ�� �������� go
						{
							cost[s.mode][xx][yy] = s.time + 1;
							q.push({ xx,yy,s.mode,cost[s.mode][xx][yy] });
						}
						break;
					}
				}
			}
			int mode = (s.mode + 1) % 2; // �Ϲݸ��

			if (s.time< cost[mode][s.x][s.y]) // ���� -> �Ϲ� : ����ġ 0
			{
				cost[mode][s.x][s.y] = s.time;
				q.push({ s.x,s.y,mode ,cost[mode][s.x][s.y] });
			}
			
		}
	}
}

int main()
{
	scanf("%d %d %d %d", &N, &T, &R, &C);
	for (int i = 1; i <= N; i++)
	{
		scanf("%s", map[i] + 1);
		for (int j = 1; j <= N; j++) // ���� ū������ cost �ʱ�ȭ
		{
			cost[0][i][j] = INF;
			cost[1][i][j] = INF;
		}
	}

	Dijk();
	Min = cost[0][R][C];
	if (Min > cost[1][R][C])
		Min = cost[1][R][C];

	printf("%d\n", Min);
}