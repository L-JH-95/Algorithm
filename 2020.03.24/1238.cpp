// 1329 ��Ƽ
/*
bfs + ���ͽ�Ʈ��
��� �� -> X, X -> ��� ���� ��� �����ؾ���
=> ���� �־��� �׷��� : ���� ������ ���ͽ�Ʈ��
=> ���� �׷����� ����, �����ݴ�� : ����(��� �� -> X) -> (X->�����)
�ΰ��� �׷����� ���� �ö�, ������ �˼� �ִ�

priority_queue�� ����ϸ� �ӵ���������
*/

#define _CRT_SECURE_NO_WARNINGS
#define INF 2147000000

#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;
int N, M, X;
vector <pair<int, int>> TOX[1001], FROMX[1001]; // �ΰ��� ������ �׷����� ����
int tox[1001], fromx[1001]; // �ΰ��� ������ ���� ������ �迭
queue <pair<int, int>> q;

void FromX()
{
	fromx[X] = 0; // X���� ���ư���
	q.push({ X,0 });

	while (!q.empty())
	{
		pair<int, int> p = q.front();
		q.pop();

		if (fromx[p.first] < p.second) // pq�϶� �� ������ ��
			continue;

		for (int i = 0; i < FROMX[p.first].size(); i++)
		{
			pair<int, int> now = FROMX[p.first][i];
			if (p.second + now.second < fromx[now.first]) // ���� �� ���� ���� in
			{
				fromx[now.first] = p.second + now.second;
				q.push({now.first,fromx[now.first] });
			}
		}
	}
}

void ToX() // FromX�� ���� �˰���
{
	tox[X] = 0;
	q.push({ X,0 });

	while (!q.empty())
	{
		pair<int, int> p = q.front();
		q.pop();

		if (tox[p.first] < p.second)
			continue;

		for (int i = 0; i < TOX[p.first].size(); i++)
		{
			pair<int, int> now = TOX[p.first][i];
			if (p.second + now.second < tox[now.first])
			{
				tox[now.first] = p.second + now.second;
				q.push({ now.first,tox[now.first] });
			}
		}
	}
}

int main()
{
	scanf("%d %d %d", &N, &M, &X);
	for (int i = 0; i < M; i++)
	{
		int s, e, t;
		scanf("%d %d %d", &s, &e, &t);
		FROMX[s].push_back({ e,t });
		TOX[e].push_back({ s,t });
	}
	fill(tox, tox + 1 + N, INF);
	fill(fromx, fromx + 1 + N, INF);

	FromX();
	ToX();

	int res = 0;
	for (int i = 1; i <= N; i++) // ���� ������ ���� ���� ū �� ���ϱ�
	{
		if (fromx[i] + tox[i] > res)
			res = fromx[i] + tox[i];
	}
	printf("%d\n", res);
}
