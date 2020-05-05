// 1329 파티
/*
bfs + 다익스트라
모든 점 -> X, X -> 모든 점을 모두 만족해야함
=> 기존 주어진 그래프 : 돌아 갈때의 다익스트라
=> 기존 그래프의 시작, 도착반대로 : 원래(모든 점 -> X) -> (X->모든점)
두가지 그래프를 통해 올때, 갈때를 알수 있다

priority_queue를 사용하면 속도빨라질듯
*/

#define _CRT_SECURE_NO_WARNINGS
#define INF 2147000000

#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;
int N, M, X;
vector <pair<int, int>> TOX[1001], FROMX[1001]; // 두가지 방향의 그래프를 저장
int tox[1001], fromx[1001]; // 두가지 방향의 값을 저장할 배열
queue <pair<int, int>> q;

void FromX()
{
	fromx[X] = 0; // X에서 돌아갈때
	q.push({ X,0 });

	while (!q.empty())
	{
		pair<int, int> p = q.front();
		q.pop();

		if (fromx[p.first] < p.second) // pq일때 더 유용할 듯
			continue;

		for (int i = 0; i < FROMX[p.first].size(); i++)
		{
			pair<int, int> now = FROMX[p.first][i];
			if (p.second + now.second < fromx[now.first]) // 값이 더 작을 때만 in
			{
				fromx[now.first] = p.second + now.second;
				q.push({now.first,fromx[now.first] });
			}
		}
	}
}

void ToX() // FromX와 같은 알고리즘
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
	for (int i = 1; i <= N; i++) // 오고 갈때의 합이 가장 큰 값 구하기
	{
		if (fromx[i] + tox[i] > res)
			res = fromx[i] + tox[i];
	}
	printf("%d\n", res);
}
