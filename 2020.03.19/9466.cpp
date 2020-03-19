// 9466 텀 프로젝트

/*
시간초과의 늪에 빠진문제
Union find사용할까도 고민 -> dfs로 해결

***** Key Point ******
1~N까지 순서대로 dfs를 돌리기 때문에 현재도착점이 start보다 작으면 더이상 볼 필요x
*/
#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;
int N;
int map[100001], visit[100001];
int group; // 그룹이 만들어진 학생의 수

bool dfs(int start,int index,int cnt) // 시작 인덱스, 현재 인덱스, 노드의 개수
{
	if (visit[index] != 0)
	{
		if (index == start)
		{
			group += cnt;
			return true; //그룹이 성공적으로 만들어짐
		}
		return false; // 그룹 x
	}

	if(index<start) // 현재노드가 시작노드보다 작으면 사이클 생성 x
		return;

	visit[index] = 1;
	bool flag = dfs(start, map[index], cnt + 1);
	if (!flag) //cycle이 만들어지지 않았으면 visit배열을 복구
		visit[index] = 0;
	return flag; // 나머지 index에도 적용하기 위해
}

int main()
{
	int Test;
	scanf("%d", &Test);
	for (int T = 1; T <= Test; T++)
	{
		group = 0;
		memset(visit, 0, sizeof(visit));
		scanf("%d", &N);
		for (int i = 1; i <= N; i++)
			scanf("%d", &map[i]);

		for (int i = 1; i <= N; i++)
			if (visit[i] == 0)
				dfs(i, i, 0);

		printf("%d\n", N - group); // 전체 학생수 - 그룹지어진 학생수
	}
}