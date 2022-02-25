
#ifndef ITEM_CPP
#define ITEM_CPP

#include "node.h"

using namespace std;

namespace coen79_lab7
{
    // Constructor for class node
    node::node(const std::string &itemName, const float &newPrice, node *nextNode) 
    {
        name = itemName;
        price = newPrice;
        link = nextNode;
    }
    
    // Setter for private variable name of class node
    void node::setName(const std::string &newName) 
    {
        name = newName;
    }
    
    // Setter for private variable price of class node
    void node::setPrice(const float &newPrice) 
    {
        price = newPrice;
    }
    
    // Setter for private variable link of class node
    void node::setLink(node *new_next) 
    {
        link = new_next;
    }
    
    // Getter for private variable link of class node
    node* node::getLink() 
    {
        return link;
    }
    
    // Const getter for private variable link of class node
    const node* node::getLink() const 
    {
        return link;
    }
    
    // Getter for private variable name of class node
    std::string node::getName() const
    {
        return name;
    }
    
    // Getter for private variable price of class node
    float node::getPrice() const 
    {
        return price;
    }
    
    // Initializes a new linked list with one node
    void list_init(node*& head, node*& tail, const std::string& newName, const float& newPrice) 
    {
        head = new node(newName, newPrice, NULL);
        tail = head;
    }
    
    // Attaches a new node to the end of linked list
    void list_tail_insert(node*& tail, const std::string &newName, const float &newPrice) 
    {
        assert(tail != NULL); // is this assert or if-else check ??
        tail->setLink(new node(newName, newPrice, NULL));
        tail = tail->getLink();
    }
    
    // Empties the list pointed to by head
    void list_clear(node*& head) 
    {
        while(head != NULL)
        {
            list_head_remove(head);
        }
    }
    
    // Copies list point to from old_head to list pointed to by new_head
    void list_copy(const node *old_head, node* &new_head, node* &new_tail) 
    {
        new_head = NULL;
        new_tail = NULL;
        
        const node *cur = old_head;
        while (cur != NULL) {
            if (new_head == NULL) {
                new_head = new node(cur->getName(), cur->getPrice());
                new_tail = new_head;
            }
            else {
                new_tail->setLink(new node(cur->getName(), cur->getPrice()));
                new_tail = new_tail->getLink();
            }
            cur=cur->getLink();
        }
    }
    
    // Removes the head of a linked list pointed to by head
    void list_head_remove(node*& head) 
    {
        if(head == NULL)
            return;

        node* dlt = head;
        head = head->getLink();
        delete dlt;
    }

    // Removes node from linked list given the node before it
    void list_remove(node*& prev_ptr)
    {
        if(prev_ptr == NULL)
            return;
        
        node* dlt = prev_ptr->getLink();
        prev_ptr->setLink(dlt->getLink());
        delete dlt;
    }
    
    // Prints the list
    void list_print(node *head) 
    {
        node *cur = head;
        while (cur != NULL) {
            std::cout << "- " << cur->getName() << ", where the price is $" << cur->getPrice() << std::endl;
            cur = cur->getLink();
        }
    }
    
    // Returns true if a linked list contains a specified product
    bool list_contains_item(node *head_ptr, const std::string& newName) 
    {
        return (list_search(head_ptr, newName) != NULL);
    }
    
    // Returns the location of a target product in a linked list pointed to by head
    node* list_search(node* head_ptr, const std::string& target)
    {
        node *cursor;
        
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->getLink( ))
            if (target == cursor->getName( ))
                return cursor;
        return NULL;
    }
    
    // Returns the location of a constant target product in a linked list pointed to by head
    const node* list_search(const node* head_ptr, const std::string & target)
    {
        const node *cursor;
        
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->getLink( ))
            if (target == cursor->getName( ))
                return cursor;
        return NULL;
    }
    
}

#endif