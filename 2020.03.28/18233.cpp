// 18233 러버덕을 사랑하는 모임
/*
시간초과문제... -> dfs문제
N,P는 인원이 적어 문제x -> 총 개수가 크다 -> 시간초과
N명 중 P명을 뽑는것이 먼저다 : DFS사용
뽑은 후 가능 한 경우 뽑기
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
	memset(cost, 0, sizeof(cost)); // 내부에서 cost값을 0으로 바꾸었더니 문제가 생긴다
	int num[2] = { 0,0 }; // P명의 최소값의 합과 최대값의 합 저장
	for (int i = 0; i < P; i++)
	{
		num[0] += Min[member[i]];
		num[1] += Max[member[i]];
		cost[member[i]] = Min[member[i]];
	}

	if (num[0] <= E && E <= num[1]) // E가 최소값의 합과 최대값의 합 사이에 있으면 가능
	{
		flag = true; // 한번 가능하면 더이상x
		int duck = E - num[0]; // 추가로 더해줘야할 개수
		for (int i = 0; i < P; i++)
		{
			int d = Max[member[i]] - Min[member[i]]; // i번째 사람에게 최대로 줄 수 있는 최대 러버덕
			if (duck - d >= 0) // 최대 개수를 모두 넣을 수 있는 경우
			{
				cost[member[i]] += d; // 모두 넣기
				duck -= d;
			}
			else // 최대로 넣을 수 없는 경우 
			{ 
				cost[member[i]] += duck; // 가능한 개수만 넣기
				break; // 모든 러버덕 분배 -> stop
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
	if (flag) // 가능한 경우의 수 찾으면 stop
		return;
	if (cnt >= P) // P개 뽑은 경우
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