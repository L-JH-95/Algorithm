//13023 ABCDE
/* 
�� �ټ����� ������ ģ�������ϴ� ����
*/

#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

int N, M;
vector <int> map[2000]; // �������
int visit[2000];
bool flag = false; // ������ �����ϴ� ģ�� 5���� �����ϸ� true

void dfs(int index,int depth)
{
	if (flag || visit[index] != 0) // �̹̿ϼ��� ģ���� ������ ���̻� ���ʿ�x
		return;

	visit[index] = 1;
	if (depth == 4) // ����� 5�� -> ���� 4��
	{
		flag = true;
		return;
	}

	for (int i = 0; i < map[index].size(); i++)
		dfs(map[index][i], depth + 1);

	visit[index] = 0;
}

int main()
{
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; i++)
	{
		int a, b;
		scanf("%d %d",&a, &b);
		map[a].push_back(b);
		map[b].push_back(a);
	}

	for (int i = 0; i < N; i++)
		if (!flag)
			dfs(i, 0);
	printf("%d\n", flag);
}