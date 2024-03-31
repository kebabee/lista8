/*
Implementację cpplab::unique_ptr zawierającą podstawowe funkcjonalności unique pointera, które są opisane na cppreference.
*/

#include <iostream>
#include <concepts>
#include <chrono>
#include <memory>
#include <vector>

namespace cpplab 
{
    template <typename T>
    class unique_ptr 
    {
    private:
        T* ptr;

    public:
        explicit unique_ptr(T* p)
        {
            ptr = p;
            std::cout << "constructed\n";
        }

        unique_ptr(unique_ptr& other)
        {
            std::cout << "tried to copy, unique_ptr not constructed\n";
            ptr = nullptr;
        }

        unique_ptr(unique_ptr&& other)
        {
            ptr = other.ptr;
            other.ptr = nullptr;
            std::cout << "move constructed\n";
        }

        ~unique_ptr()
        {
            if (ptr != nullptr)
            {
                delete ptr;
                std::cout << "destructed\n";
            }
        }

        unique_ptr& operator=(unique_ptr& other)
        {
            std::cout << "tried to copy, unique_ptr not constructed\n";
            ptr = nullptr;
        }

        unique_ptr& operator=(unique_ptr&& other)
        {
            if (this != &other) 
            {
                delete ptr;
                ptr = other.ptr;
                other.ptr = nullptr;
                std::cout << "moved\n";
            }
            return *this;
        }

        T* release() 
        {
            T* releasedPtr = ptr;
            ptr = nullptr;
            return releasedPtr;
        }

        void reset(T* p) 
        {
            delete ptr;
            ptr = p;
        }

        void swap(unique_ptr& other)
        {
            std::swap(ptr, other.ptr);
        }

        T& operator*() const // dereferencja
        {
            return *ptr;
        }

        T* get() const // get adress
        {
            return ptr;
        }

        explicit operator bool() const 
        {
            return ptr != nullptr;
        }
    };

    // specjalizacja dla dynamicznych tablic
    template <typename T>
    class unique_ptr<T[]>
    {
    private:
        T* ptr;

    public:
        explicit unique_ptr(T* p)
        {
            ptr = p;
            std::cout << "constructed\n";
        }

        unique_ptr(unique_ptr&& other)
        {
            ptr = other.ptr;
            other.ptr = nullptr;
        }

        ~unique_ptr()
        {
            if (ptr != nullptr)
            {
                delete[] ptr;
                std::cout << "destructed\n";
            }
        }

        unique_ptr& operator=(unique_ptr&& other)
        {
            if (this != &other) 
            {
                delete[] ptr;
                ptr = other.ptr;
                other.ptr = nullptr;
            }
            return *this;
        }

        T* release() 
        {
            T* releasedPtr = ptr;
            ptr = nullptr;
            return releasedPtr;
        }

        void reset(T* p) 
        {
            delete ptr;
            ptr = p;
        }

        void swap(unique_ptr& other)
        {
            std::swap(ptr, other.ptr);
        }

        T& operator*() const 
        {
            return *ptr;
        }

        T& operator[](int index) const
        {
            return ptr[index];
        }

        T* get() const 
        {
            return ptr;
        }

        explicit operator bool() const 
        {
            return ptr != nullptr;
        }
    };

    template <typename T>
    bool operator==(const unique_ptr<T>& p1, const unique_ptr<T>& p2) 
    {
        return p1.get() == p2.get();
    }

    template <typename T>
    bool operator==(const unique_ptr<T[]>& p1, const unique_ptr<T[]>& p2) 
    {
        return p1.get() == p2.get();
    }

    // non0_ptr bez konceptu
    template <typename T>
    class non0_ptr 
    {
    private:
        T* ptr;

    public:
        non0_ptr(T* p)
        {
            ptr = p;
            if (ptr == nullptr) {
                throw std::invalid_argument("nullptr nie jest poprawnym wskaźnikiem!");
            }
        }

        ~non0_ptr()
        {
            delete ptr;
        }

        T* get() const {
            return ptr;
        }

        T& operator*() const 
        {
            return *ptr;
        }
    };
}
