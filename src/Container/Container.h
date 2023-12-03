#ifndef _CONTAINER_H_
#define _CONTAINER_H_

#include <cstdlib>
#include <cstring>
#include <algorithm>

#include "LogInfo/LogErrors.h"

static const size_t Init_container_capacity = 100;

template<typename ItemType>
class Container 
{
    public:
        Container(const size_t capacity):m_data(nullptr),  m_size(capacity), m_capacity(capacity)
        {

            m_data = (ItemType*) calloc(m_capacity, sizeof(ItemType));
            if (m_data == nullptr)
            {
                PROCESS_ERROR(ERR_MEMORY_ALLOC, "allocate memmory to class container failed\n");
                return;
            }

            return;
        }
        
        Container():Container(Init_container_capacity){ m_size = 0; }


        ~Container()
        {
            for (size_t it = 0; it < m_size; it++)
                m_data[it].~ItemType();

            free(m_data);
            
            return;
        }

        void operator= ( const Container& ) = delete;

        bool   isEmpty () const {return m_size == 0;}
        size_t getSize () const {return m_size;};

        void pushBack (const ItemType &value)
        {
            if (m_size >= m_capacity) 
                this->AddMemory();
            
            memcpy(m_data + m_size, &value, sizeof(ItemType));

            m_size++;

            return;
        }

        void popBack  ()
        {
            if (m_size != 0) m_size--;

            m_data[m_size].~ItemType();

            return;
        }

        void ascent (size_t pos)
        {
            if (pos >= m_size)
                return;

            while (pos != 0)
            {
                std::swap(m_data[pos], m_data[pos - 1]);
                pos--;
            }    

            return;

        }

        void drown (size_t pos)
        {
            if (pos >= m_size)
                return;

            while (pos != m_size - 1)
            {
                std::swap(m_data[pos], m_data[pos + 1]);
                pos++;
            }    

            return;

        }

        ItemType& getBack() const
        {
            return m_data[m_size - 1];
        }

        ItemType& operator[](const size_t index)
        {
            if (index < m_capacity)
                return m_data[index];
        }

        const ItemType& operator[](const size_t index) const 
        {
            if (index < m_capacity)
                return m_data[index];
        }
        
    private:

        void AddMemory ()
        {
            m_capacity *= 2;

            ItemType* tmp = m_data;
            
            m_data = (ItemType*) calloc(m_capacity, sizeof(ItemType));
            if (m_data == nullptr)
            {
                PROCESS_ERROR(ERR_MEMORY_ALLOC, "allocate memmory to class container failed\n");
                return;
            }

            for (size_t it = 0; it < m_size; ++it) 
            {
                memcpy( m_data + it, tmp + it, sizeof(ItemType));
                tmp[it].~ItemType();
            }
            
            free(tmp);
            return;
        }

        ItemType* m_data;

        size_t m_size;
        size_t m_capacity;
};



#endif