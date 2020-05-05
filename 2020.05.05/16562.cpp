// 16562 친구비
/*
MST문제
이미 친구인 경우 Union -> pq사용해서 가격이 싼 경우부터 확인
1~N까지가 index범위이므로 새롭게 된 친구는 0으로 저장
*/

#define _CRT_SECURE_NO_WARNINGS
#define P pair<int,int>

#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;
int N, M, K;
priority_queue <P,vector<P>,greater<P>> q; // 따로 비교함수를 넣지 않기 위해 <가격, 인덱스>로 저장
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
	memset(root, -1, sizeof(root)); // 모든 경우 -1로 초기화
	for (int k, i = 0; i < N; i++)
	{
		scanf("%d", &k);
		q.push({ k,i + 1 }); // (가격, 인덱스) 순서로 저장
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

		if (Find(p.second) != 0) { // 나와 친구가 아닌경우
			if (sum - p.first >= 0) // 가격 지불 가능
			{
				int rb = Find(p.second); 
				root[rb] = 0;// Union함수의 역할 -> 단 으로 저장
				sum -= p.first;
			}
		}
	}
	bool flag = true; // 친구비 지불 가능

	for (int i = 1; i <= N; i++)
	{
		if (root[i] == -1) // 나와 연결되지 않은 경우
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