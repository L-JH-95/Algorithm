// 2056 �۾�

/*
�켱���� ť ��빮�� 
ũ�Ⱑ ���� �� ���� ���� ó���Ǵ°��� ����Ʈ

ó���� ť�� ������ �� ���Ŀ��� ���� �ʿ�x
*/

#define _CRT_SECURE_NO_WARNINGS

#define P pair<int,int>
#include <cstdio>
#include <queue>

using namespace std;
int N;
int visit[10001], time[10001]; // ��������� �� ����, �ش� �ε����� �ҿ� �ð�

priority_queue <P,vector<P>,greater<P>> pq; // ���� ������� �̴� ť

int main()
{
	int Max = 0;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
	{
		int n, a, t;
		scanf("%d %d", &t, &n);
		if (n == 0) // �켱���� ó���ؾ��� �ε��� x -> �ٷ� ����
			visit[i] = t;

		time[i] = t;
		for (int j = 0; j < n; j++)
		{
			scanf("%d", &a);
			pq.push({ a,i }); // (�켱 ó���� �ε���, ���� ó���� �ε���)
		}
	}
	while (!pq.empty())
	{
		pair<int,int> now = pq.top();
		pq.pop();

		if (visit[now.first] + time[now.second] > visit[now.second]) // ���纸�� ���Ѱ� ū ��츸 �� ������Ʈ
			visit[now.second] = visit[now.first] + time[now.second];
		
	}
	for (int i = 1; i <= N; i++) // visit[N]�����ε� �����ҵ�  -> �Ұ��� (�������� ���� ��� ����)
		if (Max < visit[i])
			Max = visit[i];

	printf("%d\n", Max);
}