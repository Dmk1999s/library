#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>



typedef struct // å ����ü
{
	char bookname[50];	//å �̸��� ��� �迭
	char bookpublisher[50]; //å ���ǻ縦 ��� �迭
	int bookid; //å id�� ��� ����
	int bookyear; // ���ǿ����� ��Ƶδ� ����
	bool cancheckout; // ���Ⱑ�ɿ��θ� ����δ� ����
	int edition; // å�� �Ǻ��� ����δ� ����
}book;


// ȸ�� ���, �α��� �޴� ���� �Լ��� ����

//-----------------------------------------------------------------

int disp_menu(void);	//�޴� �������̽�
void enroll_num(int* e_num, char(*e_pwd)[11], int* e_cnt, int login_num); //ȸ�����/���� 
int is_enroll_num(int num, int* e_num, int e_cnt); //ȸ���� ��ϵǾ����� Ȯ��
void login_out(int* e_num, char(*e_pwd)[11], int e_cnt, int* login_num); //�α��� �α׾ƿ�

//-----------------------------------------------------------------
// ȸ�� ��� ���� ó�� �Լ�

int get_checkRange(int min, int max); //ȸ����ȣ�� �Է¹޾� ��ȯ�ϴ� �Լ�
void printIDList(int* e_num, char(*e_pwd)[11], int e_cnt); // ȸ����ȣ �� ��й�ȣ�� ����ϴ� �Լ�
int deleteID(int dno, int* e_num, char(*e_pwd)[11], int e_cnt); // ȸ����ȣ �� ��й�ȣ ����
int insertID(int id, int* e_num, char(*e_pwd)[11], int e_cnt); // ȸ����ȣ �� ��й�ȣ ����
void printIDList(int* e_num, char(*e_pwd)[11], int e_cnt); // ���� ��ϵ� ȸ����ȣ Ȯ��

// ȸ����ȣ �� ��й�ȣ �迭�� dno ��° ��Ҹ� �����ϴ� �Լ�, ����� ����� �� ��ȯ

int deleteFromIDList(int dno, int* e_num, char(*e_pwd)[11], int e_cnt); //e_cnt ��ȯ


// ȸ����ȣ �� ��й�ȣ �迭�� ���ο� id, pwd�� �����ϴ� �Լ�, ����� ����� �� ��ȯ

int insertToIDList(int id, char* pwd, int* e_num, char(*e_pwd)[11], int e_cnt); // e_cnt ��ȯ

//-----------------------------------------------------------------
// ��й�ȣ �Է°� ���ڿ� ó�� �Լ�

void input_password(char* pwd);
int verify_pwd(char* sp);
int my_strlen(char* sp);
void my_strcpy(char* dp, char* sp);
void my_gets(char* sp, int size);

//-----------------------------------------------------------------
// ���� ���� �Լ�
void registerordelete(book* books, int* book_count);
void register_book(book* books, int* book_count);
void delete_book(book* books, int* book_count);
void checkout_book(book* books, int book_count, int login_num);
//-----------------------------------------------------------------



#define MAX_ARY 100 // �ִ� ��� �ο� ��



int main(void)
{
	int a = 0;

	int b = 0;
	
	int e_num[MAX_ARY] = { 0 }; // ȸ�� �迭

	char e_pwd[MAX_ARY][11] = { "" }; // ��й�ȣ �迭 (�ִ� 100��, �ִ� 10��)

	int e_cnt = 0; // ��� �ο� ��

	int login_num = 0; // �α��ε� ȸ�� ��ȣ ����

	int num;

	book books[MAX_ARY]; // ���� ����ü �迭
	int book_count = 0; // ��ϵ� ���� ��


	// ������ ����

	e_num[0] = 1;

	strcpy_s(e_pwd[0], "123456789");

	e_cnt = 1;

	login_num = 1;




	while (1)
	{

		num = disp_menu();

		if (num == 0)

			break;



		switch (num)
		{
		case 1:

			enroll_num(e_num, e_pwd, &e_cnt, login_num);

			break;

		case 2:

			login_out(e_num, e_pwd, e_cnt, &login_num);

			break;

		case 3:

			registerordelete(books, & book_count);

			break;

		case 4:

			checkout_book(books, book_count, login_num);

			break;


		default:

			printf("@ �޴� ��ȣ�� �ƴմϴ�!\n\n");

			break;

		}

	}



	return 0;
}

