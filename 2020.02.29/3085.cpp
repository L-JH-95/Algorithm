// 사탕게임


#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <queue>

using namespace std;

int N;
char map[51][51];

// 4방향을 체크할 필요 없이 두방향 체크로 중복확인 피하기
int dx[2] = { 0,1 };
int dy[2] = { 1,0 };
int Max = 0;

void candy() // 같은 행/열 에서 같은 색 사탕의 최대 개수 구하기
{
	int cnt = 1;

	for (int i = 0; i < N; i++) // 같은 행 확인
	{
		cnt = 1;
		for (int j = 1; j < N; j++)
		{
			if (map[i][j] == map[i][j - 1])
				cnt++;
			else
			{
				if (cnt > Max)
					Max = cnt;
				cnt = 1;
			}
		}
		if (cnt > Max) // 이부분 안넣어서 틀림 마지막을 세주는 경우까지 확인할것
			Max = cnt;
	}

	for (int j = 0; j < N; j++) // 같은 열 확인
	{
		cnt = 1;
		for (int i = 1; i < N; i++)
		{
			if (map[i][j] == map[i - 1][j])
				cnt++;
			else
			{
				if (cnt > Max)
					Max = cnt;
				cnt = 1;
			}
		}
		if (cnt > Max)
			Max = cnt;
	}
}


int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%s", map[i]);

	for(int i=0;i<N;i++)
		for (int j = 0; j < N; j++)
		{
			for (int d = 0; d < 2; d++)
			{
				int xx = i + dx[d], yy = j + dy[d];
				if (xx < 0 || xx >= N || yy < 0 || yy >= N || map[i][j] == map[xx][yy])
					continue;

				char temp = map[i][j];
				map[i][j] = map[xx][yy];
				map[xx][yy] = temp;

				candy();

				temp = map[i][j];
				map[i][j] = map[xx][yy];
				map[xx][yy] = temp;

			}
		}

	printf("%d\n", Max);
}