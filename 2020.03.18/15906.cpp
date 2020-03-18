// 15906 
/*
bfs + 다익스트라 (dp)
cost값은 계속 바뀌기 때문에 현재 저장되어있는 값이 아닌 st에 저장되엉있는 time을 이용하여 비교
*/
/*
다익스트라
- 특정 정점에서 특정 정점으로 갈때의 최단 경로
- BFS가 기본
- 음수일때는 사용x
*/

#define _CRT_SECURE_NO_WARNINGS
#define INF 2147000000;

#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;
int N, T, R, C;
int cost[2][501][501]; // (1,1) 에서 (x,y)까지의 최소길이 : cost[mode][x][y]
char map[502][502];
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };
int Min;

struct st {
	int x, y;
	int mode;
	int time;
};

queue <st> q;

void Dijk() // bfs + 다익스트라
{
	cost[0][1][1] = 0;
	q.push({ 1,1,0,0 });

	while (!q.empty())
	{
		st s = q.front();
		q.pop();

		if (s.mode == 0) // 일반모드
		{
			for (int d = 0; d < 4; d++) // 4방향으로 1칸씩
			{
				int xx = s.x + dx[d], yy = s.y + dy[d];
				if (xx<1 || xx>N || yy<1 || yy>N)
					continue;
				if (s.time + 1 < cost[s.mode][xx][yy])
				{
					cost[s.mode][xx][yy] = s.time + 1;
					q.push({ xx,yy,s.mode,cost[s.mode][xx][yy] });
				}
			}
			int mode = (s.mode + 1) % 2; // 일반모드

			if (s.time + T < cost[mode][s.x][s.y])
			{
				cost[mode][s.x][s.y] = s.time + T; // 일반 -> 변신 : 가중치 T
				q.push({ s.x,s.y,mode,cost[mode][s.x][s.y] });
			}
			
		}
		else {
			for (int d = 0; d < 4; d++) // 4방향
			{ 
				int xx = s.x, yy = s.y;
				while (1) // #찾기
				{
					xx += dx[d], yy += dy[d];
					if (xx<1 || xx>N || yy<1 || yy>N) // 범위를 벗어나면 그방향으로 가지x
						break;
					if (map[xx][yy] == '#')
					{
						if (s.time + 1 < cost[s.mode][xx][yy]) // 워프가 있더라도 현재값+가중치가 더작으면 go
						{
							cost[s.mode][xx][yy] = s.time + 1;
							q.push({ xx,yy,s.mode,cost[s.mode][xx][yy] });
						}
						break;
					}
				}
			}
			int mode = (s.mode + 1) % 2; // 일반모드

			if (s.time< cost[mode][s.x][s.y]) // 변신 -> 일반 : 가중치 0
			{
				cost[mode][s.x][s.y] = s.time;
				q.push({ s.x,s.y,mode ,cost[mode][s.x][s.y] });
			}
			
		}
	}
}

int main()
{
	scanf("%d %d %d %d", &N, &T, &R, &C);
	for (int i = 1; i <= N; i++)
	{
		scanf("%s", map[i] + 1);
		for (int j = 1; j <= N; j++) // 가장 큰값으로 cost 초기화
		{
			cost[0][i][j] = INF;
			cost[1][i][j] = INF;
		}
	}

	Dijk();
	Min = cost[0][R][C];
	if (Min > cost[1][R][C])
		Min = cost[1][R][C];

	printf("%d\n", Min);
}