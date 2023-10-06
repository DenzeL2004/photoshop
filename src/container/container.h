#ifndef _CONTAINER_H_
#define _CONTAINER_H_

#include "../generals_func/generals.h"
#include "../log_info/log_errors.h"

static const size_t Init_container_capacity = 100;

template<typename ItemType>
class Container 
{
    public:
        Container(const size_t capacity):data_(nullptr),  size_(0), capacity_(0)
        {
            capacity_ = capacity;

            data_ = (ItemType*) calloc(capacity_, sizeof(ItemType));
            if (data_ == nullptr)
            {
                PROCESS_ERROR(ERR_MEMORY_ALLOC, "allocate memmory to class container failed\n");
                return;
            }

            return;
        }
        
        Container():Container(Init_container_capacity){}


        ~Container()
        {
            for (size_t it = 0; it < size_; it++)
                data_[it].~ItemType();

            free(data_);
            
            return;
        }

        void operator= ( const Container& ) = delete;

        bool   IsEmpty () const {return size_ == 0;}
        size_t GetSize () const {return size_;};

        void PushBack (const ItemType &value)
        {
            if (size_ >= capacity_) 
                this->AddMemory();
            
            memcpy(data_ + size_, &value, sizeof(ItemType));

            size_++;

            return;
        }

        void PopBack  ()
        {
            if (size_ != 0) size_--;

            data_[size_].~ItemType();

            return;
        }

        void Ascent (size_t pos)
        {
            if (pos >= size_)
                return;

            while (pos != 0)
            {
                std::swap(data_[pos], data_[pos - 1]);
                pos--;
            }    

            return;

        }

        void Drown (size_t pos)
        {
            if (pos >= size_)
                return;

            while (pos != size_ - 1)
            {
                std::swap(data_[pos], data_[pos + 1]);
                pos++;
            }    

            return;

        }

        ItemType& GetBack() const
        {
            return data_[size_ - 1];
        }

        

        ItemType& operator[](const size_t index) const
        {
            if (index < size_)
                return data_[index];
        }

        const ItemType& operator[](const size_t index)
        {
            if (index < size_)
                return data_[index];
        }
        
    private:

        void AddMemory ()
        {
            capacity_ *= 2;

            ItemType* tmp = data_;
            
            data_ = (ItemType*) calloc(capacity_, sizeof(ItemType));
            if (data_ == nullptr)
            {
                PROCESS_ERROR(ERR_MEMORY_ALLOC, "allocate memmory to class container failed\n");
                return;
            }

            for (size_t it = 0; it < size_; ++it) 
            {
                memcpy( data_ + it, tmp + it, sizeof(ItemType));
                tmp[it].~ItemType();
            }
            
            free(tmp);
            return;
        }

        ItemType* data_;

        size_t size_;
        size_t capacity_;
};



#endif