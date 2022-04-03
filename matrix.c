#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//�Լ�����
int** create_matrix(int row, int col);      //��Ļ���
void print_matrix(int** matrix, int row, int col);      //������
int free_matrix(int** matrix, int row, int col);        //�����޸𸮹�ȯ
int fill_data(int** matrix, int row, int col);          //��Ľ�ä���
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);      //��ĵ���
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);   //��Ļ���
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);       //��ġ��ı��ϱ�
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);      //��İ��ϱ�

int main()
{
    char command;
    printf("[----- [������]  [2021041021] -----]\n");

	int row, col;
    int** matrix_a = NULL;
    int** matrix_b = NULL;
	srand(time(NULL));      //�Ź������Ѽ��������ϱ����ؼ�

	printf("Input row and col : ");
	scanf("%d %d", &row, &col);         //��� �� ������ �Է¹���
    matrix_a = create_matrix(row, col);       //A��Ļ���(�࿭�� 2�������ξ����� ���������Ϳ� �ּҳֱ�)
	matrix_b = create_matrix(row, col);       //B��Ļ���
    int** matrix_a_t = create_matrix(col, row);

	printf("Matrix Created.\n");

	if (matrix_a == NULL || matrix_b == NULL) {return -1;}  //�ι�ȯ������ ��Ļ������ж� ������ ����

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Matrix Manipulation                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Matrix   = z           Print Matrix        = p \n");
		printf(" Add Matrix          = a           Subtract Matrix     = s \n");
		printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
		printf(" Quit                = q \n");
		printf("----------------------------------------------------------------\n");
        //�޴�â ���
		printf("Command = ");
		scanf(" %c", &command);     //Ŀ�ǵ��Է¹ޱ�

		switch(command) {       //Ŀ�ǵ忡 ���� ó��
		case 'z': case 'Z':     //��Ļ��������ϱ�
		    printf("Matrix Initialized\n");
			fill_data(matrix_a, row, col);
			fill_data(matrix_b, row, col);
			break;
        case 'p': case 'P':       //�������ϱ�
            printf("Print matrix\n");
            printf("matrix_a\n");
			print_matrix(matrix_a, row, col);   //a�� ����Լ�ȣ��
			printf("matrix_b\n");
			print_matrix(matrix_b, row, col);	//b�� ����Լ�ȣ��
			break;
        case 'a': case 'A':     //����� ���ϱ�
			printf("Add two matrices\n");
			addition_matrix(matrix_a, matrix_b, row, col);	//a, b ��Ĵ��ϴ��Լ�ȣ��
			break;
        case 's': case 'S':     //����� ����
			printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);		//a, b��� ���� �Լ� ȣ��
			break;
        case 't': case 'T':     //a��ġ��ı��ϱ�
			printf("Transpose matrix_a \n");
			printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);		//��ġ��ı��ϴ� �Լ� ȣ��
            print_matrix(matrix_a_t, col, row);
			break;
        case 'm': case 'M':     //a��İ� a��ġ��� ���ϱ�
			printf("Multiply matrix_a with transposed matrix_a \n");
			transpose_matrix(matrix_a, matrix_a_t, col, row);		//a��ġ��ĸ��� ���ϴ� �Լ�ȣ���ؼ� ���ϰ�
            multiply_matrix(matrix_a, matrix_a_t, row, col);		//a�� a��ġ��� ���ϴ� �Լ� ȣ��
			break;
        case 'q': case 'Q':     //�޸𸮹�ȯ�ϱ�
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);		//��ġ���, a, b ��� �޸𸮹�ȯ�Լ� ȣ��
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');       //�޸𸮹�ȯ�ϱ⼱�������� ������������

	return 1;
}


int** create_matrix(int row, int col)
{
	if (row <= 0 || col <= 0) {     //�࿭���� 0���ϸ� Ȯ���϶�¸޼�������� �ι�ȯ
		printf("Check the size of row and col!\n");
		return NULL;    //�ι�ȯ
	}

	int** matrix = (int**)malloc(sizeof(int*) * row);       //�హ����ŭ �����Ҵ�
	for (int r = 0; r < row; r++) {     //�ึ�� ����
		matrix[r] = (int*)malloc(sizeof(int) * col);        //��������ŭ �����Ҵ�
	}

	if (matrix == NULL) {           //��Ŀ� ���� ��������� �����Ҵ� ���� ����ϰ� �� ��ȯ   
		printf("Memory Allocation Failed.\n");
		return NULL;
	}

	return matrix;
}


void print_matrix(int** matrix, int row, int col)
{
	if (row <= 0 || col <= 0) {     //��� �����ȿ� �ִ°��� Ȯ��
		printf("Check the size of row and col!\n");
		return;
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++) {
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			printf("%3d ", matrix[matrix_row][matrix_col]);         //��Ʈ���� �� ���
		printf("\n");
	}
	printf("\n");
	 if (matrix == NULL) {      //��������Ͱ� ���� ����Ű�� �޸��Ҵ���� ���
		printf("Memory Allocation Failed.\n");
		return;
	}

	return;
}


