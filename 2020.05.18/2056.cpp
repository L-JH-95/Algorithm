// 2056 작업

/*
우선순위 큐 사용문제 
크기가 작은 것 부터 먼저 처리되는것이 포인트

처음에 큐에 넣으면 그 이후에는 넣을 필요x
*/

#define _CRT_SECURE_NO_WARNINGS

#define P pair<int,int>
#include <cstdio>
#include <queue>

using namespace std;
int N;
int visit[10001], time[10001]; // 현재까지의 값 저장, 해당 인덱스의 소요 시간

priority_queue <P,vector<P>,greater<P>> pq; // 작은 순서대로 뽑는 큐

int main()
{
	int Max = 0;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
	{
		int n, a, t;
		scanf("%d %d", &t, &n);
		if (n == 0) // 우선으로 처리해야할 인덱스 x -> 바로 저장
			visit[i] = t;

		time[i] = t;
		for (int j = 0; j < n; j++)
		{
			scanf("%d", &a);
			pq.push({ a,i }); // (우선 처리할 인덱스, 다음 처리할 인덱스)
		}
	}
	while (!pq.empty())
	{
		pair<int,int> now = pq.top();
		pq.pop();

		if (visit[now.first] + time[now.second] > visit[now.second]) // 현재보다 합한게 큰 경우만 값 업데이트
			visit[now.second] = visit[now.first] + time[now.second];
		
	}
	for (int i = 1; i <= N; i++) // visit[N]값으로도 가능할듯  -> 불가능 (연관되지 않은 경우 존재)
		if (Max < visit[i])
			Max = visit[i];

	printf("%d\n", Max);
}