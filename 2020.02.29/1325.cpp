// ȿ������ ��ŷ
/*
dp�� ����Ϸ��� ������ cycle�� �����Ǵ� ��� �ߺ��Ǵ� ��찡 ����
-> queue�� �̿��Ͽ� bfs�� ����
-> �� ������ �ٷιٷ� üũ���൵ �ɵ�
*/

#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

int N, M;
int visit[10001],dp[10001]; 
vector <int> v[10001];
queue <int> q;

int main()
{
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; i++)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		v[b].push_back(a);
	}

	for (int i = 1; i <= N; i++) // 1�� ��ǻ�ͺ��� ������� ����Ŭ �׸���
	{
		memset(visit, 0, sizeof(visit));
		if (v[i].size() == 0 || visit[i] != 0)
			continue;

		int cnt = 0;
		visit[i] = 1;
		q.push(i);
		while (!q.empty()) // visit üũ �ϸ� �ߺ����� �ʰ� ��ŷ�� ����� �� ���ϱ�
		{
			int n = q.front();
			q.pop();

			for (int s = 0; s < v[n].size(); s++)
			{
				if (visit[v[n][s]] != 0)
					continue;

				// ���⼭ v[n][s]�� size�� 0���� ū��츸 count�ؼ� Ʋ��
				// -> �ѹ��� ������ size�� üũ�ؼ� �ȵȵ�
				visit[v[n][s]] = 1;
				q.push(v[n][s]);
				cnt++;
			}
		}
		dp[i] = cnt; // ��ŷ ���� �� �� ����
	}

	vector <int> res;
	int Max = 0;

	for (int i = 1; i <= N; i++) //������ ���� ���� ū ���� ��ȣ��� �����ϱ�
	{
		if (dp[i] > Max)
		{
			Max = dp[i];
			res.clear();
			res.push_back(i);
		}
		else if (dp[i] == Max)
			res.push_back(i);
	}
	for (int i = 0; i < res.size(); i++)
		printf("%d ", res[i]);
	printf("\n");
}