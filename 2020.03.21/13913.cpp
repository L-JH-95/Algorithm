// 13913 ���ٲ���4
/*
0�� ������ ���ԵǹǷ� -1�� �ʱ�ȭ�ؾ� �޸� �ʰ�x
*/

#define _CRT_SECURE_NO_WARNINGS
#define P pair<int,int>
#define Max 100000

#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;
int N, K;
int visit[Max + 1]; // �θ� ��� ����
int dx[2] = { 1,-1 };
priority_queue <P,vector<P>,greater<P>> q; //greater�� ����ϹǷ� first�� �ð��� ���� �ϱ�
int Min = 987654321;
vector <int> v;

void bfs()
{
	visit[N] = -5; // �ʱⰪ�� -1�� ������ ������ �� : -5�� ����
	q.push({ 0,N }); //(�ð�, ��)

	while (!q.empty())
	{
		P p = q.top();
		q.pop();

		if (p.second == K) // ������ �ִ� �� �����ϸ� return : pq������� �ּҰ� ����
		{
			Min = p.first;
			return;
		}

		for (int d = 0; d < 2; d++)
		{
			int xx = p.second + dx[d];
			if (xx<0 || xx>Max)
				continue;

			if (visit[xx] == -1) // �������� -5�� �����ϹǷ� -1�϶��� ����
			{
				visit[xx] = p.second;
				q.push({ p.first + 1,xx });
			}
		}

		if (2 * p.second <= Max && visit[2 * p.second] == -1)
		{
			visit[2 * p.second] = p.second;
			q.push({ p.first + 1,2 * p.second });
		}
	}

}

void dfs(int index) // �θ��� ã�ư��� �Լ� : K���� �ö󰡱�
{
	v.push_back(index);
	if (index != N) // ��ϰ� �ִ� ���� �ƴϸ� ��� ����
		dfs(visit[index]);
}

int main()
{
	memset(visit, -1, sizeof(visit));
	scanf("%d %d", &N, &K);
	bfs();
	printf("%d\n", Min);
	dfs(K);
	for (int i = v.size() - 1; i >= 0; i--) // K���� �����ϹǷ� �ڿ��� ���� ���
		printf("%d ", v[i]);
	
	printf("\n");
}