// �޴� ��� �� ���� ��ȣ ��ȯ

int disp_menu(void)

{

	int num;



	printf("\n\n===[ ������ �ý��� ]===\n");

	printf("1. ȸ�� ���/����\n");

	printf("2. �α���/�α׾ƿ�\n");

	printf("3. �������\n");

	printf("4. ��������\n");

	printf("0. ����\n");

	printf("---------------------------\n");



	printf("> ��ȣ ���� : ");

	scanf_s("%d", &num);



	return num;

}

//==========< ȸ�� ���/����, �α���/�α׾ƿ� ���� �Լ� >==========
void enroll_num(int* e_num, char(*e_pwd)[11], int* e_cnt, int login_num)
{
	int num; //ȸ�� ��ȣ
	int index; //ȸ����ȣ�� �ִ� �迭�� ��ġ

	if (login_num != 1) //�����ڰ� �ƴ϶�� ��ȯ
	{
		printf("@ �����ڸ� ����Ͻ� �� �ֽ��ϴ�!\n");
		return;
	}

	printf("\n[ ȸ�� ���/���� ]\n\n");

	num = get_checkRange(1, 9999);
	if (num == 0)
	{
		return;
	}
	else if (num == 1)
	{
		printf("�����ڴ� ������ �� �����ϴ�!\n");
		return;
	}

	index = is_enroll_num(num, e_num, *e_cnt); // ��ϵ� ��ȣ���� Ȯ��


	if (index >= 0) { // ��ϵ� ��ȣ�� ������ ȸ�� ����

		*e_cnt = deleteID(index, e_num, e_pwd, *e_cnt);

	}

	else { // ������ ȸ�� ��� ����

		*e_cnt = insertID(num, e_num, e_pwd, *e_cnt);

	}

}


int get_checkRange(int min, int max)
{
	int input = 0;
	printf("> ȸ����ȣ(%d-%d) : ", min, max);
	scanf("%d", &input);
	if ((input < min) || (input > max)) // ��� ������ ���ڰ� �ƴϸ� ��ȯ
	{
		printf("@ ��ȿ�� ��ȣ�� �ƴմϴ�!\n");
		return 0;
	}
	return input;
}


int deleteFromIDList(int dno, int* e_num, char(*e_pwd)[11], int e_cnt)
{
	//dno ��° �迭�� ȸ�� ������ �����ϰ� �ϳ��� ����, ���ҵ� e_cnt(��ϵ� ȸ�� ��) ��ȯ
	int i = 0;

	for (i = dno; i < (e_cnt - 1); i++)
	{
		e_num[i] = e_num[i + 1];
		strcpy(e_pwd[i], e_pwd[i + 1]);
	}
	e_cnt--; //��ϵ� ȸ���� ����
	return e_cnt;
}


int insertToIDList(int id, char* pwd, int* e_num, char(*e_pwd)[11], int e_cnt)
{
	e_num[e_cnt] = id;
	strcpy(e_pwd[e_cnt], pwd);
	e_cnt++;
	printf("# %d���� ��ϵǾ����ϴ�!\n", id);
	return e_cnt;
}


void printIDList(int* e_num, char(*e_pwd)[11], int e_cnt)

{

	int i = 0;



	printf("\n>> ���� ��ϵ� ��ȣ (��й�ȣ) : ");

	for (i = 0; i < e_cnt; i++) {

		printf("%5d(%s)", e_num[i], e_pwd[i]);

	}

	printf("\n\n");

}


