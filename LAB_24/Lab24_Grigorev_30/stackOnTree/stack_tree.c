#include <stdlib.h>

#include "stack_tree.h"

stack_tree* stree_create(int max_len) {
	stack_tree* res = malloc(sizeof(stack_tree));

	if (res == NULL) 
    	return NULL;
  
	res -> max_len = max_len;
	res -> buf = malloc(sizeof(tree) * max_len);
	
	if (res -> buf == NULL) {
    	free(res);
    	return NULL;
	}

	res -> len = 0;
	
	return res;
}

static int grow(stack_tree* stree) {
	int new_max_len = stree -> max_len * 2;
	tree* new_buf = realloc(stree -> buf, sizeof(tree) * new_max_len);
	
	if (new_buf == NULL) 
		return 0;
	
	stree -> buf = new_buf;
	stree -> max_len = new_max_len;
	
	return 1;
}

void stree_destroy(stack_tree* stree) {
	if (!stree) 
		return;
	
	free(stree -> buf);
	free(stree);
}

int stree_is_empty(stack_tree* stree) {
	return stree -> len == 0;
}

int stree_push_back(stack_tree* stree, tree value) {
	if (stree -> len == stree -> max_len)
		if (!grow(stree)) 
			return 0;
	
	stree -> buf[stree -> len] = value;
	stree -> len++;
	
	return 1;
}

tree stree_pop_back(stack_tree* stree) {
	tree value = stree -> buf[stree -> len - 1];
  	stree -> len--;
  
	return value;
}

tree stree_top(stack_tree* stree) {
	return stree -> buf[0];
}
