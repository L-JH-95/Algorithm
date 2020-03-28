// 18233 �������� ����ϴ� ����
/*
�ð��ʰ�����... -> dfs����
N,P�� �ο��� ���� ����x -> �� ������ ũ�� -> �ð��ʰ�
N�� �� P���� �̴°��� ������ : DFS���
���� �� ���� �� ��� �̱�
*/

#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm> 

using namespace std;

int N, P, E;
int cost[20];
int Min[20],Max[20];
int member[20];
bool flag = false;


void check()
{
	memset(cost, 0, sizeof(cost)); // ���ο��� cost���� 0���� �ٲپ����� ������ �����
	int num[2] = { 0,0 }; // P���� �ּҰ��� �հ� �ִ밪�� �� ����
	for (int i = 0; i < P; i++)
	{
		num[0] += Min[member[i]];
		num[1] += Max[member[i]];
		cost[member[i]] = Min[member[i]];
	}

	if (num[0] <= E && E <= num[1]) // E�� �ּҰ��� �հ� �ִ밪�� �� ���̿� ������ ����
	{
		flag = true; // �ѹ� �����ϸ� ���̻�x
		int duck = E - num[0]; // �߰��� ��������� ����
		for (int i = 0; i < P; i++)
		{
			int d = Max[member[i]] - Min[member[i]]; // i��° ������� �ִ�� �� �� �ִ� �ִ� ������
			if (duck - d >= 0) // �ִ� ������ ��� ���� �� �ִ� ���
			{
				cost[member[i]] += d; // ��� �ֱ�
				duck -= d;
			}
			else // �ִ�� ���� �� ���� ��� 
			{ 
				cost[member[i]] += duck; // ������ ������ �ֱ�
				break; // ��� ������ �й� -> stop
			}
		}
		for (int i = 0; i < N; i++)
		{
			printf("%d ", cost[i]);
		}
		printf("\n");
	}

}

void find_member(int index,int cnt)
{
	if (flag) // ������ ����� �� ã���� stop
		return;
	if (cnt >= P) // P�� ���� ���
	{
		check();
		return;
	}

	for (int i = index; i < N; i++)
	{
		member[cnt] = i;
		find_member(i + 1, cnt + 1);
	}
}

int main()
{
	scanf("%d %d %d", &N, &P, &E);
	int cnt = 0;
	for (int i = 0; i < N; i++)
	{
		int x, y;
		scanf("%d %d", &x, &y);
		Min[i] = x;
		Max[i] = y;
	}

	find_member(0, 0);
	if (!flag)
		printf("-1\n");


}