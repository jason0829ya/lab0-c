#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* TODO: What if malloc returned NULL? */
    if (!q)
        return NULL;

    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* TODO: How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (!q)
        return;

    list_ele_t *this_node = q->head;
    list_ele_t *remove_node = NULL;
    while (this_node) {
        free(this_node->value);
        remove_node = this_node;
        this_node = this_node->next;

        free(remove_node);
    }

    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    /* TODO: What should you do if the q is NULL? */
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    if (!q)
        return false;

    list_ele_t *new_head = malloc(sizeof(list_ele_t));
    char *str = malloc(sizeof(char) * (strlen(s) + 1));
    if (!new_head || !str) {
        free(new_head);
        free(str);
        return false;
    }

    memset(new_head, 0, sizeof(list_ele_t));
    memset(str, 0, strlen(s) + 1);
    strncpy(str, s, strlen(s));
    new_head->next = NULL;
    new_head->value = str;

    /* first insertion */
    if (q->size == 0) {
        q->head = q->tail = new_head;
    }
    /* item exists in the queue already */
    else {
        new_head->next = q->head;
        q->head = new_head;
    }

    q->size += 1;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* TODO: You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q)
        return false;

    list_ele_t *new_tail = malloc(sizeof(list_ele_t));
    char *str = malloc(sizeof(char) * (strlen(s) + 1));
    if (!new_tail || !str) {
        free(new_tail);
        free(str);
        return false;
    }

    memset(new_tail, 0, sizeof(list_ele_t));
    memset(str, 0, strlen(s) + 1);
    strncpy(str, s, strlen(s));
    new_tail->next = NULL;
    new_tail->value = str;

    /* first insertion */
    if (q->size == 0) {
        q->head = q->tail = new_tail;
    }
    /* item exists in the queue already */
    else {
        q->tail->next = new_tail;
        q->tail = new_tail;
    }

    q->size += 1;
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || q->size == 0)
        return false;

    list_ele_t *original_head = q->head;
    if (sp) {
        // printf("%s\n", original_head->value);
        memset(sp, 0, bufsize);
        strncpy(sp, original_head->value, bufsize - 1);
    }

    q->head = q->head->next;
    /* remove the last node... */
    if (!q->head)
        q->tail = NULL;

    free(original_head->value);
    free(original_head);

    q->size -= 1;
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q)
        return 0;

    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || q->size == 0)
        return;

    list_ele_t *original_head = q->head;
    list_ele_t *original_tail = q->tail;

    list_ele_t *this_node = q->head;
    list_ele_t *next_node = this_node->next;
    list_ele_t *last_node = NULL;
    while (this_node != NULL) {
        this_node->next = last_node;

        last_node = this_node;
        this_node = next_node;
        if (this_node)
            next_node = this_node->next;
    }

    q->head = original_tail;
    q->tail = original_head;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || q->size == 1)
        return;

    /*  bubble sort  */
    int last_idx = q->size - 1;
    while (last_idx > 0) {
        list_ele_t *this_node = q->head;
        list_ele_t *last_node = NULL;
        for (unsigned i = 0; i < last_idx; i++) {
            list_ele_t *next_node = this_node->next;

            /* swap value if necessary */
            if (strcmp(this_node->value, next_node->value) > 0) {
                /* swap head and its next node */
                if (!last_node) {
                    q->head = next_node;
                    list_ele_t *tmp = next_node->next;
                    next_node->next = this_node;
                    this_node->next = tmp;
                }
                /* swap nodes except the head node */
                else {
                    list_ele_t *tmp = next_node->next;
                    last_node->next = next_node;
                    next_node->next = this_node;
                    this_node->next = tmp;
                }

                /* swap to the last node */
                if (!this_node->next) {
                    q->tail = this_node;
                }
                last_node = next_node;
            } else {
                last_node = this_node;
                this_node = this_node->next;
            }
        }
        --last_idx;
    }
}

// void q_sort(queue_t *q)
//{
//    /* TODO: You need to write the code for this function */
//    /* TODO: Remove the above comment when you are about to implement. */
//    if (!q || q->size <= 1)
//        return;
//    sort(&q->head, q->size, &q->tail);
//}
//
// void merge(list_ele_t **llist_head,
//           list_ele_t **llist_tail,
//           list_ele_t **rlist_head,
//           list_ele_t **rlist_tail)
//{
//    list_ele_t *tmp = NULL;
//
//    if (strcmp((*llist_head)->value, (*rlist_head)->value) > 0) {
//        tmp = *llist_head;
//        *llist_head = *rlist_head;
//        *rlist_head = tmp;
//        tmp = *llist_tail;
//        *llist_tail = *rlist_tail;
//        *rlist_tail = tmp;
//    }
//
//    list_ele_t *l_head = *llist_head, *l_tail = *llist_tail;
//    list_ele_t *r_head = *rlist_head;
//    list_ele_t *r_end_next = (*rlist_tail)->next;
//    while (l_head != l_tail && r_head != r_end_next) {
//        if (strcmp(l_head->next->value, r_head->value) > 0) {
//            tmp = r_head->next;
//            r_head->next = l_head->next;
//            l_head->next = r_head;
//            r_head = tmp;
//        }
//        l_head = l_head->next;
//    }
//    /*if rlist is empty but llist in not,
//    all of rlist nodes are alreay inserted into llist*/
//    if (l_head == l_tail)
//        // In this case the tail of sorted list is rlist_tail
//        l_head->next = r_head;
//    else
//        // In this case the tail of sorted list is llist_tail
//        *rlist_tail = *llist_tail;
//}
// void sort(list_ele_t **start, int n, list_ele_t **end)
//{
//    list_ele_t *prev_tail = NULL;
//    for (int cmp_t = 1; cmp_t < n; cmp_t *= 2) {
//        list_ele_t *iter;
//        for (iter = *start; iter;) {
//            list_ele_t *llist_head = iter, *llist_tail = iter;
//            list_ele_t *rlist_head, *rlist_tail;
//            int is_first = (llist_head == *start) ? 1 : 0;
//
//            for (int i = 1; i < cmp_t && llist_tail->next;
//                 i++, llist_tail = llist_tail->next)
//                ;
//            rlist_head = llist_tail->next;
//            if (!rlist_head)
//                break;
//            rlist_tail = rlist_head;
//            for (int i = 1; i < cmp_t && rlist_tail->next;
//                 i++, rlist_tail = rlist_tail->next)
//                ;
//
//            list_ele_t *tmp = rlist_tail->next;
//
//            merge(&llist_head, &llist_tail, &rlist_head, &rlist_tail);
//            if (is_first)
//                *start = llist_head;
//            else
//                prev_tail->next = llist_head;
//            prev_tail = rlist_tail;
//            iter = tmp;
//        }
//        /*NEED TO INSURE THAT
//        prev_tail ALWAYS POINT TO THE TAIL OF WHOLE LIST!*/
//        prev_tail->next = iter;
//    }
//}
