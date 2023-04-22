// HashSet.hpp
//
// ICS 46 Winter 2022
// Project #4: Set the Controls for the Heart of the Sun
//
// A HashSet is an implementation of a Set that is a separately-chained
// hash table, implemented as a dynamically-allocated array of linked
// lists.  At any given time, the HashSet has a "size" indicating
// how many elements are stored within it, along with a "capacity"
// indicating the size of the array.
//
// As elements are added to the HashSet and the proportion of the HashSet's
// size to its capacity exceeds 0.8 (i.e., there are more than 80% as many
// elements as there are array cells), the HashSet should be resized so
// that it is twice as large as it was before.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector) to store the information
// in your data structure.  Instead, you'll need to use a dynamically-
// allocated array and your own linked list implemenation; the linked list
// doesn't have to be its own class, though you can do that, if you'd like.

#ifndef HASHSET_HPP
#define HASHSET_HPP

#include <functional>
#include "Set.hpp"



template <typename ElementType>
class HashSet : public Set<ElementType>
{
public:
    // The default capacity of the HashSet before anything has been
    // added to it.
    static constexpr unsigned int DEFAULT_CAPACITY = 10;

    // A HashFunction is a function that takes a reference to a const
    // ElementType and returns an unsigned int.
    using HashFunction = std::function<unsigned int(const ElementType&)>;

public:
    // Initializes a HashSet to be empty, so that it will use the given
    // hash function whenever it needs to hash an element.
    explicit HashSet(HashFunction hashFunction);

    // Cleans up the HashSet so that it leaks no memory.
    ~HashSet() noexcept override;

    // Initializes a new HashSet to be a copy of an existing one.
    HashSet(const HashSet& s);

    // Initializes a new HashSet whose contents are moved from an
    // expiring one.
    HashSet(HashSet&& s) noexcept;

    // Assigns an existing HashSet into another.
    HashSet& operator=(const HashSet& s);

    // Assigns an expiring HashSet into another.
    HashSet& operator=(HashSet&& s) noexcept;