int deleteID(int dno, int* e_num, char(*e_pwd)[11], int e_cnt)
{
	char yn;
	char pwd[11] = "";

	printf("@ �̹� ��ϵǾ����ϴ�!\n");
	printf("@ �����Ͻðڽ��ϱ�(Y/N)? : ");

	yn = getchar();
	scanf_s("%c", &yn);

	if ((yn == 'Y') || (yn == 'y'))
	{
		//��й�ȣ�� �Է¹޾� ȸ����ȣ�� �´� ��й�ȣ�� ��� ���� ó��
		printf("> ��й�ȣ �Է� : ");
		my_gets(pwd, 11); // �迭�� ũ������� �Է�
		if (strcmp(pwd, e_pwd[dno]) != 0)
		{
			printf("@ ��й�ȣ�� �ٸ��ϴ�. ������ �� �����ϴ�.\n");
			return e_cnt;
		}
		printf("@ %d���� �����Ǿ����ϴ�!\n", e_num[dno]);
		e_cnt = deleteFromIDList(dno, e_num, e_pwd, e_cnt);
		printIDList(e_num, e_pwd, e_cnt);
	}
	else
	{
		printf("@ ��ҵǾ����ϴ�!\n");
	}
	return e_cnt;
}


int insertID(int id, int* e_num, char(*e_pwd)[11], int e_cnt)
{
	// ����ο��� �߰����� �ʾҴٸ� �ο� �߰�
	char pwd[11] = "";



	if (e_cnt == MAX_ARY) { // ��� �ο� ���� �ִ� �ο� ���� ������ ��ȯ

		printf("@ ��� �ο��� �ʰ��Ǿ����ϴ�!");

		return e_cnt;

	}

	input_password(pwd);



	e_cnt = insertToIDList(id, pwd, e_num, e_pwd, e_cnt);

	printIDList(e_num, e_pwd, e_cnt); // ��ϵǾ����� Ȯ���ϴ� �Լ�

	return e_cnt;
}


int is_enroll_num(int num, int* e_num, int e_cnt) // ��ϵ� ��ȣ���� Ȯ��
{
	int i;

	for (i = 0; i < e_cnt; i++)
	{
		if (num == e_num[i])
			return i;
	}

	return -1;
}


int verify_pwd(char* sp) //��й�ȣ ���� �˻�
{
	if (my_strlen(sp) < 5) {

		return 1; //������ �ִٸ� 1 ��ȯ

	}

	return 0; //������ ������ 0 ��ȯ
}


void input_password(char* pwd) // ��й�ȣ �Է�

{

	char first[11]; // ù ��° �Է��� ��й�ȣ ����

	char second[11]; // ��й�ȣ ���ڿ� �Է��� �ӽ� �迭

	int err;

	do {


		while (1) {
			gets_s(first); // �迭�� ũ������� �Է�
			err = verify_pwd(first); // ���ڿ� ���� �˻� 
			if (err == 0) // ��й�ȣ ��Ŀ� ���� �ʴٸ� �ٽ�
				break;
			printf("@ ��й�ȣ�� 5���� �̻�, 10���� ���Ϸ� ���ؾ� �մϴ�!\n");
			printf("> ��й�ȣ(5-10��) : ");
		}



		printf("> �ѹ� �� �Է��ϼ��� : ");

		gets_s(second); // �迭 ũ�� ����

		if (strcmp(first, second) == 0)

			break; // ù ��°�� �ι�° �Է� ���ڿ��� ������ ��



		printf("@ ��й�ȣ�� ��ġ���� �ʽ��ϴ�!\n");

	} while (1);

	my_strcpy(pwd, first);

}


void my_gets(char* sp, int size) //�迭�� ũ������� ���ڿ� �Է�

{

	char ch;

	int i = 0;



	getchar();

	ch = getchar();

	while ((i < (size - 1)) && (ch != '\n')) {

		sp[i] = ch;

		i++;

		ch = getchar();

	}

	sp[i] = '\0';

}




int my_strlen(char* sp) // �迭�� ����� ���ڿ��� ���� ��ȯ

{

	int cnt = 0;



	while (*sp++ != '\0') {

		cnt++;

	}

	return cnt;

}


void login_out(int* e_num, char(*e_pwd)[11], int e_cnt, int* login_num)
{
	//��й�ȣ�� Ȯ���Ͽ� �α���, �α��ε� ��� �α׾ƿ�.
	int num;

	char pwd[11] = "";

	int index;



	if (*login_num != 0) {

		*login_num = 0;

		printf("# �α׾ƿ��Ǿ����ϴ�!\n");

		return;

	}



	printf("\n[ �α��� ]\n\n");



	printf("> ȸ����ȣ : ");

	scanf("%d", &num);

	index = is_enroll_num(num, e_num, e_cnt); // ��ϵ� ��ȣ�̸� �迭�� ��� ��ġ ��ȯ, �ƴϸ� -1 ��ȯ



	if (index == -1) {

		printf("@ %d���� ��ϵ��� ���� ��ȣ�Դϴ�!\n", num);

		return;

	}



	printf("> ��й�ȣ : ");

	fflush(stdin);

	my_gets(pwd, 11);

	if (strcmp(pwd, e_pwd[index]) != 0) {

		printf("@ ��й�ȣ�� Ʋ�Ƚ��ϴ�!\n");

		return;

	}

	*login_num = num; // �α��� ��� ����

	printf("# �α��εǾ����ϴ�!\n");

}

