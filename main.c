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
	int i=1, t=0, b=0;
	int size = o_count();

	printf("Enter a name > ");
    scanf("%s", name);
	
	for(i=1;i<=size;i++){
		T_Record* p = o_search_by_name(name, &b);
		
		if(p){
			if(o_search_by_obj2(p->obj, p->name, &b)){
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
    char obj[20], name[20];
    int price, cnt;  
	
	printf("Enter a name > ");
	scanf("%s", name);
	printf("Enter a object > ");
	scanf("%s", obj);

	T_Record* p = o_search_by_obj(obj, name);
	
	if(p) {
		printf("Enter a updated info.\n");
		printf("price > ");
		scanf("%d", &price);
		printf("count > ");
		scanf("%d", &cnt);
		
		o_update(p, price, cnt);
		printf("Complete!\n");
	}
	else {
		printf("No such object & name!\n");
	}
}

void delete_record(){
	char obj[20], name[20];
	
	printf("Enter a name > ");
	scanf("%s", name);
	printf("Enter a object > ");
	scanf("%s", obj);

	T_Record* p = o_search_by_obj(obj, name);
	
	if(p) {
			o_delete(p);
			printf("The record is deleted!\n");
	}
	else {
			printf("No such object & name!\n");
	}
}

void list_record(){
    // 전체 리스트 출력
	printf("All records.\n");
	
	int size = o_count();
	T_Record* records[MAX_OBJ];
	o_get_all(records);
	
	for(int i=0; i<size; i++){
		T_Record* p = records[i];
		printf("%d. %s\n", i+1, o_to_string(p));
	}
}

void total_price(){
    char name[20];
	int i=0, t=0, b=0, t_price=0;
	int size = o_count();

	printf("Enter a name > ");
    scanf("%s", name);
	
	for(i=0;i<size;i++){
		T_Record* p = o_search_by_name(name, &b);
		
		if(p){
			if(o_search_by_obj2(p->obj, p->name, &b)){
				continue;
			}
			t_price = o_total_price(p, t_price);
			t++;
		}
	}
	
	if(t==0)
		printf("No such name!\n");
	else
		printf("%s's total price >> %d 원\n", name, t_price);	
}

void sort_record(){
	int answer;
	
	printf("All data is sorted in ascending order of names.\n");
	printf("1. Yes 0. No > ");
	scanf("%d", &answer);

	if(answer == 0) return;
	else if(answer == 1){	
		int size = o_count();

		T_Record* records[MAX_OBJ];
		o_get_all(records);
		o_sort(records, size);
		printf("Complete!\n");
	}
	else{
		printf("Your answer is wrong!\n");

		return;
	}
}

void import_record(){
    // 데이터파일 읽기
	int answer;

	printf("All data will be deleted and new records will be reloaded.\n");
	printf("1. Yes 0. No > ");
	scanf("%d", &answer);

	if(answer == 0) return;
	else if(answer == 1){	
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
	else{
		printf("Your answer is wrong!\n");

		return;
	}
}

void save_record(){
    // 데이터파일 저장
	int answer;

	printf("You choose one.\n");
	printf("1. ranking top5(total price) 2. All records > ");
	scanf("%d", &answer);

	if(answer == 1){
		FILE* fd = fopen("ranking.txt", "w");
		int i=0, j=0, k=0, b=0, t_price=0;
		int s = o_count();
		T_Record* r[MAX_OBJ];
		R_Record* rank[MAX_OBJ];
	
		o_get_all(r);
		for(j=0;j<s;j++){	
			for(i=0;i<s;i++){
				T_Record* p = o_search_by_name(r[j]->name, &b);
				
				if(p){
					if(o_search_by_obj2(p->obj, p->name, &b)){
						continue;
					}
					t_price = o_total_price(p, t_price);
				}
			}
			rank[j] = o_ranking(r[j], t_price);
			t_price = 0;
			b=0;
		}
		
		o_ranking_list(rank, s);

		for(k=0;k<5;k++){
			fprintf(fd, "%s\n", o_ranking_string(k));
		}
		printf("Complete!\n");

		fclose(fd);
	}
	else if(answer == 2){
		FILE* f = fopen("cart.txt", "w");

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
	else{
		printf("Your answer is wrong!\n");

		return;
	}
}
