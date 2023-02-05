//
//  IntegerArray.h
//  Module7-7
//
//  Created by Ольга Полевик on 05.07.2021.
//

#ifndef IntegerArray_h
#define IntegerArray_h

#include <iostream>
#include <cassert>
#include <exception>

using namespace std;

class BadLength : public exception
{
public:
    virtual  const char* what() const noexcept override
    {
        return "ERROR: wrong length.";
    }
};

class NotFound : public exception
{
public:
    virtual  const char* what() const noexcept override
    {
        return "ERROR: not found.";
    }
};

class BadRange : public exception
{
public:
    virtual  const char* what() const noexcept override
    {
        return "ERROR: out of range.";
    }
};

class IntegerArray
{
private:
    int m_length = 0;
    int* m_data = nullptr;
public:
    IntegerArray() = default;
    IntegerArray(int length) : m_length (length)
    {
        if (length < 0)
        {
            throw BadLength();
        }
        m_data = new int[length];
    }
    
IntegerArray(const IntegerArray &that) : m_length (that.m_length)
    {
        m_data = new int[m_length];
        for (int index = 0 ; index < m_length ; ++index)
        {
            m_data[index] = that.m_data[index];
        }
    }
    
~IntegerArray()
    {
        delete[] m_data;
    }
    
int find(int value)
    {
        for (int index = 0 ; index < m_length ; ++index)
        {
            if (m_data[index] == value)
            {
                return index;
            }
        }
        throw NotFound();
    }
    
void erase()
    {
        delete[] m_data;
        m_data = nullptr;
        m_length = 0;
    }
    
int& operator[](int index)
    {
        if (index < 0 || index >= m_length)
        {
            throw BadRange();
        }
        return m_data[index];
    }
     
void reallocate(int newLength)
    {
        erase();
        if (newLength <= 0)
        {
            throw BadLength();
        }
        m_data = new int[newLength];
        m_length = newLength;
    }
    
void insertBefore(int value, int index)
    {
        if (index < 0 || index > m_length)
        {
            throw BadRange();
        }
        int *data = new int[m_length + 1];
        for (int before = 0; before < index; ++before)
        {
            data[before] = m_data[before];
        }
        data[index] = value;
        for (int after = index; after < m_length; ++after)
        {
            data[after + 1] = m_data[after];
        }
        delete[] m_data;
        m_data = data;
        ++m_length;
    }
    
int getLength() const
    {
        return m_length;
    }
    
//реализация изменения длины массива согласно замечания к дз
// resize resizes the array.  Any existing elements will be kept.  This function operates slowly.
void resize(int newLength)
    {
        // if the array is already the right length, we're done
        if (newLength == m_length)
        {
            return;
        }

        // If we are resizing to an empty array, do that and return
        if (newLength <= 0)
        {
            erase();
            return;
        }

        // Now we can assume newLength is at least 1 element.  This algorithm
        // works as follows: First we are going to allocate a new array.  Then we
        // are going to copy elements from the existing array to the new array.
        // Once that is done, we can destroy the old array, and make m_data
        // point to the new array.

        // First we have to allocate a new array
        int* data = new int[newLength];

        // Then we have to figure out how many elements to copy from the existing
        // array to the new array.  We want to copy as many elements as there are
        // in the smaller of the two arrays.
        if (m_length > 0)
        {
            int elementsToCopy{ (newLength > m_length) ? m_length : newLength };

            // Now copy the elements one by one
            for (int index = 0; index < elementsToCopy ; ++index)
            {
                data[index] = m_data[index];
            }
        }

        // Now we can delete the old array because we don't need it any more
        delete[] m_data;

        // And use the new array instead!  Note that this simply makes m_data point
        // to the same address as the new array we dynamically allocated.  Because
        // data was dynamically allocated, it won't be destroyed when it goes out of scope.
        m_data = data;
        m_length = newLength;
    }
};

#endif /* IntegerArray_h */
