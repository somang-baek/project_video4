#include "cart.h"

T_Record* obj[MAX_OBJ]; // 회원정보데이터 (전역)
int _count = 0;

int o_is_available(){
	int i;
	for(i=0; i<MAX_OBJ; i++){
			if(obj[i]==NULL) return 1;
	}
	return 0;
}

int o_first_available(){
	int i;
	for(i=0; i<MAX_OBJ; i++){
		if(obj[i]==NULL) return i;
	}
	return -1;
}

int o_count(){
    return _count;
}

void o_create(char* o, int p, int c, char* n){
	int index = o_first_available();
	obj[index] = (T_Record*)malloc(sizeof(T_Record));
	T_Record* a = obj[index];
	strcpy(a->obj, o);
	a->price = p;
	a->cnt = c;
	strcpy(a->name, n);
	_count++;

#ifdef DEBUG
	printf("[DEBUG] #%d record Complete(%s)!\n", _count, n);
#endif
}

T_Record* o_search_by_obj(char* o,char* n){
	int i;
	for(i=0; i<MAX_OBJ; i++){
		if(obj[i]!=NULL && strcmp(obj[i]->obj, o)==0){
#ifdef DEBUG
			printf("[DEBUG]Find same object(%s)\n", o);
#endif
			for(i=0; i<MAX_OBJ; i++){
				if(obj[i]!=NULL && strcmp(obj[i]->name, n)==0){
#ifdef DEBUG
					printf("[DEBUG]Find same object(%s) & name(%s)\n", o, n);
#endif
					return obj[i];
				}
			}
		}
	}
#ifdef DEBUG
	printf("[DEBUG]There are no same object(%s) & name(%s)\n", o, n);
#endif
	return NULL;
}

T_Record* o_search_by_name(char* n, int* b){
	int i=0;

	for(i=*b; i<MAX_OBJ; i++){
		if(obj[i]!=NULL && strcmp(obj[i]->name, n)==0){
			*b = i;
#ifdef DEBUG
			printf("[DEBUG]Find same name(%s) & record index is %d = %d\n", n, i, *b);
#endif
			return obj[i];
		}
	}
#ifdef DEBUG
	printf("[DEBUG]There is no same name(%s)\n", n);
#endif
	return NULL;
}

T_Record* o_search_by_obj2(char* o,char* n, int* b){
	int i;
	
	if(*b == 0){
#ifdef DEBUG
		printf("[DEBUG]Record index is %d (= 0)\n", *b);
#endif
		*b = *b + 1;
#ifdef DEBUG
		printf("[DEBUG]Next record index is %d (= 1)\n", *b);
#endif
		return NULL;
	}
	else{
		for(i=0; i<*b; i++){
			if(obj[i]!=NULL && strcmp(obj[i]->obj, o)==0){
#ifdef DEBUG
				printf("[DEBUG]Find same object(%s)\n", o);
#endif
				if(obj[i]!=NULL && strcmp(obj[i]->name, n)==0){
					*b = *b + 1;
#ifdef DEBUG
					printf("[DEBUG]Find same object(%s) & name(%s)\n", o, n);
#endif
					return obj[i];
				}
			}
		}
		
		*b = *b + 1;
#ifdef DEBUG
		printf("[DEBUG]There are no same object(%s) & name(%s), next record index is %d\n", o, n, *b);
#endif
		return NULL;
	}
}

void o_update(T_Record* o, int p, int c){
	
}

void o_delete(T_Record* o){
	
}

void o_get_all(T_Record* a[]){
	int i, c=0;
	for(i=0; i<MAX_OBJ; i++){
		if(obj[i]!=NULL){
			a[c]=obj[i];
			c++;
#ifdef DEBUG
			printf("[DEBUG]Complete making %s's array\n", a[i]->name);
#endif
		}
	}
}

void o_get_all2(T_Record* a[]){

}

char* o_to_string(T_Record* o){

}

char* o_getobj(T_Record* o){
	return o->obj;
}

int o_getprice(T_Record* o){
	return o->price;
}

int o_getcount(T_Record* o){
	return o->cnt;
}

char* o_getname(T_Record* o){
	return o->name;
}

int o_get_all_by_obj(T_Record* a[], char* p){

} 

int o_get_all_by_name(T_Record* a[], char* p){

}

void o_init(){
	// 모든 레코드 제거    
	for(int i=0;i<MAX_OBJ;i++){
		if(obj[i]!=NULL) free(obj[i]);
		obj[i] = NULL;
#ifdef DEBUG
		printf("[DEBUG]Remove all records\n");
#endif
	}
	_count = 0;
} 

char* o_to_string_save(T_Record* o){
	static char str[80];
	sprintf(str, "%s %d %d %s", o->obj, o->price, o->cnt, o->name);
#ifdef DEBUG
	printf("[DEBUG](%s) Complete!\n", str);
#endif
	return str;
}

void o_to_upload(){

}

void o_to_save(){

}

int o_total_price(T_Record* o){

}

int o_sort(T_Record* a[]){

}
