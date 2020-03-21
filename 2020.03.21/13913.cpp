// 13913 숨바꼭질4
/*
0도 범위에 포함되므로 -1로 초기화해야 메모리 초과x
*/

#define _CRT_SECURE_NO_WARNINGS
#define P pair<int,int>
#define Max 100000

#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;
int N, K;
int visit[Max + 1]; // 부모 노드 저장
int dx[2] = { 1,-1 };
priority_queue <P,vector<P>,greater<P>> q; //greater를 사용하므로 first를 시간이 오게 하기
int Min = 987654321;
vector <int> v;

void bfs()
{
	visit[N] = -5; // 초기값인 -1과 범위를 제외한 수 : -5로 설정
	q.push({ 0,N }); //(시간, 점)

	while (!q.empty())
	{
		P p = q.top();
		q.pop();

		if (p.second == K) // 동생이 있는 곳 도착하면 return : pq사용으로 최소값 보장
		{
			Min = p.first;
			return;
		}

		for (int d = 0; d < 2; d++)
		{
			int xx = p.second + dx[d];
			if (xx<0 || xx>Max)
				continue;

			if (visit[xx] == -1) // 시작점을 -5로 설정하므로 -1일때만 실행
			{
				visit[xx] = p.second;
				q.push({ p.first + 1,xx });
			}
		}

		if (2 * p.second <= Max && visit[2 * p.second] == -1)
		{
			visit[2 * p.second] = p.second;
			q.push({ p.first + 1,2 * p.second });
		}
	}

}

void dfs(int index) // 부모값을 찾아가는 함수 : K부터 올라가기
{
	v.push_back(index);
	if (index != N) // 언니각 있는 곳이 아니면 계속 들어간다
		dfs(visit[index]);
}

int main()
{
	memset(visit, -1, sizeof(visit));
	scanf("%d %d", &N, &K);
	bfs();
	printf("%d\n", Min);
	dfs(K);
	for (int i = v.size() - 1; i >= 0; i--) // K부터 시작하므로 뒤에서 부터 출력
		printf("%d ", v[i]);
	
	printf("\n");
}