    // isImplemented() should be modified to return true if you've
    // decided to implement a HashSet, false otherwise.
    bool isImplemented() const noexcept override;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function triggers a resizing of the
    // array when the ratio of size to capacity would exceed 0.8, in which case
    // the new capacity should be determined by this formula:
    //
    //     capacity * 2 + 1
    //
    // In the case where the array is resized, this function runs in linear
    // time (with respect to the number of elements, assuming a good hash
    // function); otherwise, it runs in constant time (again, assuming a good
    // hash function).  The amortized running time is also constant.
    void add(const ElementType& element) override;


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in constant time (with respect
    // to the number of elements, assuming a good hash function).
    bool contains(const ElementType& element) const override;


    // size() returns the number of elements in the set.
    unsigned int size() const noexcept override;


    // elementsAtIndex() returns the number of elements that hashed to a
    // particular index in the array.  If the index is out of the boundaries
    // of the array, this function returns 0.
    unsigned int elementsAtIndex(unsigned int index) const;


    // isElementAtIndex() returns true if the given element hashed to a
    // particular index in the array, false otherwise.  If the index is
    // out of the boundaries of the array, this functions returns false.
    bool isElementAtIndex(const ElementType& element, unsigned int index) const;


private:
    HashFunction hashFunction;

    // You'll no doubt want to add member variables and "helper" member
    // functions here.
    
    struct Node
    {
        ElementType key;
        ElementType value;
        Node* next;
    };

    Node **bucket;
    unsigned int bucketSize;
    unsigned int cap;
};



namespace impl_
{
    template <typename ElementType>
    unsigned int HashSet__undefinedHashFunction(const ElementType& element)
    {
        return 0;
    }
}


template <typename ElementType>
HashSet<ElementType>::HashSet(HashFunction hashFunction)
    : hashFunction{hashFunction}, bucket{new Node*[DEFAULT_CAPACITY]}, bucketSize{0}, cap{DEFAULT_CAPACITY}
{
    for(unsigned int i = 0; i < DEFAULT_CAPACITY; ++i)
    {
        bucket[i] = nullptr;
    }
}


template <typename ElementType>
HashSet<ElementType>::~HashSet() noexcept
{
    for(unsigned int i = 0; i < DEFAULT_CAPACITY; i++)
    {
        Node* newNode = bucket[i];
        while(newNode != nullptr)
        {
            Node* temp = newNode;
            newNode = newNode->next; 
            delete temp;
        }
    }
    delete[] bucket;
}


template <typename ElementType>
HashSet<ElementType>::HashSet(const HashSet& s)
    : hashFunction{impl_::HashSet__undefinedHashFunction<ElementType>}
{
    bucketSize = s.bucketSize;
    cap = s.cap;
    bucket = new Node*[cap];
    
    for(unsigned int i = 0; i < cap; ++i)
    {
        bucket[i] = nullptr;
    }

    for(unsigned int i = 0; i < cap; ++i)
    {
        Node* newNode = s.bucket[i];

        while(newNode != nullptr)
        {
            bucket[i]->key = s.bucket[i]->key;
            bucket[i]->value = s.bucket[i]->value;
            bucket[i]->next = s.bucket[i]->next;

            newNode = newNode->next;
        }
    }
}


template <typename ElementType>
HashSet<ElementType>::HashSet(HashSet&& s) noexcept
    : hashFunction{impl_::HashSet__undefinedHashFunction<ElementType>}
{
    bucketSize = 0;
    cap = DEFAULT_CAPACITY;
    bucket = new Node*[cap];

    for(unsigned int i = 0; i < cap; ++i)
    {
        bucket[i] = nullptr;
    }
    
    std::swap(bucketSize, s.bucketSize);
    std::swap(cap, s.cap);
    std::swap(bucket, s.bucket);
}


template <typename ElementType>
HashSet<ElementType>& HashSet<ElementType>::operator=(const HashSet& s)
{
    if(this != &s)
    {
        bucketSize = s.bucketSize;
        cap = s.cap;
        
        for(unsigned int i = 0; i < cap; ++i)
        {
            bucket[i] = nullptr;
        }

        for(unsigned int j = 0; j < cap; ++j)
        {
            Node* newNode = s.bucket[j];

            while(newNode != nullptr)
            {
                bucket[j] = newNode;
                newNode = newNode->next;
            }
            delete newNode;
        }
    }
    return *this;
}


template <typename ElementType>
HashSet<ElementType>& HashSet<ElementType>::operator=(HashSet&& s) noexcept
{
    std::swap(bucketSize, s.bucketSize);
    std::swap(cap, s.cap);
    std::swap(bucket, s.bucket);
    
    return *this;
}


template <typename ElementType>
bool HashSet<ElementType>::isImplemented() const noexcept
{
    return true;
}


template <typename ElementType>
void HashSet<ElementType>::add(const ElementType& element)
{
    unsigned int hashKey = hashFunction(element) % cap;
    Node* temp = nullptr;
    Node* newNode;
    newNode = bucket[hashKey];
    
    while(newNode != nullptr)
    {
        temp = newNode;
        newNode = newNode->next;
    }
    if(newNode == nullptr)
    {
        newNode = new Node;
        newNode->key = hashKey;
        newNode->value = element;
        newNode->next = nullptr;
        
        if(temp == nullptr)
        {
            bucket[hashKey] = newNode;
        }
        else
        {
            temp->next = newNode;
        }
    }
    else
    {
        newNode->value = element;
    }

    if(bucketSize > (0.8 * cap))
    {
        int newCap = cap*2 + 1;
        Node** newBucket = new Node*[newCap];

        for(unsigned int i = 0; i < newCap; ++i)
        {
            newBucket[i] = nullptr;
        }
        
        int newHashKey;
        for(unsigned int j = 0; j < newCap; ++j)
        {
            newHashKey = hashFunction(element) % newCap;
            Node* temp2 = nullptr;
            Node* newNode2;
            newNode2 = newBucket[newHashKey];

            while(temp2 != nullptr)
            {
                temp2 = newNode2;
                newNode2 = newNode2->next;
            }
            if(newNode2 == nullptr)
            {
                newNode2 = new Node;
                newNode2->key = newHashKey;
                newNode2->value = element;
                newNode2->next = nullptr;

                if(temp2 == nullptr)
                {
                    newBucket[newHashKey] = newNode2;
                }
                else
                {
                    temp2->next = newNode2;
                }
            }
            else
            {
                newNode2->value = element;
            }
            
        }
        delete [] bucket;
        bucket = newBucket;
        cap = newCap;
    }
    bucketSize++;
}


template <typename ElementType>
bool HashSet<ElementType>::contains(const ElementType& element) const
{
    unsigned int hashKey = hashFunction(element) % cap;
    Node* newNode = bucket[hashKey];

    while(newNode != nullptr)
    {
        if(newNode->value == element)
        {
            return true;
        }
        else
        {
            newNode = newNode->next;
        }
    }
    return false;

}


template <typename ElementType>
unsigned int HashSet<ElementType>::size() const noexcept
{
    return bucketSize;
}


template <typename ElementType>
unsigned int HashSet<ElementType>::elementsAtIndex(unsigned int index) const
{
    unsigned int total = 0;
    
    if(index >= cap && index < 0)
    {
        return 0;
    }
    else
    {
        Node* newNode;
        newNode = bucket[index];

        while(newNode != nullptr)
        {
            newNode = newNode->next;
            total++;
        }
        delete newNode;;
    }
    return total;
}


template <typename ElementType>
bool HashSet<ElementType>::isElementAtIndex(const ElementType& element, unsigned int index) const
{
    if(index >= cap && index < 0)
    {
        return false;
    }
    else
    {
        Node* newNode;
        newNode = bucket[index];

        while(newNode != nullptr)
        {
            if(newNode->value == element)
            {
                return true;
            }
            newNode = newNode->next;
        }
        delete newNode;
    }
    return false;
}



#endif

