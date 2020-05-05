// 16562 ģ����
/*
MST����
�̹� ģ���� ��� Union -> pq����ؼ� ������ �� ������ Ȯ��
1~N������ index�����̹Ƿ� ���Ӱ� �� ģ���� 0���� ����
*/

#define _CRT_SECURE_NO_WARNINGS
#define P pair<int,int>

#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;
int N, M, K;
priority_queue <P,vector<P>,greater<P>> q; // ���� ���Լ��� ���� �ʱ� ���� <����, �ε���>�� ����
int root[10001];

int Find(int a)
{
	if (root[a] == -1)
		return a;
	return root[a] = Find(root[a]);
}

void Union(int a, int b) {
	int ra = Find(a), rb = Find(b);
	if (ra == rb)
		return;

	root[rb] = ra;	
}

int main()
{
	scanf("%d %d %d", &N, &M, &K);
	memset(root, -1, sizeof(root)); // ��� ��� -1�� �ʱ�ȭ
	for (int k, i = 0; i < N; i++)
	{
		scanf("%d", &k);
		q.push({ k,i + 1 }); // (����, �ε���) ������ ����
	}
	for (int v, w, i = 0; i < M; i++)
	{
		scanf("%d %d", &v, &w);
		Union(v, w);
	}

	int sum = K;
	while (!q.empty()) {
		P p = q.top();
		q.pop();

		if (Find(p.second) != 0) { // ���� ģ���� �ƴѰ��
			if (sum - p.first >= 0) // ���� ���� ����
			{
				int rb = Find(p.second); 
				root[rb] = 0;// Union�Լ��� ���� -> �� ���� ����
				sum -= p.first;
			}
		}
	}
	bool flag = true; // ģ���� ���� ����

	for (int i = 1; i <= N; i++)
	{
		if (root[i] == -1) // ���� ������� ���� ���
		{
			flag = false; 
			break;
		}
	}
	if (flag)
		printf("%d\n", K - sum);
	else
		printf("Oh no\n");
}