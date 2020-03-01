// �̳׶�
/*
�迭 ��ü�� ������ ���� �ٴ��� index�� 1�̵ǵ��� �ް� ����
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

void dispatch() // Ŭ�����Ͱ� �и��Ǿ��ְ� ���߿� ������ ����߸���
{
	int d = 100;
	int n = 0;
	for (int i = 1; i <= R; i++)
	{
		for (int j = 1; j <= C; j++)
		{
			if (mineral[i][j] == Group-1) // ���� �����ִ� Ŭ������ ã��
			{
				int x = i, y = j;
				while (1)
				{
					x--;
					if (mineral[x][y] == mineral[i][j]) // Ŭ�������� ���� �Ʒ��� �ִ� �̳׶��� �˻�
						break;

					
					if (map[x][y] == 'x' || x < 1)
					{
						if (i - x - 1 < d) // �Ÿ��� ���� ����� �� ����
						{
							d = i - x - 1;
						}
						break;
					}
				}
			}
		}
	}

	if (d == 0) // ����߸� Ŭ������ x
		return;

	for(int i=1;i<=R;i++)
		for (int j = 1; j <= C; j++)
		{
			if (mineral[i][j] == Group - 1) // ���ִ� �̳׶� �̵�
			{
				map[i][j] = '.'; 
				map[i - d][j] = 'x';
			}
		}

}

void stick(int dir, int loc) // ����⸦ ���� �̳׶��� �ı�
{
	int d = -1, start = C;
	if (dir % 2 == 0) // ������ ���� ���� ����
	{
		d = 1;
		start = 1;
	}

	for (int i = 0; i < C; i++)
	{
		if (map[loc][start] == 'x') // �̳׶� �߰��ϸ� �ı� �� Ŭ������ ����߸���
		{
			map[loc][start] = '.';
			bfs(); // Ŭ������ �и�
			dispatch(); // Ŭ������ ����߸���
			break;
		}
		start += d;
	}

}

int main()
{
	scanf("%d %d", &R, &C);
	// input�� R���� �޾� ������ �����ϰ� ����� �� �����ϰ� Ǭ��
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