void my_strcpy(char* dp, char* sp)
{
	while ((*dp++ = *sp++) != '\0');
}

void registerordelete(book* books, int* book_count)
{
	int num;
	printf("���� ��� �� 0, ���� ���� �� 1 �Է� : ");
	scanf("%d", &num);
	if (num == 0)
	{
		register_book(books, book_count);
	}
	else if (num == 1)
	{
		delete_book(books, book_count);
	}
	else
	{
		printf("�ٽ� �Է��Ͻʽÿ�");
	}
}

void register_book(book* books, int* book_count)
{
	printf("\n[���� ��� ]\n\n");

	//���� ���� �Է�
	printf("> ���� �̸�: ");
	scanf("%s", books[*book_count].bookname);

	printf("> ���ǻ�: ");
	scanf("%s", books[*book_count].bookpublisher);

	printf("> ���ǿ���: ");
	scanf("%d", &books[*book_count].bookyear);

	printf("> ���� ���� ���� (1: ����, 0: �Ұ���): ");
	scanf("%d", &books[*book_count].cancheckout);

	printf("> �Ǻ�: ");
	scanf("%d", &books[*book_count].edition);

	// å�� ID �ֱ�
	books[*book_count].bookid = (*book_count) + 1;

	(*book_count)++; // ���� �� ����

	printf("������ ��ϵǾ����ϴ�\n");
}

void delete_book(book* books, int* book_count)
{
	printf("\n[ ���� ���� ]\n\n");

	int book_id;
	printf("> ������ ������ ID�� �Է��ϼ���: ");
	scanf("%d", &book_id);

	int found_index = -1;

	// ���� ID�� ���� ã��
	for (int i = 0; i < *book_count; i++) {
		if (books[i].bookid == book_id) {
			found_index = i;
			break;
		}
	}

	if (found_index != -1) {
		// ������ ã�� ��� �����Ѵ�
		for (int i = found_index; i < (*book_count - 1); i++) {
			books[i] = books[i + 1];
		}

		(*book_count)--; // ���� �� ����
		printf("������ �����Ǿ����ϴ�.\n");
	}
	else {
		printf("@ �ش� ������ ã�� �� �����ϴ�.\n");
	}
}

#include <stdio.h>

void checkout_book(book* books, int book_count, int login_num)
{
	printf("\n[ ���� ���� ]\n\n");

	// �α��� Ȯ��
	if (login_num == 0) {
		printf("@ �α��� �� �̿� �����մϴ�.\n");
		return;
	}

	// ���� ������ ���� ��� ���
	printf("���� ������ ���� ���:\n");
	for (int i = 0; i < book_count; i++) {
		if (books[i].cancheckout) {
			printf("ID: %d, ���� �̸�: %s\n", books[i].bookid, books[i].bookname);
		}
	}

	// ������ ���� ����
	int book_id;
	printf("> ������ ������ ID�� �Է��ϼ���: ");
	scanf("%d", &book_id);

	int found_index = -1;

	// ���� ID�� ������ ã��
	for (int i = 0; i < book_count; i++) {
		if (books[i].bookid == book_id) {
			found_index = i;
			break;
		}
	}

	if (found_index != -1) {
		// ������ ã�� ��� ���� ó��
		if (books[found_index].cancheckout) {
			books[found_index].cancheckout = false;
			printf("# ������ ���������� ����Ǿ����ϴ�.\n");
		}
		else {
			printf("@ �ش� ������ �̹� ���� ���Դϴ�.\n");
		}
	}
	else {
		printf("@ �ش� ������ ã�� �� �����ϴ�.\n");
	}
}
