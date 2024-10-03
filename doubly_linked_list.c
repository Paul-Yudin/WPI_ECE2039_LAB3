#include <stdio.h>
#include <stdlib.h>

struct float_dll{
    float data;
    struct float_dll *next;
    struct float_dll *prev;
};

struct float_dll *init_float_dll(void);
struct float_dll *insert_after(struct float_dll *target);
void delete(struct float_dll *target);
void dump_all(struct float_dll *target);
int shuffle(struct float_dll *target, int n);

int main(){
	int moved;

	struct float_dll *first = init_float_dll();
	first->data = 1.1;
	struct float_dll *second = insert_after(first);
	second->data = 2.1;
	struct float_dll *third = insert_after(second);
	third->data = 3.1;
	struct float_dll *fourth = insert_after(third);
	fourth->data = 4.1;
	struct float_dll *fifth = insert_after(fourth);
	fifth->data = 5.1;
	struct float_dll *sixth = insert_after(fifth);
	sixth->data = 6.1;
	struct float_dll *seventh = insert_after(sixth);
	seventh->data = 7.1;
	struct float_dll *eighth = insert_after(seventh);
	eighth->data = 8.1;
	struct float_dll *ninth = insert_after(eighth);
	ninth->data = 9.1;
	struct float_dll *tenth = insert_after(ninth);
	tenth->data = 10.1;

	printf("Initial list: ");
	dump_all(first);

	printf("\nDeleting third node...\n");
	delete(third);
	printf("List after deletion: ");
	dump_all(first);

	printf("\nDeleting sixth node...\n");
	delete(sixth);
	printf("List after deletion: ");
	dump_all(first);

	printf("\nDeleting first node...\n");
	delete(first);
	printf("List after deletion: ");
	dump_all(second);

	printf("\nDeleting tenth node...\n");
	delete(tenth);
	printf("List after deletion: ");
	dump_all(second);

	printf("\nShuffling second by 10...\n");
	moved = shuffle(second, 10);
	printf("Moved %d positions. List: ", moved);
	dump_all(second);

	printf("\nShuffling second by -10...\n");
	moved = shuffle(second, -10);
	printf("Moved %d positions. List: ", moved);
	dump_all(second);

	printf("\nShuffling fifth by 0...\n");
	moved = shuffle(fifth, 0);
	printf("Moved %d positions. List: ", moved);
	dump_all(second);

	printf("\nShuffling fifth by -1...\n");
	moved = shuffle(fifth, -1);
	printf("Moved %d positions. List: ", moved);
	dump_all(second);

	printf("\nShuffling fifth by 2...\n");
	moved = shuffle(fifth, 2);
	printf("Moved %d positions. List: ", moved);
	dump_all(second);

	printf("\nShuffling seventh by 3...\n");
	moved = shuffle(seventh, 3);
	printf("Moved %d positions. List: ", moved);
	dump_all(second);

	printf("\nInserting eleventh node after fifth...\n");
	struct float_dll *eleventh = insert_after(fifth);
	eleventh->data = 11.1;
	printf("List after insertion: ");
	dump_all(second);

	printf("\nInserting twelfth node after second...\n");
	struct float_dll *twelfth = insert_after(second);
	twelfth->data = 12.1;
	printf("List after insertion: ");
	dump_all(second);
	
	printf("\nDumping from fifth node...\n");
	dump_all(fifth);
	
	printf("\nDumping from ninth node...\n");
	dump_all(ninth);

	printf("\nDone\n");

	return 0;
}

struct float_dll *init_float_dll(void){
    struct float_dll *new_node = (struct float_dll *) malloc(sizeof(struct float_dll));
	if (!new_node) return NULL; //Return if memory allocation fails
	
    new_node->next = NULL;
    new_node->prev = NULL;
	
    return new_node;
}

struct float_dll *insert_after(struct float_dll *target){
    if (!target) return NULL; //Return if target NULL
	
	struct float_dll *future_prev_node = target;
	struct float_dll *future_next_node = target->next;
    struct float_dll *new_node = init_float_dll();
    if (new_node == NULL) return NULL; //Return if memory allocation fails
	
	//future previous node and new node exist at this stage, dont check for null
	
	//Link future_prev_node with new_node
	future_prev_node->next = new_node;
	new_node->prev = future_prev_node;
	
	//Link new_node with future_next_node
	new_node->next = future_next_node;
	if(future_next_node){
		future_next_node->prev = new_node;
	}

    return new_node;
}

void delete(struct float_dll *target){
    if (!target) return; //Return if target NULL
	
	struct float_dll *prev_node = target->prev;
	struct float_dll *next_node = target->next;
	
	//Link prev_node with next_node
	if (prev_node){
		prev_node->next = next_node;
	}
	if (next_node){
		next_node->prev = prev_node;
	}

    free(target);
}

void dump_all(struct float_dll *target){
	if (!target) return; //Return if target NULL
	
    struct float_dll *current = target;
	
	//Find the first node of the list
    while (current->prev != NULL) {
		current = current->prev;
    }
	
	//Print from first node to last
	while (current != NULL) {
        printf("%f ", current->data);
        current = current->next;
    }
	
    printf("\n");
}

int shuffle(struct float_dll *target, int n) {
    if (!target || n == 0) return 0;  //Return 0 if target is NULL or no movement is requested
	
    int moved = 0;
	
    // Move forward in the list if n is positive
    if (n > 0) {
        for (int i = 0; i < n && target->next != NULL; i++) {
			struct float_dll *prev_node = target->prev;
			struct float_dll *next_node = target->next;
			struct float_dll *future_next_node = next_node->next;
			
			//target and next_node exist at this stage, don't check for null
			
			//Link prev_node with next_node
			if (prev_node){
				prev_node->next = next_node;
			}
			next_node->prev = prev_node;
			
			//Link next_node with target node
			next_node->next = target;
			target->prev = next_node;
			
			//Link target node with future_next_node
			target->next = future_next_node;
			if (future_next_node){
				future_next_node->prev = target;
			}
			
            moved++;
        }
    } 
    // Move backward in the list if n is negative
    else {
        for (int i = 0; i < -n && target->prev != NULL; i++) {
			struct float_dll *prev_node = target->prev;
			struct float_dll *next_node = target->next;
			struct float_dll *future_prev_node = prev_node->prev;
			
			//target and prev_node exist at this stage, don't check for null
			
			//Link next_node with prev_node
			if (next_node){
				next_node->prev = prev_node;
			}
			prev_node->next = next_node;
			
			//Link prev_node with target node
			prev_node->prev = target;
			target->next = prev_node;
			
			//Link target node with future_prev_node
			target->prev = future_prev_node;
			if (future_prev_node){
				future_prev_node->next = target;
			}
			
            moved--;
        }
    }
	
    return moved;  //Return the total distance moved
}