#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <cstdio>
#include <cstring>
#pragma warning(disable 4996)
#define CLOCKS_PER_SEC 1000 //���α׷� ����ð� ����

#define COL 4  // �����ͼ��� ũ��(���� ���� ���ڸ��ø� (4,6,8,9,10.... ���� ������ ����)
#define ROW 4// �����ͼ��� ũ��


int check(int); // �ش� ��ġ�� ���� ������ �Ǵ��� üũ
int n; //���� ����
int col[300] = { 0, };	// �࿡ ���̴� ��(0���� ����) 
int ans = 0;  // ���� ��

void backTracking(int i) { //backtracking �Լ�
	if (check(i))
	{//������ ���డ���� ��� 1 ����
		if (i == n) { //i�� ���� ������ ��
			ans++;	// �� ������ ����
		}
		else {
			for (int j = 1; j <= n; j++) {  //j�� 1���� n�� �������� �� ��
				col[i + 1] = j;  //���� �����ڸ� ���� ĭ�� �� ���� j
				backTracking(i + 1); //���� �� ��ġ ã��
			}
		}
	}
}

int check(int i) { // ����, �밢������ �������� �˻�

	int q = 1; //���� ����
	int check = 1;

	while (q < i && check) {//�����̳� �밢���� ���� �ִ��� �˻�
		if (col[i] == col[q] || abs(col[i] - col[q]) == abs(i - q))
		{//���ο� ���� ������ ���� ���� �࿡ �ְų� �밢���� �ִ� ���
			check = 0; //false
		}
		q++; //1 ī��Ʈ
	}

	return check; //����, �밢������ �������� �˻��� check �� ��ȯ

}

int getRand(int mod) { //genetic algorithm�� ����ϴµ� �ʿ��� ���� �Լ�
	if (mod == 0) //�������� ���� ��, �� mod���� 0�϶�
		return 0; //0 ����
	else
		return rand() % mod; //�������� ������ ���� ������
}

void printArr(int array[]) { ////genetic algorithm�� ����ϴµ� �ʿ��� ��� �Լ�
	int i;
	for (i = 0; i<COL - 1; i++) //i�� ���� ������ŭ �� �� (col-1�� ������ 0���� ����
		printf("(%i,%i),", i, array[i]); //�迭 ���
	printf("(%i,%i)", COL - 1, array[COL - 1]); //�� ���
	printf("\n"); //�� �ٲ�
}

int getSize(int array[]) { //genetic algorithm�� ����ϴµ� �ʿ��� �Լ�
	int size = 30; //ũ�� ���Ƿ� ����
	int queen; //��
	for (queen = 0; queen<COL; queen++) {    //���� ���� ������ŭ ���� ����
		int nextqueen; //���� �� ����
		for (nextqueen = queen + 1; nextqueen<COL; nextqueen++) { //��ġ�� ���� ��� ���� �� 
			if (array[queen] == array[nextqueen] || abs(queen - nextqueen) == abs(array[queen] - array[nextqueen])) {//�����̳� �밢���� ���� �ִ��� �˻�
				size--; //��ĥ ��� ����
			}
		}
	}
	return size; //size �� ����
}

