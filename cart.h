#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OBJ 100	// 저장할 수 있는 물건 레코드 최대 갯수

//물건 정보 레코드의 데이터 타입 
typedef struct st_object{
	char obj[20]; 	// 물건 이름
	int price; 		// 물건 가격
	int cnt; 		// 물건 수량
	char name[20]; 	// 주문자 이름
}T_Record;

typedef struct ranking{
	char name[20]; 	// 주문자 이름
	int t_price;	// 총 주문 가격
}R_Record;

//라이브러리 함수 원형을 선언
int o_is_available();		// 데이터 공간 유무
int o_first_available();    // 추가할 수 있는 가장 빠른 포인터 배열의 인덱스 찾기
int o_count();		 		//현재 저장된 물건 레코드 갯수
void o_create(char* o, int p, int c, char* n);	// 물건 정보 추가
T_Record* o_search_by_obj(char* o, char* n);	// 물건 이름과 주문자 이름이 일치하는 물건 레코드 포인터 찾기
T_Record* o_search_by_name(char* n, int* b);	// 주문자와 일치하는 물건 레코드 포인터 찾기
T_Record* o_search_by_obj2(char* o,char* n, int* b);
void o_update(T_Record* o, int p, int c);	//특정 물건 레코드 정보 업데이트
void o_delete(T_Record* o);	// 특정 물건 레코드의 정보 제거
void o_get_all(T_Record* a[]);	// 물건 정보가 들어있는 모든 레코드 포인터의 배열 만들기
char* o_to_string(T_Record* o);	// 특정 물건 레코드의 내용을 문자열로 가져오기
char* o_getobj(T_Record* o);	// 특정 물건 레코드의 물건이름 가져오기
int o_getprice(T_Record* o);	// 특정 물건 레코드의 가격 가져오기
int o_getcount(T_Record* o);	// 특정 물건 레코드의 수량 가져오기
char* o_getname(T_Record* o);	// 특정 물건 레코드의 주문자이름 가져오기
void o_init();	// 모든 레코드 제거
char* o_to_string_save(T_Record* o);	//레코드의 내용을 파일 저장용 문자열로 가져오기
int o_total_price(T_Record* o, int total);	// 특정 물건 레코드의 총 가격
void o_sort(T_Record* a[], int size);	// 가나다 순으로 정렬된 레코드 포인터 배열 만들기
R_Record* o_ranking(T_Record* o, int total);
void o_ranking_list(R_Record* rank[], int size);
char* o_ranking_string(int i);
