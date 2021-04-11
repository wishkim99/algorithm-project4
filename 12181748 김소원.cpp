#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <cstdio>
#include <cstring>
#pragma warning(disable 4996)
#define CLOCKS_PER_SEC 1000 //프로그램 수행시간 측정

#define COL 4  // 데이터셋의 크기(열과 행의 숫자를늘림 (4,6,8,9,10.... 같은 순으로 증가)
#define ROW 4// 데이터셋의 크기


int check(int); // 해당 위치에 퀸이 놓여도 되는지 체크
int n; //퀸의 갯수
int col[300] = { 0, };	// 행에 놓이는 값(0부터 시작) 
int ans = 0;  // 최종 값

void backTracking(int i) { //backtracking 함수
	if (check(i))
	{//끝까지 진행가능한 경우 1 증가
		if (i == n) { //i가 퀸의 갯수일 때
			ans++;	// 총 갯수를 구함
		}
		else {
			for (int j = 1; j <= n; j++) {  //j가 1부터 n의 갯수까지 돌 때
				col[i + 1] = j;  //행의 기존자리 다음 칸의 행 값은 j
				backTracking(i + 1); //다음 퀸 위치 찾기
			}
		}
	}
}

int check(int i) { // 직선, 대각선으로 만나는지 검사

	int q = 1; //변수 선언
	int check = 1;

	while (q < i && check) {//직선이나 대각선상에 퀸이 있는지 검사
		if (col[i] == col[q] || abs(col[i] - col[q]) == abs(i - q))
		{//새로운 퀸과 기존의 퀸이 같은 행에 있거나 대각선에 있는 경우
			check = 0; //false
		}
		q++; //1 카운트
	}

	return check; //직선, 대각선으로 만나는지 검사한 check 값 반환

}

int getRand(int mod) { //genetic algorithm을 사용하는데 필요한 랜드 함수
	if (mod == 0) //나머지가 없을 때, 즉 mod값이 0일때
		return 0; //0 리턴
	else
		return rand() % mod; //랜덤으로 생성한 수의 나머지
}

void printArr(int array[]) { ////genetic algorithm을 사용하는데 필요한 출력 함수
	int i;
	for (i = 0; i<COL - 1; i++) //i가 행의 갯수만큼 돌 때 (col-1인 이유는 0부터 시작
		printf("(%i,%i),", i, array[i]); //배열 출력
	printf("(%i,%i)", COL - 1, array[COL - 1]); //열 출력
	printf("\n"); //줄 바꿈
}

int getSize(int array[]) { //genetic algorithm을 사용하는데 필요한 함수
	int size = 30; //크기 임의로 설정
	int queen; //퀸
	for (queen = 0; queen<COL; queen++) {    //퀸이 열의 갯수만큼 도는 동안
		int nextqueen; //다음 퀸 선언
		for (nextqueen = queen + 1; nextqueen<COL; nextqueen++) { //겹치지 않을 경우 다음 퀸 
			if (array[queen] == array[nextqueen] || abs(queen - nextqueen) == abs(array[queen] - array[nextqueen])) {//직선이나 대각선상에 퀸이 있는지 검사
				size--; //겹칠 경우 감소
			}
		}
	}
	return size; //size 값 리턴
}

