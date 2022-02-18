// FILE: node.cpp
//
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
// IMPLEMENTS: The functions of the node class and the
// linked list toolkit (see node1.h for documentation).
//
// INVARIANT for the node class:
//   The data of a node is stored in data_field
//   and the link to the next node is stored in link_field.

#include "node.h"
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t
#include <iostream>   // Provides printing capabilities

using namespace std;

namespace coen79_lab6
{
	// returns length of linked list
    size_t list_length(const node* head_ptr)
    {
		const node *cursor;
		size_t answer;

		answer = 0;
		for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
	    	++answer;

		return answer;
    }

	// inserts node at head of linked list
    void list_head_insert(node*& head_ptr, const node::value_type& entry)
    {
    	head_ptr = new node(entry, head_ptr);
    }

	// inserts node ahead of previous_ptr with value entry
    void list_insert(node* previous_ptr, const node::value_type& entry)
    {
    	node *insert_ptr;

    	insert_ptr = new node(entry, previous_ptr->link( ));
    	previous_ptr->set_link(insert_ptr);
    }

	// returns location of node with value target
    node* list_search(node* head_ptr, const node::value_type& target)
    {
    	node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

	// returns constant location of node with value target
    const node* list_search(const node* head_ptr, const node::value_type& target)
    {
    	const node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

	// returns the pointer to the node at position in linked list
    node* list_locate(node* head_ptr, size_t position)
    {
    	node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

	// returns a constant pointer to the node at position in linked list
    const node* list_locate(const node* head_ptr, size_t position)
    {
    	const node *cursor;
    	size_t i;

    	assert (position > 0);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

	// removes the head pointer of a linked list
    void list_head_remove(node*& head_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = head_ptr;
    	head_ptr = head_ptr->link( );
    	delete remove_ptr;
    }

	// removes node pointed to by previous_ptr
    void list_remove(node* previous_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = previous_ptr->link( );
    	previous_ptr->set_link( remove_ptr->link( ) );
    	delete remove_ptr;
    }

	// removes each node of a linked list one by one
    void list_clear(node*& head_ptr)
    {
    	while (head_ptr != NULL)
    	    list_head_remove(head_ptr);
    }

	// creates a copy of linked list
    void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
    {
    	head_ptr = NULL;
    	tail_ptr = NULL;

    	// Handle the case of the empty list.
    	if (source_ptr == NULL)
    	    return;

    	// Make the head node for the newly created list, and put data in it.
    	list_head_insert(head_ptr, source_ptr->data( ));
    	tail_ptr = head_ptr;

    	// Copy the rest of the nodes one at a time, adding at the tail of new list.
    	source_ptr = source_ptr->link( );
    	while (source_ptr != NULL)
    	{
    	    list_insert(tail_ptr, source_ptr->data( ));
    	    tail_ptr = tail_ptr->link( );
    	    source_ptr = source_ptr->link( );
    	}
    }

	// makes copy of linked list excluding end pointer
	void list_piece(node* start_ptr, node* end_ptr, node*& head_ptr, node*& tail_ptr) 
	{
		head_ptr = NULL;
		tail_ptr = NULL;

		// handles cases of start pointer being invalid
		if(start_ptr == NULL || start_ptr == end_ptr)
			return;

		// makes the start node the head node of the new linked list
		list_head_insert(head_ptr, start_ptr->data());
		tail_ptr = head_ptr;

		// copies rest of the nodes one at a time until the end node is reached
		while(start_ptr->link() != end_ptr) {
			start_ptr = start_ptr->link();
			list_insert(tail_ptr, start_ptr->data());
			tail_ptr = tail_ptr->link();
		}
	}

	// returns the occurences of target data in linked list
    size_t list_occurrences(node* head_ptr, const node::value_type& target) 
	{
		size_t sum = 0;
		node *tmp = head_ptr;

		while(tmp != NULL) 
		{
			if(tmp->data() == target)
				sum++;
			tmp = tmp->link();
		}
		return sum;
	}

	// inserts new node with data field entry into position of linked list
    void list_insert_at(node*& head_ptr, const node::value_type& entry, size_t position) 
	{
		// handles out of bounds case and pointer being invalid
		assert((position > 0) && (position <= list_length(head_ptr) + 1));

		// inserts node into head position
		if (position==1) {
            list_head_insert(head_ptr, entry);
            return;
        }

		// inserts node into position
        node* temp = list_locate(head_ptr, position-1);
        list_insert(temp,entry);
	}

	// removes node in linked list at position
    node::value_type list_remove_at(node*& head_ptr, size_t position) 
	{
		// handles boundary case
		assert((position > 0) && (position <= list_length(head_ptr)));

		// obtains value of entry
		node::value_type value = list_locate(head_ptr, position) -> data();

		if(position == 1)
			list_head_remove(head_ptr);
		else
			list_remove(list_locate(head_ptr, position - 1));
		
		// return value of removed node
		return value;
		
	}

	// copies segment of linked list including the node at position finish
    node* list_copy_segment(node* head_ptr, size_t start, size_t finish) 
	{		
		// handles out of bounds case and pointer being invalid
		assert((start > 0) && (start <= finish) && (finish <= list_length(head_ptr)));
		if(head_ptr == NULL)
			return NULL;

		// finds location of start and finish positions
		node* start_loc = list_locate(head_ptr, start);
		node* fin_loc = list_locate(head_ptr, finish + 1);

		// makes the head and tail nodes for the new linked list
		node* new_head;
		node* new_tail;

		// creates new linked list
		list_piece(start_loc, fin_loc, new_head, new_tail);
		
		// returns head pointer for new linked list
		return new_head;
		
	}

	// prints out value of every node in linked list to standard out
    void list_print (const node* head_ptr) 
	{
		if(head_ptr == NULL){
      		cout << endl;
      		return;
    	}
   	 	while(head_ptr->link() != NULL){
      		cout << head_ptr->data() << ", ";
      		head_ptr = head_ptr->link();
    	}
    	cout << head_ptr->data() << endl;
    	return;
	}

	// removes all nodes with duplicate values in linked list DOES THIS WORK??
    void list_remove_dups(node* head_ptr) 
	{
		node* cursor = head_ptr;
		node* scanner;
		
		// iterates cursor through linked list
		while(cursor != NULL)
		{
			scanner = cursor;

			// iterates scanner through linked list, checking for duplicates
			while(scanner->link() != NULL)
			{
				// if duplicate is found, node is removed
				if(scanner->link()->data() == cursor->data())
					list_remove(scanner);
				else
					scanner = scanner->link();
			}
			cursor = cursor->link();
		}
	}

	// Floyd's loop detection algorithm to find start of loop
    node* list_detect_loop (node* head_ptr) 
	{
		// checking head pointer
		if(head_ptr == NULL)
			return NULL;

		node* slow_runner = head_ptr;
		node* fast_runner = head_ptr;

		// moving runners until they meet or leave bounds
		while((fast_runner != NULL) && (fast_runner->link() != NULL)) 
		{
			slow_runner = slow_runner->link();
			fast_runner = fast_runner->link()->link();
			if(slow_runner == fast_runner)
				break;
		}

		// checking if loop was found
		if((fast_runner == NULL) || (fast_runner->link() == NULL))
			return NULL;

		// locating start of loop, moving both fast and slow runner one at a time
		slow_runner = head_ptr;
		while(slow_runner != fast_runner) 
		{
			slow_runner = slow_runner->link();
			fast_runner = fast_runner->link();
		}

		// returning location of start of loop
		cout << "the pointers met!" << endl;
		return slow_runner;
	}
}
