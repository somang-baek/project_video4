#include "cart.h"

// 애플리케이션용 함수 원형
void create_record();
void read_record();
void update_record();
void delete_record();
void list_record();
void total_price();
void sort_record();
void import_record();
void save_record();

int main(){
    o_init();
    int menu;

    while(1){
        printf("\nMenu : 1.Create 2.Read 3.Update 4.Delete 5.List 6.total_price 7.sort 8.import 9.Save 0.Quit > ");
        scanf("%d", &menu);
        printf("\n");
        switch(menu){
            case 1: 
                create_record();
                break;
            case 2: 
                read_record();
                break;
            case 3: 
                update_record();
                break;
            case 4: 
                delete_record();
                break;
            case 5: 
                list_record();
                break;
			case 6:
				total_price();
				break;
			case 7:
				sort_record();
				break;
            case 8: 
                import_record();
                break;
            case 9: 
                save_record();
                break;
            case 0: 
            default: 
                return 0;
        }
    }
    return 0;
}

void create_record(){
    if(!o_is_available()) {
        printf("There is no space!\n");
        return;
    }
    char obj[20], name[20];
    int price, cnt;  
    printf("Enter a new object's info.\n");
    printf("Object > ");
    scanf("%s", obj); 
    printf("Price(원) > ");
    scanf("%d", &price);
    printf("Count > ");
    scanf("%d", &cnt);
    printf("Name > ");
    scanf("%s", name);
	if(o_search_by_obj(obj, name)) {
        printf("Duplicated object&name!\n");
        return;
    }
    o_create(obj, price, cnt, name);
	printf("Complete!\n");
}

void read_record(){
    char name[20];
	int i=1, t=0;
	int* b;

	printf("Enter a name > ");
    scanf("%s", name);
	
	*b = 0;
	//printf("%d\n", *b);
	
	for(i=1;i<=MAX_OBJ;i++){
		T_Record* p = o_search_by_name(name, b);
		
		//printf("%d --- %s --- %d\n", i, name, *b);
		if(p){
			//printf("%s\n", p->name);
			if(o_search_by_obj2(p->obj, p->name, b)){
				//printf("pass\n");
				continue;
			}
	        printf("#%d Object info.\n", i);
    	    printf("Object : %s\n", o_getobj(p));
        	printf("Price : %d\n", o_getprice(p));
	        printf("Count : %d\n", o_getcount(p));
    	    printf("Name : %s\n\n", o_getname(p));
			t++;
		}
	}
	
	if(t==0)
		printf("No such name!\n");
}

void update_record(){

}

void delete_record(){

}

void list_record(){
    // 전체 리스트 출력

}

void total_price(){

}

void sort_record(){

}

void import_record(){
    // 데이터파일 읽기
	int answer;

	printf("All data will be deleted and new records will be reloaded.\n");
	printf("1. Yes 0. No > ");
	scanf("%d", &answer);

	if(answer == 0) return;
	
	o_init();
	FILE* f = fopen("cart.txt", "r");
	char obj[20], name[20];
	int price, cnt;
	
	while(!feof(f)){
		if(!o_is_available()){
			printf("[Import] There is no space!\n");
		}

		int n = fscanf(f, "%s %d %d %s", obj, &price, &cnt, name);
		if(n<4) break;
		if(o_search_by_obj(obj, name)){
			printf("[Import] Duplicated object(%s) & name(%s)!\n", obj, name);
			continue;
		}
		o_create(obj, price, cnt, name);
	}
	printf("%d records are read from file!\n", o_count());
	fclose(f);
}

void save_record(){
    // 데이터파일 저장
	FILE* f = fopen("cart.txt", "w");
	//printf("All records.\n");

	int size = o_count();
	T_Record* records[MAX_OBJ];
	o_get_all(records);
	for(int i=0;i<size;i++){
		T_Record* p = records[i];
		fprintf(f, "%s\n", o_to_string_save(p));
	}
	printf("%d records are saved in file!\n", size);
	fclose(f);
}
