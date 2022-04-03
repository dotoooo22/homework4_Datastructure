#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//함수선언
int** create_matrix(int row, int col);      //행렬생성
void print_matrix(int** matrix, int row, int col);      //행렬출력
int free_matrix(int** matrix, int row, int col);        //동적메모리반환
int fill_data(int** matrix, int row, int col);          //행렬식채우기
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);      //행렬덧셈
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);   //행렬뺄셈
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);       //전치행렬구하기
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);      //행렬곱하기

int main()
{
    char command;
    printf("[----- [곽민정]  [2021041021] -----]\n");

	int row, col;
    int** matrix_a = NULL;
    int** matrix_b = NULL;
	srand(time(NULL));      //매번랜덤한수를생성하기위해서

	printf("Input row and col : ");
	scanf("%d %d", &row, &col);         //행과 열 갯수를 입력받음
    matrix_a = create_matrix(row, col);       //A행렬생성(행열을 2차원으로쓰려고 이중포인터에 주소넣기)
	matrix_b = create_matrix(row, col);       //B행렬생성
    int** matrix_a_t = create_matrix(col, row);

	printf("Matrix Created.\n");

	if (matrix_a == NULL || matrix_b == NULL) {return -1;}  //널반환받으면 행렬생성실패라서 비정상 종료

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Matrix Manipulation                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Matrix   = z           Print Matrix        = p \n");
		printf(" Add Matrix          = a           Subtract Matrix     = s \n");
		printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
		printf(" Quit                = q \n");
		printf("----------------------------------------------------------------\n");
        //메뉴창 출력
		printf("Command = ");
		scanf(" %c", &command);     //커맨드입력받기

		switch(command) {       //커맨드에 따라 처리
		case 'z': case 'Z':     //행렬생성새로하기
		    printf("Matrix Initialized\n");
			fill_data(matrix_a, row, col);
			fill_data(matrix_b, row, col);
			break;
        case 'p': case 'P':       //행렬출력하기
            printf("Print matrix\n");
            printf("matrix_a\n");
			print_matrix(matrix_a, row, col);   //a로 출력함수호출
			printf("matrix_b\n");
			print_matrix(matrix_b, row, col);	//b로 출력함수호출
			break;
        case 'a': case 'A':     //두행렬 더하기
			printf("Add two matrices\n");
			addition_matrix(matrix_a, matrix_b, row, col);	//a, b 행렬더하는함수호출
			break;
        case 's': case 'S':     //두행렬 빼기
			printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);		//a, b행렬 빼는 함수 호출
			break;
        case 't': case 'T':     //a전치행렬구하기
			printf("Transpose matrix_a \n");
			printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);		//전치행렬구하는 함수 호출
            print_matrix(matrix_a_t, col, row);
			break;
        case 'm': case 'M':     //a행렬과 a전치행렬 곱하기
			printf("Multiply matrix_a with transposed matrix_a \n");
			transpose_matrix(matrix_a, matrix_a_t, col, row);		//a전치행렬먼저 구하는 함수호출해서 구하고
            multiply_matrix(matrix_a, matrix_a_t, row, col);		//a랑 a전치행렬 곱하는 함수 호출
			break;
        case 'q': case 'Q':     //메모리반환하기
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);		//전치행렬, a, b 행렬 메모리반환함수 호출
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');       //메모리반환하기선택했으면 루프빠져나옴

	return 1;
}


int** create_matrix(int row, int col)
{
	if (row <= 0 || col <= 0) {     //행열갯수 0이하면 확인하라는메세지출력후 널반환
		printf("Check the size of row and col!\n");
		return NULL;    //널반환
	}

	int** matrix = (int**)malloc(sizeof(int*) * row);       //행갯수만큼 동적할당
	for (int r = 0; r < row; r++) {     //행마다 열에
		matrix[r] = (int*)malloc(sizeof(int) * col);        //열갯수만큼 동적할당
	}

	if (matrix == NULL) {           //행렬에 널이 들어있으면 동적할당 실패 출력하고 널 반환   
		printf("Memory Allocation Failed.\n");
		return NULL;
	}

	return matrix;
}


