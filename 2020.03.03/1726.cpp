// �κ�
/*
������ bit�� üũ�ϸ� 3�������� �ʿ������ -> �޸� ���̱Ⱑ��
�ߺ��ȵǴ� �κ� �� üũ����
*/

#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <queue>

using namespace std;
int N, M;
int map[101][101];
int visit[5][101][101]; // ���⸶�� �湮�� ��ġ�� Ȯ���ϱ� ���� 3���� �迭 ���

int dx[5] = { 0,0,0,1,-1 };
int dy[5] = { 0,1,-1,0,0 };

struct Robot {
	int x, y;
	int dir;
	int num;
};
struct cmp {
	bool operator()(Robot a, Robot b) {
		return a.num > b.num;
	}
};

priority_queue <Robot,vector<Robot>,cmp> q; // num�� ���� ������� q�� ����ϱ� ���� pq
Robot Arrive; // ��������
int res;

void bfs()
{
	while (!q.empty())
	{
		Robot r = q.top();
		q.pop();

		if (r.x == Arrive.x&&r.y == Arrive.y&&r.dir == Arrive.dir)
		{
			res = r.num;
			return;
		} 


		for (int k = 1; k <= 3; k++) // Go���
		{
			int xx = r.x + dx[r.dir] * k, yy = r.y + dy[r.dir] * k;
			if (xx<1 || xx>N || yy<1 || yy>M || map[xx][yy] == 1) //�����ְų� ���� ����� break
				break;
			if (visit[r.dir][xx][yy] != 0) // �湮�ߴ� ���� �ǳʶٰ� ��������
				continue;
			q.push({ xx,yy,r.dir,r.num + 1 });
			visit[r.dir][xx][yy] = 1;
		}

		int dd; // ����� �ݴ� ���� ���ϱ�
		if (r.dir % 2 == 0)
			dd = r.dir - 1;
		else
			dd = r.dir + 1;
		for (int d = 1; d <= 4; d++) 
		{
			if (d == r.dir || d == dd)// �������� �ݴ������ ����( ����, ������ )
				continue;
			if (visit[d][r.x][r.y] == 0)
			{
				q.push({ r.x,r.y,d,r.num + 1 });
				visit[d][r.x][r.y] = 1;
			}
		}
	}
}


int main()
{
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			scanf("%d", &map[i][j]);

	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);
	q.push({ a,b,c,0 });
	visit[c][a][b] = 1;
	scanf("%d %d %d", &a, &b, &c);
	Arrive = Robot({ a,b,c,0 });

	bfs();
	printf("%d\n", res);

}