void geneticAlgorithm() { //genetic algorithm �Լ�
	int population[ROW][COL]; //������
	int children[ROW][COL]; //�ڽ� ������
	int sizeProb[224] = {};
	int sLength = 0; //sizeProb[]�� ����
	double mutProb = 0.2; //����ӵ� ������ ����

	int end = 0;
	int i;
	for (i = 0; i<ROW; i++) //i�� ��
		for (int j = 0; j<COL; j++) //j�� �ุŭ �� ��
			population[i][j] = getRand(COL); //�������� �������� ������ �迭
	while (end == 0) { //end�� ���� 0�̵� ��
		for (i = 0; i<ROW; i++) { //i�� ����ŭ for���� �� ��
			if (getSize(children[i]) == 30) { //�ڽ� �迭�� getSize�� 30, �� �ִ밡 ��
				printf("���� �� �� �ִ� �ڸ�");
				printf("\n"); //�ٹٲ�
				printf("=>");
				printArr(children[i]); //�ڽ� ������ ���
				end = 1;
			}
		}

		for (i = 0; i< sLength; i++) //i�� sizeProb�� ���̸�ŭ for���� �� ��
			sizeProb[i] = (int)NULL; //sizeProb �ʱ�ȭ
		sLength = 0; //sizeProb�� ���� 0

		for (i = 0; i<ROW; i++) { //i�� ����ŭ �� ��
			int s = getSize(population[i]); //s�� �������� getSize
			for (int j = 0; j<s; j++) {//j�� �������� getSize��ŭ �� ��
				sizeProb[sLength] = i; //������ ��ȣ�ι迭 ���� ä��
				sLength++; //��������
			}
		}

		//����(selection)
		for (i = 0; i<ROW; i += 2) { //i�� ������ 2�� ����
			int se1 = sizeProb[getRand(sLength)];
			int se2 = sizeProb[getRand(sLength)]; //�ΰ��� �迭 ����
			int select = getRand(COL); //�������� �����Ѵ�

									   //����(crossover)
			for (int j = 0; j<select; j++) { //�������� ������ ������ ������
				children[i][j] = population[se1][j]; //�ڽİ� ������ �迭 �Ϻθ� ����
				children[i + 1][j] = population[se2][j]; //�ڽİ� ������ �迭 �Ϻθ� ����
			}
			for (int j = select; j<COL; j++) { //j�� ������ for���� �� ����
				children[i][j] = population[se2][j];//�ڼհ� ������ �迭 �Ϻθ� ����
				children[i + 1][j] = population[se1][j];//�ڼհ� ������ �迭 �Ϻθ� ����(������ ���� �� ������)
			}
			//��������(mutation)
			if (getRand(1000000) <= mutProb * 1000000) {
				int child = getRand(2); //�������� ����
				if (child == 0) //�ڽ��� 0�϶�
					children[i][getRand(COL)] = getRand(COL); //�������� ������ ���� �Ϻΰ� �ٲ�
				else
					children[i + 1][getRand(COL)] = getRand(COL); //�������� ������ ���� �Ϻΰ� �ٲ�
			}
		}
		for (i = 0; i<ROW; i++) //i�� ����ŭ ������
			for (int j = 0; j<COL; j++)  //j�� �ุŭ ������
				population[i][j] = children[i][j]; //�����ܰ� �ڽ��� ����
		sLength = 0;
	}
}

int main(void) {
    ////////////��Ʈ��ŷ////////////////////

	clock_t start, finish; //����ð��� ����, �� �ð�
	double duration; //����ð�
	printf(" <<Backtracking �̿�>>");
	printf("\n"); //�ٹٲ�
	printf("�� ���� �Է�: ");
	start = clock(); // �������� �ð�
	scanf_s("%d", &n);
	backTracking(0); //��Ʈ��ŷ ȣ��

	printf("������ ����� ��: ");
	printf("%d", ans); //���� ���� ȣ��
	printf("\n"); //�ٹٲ�

	finish = clock(); //������ �ð�
	duration = (double)(finish - start) / CLOCKS_PER_SEC; // (�������� �ð� - �������� �ð�)/1000
	printf("����ð�: ");
	printf("%f��", duration);

	printf("\n"); //�ٹٲ�
	 ///////////////////////////������ �˰���///////////////////////
	printf("\n"); //�ٹٲ�
	clock_t startt, ffinish; ////����ð��� ����, �� �ð�
	double dduration; //����ð�
	startt = clock(); // �������� �ð�
	printf(" <<������ �˰���(Genetic Algorithm) �̿�>>");
	printf("\n"); //�ٹٲ�
	srand((unsigned int)time(NULL));  //seed random
	geneticAlgorithm(); //genetic �˰��� ȣ��
	ffinish = clock(); // �������� �ð�
	dduration = (double)(ffinish - startt) / CLOCKS_PER_SEC; // (�������� �ð� - �������� �ð�)/1000
	printf("����ð�: ");
	printf("%f��", dduration);
	printf("\n"); //�ٹٲ�

	return 0;

}






