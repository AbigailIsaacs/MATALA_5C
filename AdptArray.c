#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { FAIL = 0, SUCCESS = 1 } Result;
typedef void *PElement;
typedef void (*DEL_FUNC)(PElement);
typedef PElement (*COPY_FUNC)(PElement);
typedef void (*PRINT_FUNC)(PElement);

typedef struct AdptArray_ {
  int size;
  DEL_FUNC del;
  COPY_FUNC copy;
  PRINT_FUNC print;
  PElement *arr;
} AdptArray_, *PAdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copy, DEL_FUNC del, PRINT_FUNC print) {

 	PAdptArray adpt_arr = (PAdptArray)malloc(sizeof(AdptArray_));
 	if (adpt_arr == NULL) {
		printf("memory error");
		return NULL;
	}
	//initilizing an empty array
	adpt_arr->arr = (PElement)calloc(4, sizeof(PElement));
	if (adpt_arr->arr == NULL) {
		printf("memory error");   
		adpt_arr->size = -1; 
		return NULL;
  	} else {
    		adpt_arr->size = 4;
	}

	adpt_arr->copy = copy;
	adpt_arr->del = del;
	adpt_arr->print = print;

  return adpt_arr;
}

void DeleteAdptArray(PAdptArray adpt_arr) {
	for (int i = 0; i < (adpt_arr->size); i++) {
		if(adpt_arr->arr[i]!=NULL){
			adpt_arr->del(adpt_arr->arr[i]);
		}
	}
	free(adpt_arr->arr);
	free(adpt_arr);
}

Result SetAdptArrayAt(PAdptArray adpt_arr, int index, PElement p_element) {

	if ((adpt_arr->size) <= index) {
		PElement arrnew =(PElement)realloc(adpt_arr->arr, (index+1) * sizeof(PElement));
		
		if (arrnew == NULL) {
			
			return FAIL;
		}
	 	
    		adpt_arr->arr = arrnew;
		

    		for (int i = adpt_arr->size; i <= index; i++) {
      			adpt_arr->arr[i] = NULL;
    		}
		adpt_arr->size = index+1;
   
  	}

  	if (adpt_arr->arr[index] != NULL) {
    		adpt_arr->del(adpt_arr->arr[index]);
  	}

  	PElement c_element = adpt_arr->copy(p_element);
  	adpt_arr->arr[index] = c_element;
  	return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray adpt_arr, int index) {
	if(adpt_arr->arr[index]==NULL){
		return NULL;
	}
	PElement c_element = adpt_arr->copy(adpt_arr->arr[index]);
	return c_element;
}

int GetAdptArraySize(PAdptArray adpt_arr) {
	 return adpt_arr->size;
}

void PrintDB(PAdptArray adpt_arr) {
  for (int i = 0; i < adpt_arr->size; i++) {
	if (adpt_arr->arr[i] ==NULL){
		
	}
	else{
		adpt_arr->print(adpt_arr->arr[i]);
	}
  }
}
