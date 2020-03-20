//13023 ABCDE
/* 
총 다섯명이 서로의 친구여야하는 문제
*/

#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

int N, M;
vector <int> map[2000]; // 인접행렬
int visit[2000];
bool flag = false; // 조건을 만족하는 친구 5명이 존재하면 true

void dfs(int index,int depth)
{
	if (flag || visit[index] != 0) // 이미완성된 친구가 있으면 더이상 볼필요x
		return;

	visit[index] = 1;
	if (depth == 4) // 사람이 5명 -> 간선 4개
	{
		flag = true;
		return;
	}

	for (int i = 0; i < map[index].size(); i++)
		dfs(map[index][i], depth + 1);

	visit[index] = 0;
}

int main()
{
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; i++)
	{
		int a, b;
		scanf("%d %d",&a, &b);
		map[a].push_back(b);
		map[b].push_back(a);
	}

	for (int i = 0; i < N; i++)
		if (!flag)
			dfs(i, 0);
	printf("%d\n", flag);
}