//FILE: sequence.cpp
//CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
//
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
//INVARIANT for the sequence class
//  1. The number of items in the sequence is stored in the member variable "many_nodes"
//
//  2. For an empty sequence, we do not care what is stored in any of data and head_ptr
//      and tail_ptr point to NULL; for a non-empty sequence, the items stored in the
//      sequence can be accessed using head_ptr and tail_ptr and we don't care what is
//      stored in the rest of the data.
//
//  3. If there is a current item, then it lies in *cursor; if there is no
//     current item, then cursor* equals NULL.
//
//  4. If there is a previous item, then it lies in precursor*.  If there is no previous
//       item, then precursor equals NULL.


#include <iostream>
#include <algorithm> //provides copy function
#include <cassert> //for assert function
#include "sequence.h" //header file for class
#include "node.h" // provides node class

using namespace std; //For copy function

namespace coen79_lab6
{
    // Default private member variable initialization function.
    void sequence::init()
    {
            head_ptr = NULL;
            tail_ptr = NULL;
            cursor = NULL;
            precursor = NULL;
            many_nodes = 0;
    }

    // Default Constructor
    sequence :: sequence ()
    {
            init();
    }

    // Copy Constructor
    sequence :: sequence(const sequence& source)
    {
            init();
            *this = source;
    }

    // Destructor
    sequence :: ~sequence() 
    {
            list_clear(head_ptr);
    }

    // cursor and precursor are adjusted to the beginning of the sequence
    void sequence :: start()
    {
            cursor = head_ptr;
            precursor = NULL; 
    }

    // cursor and precursor are adjusted to the end of the sequence
    void sequence :: end()
    {
            cursor = tail_ptr;
            if(many_nodes <= 1)
                precursor = NULL;
            else
            {
                precursor = head_ptr;
                while(precursor->link() != cursor)
                    precursor = precursor->link();
            }
    }

    // advances current location by one
    void sequence :: advance()
    {
            assert(is_item());
            precursor = cursor;
            cursor = cursor->link();
    }

    // inserts new node BEFORE current item in sequence
    void sequence :: insert(const value_type& entry)
    {
            many_nodes++;
            // list is empty
            if(head_ptr == NULL) 
            { 
                list_head_insert(head_ptr, entry);
                tail_ptr = head_ptr;
                cursor = head_ptr;
                precursor = NULL;
                return;
            }
            
            // cursor is at head or after tail
            if(cursor == head_ptr || cursor == NULL)
            {
                list_head_insert(head_ptr, entry);
                cursor = head_ptr;
                precursor = NULL;
                return;
            }

            // cursor is somewhere in middle
            list_insert(precursor, entry);
            cursor = precursor->link();
    }

    // attaches new node AFTER the current item in sequence
    void sequence :: attach(const value_type& entry)
    {
            many_nodes++;
            // list is empty
            if(head_ptr == NULL)
            { 
                list_head_insert(head_ptr, entry);
                tail_ptr = head_ptr;
                cursor = head_ptr;
                precursor = NULL;
                return;
            }

            // cursor is after tail or on tail
            if(cursor == NULL || cursor == tail_ptr)
            {
                list_insert(tail_ptr, entry);
                if(cursor == tail_ptr)
                    precursor = cursor;
                tail_ptr = tail_ptr->link();
                cursor = tail_ptr;
                return;
            }

            // cursor is somewhere in middle
            list_insert(cursor, entry);
            precursor = cursor;
            cursor = cursor->link();
            
    }

    // overloaded assignment operator
    void sequence :: operator= (const sequence& source)
    {
            // checking self assignment
            if(this == &source)
                return;

            // copying list
            list_clear(head_ptr);
            list_copy(source.head_ptr, head_ptr, tail_ptr);
            many_nodes = source.many_nodes;

            // checking precursor
            if(source.precursor == NULL) 
            {
                cursor = head_ptr;
                precursor = NULL;
                return;
            }

            // assigning cursor
            node* tmp = source.head_ptr;
            precursor = head_ptr;
            while(tmp != source.precursor)
            {
                tmp = tmp->link();
                precursor = precursor->link();
            }

            cursor = precursor->link();
    }

    // removes current item
    void sequence :: remove_current()
    {
            assert(is_item());
            many_nodes--;

            // cursor is at head
            if(cursor == head_ptr)
            {
                cursor = cursor->link();
                list_head_remove(head_ptr);
                return;
            }
            
            // cursor is at tail
            if(cursor == tail_ptr)
            {
                list_remove(precursor);
                tail_ptr = precursor;
                return;
            }
            
            // current location is in middle
            list_remove(precursor);
            cursor = precursor->link();
    }

    // returns length of sequence
    sequence :: size_type sequence :: size () const
    {
            return many_nodes;
    }

    // returns true if current item is valid
    bool sequence :: is_item() const
    {
            if(cursor != NULL)
                return true;
            return false;
    }

    // returns value for current item
    sequence :: value_type sequence :: current () const
    {
            assert(is_item());
            return cursor->data();
    }
}
