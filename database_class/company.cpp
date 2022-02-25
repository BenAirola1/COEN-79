// FILE: company.cpp
// CLASS implemented: company (see company.h for documentation)


#include <cassert>
#include "company.h"

//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif

namespace coen79_lab7
{
    // Default constructor for class company
    company::company() 
    {
        this->company_name = "";
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
    
    // Constructor for class company with parameter name
    company::company(const std::string& company_name) 
    {
        assert(company_name.length() > 0);
        this->company_name = company_name;
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
    
    // Copy constructor for class company
    company::company(const company &src) 
    {
        Debug("Company copy constructor..." << std::endl);
        this->company_name = src.company_name;
        list_copy(src.get_head(), head_ptr, tail_ptr);
    }

    // Overloaded assignment operator for class company
    company& company::operator= (const company &src) 
    {
        Debug("Company assignment operator..." << std::endl);
        company_name = src.company_name;
        list_clear(head_ptr);
        list_copy(src.get_head(), head_ptr, tail_ptr);
        return *this;
    }
    
    // Destructor for class company
    company::~company() 
    {
        list_clear(head_ptr);
    }
    
    // Getter for private variable company_name of class company
    std::string company::get_name() const 
    {
        return company_name;
    }
    
    // Getter for const private variable head_ptr of class company
    const node *company::get_head() const 
    {
        return head_ptr;
    }
    
    // Getter for const private variable tail_ptr of class company
    const node *company::get_tail() const 
    {
        return tail_ptr;
    }
    
    // Getter for private variable head_ptr of class company
    node* company::get_head() 
    {
        return head_ptr;
    }
    
    // Getter for private variable tail_ptr of class company
    node* company::get_tail() 
    {
        return tail_ptr;
    }
    
    // Prints components of company object
    void company::print_items() 
    {
        list_print(head_ptr);
    }
    
    // Inserts new product as a node into the company object
    bool company::insert(const std::string& product_name, const float& price) 
    {    
        assert(product_name.length() > 0);

        // Checks if product already exists in company object
        if (list_contains_item(head_ptr, product_name)) 
        {
            return false;
        }
        
        // Deals with insertion case where list is empty
        if (head_ptr == NULL) 
        {
            list_init(head_ptr, tail_ptr, product_name, price);
        }
        // Deals with insertion case where list is occupied
        else 
        {
            list_tail_insert(tail_ptr, product_name, price);
        }
        
        return true;
    }

    // Deletes the product with a matching name as product_name from company object
    bool company::erase(const std::string& product_name) 
    {
        assert(product_name.length() > 0);
        
        // Checks if empty list or doesn't contain target
        if(head_ptr == NULL || !list_contains_item(head_ptr, product_name))
            return false;
        
        node* target = list_search(head_ptr, product_name);

        // Deals with the case where target is head
        if(target == head_ptr)
        {
            list_head_remove(head_ptr);
            return true;
        }

        // Finds node immediately before target
        node* prev = head_ptr;
        while(prev->getLink() != target)
            prev = prev->getLink();

        // Deals with the case where target is on the tail
        if(target == tail_ptr)
        {
            list_remove(prev);
            tail_ptr = prev;
            return true;
        }

        // Deals with the case where target is in the middle
        list_remove(prev);
        return true;
    }
}