void geneticAlgorithm() { //genetic algorithm 함수
	int population[ROW][COL]; //모집단
	int children[ROW][COL]; //자식 유전자
	int sizeProb[224] = {};
	int sLength = 0; //sizeProb[]의 길이
	double mutProb = 0.2; //생산속도 빠르게 해줌

	int end = 0;
	int i;
	for (i = 0; i<ROW; i++) //i는 열
		for (int j = 0; j<COL; j++) //j는 행만큼 돌 때
			population[i][j] = getRand(COL); //모집단은 랜덤으로 생성한 배열
	while (end == 0) { //end의 값이 0이될 때
		for (i = 0; i<ROW; i++) { //i가 열만큼 for문을 돌 때
			if (getSize(children[i]) == 30) { //자식 배열의 getSize는 30, 즉 최대가 됨
				printf("퀸이 올 수 있는 자리");
				printf("\n"); //줄바꿈
				printf("=>");
				printArr(children[i]); //자식 유전자 출력
				end = 1;
			}
		}

		for (i = 0; i< sLength; i++) //i가 sizeProb의 길이만큼 for문을 돌 때
			sizeProb[i] = (int)NULL; //sizeProb 초기화
		sLength = 0; //sizeProb의 길이 0

		for (i = 0; i<ROW; i++) { //i가 열만큼 돌 때
			int s = getSize(population[i]); //s는 모집단의 getSize
			for (int j = 0; j<s; j++) {//j가 모집단의 getSize만큼 돌 때
				sizeProb[sLength] = i; //구성원 번호로배열 길이 채움
				sLength++; //길이증가
			}
		}

		//선택(selection)
		for (i = 0; i<ROW; i += 2) { //i가 열까지 2씩 증가
			int se1 = sizeProb[getRand(sLength)];
			int se2 = sizeProb[getRand(sLength)]; //두개의 배열 선언
			int select = getRand(COL); //랜덤으로 선택한다

									   //교차(crossover)
			for (int j = 0; j<select; j++) { //랜덤으로 무작위 선택한 내에서
				children[i][j] = population[se1][j]; //자식과 모집단 배열 일부를 교차
				children[i + 1][j] = population[se2][j]; //자식과 모집단 배열 일부를 교차
			}
			for (int j = select; j<COL; j++) { //j가 열까지 for문을 돌 동안
				children[i][j] = population[se2][j];//자손과 모집단 배열 일부를 교차
				children[i + 1][j] = population[se1][j];//자손과 모집단 배열 일부를 교차(교차점 도달 할 때까지)
			}
			//돌연변이(mutation)
			if (getRand(1000000) <= mutProb * 1000000) {
				int child = getRand(2); //무작위로 뽑음
				if (child == 0) //자식이 0일때
					children[i][getRand(COL)] = getRand(COL); //무작위로 생성된 열의 일부가 바뀜
				else
					children[i + 1][getRand(COL)] = getRand(COL); //무작위로 생성된 열의 일부가 바뀜
			}
		}
		for (i = 0; i<ROW; i++) //i가 열만큼 돌동안
			for (int j = 0; j<COL; j++)  //j는 행만큼 돌동안
				population[i][j] = children[i][j]; //모집단과 자식이 동일
		sLength = 0;
	}
}

int main(void) {
    ////////////백트래킹////////////////////

	clock_t start, finish; //수행시간의 시작, 끝 시간
	double duration; //수행시간
	printf(" <<Backtracking 이용>>");
	printf("\n"); //줄바꿈
	printf("퀸 갯수 입력: ");
	start = clock(); // 시작지점 시간
	scanf_s("%d", &n);
	backTracking(0); //백트래킹 호출

	printf("가능한 경우의 수: ");
	printf("%d", ans); //최종 갯수 호출
	printf("\n"); //줄바꿈

	finish = clock(); //끝나는 시간
	duration = (double)(finish - start) / CLOCKS_PER_SEC; // (종료지점 시간 - 시작지점 시간)/1000
	printf("수행시간: ");
	printf("%f초", duration);

	printf("\n"); //줄바꿈
	 ///////////////////////////유전자 알고리즘///////////////////////
	printf("\n"); //줄바꿈
	clock_t startt, ffinish; ////수행시간의 시작, 끝 시간
	double dduration; //수행시간
	startt = clock(); // 시작지점 시간
	printf(" <<유전자 알고리즘(Genetic Algorithm) 이용>>");
	printf("\n"); //줄바꿈
	srand((unsigned int)time(NULL));  //seed random
	geneticAlgorithm(); //genetic 알고리즘 호출
	ffinish = clock(); // 종료지점 시간
	dduration = (double)(ffinish - startt) / CLOCKS_PER_SEC; // (종료지점 시간 - 시작지점 시간)/1000
	printf("수행시간: ");
	printf("%f초", dduration);
	printf("\n"); //줄바꿈

	return 0;

}






