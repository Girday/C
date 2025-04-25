#include <stdlib.h>

#include "queue_tree.h"
#include "../binaryTree/tree.h"

queue_tree* qtree_create(int max_len) {
	queue_tree* res = malloc(sizeof(queue_tree));

	if (res == NULL) 
    	return NULL;
  
	res -> max_len = max_len;
	res -> buf = malloc(sizeof(tree) * max_len);
	
	if (res -> buf == NULL) {
		free(res);
		return NULL;
	}
	
	res -> len = 0;
	res -> start = 0;
	
	return res;
}

static int grow(queue_tree* qtree) {
	int new_max_len = qtree -> max_len * 2;
	tree* new_buf = realloc(qtree -> buf, sizeof(tree) * new_max_len);

	if (new_buf == NULL) 
		return 0;
	
	for (int i = qtree -> max_len - 1; i >= qtree -> start; i--)
		new_buf[new_max_len - qtree -> len + i] = new_buf[i];
	
	qtree -> start += new_max_len - qtree -> max_len;
	qtree -> buf = new_buf;
	qtree -> max_len = new_max_len;
	
	return 1;
}

void qtree_destroy(queue_tree* qtree) {
	if (!qtree) 
		return;
	
	free(qtree -> buf);
	free(qtree);
}

int qtree_is_empty(queue_tree* qtree) {
  	return qtree -> len == 0;
}

int qtree_get_size(queue_tree* qtree) {
    return qtree -> len;
}

int qtree_push_back(queue_tree* qtree, tree value) {
	if (qtree -> len == qtree -> max_len)
		if (!grow(qtree)) 
			return 0;

	qtree -> buf[(qtree -> len + qtree -> start) % qtree -> max_len] = value;
	qtree -> len++;
	
	return 1;
}

tree qtree_pop_front(queue_tree* qtree) {
	tree value = qtree -> buf[qtree -> start];
	qtree -> start = (qtree -> start + 1) % qtree -> max_len;
	qtree -> len--;
	
	return value;
}

tree qtree_top(queue_tree* qtree) {
  	return qtree -> buf[qtree -> start];
}
