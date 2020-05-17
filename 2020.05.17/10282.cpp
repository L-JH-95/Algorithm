// 10282 해킹
/*
다익스트라 문제
connect를 queue로 구현해서 중복으로 갈수가 x -> 오답
*/

#define _CRT_SECURE_NO_WARNINGS
#define INF 2147000000
#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;
int visit[10001]; // 해당 노드에 도착하는데 걸린 시간
vector <pair<int,int>> connect[10001]; // vector로 구현해 여러번을 모두 체크해줘야함
queue <pair<int,int>> q;
int cnt, time;
int n, d, c;

void init() // 초기화
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
	// 시작노드
	visit[c] = 0;
	q.push({ c,0 });

	while (!q.empty())
	{
		pair<int, int> now = q.front(); 
		q.pop();

		for (int i = 0; i < connect[now.first].size(); i++)
		{
			pair<int, int> next = connect[now.first][i];

			if (now.second + next.second < visit[next.first]) // 현재까지 적립된 시간보다 새로쌓일 시간이 적은 경우
			{
				visit[next.first] = now.second + next.second; 
				q.push({ next.first,now.second + next.second }); // 현재까지 쌓인 시간을 queue에 넣어주는게 중요
			}
		}
	}

	for (int i = 1; i <= n; i++)
	{
		if (visit[i] != INF) // 방문한 노드
		{
			cnt++; // 방문한 노드 개수
			if (time < visit[i]) // 방문한 노드중 가장 오래걸린 시간
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