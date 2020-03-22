// 1939 중량 제한
/*
bfs + 다익스트라
최소값이아닌 최대 구하는 문제 -> 0으로 초기화 된상태로 시작
도착 점에 도달하거나 현재 cost보다 작은 값을 가지고 있으면 continue!! -> 안하면 메모리 초과
시작 부터 queue에 넣지 x -> 연결된 점부터
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

	for (int i = 0; i < map[Start].size(); i++) // 시작점에서 연결된 점부터 queue에 넣는다
	{
		q.push({ map[Start][i] });
		cost[map[Start][i].first] = map[Start][i].second;
	}

	while (!q.empty())
	{
		pair<int, int> p = q.front();
		q.pop();

		if (p.first == End || p.second < cost[p.first]) // 안하면 메모리 초과 도착점에 도달했으면 더이상 가지x
			continue;

		for (int i = 0; i < map[p.first].size(); i++)
		{
			pair<int, int> temp = map[p.first][i];
			// temp.second < p.second 이면 temp.second의 무게까지만 지나갈 수 있다 
			int m = min(temp.second, p.second); // 더 작은 값이 최대로 건널 수 있는 무게
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