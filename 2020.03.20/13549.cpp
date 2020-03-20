// 13549. ���ٲ��� 3
/*
����ġ�� �ٸ��Ƿ�(�̵� : 1, �����̵� :0 ) ���ͽ�Ʈ�� �̿�
���� 0~N : 0�� N�� ��� ����
*/

#define _crt_secure_no_warnings
#define p pair<int,int>
#define INF 2147000000
#define Max 100000

#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;
int n, k;
int visit[Max + 1]; // ���ͽ�Ʈ��� ����� �迭
int dx[2] = { 1,-1 }; 

struct Move {
	int x;
	int now;
};
queue <Move> q;

void bfs()
{
	visit[n] = 0;
	q.push({ n,0 });
	while (!q.empty())
	{
		Move m = q.front();
		q.pop();

		for (int d = 0; d < 2; d++) // �Ϲ��̵� (��ĭ�̵�) : ����ġ 1
		{
			int xx = m.x + dx[d];
			if (xx<0 || xx>Max)
				continue;
			if (visit[xx] > m.now + 1)
			{
				visit[xx] = m.now + 1;
				q.push({ xx,visit[xx] });
			}
		}
		if (2 * m.x <= Max) // �����̵� (������ġ�� ��) : ����ġ 0
		{
			if (visit[2 * m.x] > m.now)
			{
				visit[2 * m.x] = m.now;
				q.push({ 2 * m.x,visit[2 * m.x] });
			}
		}
	}
}

int main()
{
	scanf("%d %d", &n, &k);
	fill(visit, visit + 1 + Max, INF);
	bfs();
	printf("%d\n", visit[k]);
}