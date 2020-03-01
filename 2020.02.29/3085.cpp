// ��������


#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <queue>

using namespace std;

int N;
char map[51][51];

// 4������ üũ�� �ʿ� ���� �ι��� üũ�� �ߺ�Ȯ�� ���ϱ�
int dx[2] = { 0,1 };
int dy[2] = { 1,0 };
int Max = 0;

void candy() // ���� ��/�� ���� ���� �� ������ �ִ� ���� ���ϱ�
{
	int cnt = 1;

	for (int i = 0; i < N; i++) // ���� �� Ȯ��
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
		if (cnt > Max) // �̺κ� �ȳ־ Ʋ�� �������� ���ִ� ������ Ȯ���Ұ�
			Max = cnt;
	}

	for (int j = 0; j < N; j++) // ���� �� Ȯ��
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