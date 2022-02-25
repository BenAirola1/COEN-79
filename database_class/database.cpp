// FILE: database.cpp
// CLASS implemented: database (see database.h for documentation)

// INVARIANT for the database ADT:
//   1. The items in the database are stored in a dynamic array, where each entry of the array includes
//      a company name, a pointer to the head of the linked list of products, and a
//      a pointer to the tail of the linked list of products
//   2. The number of slots in the array of companies is stored in member varibale aloc_slots
//   3. The number of used slots of the array of companies is stored in member varibale used_slots


#ifndef DATABASE_CPP
#define DATABASE_CPP

#include "database.h"


//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif


namespace coen79_lab7
{
    // Constructor for database class
    database::database(const size_type& initial_capacity) 
    {
        used_slots = 0;
        aloc_slots = initial_capacity;
        company_array = new company[aloc_slots];
    }
    
    // Copy constructor for database class
    database::database(const database &src) 
    {
        Debug("Copy constructor..." << std::endl);
        company_array = new company[src.aloc_slots];
        std::copy(src.company_array, src.company_array + src.used_slots, company_array);
        aloc_slots = src.aloc_slots;
        used_slots = src.used_slots;
    }
    
    // Assignment operator for database class
    database& database::operator= (const database &rhs) 
    {
        Debug("Assignment operator..." << std::endl);
        
        // Checks for self assignment
        if(this == &rhs)
            return *this;

        // Copies over the company array
        delete[] company_array;
        company_array = new company[rhs.aloc_slots];
        std::copy(rhs.company_array, rhs.company_array+ rhs.used_slots, company_array);

        // Updates variables
        aloc_slots = rhs.aloc_slots;
        used_slots = rhs.used_slots;

        return *this;
    }
    
    // Destructor for database class
    database::~database() 
    {
        delete[] company_array;
    }
    
    // Allocates new array of company objects
    void database::reserve(size_type new_capacity) 
    {
        Debug("Reserve..." << std::endl);

        // Verifying new space is actually necessary
        if(new_capacity == aloc_slots)
            return;
        
        // Preventing new capacity from being smaller than used spaces
        if(new_capacity < used_slots)
            new_capacity = used_slots; 

        // Copying over each company to the new array
        company* new_company_array = new company[new_capacity];
        std::copy(company_array, company_array + used_slots, new_company_array);
        delete[] company_array;

        company_array = new_company_array;
        aloc_slots = new_capacity;
    }
    
    // Inserts company into array in database object
    bool database::insert_company(const std::string &entry) 
    {
        Debug("Insert company..." << std::endl);
        assert(entry.length() > 0);
        
        // If company already exists in database, return false
        if (search_company(entry) != COMPANY_NOT_FOUND) {
            return false;
        }

        // Allocate more space if necessary
        if(used_slots == aloc_slots)
            reserve(aloc_slots + 1);

        // Add new entry to array of companies
        company insert = company(entry);
        company_array[used_slots++] = insert;
        return true;
    }
    
    // Inserts a particular product into a specified company of the database
    bool database::insert_item(const std::string& company, const std::string& product_name, const float& price) 
    {
        Debug("Insert item..." << std::endl);
        assert(company.length() > 0 && product_name.length() > 0);

        size_type pos = search_company(company);
        
        // Checks if company exists in database
        if(pos == COMPANY_NOT_FOUND)
            return false;

        return company_array[pos].insert(product_name, price); 
    }
    
    // Erases a company from the array in the database object
    bool database::erase_company(const std::string &company) 
    {   
        size_type company_index = search_company(company);

        // Checking if company exists in database
        if(company_index == COMPANY_NOT_FOUND)
            return false;

        // Shifting company array down by one, erasing target company
        for(int i = company_index; i < used_slots-1; i++)
        {
            company_array[i] = company_array[i+1];
        }
        used_slots--;
        return true;
    }
    
    // Erases particular product from a company in the database
    bool database::erase_item(const std::string& cName, const std::string& pName) 
    {
        assert(cName.length() > 0 && pName.length() > 0);
        size_type pos = search_company(cName);

        // Checking if company exists in the database
        if(pos == COMPANY_NOT_FOUND)
            return false;

        return company_array[pos].erase(pName);
    }
    
    // Returns the location of the target company in the database array
    database::size_type database::search_company(const std::string& company) 
    {
        assert(company.length() > 0);

        // Iterates through database, checking for target
        for(int i = 0; i < used_slots; i++)
        {
            if(company_array[i].get_name() == company)
                return i;
        }
        return COMPANY_NOT_FOUND;
    }
    
    // Prints out the products belonging to a specified company
    bool database::print_items_by_company(const std::string& cName) 
    {
        assert(cName.length() > 0);

        size_type c_index = search_company(cName);
        
        if (c_index == COMPANY_NOT_FOUND) 
            return false;
        
        std::cout << "Printing the products of " << cName << ":"<< std::endl;
        company_array[c_index].print_items();
        std::cout << std::endl;
        
        return true;
    }
    
    // Prints the list of companies currently in the database
    void database::print_companies() 
    {
        std::cout << "Company List" << std::endl;
        for (int i = 0; i < used_slots; i++) 
            std::cout << "- " << company_array[i].get_name() << std::endl;
    }
}

#endif
