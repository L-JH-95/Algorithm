// 10282 ��ŷ
/*
���ͽ�Ʈ�� ����
connect�� queue�� �����ؼ� �ߺ����� ������ x -> ����
*/

#define _CRT_SECURE_NO_WARNINGS
#define INF 2147000000
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;
int visit[10001]; // �ش� ��忡 �����ϴµ� �ɸ� �ð�
vector <pair<int,int>> connect[10001]; // vector�� ������ �������� ��� üũ�������
queue <pair<int,int>> q;
int cnt, time;
int n, d, c;

void init() // �ʱ�ȭ
{
	cnt = 0;
	time = 0;
	for (int i = 1; i <= n; i++)
	{
		connect[i].clear();
		visit[i] = INF;
	}
}

void bfs()
{
	// ���۳��
	visit[c] = 0;
	q.push({ c,0 });

	while (!q.empty())
	{
		pair<int, int> now = q.front(); 
		q.pop();

		for (int i = 0; i < connect[now.first].size(); i++)
		{
			pair<int, int> next = connect[now.first][i];

			if (now.second + next.second < visit[next.first]) // ������� ������ �ð����� ���ν��� �ð��� ���� ���
			{
				visit[next.first] = now.second + next.second; 
				q.push({ next.first,now.second + next.second }); // ������� ���� �ð��� queue�� �־��ִ°� �߿�
			}
		}
	}

	for (int i = 1; i <= n; i++)
	{
		if (visit[i] != INF) // �湮�� ���
		{
			cnt++; // �湮�� ��� ����
			if (time < visit[i]) // �湮�� ����� ���� �����ɸ� �ð�
				time = visit[i];
		}
	}
}

int main()
{
	int Test;
	scanf("%d", &Test);
	for (int T = 0; T < Test; T++)
	{
		scanf("%d %d %d", &n, &d, &c);
		init();
		for (int i = 0; i < d; i++)
		{
			int a, b, s;
			scanf("%d %d %d", &a, &b, &s);
			connect[b].push_back({ a,s });
		}
		bfs();
		printf("%d %d\n", cnt, time);
	}
}