int free_matrix(int** matrix, int row, int col)
{
	if (row <= 0 || col <= 0) {     //��� �����ȿ� �ִ°��� Ȯ��
		printf("Check the size of row and col!\n");
		return -1;
	}

	for (int matrix_row = 0; matrix_row < row; matrix_row++) {
		free(matrix[matrix_row]);           //�޸𸮹�ȯ
	}

	free(matrix);       //��������͸޸𸮹�ȯ
	return 1;
}


int fill_data(int** matrix, int row, int col)
{
	if (row <= 0 || col <= 0) { //��� �����ȿ� �ִ°��� Ȯ��
		printf("Check the size of row and col!\n");
		return -1;
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++)
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix[matrix_row][matrix_col] = rand() % 20;

    if (matrix == NULL) {		//��������Ͱ� ���� ����Ű�� �޸��Ҵ���� ���
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	return 1;
}

int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)		//��Ĵ��ϱ� �Լ�
{
    int** matrix_sum = create_matrix(row, col);		//���Ѱ� ������ ���������ͻ���.
	
	if (row <= 0 || col <= 0) {		//�࿭���� 0���ϸ� Ȯ���϶�¸޼�������� �ι�ȯ
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {
		for (int matrix_col = 0; matrix_col < col; matrix_col++)		//a����̶� b��Ĵ��ؼ� sum�� �ֱ�
			matrix_sum[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] + matrix_b[matrix_row][matrix_col];
	}
	/* Check post conditions */
	if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL) {//a, b, sum �� �ϳ��� ��������Ͱ� ���� ����Ű�� �޸��Ҵ���� ���
		printf("Memory Allocation Failed.\n");
		return -1;
	}

	print_matrix(matrix_sum, row, col); //���Ѱ�� ���
	free_matrix(matrix_sum, row, col);	//sum �޸� ����
	return 1;
}


int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)//��Ļ����Լ�
{
    int** matrix_sub = create_matrix(row, col);		//sub��� �����Ҵ�
	
	if (row <= 0 || col <= 0) {		//�࿭���� 0���ϸ� Ȯ���϶�¸޼�������� �ι�ȯ
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {//a����̶� b��� ���� sum�� �ֱ�
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_sub[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] - matrix_b[matrix_row][matrix_col];
	}

    if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL) {//a, b, sub �� �ϳ��� ��������Ͱ� ���� ����Ű�� �޸��Ҵ���� ���
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	print_matrix(matrix_sub, row, col);		//������
	free_matrix(matrix_sub, row, col);		//sub�޸� ����

	return 1;
}


int transpose_matrix(int** matrix, int** matrix_t, int row, int col)		//��ġ��ı��ϱ�
{
	
	if (row <= 0 || col <= 0) {		//�࿭���� 0���ϸ� Ȯ���϶�¸޼�������� �ι�ȯ
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {		//��ġ��ı��ϱ�
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_t[matrix_row][matrix_col] = matrix[matrix_col][matrix_row];		//������� ���ϰ� ���� �ٲ㼭 ��ġ��Ŀ� ����
	}
	
    if (matrix == NULL || matrix_t ==NULL) {//�������, ��ġ��� �� �ϳ��� ��������Ͱ� ���� ����Ű�� �޸��Ҵ���� ���
		printf("Memory Allocation Failed.\n");
		return -1;
	}

	return 1;
}

int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)		//��İ��ϱ�
{
    int** matrix_axt = create_matrix(row, row);		//���Ѱ�������� ����Ҵ�(���� ����� ���, ����� ���ͼ� �࿭�� �హ����ŭ)

	if (row <= 0 || col <= 0) {		//�࿭���� 0���ϸ� Ȯ���϶�¸޼�������� �ι�ȯ
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_a_row = 0; matrix_a_row < row; matrix_a_row++) {
		for (int matrix_t_row = 0; matrix_t_row < row; matrix_t_row++) {
			int temp = 0;
			for (int matrix_col = 0; matrix_col < col; matrix_col++)
				temp += matrix_a[matrix_a_row][matrix_col] * matrix_t[matrix_col][matrix_t_row];
			matrix_axt[matrix_a_row][matrix_t_row] = temp;
		}
	}
	
    if (matrix_t == NULL || matrix_axt ==NULL) {		//��ġ����İ� ���� �� �� �ϳ��� NULL�� ����Ű�� �Ҵ����
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	print_matrix(matrix_axt, row, row);		//���Ѱ� ���
	free_matrix(matrix_axt, row, col);		//��ġ��� �޸�����
	return 1;
}
