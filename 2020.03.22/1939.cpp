// 1939 �߷� ����
/*
bfs + ���ͽ�Ʈ��
�ּҰ��̾ƴ� �ִ� ���ϴ� ���� -> 0���� �ʱ�ȭ �Ȼ��·� ����
���� ���� �����ϰų� ���� cost���� ���� ���� ������ ������ continue!! -> ���ϸ� �޸� �ʰ�
���� ���� queue�� ���� x -> ����� ������
*/

#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;
vector <pair<int, int>> map[10001];
int N, M;
int cost[10001];
int Start, End;

queue <pair<int, int>> q;

void bfs()
{

	for (int i = 0; i < map[Start].size(); i++) // ���������� ����� ������ queue�� �ִ´�
	{
		q.push({ map[Start][i] });
		cost[map[Start][i].first] = map[Start][i].second;
	}

	while (!q.empty())
	{
		pair<int, int> p = q.front();
		q.pop();

		if (p.first == End || p.second < cost[p.first]) // ���ϸ� �޸� �ʰ� �������� ���������� ���̻� ����x
			continue;

		for (int i = 0; i < map[p.first].size(); i++)
		{
			pair<int, int> temp = map[p.first][i];
			// temp.second < p.second �̸� temp.second�� ���Ա����� ������ �� �ִ� 
			int m = min(temp.second, p.second); // �� ���� ���� �ִ�� �ǳ� �� �ִ� ����
			if (cost[temp.first] < m)
			{
				cost[temp.first] = m;
				q.push({ temp.first,cost[temp.first] });
			}
		}
	}
}

int main()
{
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; i++)
	{
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		map[a].push_back({ b,c });
		map[b].push_back({ a,c });
	}
	scanf("%d %d", &Start, &End);

	bfs();
	printf("%d\n", cost[End]);
}