void print_matrix(int** matrix, int row, int col)
{
	if (row <= 0 || col <= 0) {     //행렬 범위안에 있는건지 확인
		printf("Check the size of row and col!\n");
		return;
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++) {
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			printf("%3d ", matrix[matrix_row][matrix_col]);         //매트릭스 값 출력
		printf("\n");
	}
	printf("\n");
	 if (matrix == NULL) {      //행렬포인터가 널을 가리키면 메모리할당실패 출력
		printf("Memory Allocation Failed.\n");
		return;
	}

	return;
}


int free_matrix(int** matrix, int row, int col)
{
	if (row <= 0 || col <= 0) {     //행렬 범위안에 있는건지 확인
		printf("Check the size of row and col!\n");
		return -1;
	}

	for (int matrix_row = 0; matrix_row < row; matrix_row++) {
		free(matrix[matrix_row]);           //메모리반환
	}

	free(matrix);       //행렬포인터메모리반환
	return 1;
}


int fill_data(int** matrix, int row, int col)
{
	if (row <= 0 || col <= 0) { //행렬 범위안에 있는건지 확인
		printf("Check the size of row and col!\n");
		return -1;
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++)
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix[matrix_row][matrix_col] = rand() % 20;

    if (matrix == NULL) {		//행렬포인터가 널을 가리키면 메모리할당실패 출력
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	return 1;
}

int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)		//행렬더하기 함수
{
    int** matrix_sum = create_matrix(row, col);		//합한거 저장할 이중포인터생성.
	
	if (row <= 0 || col <= 0) {		//행열갯수 0이하면 확인하라는메세지출력후 널반환
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {
		for (int matrix_col = 0; matrix_col < col; matrix_col++)		//a행렬이랑 b행렬더해서 sum에 넣기
			matrix_sum[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] + matrix_b[matrix_row][matrix_col];
	}
	/* Check post conditions */
	if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL) {//a, b, sum 중 하나라도 행렬포인터가 널을 가리키면 메모리할당실패 출력
		printf("Memory Allocation Failed.\n");
		return -1;
	}

	print_matrix(matrix_sum, row, col); //합한결과 출력
	free_matrix(matrix_sum, row, col);	//sum 메모리 해제
	return 1;
}


int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)//행렬뺄셈함수
{
    int** matrix_sub = create_matrix(row, col);		//sub행렬 동적할당
	
	if (row <= 0 || col <= 0) {		//행열갯수 0이하면 확인하라는메세지출력후 널반환
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {//a행렬이랑 b행렬 빼서 sum에 넣기
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_sub[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] - matrix_b[matrix_row][matrix_col];
	}

    if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL) {//a, b, sub 중 하나라도 행렬포인터가 널을 가리키면 메모리할당실패 출력
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	print_matrix(matrix_sub, row, col);		//결과출력
	free_matrix(matrix_sub, row, col);		//sub메모리 해제

	return 1;
}


int transpose_matrix(int** matrix, int** matrix_t, int row, int col)		//전치행렬구하기
{
	
	if (row <= 0 || col <= 0) {		//행열갯수 0이하면 확인하라는메세지출력후 널반환
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {		//전치행렬구하기
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_t[matrix_row][matrix_col] = matrix[matrix_col][matrix_row];		//원래행렬 행하고 열을 바꿔서 전치행렬에 대입
	}
	
    if (matrix == NULL || matrix_t ==NULL) {//원래행렬, 전치행렬 중 하나라도 행렬포인터가 널을 가리키면 메모리할당실패 출력
		printf("Memory Allocation Failed.\n");
		return -1;
	}

	return 1;
}

int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)		//행렬곱하기
{
    int** matrix_axt = create_matrix(row, row);		//곱한결과저장할 행렬할당(곱한 결과는 행수, 행수로 나와서 행열을 행갯수만큼)

	if (row <= 0 || col <= 0) {		//행열갯수 0이하면 확인하라는메세지출력후 널반환
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
	
    if (matrix_t == NULL || matrix_axt ==NULL) {		//전치한행렬과 곱한 행 중 하나라도 NULL을 가리키면 할당실패
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	print_matrix(matrix_axt, row, row);		//곱한거 출력
	free_matrix(matrix_axt, row, col);		//전치행렬 메모리해제
	return 1;
}
