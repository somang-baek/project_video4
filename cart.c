#include "cart.h"

T_Record* obj[MAX_OBJ]; // 회원정보데이터 (전역)
R_Record* ran[MAX_OBJ]; // 회원정보데이터 (전역)
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
	int size = o_count();

	for(i=0; i<size; i++){
		if(obj[i]!=NULL && strcmp(obj[i]->obj, o)==0){
#ifdef DEBUG
			printf("[DEBUG]Find same object(%s)\n", obj[i]->obj);
#endif
			if(obj[i]!=NULL && strcmp(obj[i]->name, n)==0){
#ifdef DEBUG
				printf("[DEBUG]Find same object(%s) & name(%s)\n", obj[i]->obj, obj[i]->name);
#endif
				return obj[i];
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
	int size = o_count();

	for(i=*b; i<size; i++){
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
	o->price = p;
	o->cnt = c;
#ifdef DEBUG
	printf("[DEBUG]Complete updating %s's price(%d) & count(%d)\n", o->name, o->price, o->cnt);
#endif
}

void o_delete(T_Record* o){
	int i, index;
	
	for(i=0; i<MAX_OBJ; i++){
		if(obj[i]==o) {
			index=i;
			break;
		}
	}
	free(o);
	obj[index] = NULL;
	_count--;
#ifdef DEBUG
	printf("[DEBUG]Complete delete obj[%d]=%s\n", index, (char*)obj[index]);
#endif

	for(i=index; i<MAX_OBJ; i++){
		obj[i] = obj[i+1];
		if((i+1)==MAX_OBJ) break;
	}
#ifdef DEBUG
	printf("[DEBUG]Complete Defragmentation.\n");
#endif
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

char* o_to_string(T_Record* o){
	static char str[80];
	sprintf(str, "[%s] %s / 수량: %d / %d 원", o->name, o->obj, o->cnt, o->price);
#ifdef DEBUG
			printf("[DEBUG]Complete making %s's array to string\n", o->name);
#endif
	return str;
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

int o_total_price(T_Record* o, int total){
	total = (o->price * o->cnt) + total;

#ifdef DEBUG
	printf("[DEBUG]Complete compute total price: %d\n", total);
#endif

	return total;
}

void o_sort(T_Record* a[], int size){
	int i=0, j=0;
	T_Record* o;

	for(i=0;i<size-1;i++){
		for(j=i+1;j<size;j++){
			if(strcmp(a[i]->name, a[j]->name)>0){
#ifdef DEBUG
				printf("[DEBUG]Before: #%d %s\n", i, a[i]->name);
#endif
				o = a[i];
				a[i] = a[j];
				a[j] = o;
#ifdef DEBUG
				printf("[DEBUG]After: #%d %s\n", i, a[i]->name);
#endif
			}
		}
	}

	for(i=0;i<size;i++){
		obj[i] = a[i];
#ifdef DEBUG
		printf("[DEBUG]Complete sorted %s\n", obj[i]->name);
#endif
	}
}

R_Record* o_ranking(T_Record* o, int total){
	R_Record* p = (R_Record*)malloc(sizeof(R_Record));

	strcpy(p->name, o->name);
	p->t_price = total;

#ifdef DEBUG
	printf("[DEBUG]Complete saving %s in ranking array \n", p->name);
#endif

	return p;
}

void ran_malloc(){
	for(int i=0;i<MAX_OBJ;i++){
		ran[i] = (R_Record*)malloc(sizeof(R_Record));
	}
}

void o_ranking_list(R_Record* rank[], int size){
	int i=0, j=0, k=0, c=0;
	R_Record* o[size];
	for(i=0;i<size;i++){
		o[i] = (R_Record*)malloc(sizeof(R_Record));
	}

	for(i=0;i<size;i++){
		for(j=0;j<i;j++){
			if(strcmp(rank[i]->name, rank[j]->name)==0){
				c++;
#ifdef DEBUG
				printf("[DEBUG]Complete comparing %s & %s\n", rank[i]->name, rank[j]->name);
#endif
			}
		}

		if(c==0){
			strcpy(o[k]->name, rank[i]->name);
			o[k]->t_price = rank[i]->t_price;
#ifdef DEBUG
			printf("[DEBUG]Complete copying %s & %s\n", o[k]->name, rank[j]->name);
#endif
			k++;
		}
		c=0;
	}

	R_Record* max[k];
	for(i=0;i<k;i++){
		max[i] = (R_Record*)malloc(sizeof(R_Record));
	}
	R_Record* tmp = (R_Record*)malloc(sizeof(R_Record));
	
	for(i=0;i<k;i++){
		strcpy(max[i]->name, o[i]->name);
		max[i]->t_price = o[i]->t_price;
#ifdef DEBUG
		printf("[DEBUG]Complete copying %s & %s\n", max[i]->name, o[i]->name);
#endif
	}

	for(i=0;i<k;i++){
		for(j=i+1;j<k;j++){
#ifdef DEBUG
			printf("[DEBUG]Complete comparing %s:%d vs. %s:%d\n", max[i]->name, max[i]->t_price, max[j]->name, max[j]->t_price);
#endif
			if(max[i]->t_price < max[j]->t_price){
				strcpy(tmp->name, max[i]->name);
				tmp->t_price = max[i]->t_price;
				strcpy(max[i]->name, max[j]->name);
				max[i]->t_price = max[j]->t_price;
				strcpy(max[j]->name, tmp->name);
				max[j]->t_price = tmp->t_price;
#ifdef DEBUG
				printf("[DEBUG]Complete changing %s:%d\n", max[i]->name, max[i]->t_price);
#endif
			}
		}
	}
	
	ran_malloc();
	for(i=0;i<k;i++){
		strcpy(ran[i]->name, max[i]->name);
		ran[i]->t_price = max[i]->t_price;
#ifdef DEBUG
		printf("[DEBUG]Complete copying %s & %s\n", ran[i]->name, max[i]->name);
#endif
	}
}

char* o_ranking_string(int i){
	static char str[80];

	sprintf(str, "%d등:  %s %d", i+1, ran[i]->name, ran[i]->t_price);
#ifdef DEBUG
	printf("[DEBUG](%s) Complete!\n", str);
#endif
	return str;

}
