// 13549. 숨바꼭질 3
/*
가중치가 다르므로(이동 : 1, 순간이동 :0 ) 다익스트라 이용
범위 0~N : 0과 N을 모두 포함
*/

#define _crt_secure_no_warnings
#define p pair<int,int>
#define INF 2147000000
#define Max 100000

#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;
int n, k;
int visit[Max + 1]; // 다익스트라로 사용할 배열
int dx[2] = { 1,-1 }; 

struct Move {
	int x;
	int now;
};
queue <Move> q;

void bfs()
{
	visit[n] = 0;
	q.push({ n,0 });
	while (!q.empty())
	{
		Move m = q.front();
		q.pop();

		for (int d = 0; d < 2; d++) // 일반이동 (한칸이동) : 가중치 1
		{
			int xx = m.x + dx[d];
			if (xx<0 || xx>Max)
				continue;
			if (visit[xx] > m.now + 1)
			{
				visit[xx] = m.now + 1;
				q.push({ xx,visit[xx] });
			}
		}
		if (2 * m.x <= Max) // 순간이동 (현재위치의 반) : 가중치 0
		{
			if (visit[2 * m.x] > m.now)
			{
				visit[2 * m.x] = m.now;
				q.push({ 2 * m.x,visit[2 * m.x] });
			}
		}
	}
}

int main()
{
	scanf("%d %d", &n, &k);
	fill(visit, visit + 1 + Max, INF);
	bfs();
	printf("%d\n", visit[k]);
}