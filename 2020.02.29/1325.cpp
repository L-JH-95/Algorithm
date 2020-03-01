// 효율적인 해킹
/*
dp를 사용하려고 했으나 cycle이 성립되는 경우 중복되는 경우가 생김
-> queue를 이용하여 bfs를 돌림
-> 값 저장대신 바로바로 체크해줘도 될듯
*/

#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

int N, M;
int visit[10001],dp[10001]; 
vector <int> v[10001];
queue <int> q;

int main()
{
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; i++)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		v[b].push_back(a);
	}

	for (int i = 1; i <= N; i++) // 1번 컴퓨터부터 순서대로 사이클 그리기
	{
		memset(visit, 0, sizeof(visit));
		if (v[i].size() == 0 || visit[i] != 0)
			continue;

		int cnt = 0;
		visit[i] = 1;
		q.push(i);
		while (!q.empty()) // visit 체크 하며 중복하지 않고 해킹할 경우의 수 구하기
		{
			int n = q.front();
			q.pop();

			for (int s = 0; s < v[n].size(); s++)
			{
				if (visit[v[n][s]] != 0)
					continue;

				// 여기서 v[n][s]의 size가 0보다 큰경우만 count해서 틀림
				// -> 한번에 세려고 size로 체크해서 안된듯
				visit[v[n][s]] = 1;
				q.push(v[n][s]);
				cnt++;
			}
		}
		dp[i] = cnt; // 해킹 가능 한 값 저장
	}

	vector <int> res;
	int Max = 0;

	for (int i = 1; i <= N; i++) //저장한 값중 가장 큰 값을 번호대로 정렬하기
	{
		if (dp[i] > Max)
		{
			Max = dp[i];
			res.clear();
			res.push_back(i);
		}
		else if (dp[i] == Max)
			res.push_back(i);
	}
	for (int i = 0; i < res.size(); i++)
		printf("%d ", res[i]);
	printf("\n");
}