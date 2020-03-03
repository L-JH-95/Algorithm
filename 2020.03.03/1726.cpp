// 로봇
/*
방향을 bit로 체크하면 3차원까지 필요없을듯 -> 메모리 줄이기가능
중복안되는 부분 잘 체크하자
*/

#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <queue>

using namespace std;
int N, M;
int map[101][101];
int visit[5][101][101]; // 방향마다 방문한 위치를 확인하기 위해 3차원 배열 사용

int dx[5] = { 0,0,0,1,-1 };
int dy[5] = { 0,1,-1,0,0 };

struct Robot {
	int x, y;
	int dir;
	int num;
};
struct cmp {
	bool operator()(Robot a, Robot b) {
		return a.num > b.num;
	}
};

priority_queue <Robot,vector<Robot>,cmp> q; // num이 작은 순서대로 q를 사용하기 위해 pq
Robot Arrive; // 도착지점
int res;

void bfs()
{
	while (!q.empty())
	{
		Robot r = q.top();
		q.pop();

		if (r.x == Arrive.x&&r.y == Arrive.y&&r.dir == Arrive.dir)
		{
			res = r.num;
			return;
		} 


		for (int k = 1; k <= 3; k++) // Go명령
		{
			int xx = r.x + dx[r.dir] * k, yy = r.y + dy[r.dir] * k;
			if (xx<1 || xx>N || yy<1 || yy>M || map[xx][yy] == 1) //막혀있거나 범위 벗어나면 break
				break;
			if (visit[r.dir][xx][yy] != 0) // 방문했던 곳은 건너뛰고 다음으로
				continue;
			q.push({ xx,yy,r.dir,r.num + 1 });
			visit[r.dir][xx][yy] = 1;
		}

		int dd; // 현재와 반대 방향 구하기
		if (r.dir % 2 == 0)
			dd = r.dir - 1;
		else
			dd = r.dir + 1;
		for (int d = 1; d <= 4; d++) 
		{
			if (d == r.dir || d == dd)// 현재방향과 반대방향을 제외( 왼쪽, 오른쪽 )
				continue;
			if (visit[d][r.x][r.y] == 0)
			{
				q.push({ r.x,r.y,d,r.num + 1 });
				visit[d][r.x][r.y] = 1;
			}
		}
	}
}


int main()
{
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			scanf("%d", &map[i][j]);

	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);
	q.push({ a,b,c,0 });
	visit[c][a][b] = 1;
	scanf("%d %d %d", &a, &b, &c);
	Arrive = Robot({ a,b,c,0 });

	bfs();
	printf("%d\n", res);

}