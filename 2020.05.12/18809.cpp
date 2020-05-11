// 18809 Gaaaaaaaaaarden
/*
dfs -> 빨간 배양액과 초록 배양액을 각 선택
queue는 하나로 가능 : 순서대로 들어가기 때문
*/
#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm> 

using namespace std;
int N, M, R, G;
int map[50][50];
pair<int,int> visit[50][50];
int visit_arr[10];
vector <pair<int, int>> v;
vector <int> Color;
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };

int Max = 0;
struct Garden {
	int x, y;
	int color; // 0 : G, 1 : R
};
queue <Garden> q;

void bfs()
{
	int res = 0;
	int time = 0;
	memset(visit, 0, sizeof(visit));
	for (int i = 0; i < 10; i++)
	{
		if (visit_arr[i] != 0) // 1 : G, 2 : R
		{
			int x = v[i].first, y = v[i].second;
			q.push({ x,y,visit_arr[i] }); // (x,y,color)
			visit[x][y].first = visit_arr[i]; // visit에 저장 -> (color,0)
		}
	}

	while (!q.empty())
	{
		int sz = q.size(); // 시간별로 확인하기 위해
		time++;
		for (int s = 0; s < sz; s++)
		{
			Garden garden = q.front();
			q.pop();

			if (visit[garden.x][garden.y].first == -1) // 이미 꽃이 핀 경우
				continue;

			for (int d = 0; d < 4; d++)
			{
				int xx = garden.x + dx[d], yy = garden.y + dy[d];
				if (xx < 0 || xx >= N || yy < 0 || yy >= M || map[xx][yy] == 0 || visit[xx][yy].first == -1)
					continue;

				if (visit[xx][yy].first == 0) // 아직 방문하지 않은 경우
				{
					visit[xx][yy] = { garden.color,time };
					q.push({ xx,yy,garden.color });
				}
				else if (visit[xx][yy].first != garden.color) // 같은 색이 아니고
				{
					if (visit[xx][yy].second == time) // 시간이 같은 경우
					{
						// 꽃이 핀다
						res++;
						visit[xx][yy].first = -1;
					}
				}
				
			}
		}
	}

	if (res > Max) // 최대값 설정
		Max = res;
}

void Red(int index, int cnt) // 빨간색 선택
{
	if (cnt >= R) // 개수만큼 선택 후 퍼트리기
	{
		bfs();
		return;
	}

	for (int i = index; i < v.size(); i++)
	{
		if (visit_arr[i] == 0)
		{
			visit_arr[i] = 2;
			Red(i, cnt + 1);
			visit_arr[i] = 0;
		}
	}
}
void Green(int index, int cnt)
{
	if (cnt >= G)
	{
		Red(0, 0);
		return;
	}

	for (int i = index; i < v.size(); i++)
	{
		if (visit_arr[i] == 0)
		{
			visit_arr[i] = 1;
			Green(i, cnt + 1);
			visit_arr[i] = 0;
		}
	}
}
int main()
{
	scanf("%d %d %d %d", &N, &M, &R, &G);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
		{
			scanf("%d", &map[i][j]);
			if (map[i][j] == 2)
				v.push_back({ i,j });
		}

	Green(0, 0);

	printf("%d\n", Max);
}