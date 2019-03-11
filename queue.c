/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
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
    if (!q)
        return;

    list_ele_t *cur = q->head, *cur_next = NULL;

    if (!cur) {
        free(q);
        return;
    }

    while (cur) {
        cur_next = cur->next;
        free(cur->value);
        free(cur);
        cur = cur_next;
    }

    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (!q)
        return false;

    list_ele_t *newh;

    newh = malloc(sizeof(list_ele_t));

    if (!newh)
        return false;

    newh->value = malloc(sizeof(char) + strlen(s));

    if (!newh->value) {
        free(newh);
        return false;
    }

    strcpy(newh->value, s);
    newh->next = NULL;

    if (!q->head)
        q->head = newh;
    else {
        newh->next = q->head;
        q->head = newh;
    }

    if (!q->tail)
        q->tail = newh;

    q->size++;

    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if (!q)
        return false;

    list_ele_t *newt = malloc(sizeof(list_ele_t));

    if (!newt)
        return false;

    newt->value = malloc(sizeof(char) + strlen(s));

    if (newt->value) {
        strcpy(newt->value, s);
        newt->next = NULL;
    } else {
        free(newt);
        return false;
    }

    if (q->tail)
        q->tail->next = newt;

    q->tail = newt;

    if (!q->head)
        q->head = newt;

    q->size++;

    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (!q || !sp || !q->head || !q->head->value)
        return false;

    list_ele_t *tmp = q->head;

    memset(sp, '\0', bufsize);
    strncpy(sp, tmp->value, bufsize - 1);
    q->head = tmp->next;

    if (!q->head)
        q->tail = NULL;

    free(tmp->value);
    free(tmp);
    q->size--;

    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (!q || !q->head)
        return 0;

    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (!q || !q->head || !q->head->next)
        return;

    list_ele_t *pre = q->head, *cur = q->head->next, *next_tmp = NULL;

    pre->next = NULL;

    while (cur) {
        next_tmp = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next_tmp;
    }

    q->tail = q->head;
    q->head = pre;
}
