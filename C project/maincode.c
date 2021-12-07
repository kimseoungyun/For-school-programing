#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#define SIZE 12
#define FLOOR 3
#define numsize 8

struct node{
	char num[numsize];
	int floor;
	int X;
	struct node* next;
};

int space[FLOOR][SIZE];

void menu()
{
	printf("============<MENU>=============\n");
	printf("1. 주차\n");
	printf("2. 출차\n");
	printf("3. 차량 위치 검색\n");
	printf("4. 현 주차 상황\n");
	printf("0. 종료\n");
	printf("번호선택 =>");
}

void Resetspace()
{
	int k,i;
	for (i=0;i<FLOOR;i++){
		for (k=0;k<SIZE;k++){
			space[i][k]='O';
		}
	}
}

void spacenow()
{
	int a,b;
	for(a=0;a<FLOOR;a++){
		printf("============<%d>======================\n", a+1);
		for (b=0;b<SIZE;b++){
			printf(" %c ", space[a][b]);}
		printf("\n");
	}
}

void change_space(int tfloor, int tX)
{
	while(1){
		if (space[tfloor-1][tX-1]=='O'){
			space[tfloor-1][tX-1]='X';
			break;}

		if (space[tfloor-1][tX-1]=='X'){
			space[tfloor-1][tX-1]='O';
			break;}
	}
}
struct node insCar_for_data(struct node** list_head, int get_floor, int get_X, char name[numsize], void (*func)(char*, char*))
{
	struct node* new_node;
	if (space[get_floor-1][get_X-1]=='O'){
		new_node = 
			(struct node*) malloc (sizeof(struct node));
		func(new_node->num, name);
		new_node->floor = get_floor;
		new_node->X = get_X;
		(new_node->next) = *list_head;
		*list_head = new_node;}
	else
		printf("이미 존재하는 자리입니다.\n");
	change_space(get_floor, get_X);
}

struct node insCar(struct node** list_head, void (*func)(char*, char*))
{
	int serv_floor, serv_X;
	struct node* new_node;
	char serv_num[numsize];
	printf("번호판을 입력하세요.:");
	scanf("%s", serv_num);
	spacenow();
	printf("주차할 위치를 선택하세요.:(층, n번째)");
	scanf("%d %d", &serv_floor, &serv_X);	
	if (space[serv_floor-1][serv_X-1]=='O'){
		
		new_node =
			(struct node*) malloc (sizeof(struct node));
		func(new_node->num, serv_num);
		new_node->floor = serv_floor;
		new_node->X = serv_X;
		(new_node->next) = *list_head;
		*list_head = new_node;}
	else
		printf("잘못 입력하셨습니다.\n");
	change_space(serv_floor, serv_X);
	spacenow();
}

void insnum(char a[],char b[])
{
	for(int i=0;i<numsize;i++){a[i] = b[i];}
}	

struct node delCar(struct node* tmp, struct node** list_head, void (*func)(char*, char*))
{
	int result;
	char get_num[numsize];
	struct node* new_node;
	struct node* jump;
	struct node* prv_node=NULL;
	printf("차량의 번호판을 입력하세요:");
	scanf("%s", get_num);
	fflush(stdin);

	new_node =
		(struct node*) malloc (sizeof(struct node));
	func(new_node->num, get_num);
	tmp = *list_head;
	
	while(tmp){
		result=strcmp(tmp->num, new_node->num);
		if(result==0){
			if((tmp->next==NULL)&&(tmp == *list_head)){
				*list_head = tmp->next;
				printf("삭제가 완료되었습니다.\n");
				change_space(tmp->floor,tmp->X);
				break;}
			else if(tmp == *list_head){
				*list_head = tmp->next;
				printf("삭제가 완료되었습니다.\n");
				change_space(tmp->floor,tmp->X);
				break;}
			jump = tmp ->next;
			prv_node->next = jump;
			printf("삭제가 완료되었습니다.\n");
			change_space(tmp->floor,tmp->X);
			break;}
		prv_node = tmp;
		tmp = tmp->next;
		
	}
}

struct node findCar(struct node* tmp, struct node** list_head, void (*func)(char*, char*))
{
	int find_floor, find_X;
	struct node* new_node;
	char get_num[numsize];
	int result;
	tmp = *list_head;
	if(tmp==NULL){printf("주차장에 차량이 없습니다.\n");} 
	else{
		printf("차량의 번호판을 입력하세요:");
		scanf("%s", get_num);
	
		new_node =
			(struct node*) malloc (sizeof(struct node));
		func(new_node->num, get_num);}

	while(tmp){
		result = strcmp(tmp->num, new_node->num);
		if(result==0){
			find_floor = tmp->floor; 
			find_X = tmp->X;
			printf("%d층, %d번째\n", find_floor, find_X);
			break;}
		if(tmp->next==NULL){
			printf("검색결과가 없습니다.\n");
			break;}
		tmp = tmp->next;
	}
}			

struct node File_w(struct node* tmp, struct node** list_head, void (*func)(char*, char*))
{
	int data_floor, data_X;
	char data_num[numsize];
	FILE *fp = NULL;
	fp = fopen("output_data.txt", "w");

	if(fp == NULL){
		printf("Failed to open file %s\n", "output_data.txt");
		
	}
	fprintf(fp, "My first data file\n");
	tmp = *list_head;
	while(tmp){
		data_floor = tmp->floor;
		data_X = tmp->X;
		func(tmp->num, data_num);
		fprintf(fp, "Car_number : %s, Car_location : %d층%d번째\n", data_num, data_floor, data_X);
		tmp = tmp->next;}
	fclose(fp);
}

struct node* File_r(struct node** list_head)
{
	FILE *fp = NULL;
	char buff[numsize];
	int floor, X;
	fp = fopen("input_data.txt", "r");
	
	if(fp == NULL){
		printf("Failed to open file %s\n", "input_data.txt");
		
	}
	while(fscanf(fp, "%s %d %d", buff, &floor, &X) != EOF){
		insCar_for_data(list_head, floor, X, buff, insnum); 
	}
	fclose(fp);
	return 0;	
}

int main()
{
	struct node* tmp;
	struct node* list_head=NULL;
	int answer;	  
	int check=1;
	Resetspace();
	File_r(&list_head);
	while(check!=0)
	{
		menu();
		scanf("%d", &answer);;
		fflush(stdin);
		

		switch(answer){
			case 1: insCar(&list_head, insnum);continue;
			case 2: delCar(tmp, &list_head, insnum);continue;
			case 3: findCar(tmp, &list_head, insnum);continue;
			case 4: spacenow();continue;
			case 0: check=0;break;
			default :
				printf("잘못 입력하셨습니다.\n");
		}
	}
	
	File_w(tmp, &list_head, insnum);
	return 0;
}

	
