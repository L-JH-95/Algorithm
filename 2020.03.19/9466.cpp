// 9466 �� ������Ʈ

/*
�ð��ʰ��� �˿� ��������
Union find����ұ ��� -> dfs�� �ذ�

***** Key Point ******
1~N���� ������� dfs�� ������ ������ ���絵������ start���� ������ ���̻� �� �ʿ�x
*/
#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;
int N;
int map[100001], visit[100001];
int group; // �׷��� ������� �л��� ��

bool dfs(int start,int index,int cnt) // ���� �ε���, ���� �ε���, ����� ����
{
	if (visit[index] != 0)
	{
		if (index == start)
		{
			group += cnt;
			return true; //�׷��� ���������� �������
		}
		return false; // �׷� x
	}

	if(index<start) // �����尡 ���۳�庸�� ������ ����Ŭ ���� x
		return;

	visit[index] = 1;
	bool flag = dfs(start, map[index], cnt + 1);
	if (!flag) //cycle�� ��������� �ʾ����� visit�迭�� ����
		visit[index] = 0;
	return flag; // ������ index���� �����ϱ� ����
}

int main()
{
	int Test;
	scanf("%d", &Test);
	for (int T = 1; T <= Test; T++)
	{
		group = 0;
		memset(visit, 0, sizeof(visit));
		scanf("%d", &N);
		for (int i = 1; i <= N; i++)
			scanf("%d", &map[i]);

		for (int i = 1; i <= N; i++)
			if (visit[i] == 0)
				dfs(i, i, 0);

		printf("%d\n", N - group); // ��ü �л��� - �׷������� �л���
	}
}