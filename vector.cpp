#pragma once
#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include "exceptions.hpp"

#include <climits>
#include <cstddef>


namespace sjtu {
    /**
     * a data container like std::vector
     * store data in a successive memory and support random access.
     */
    template<typename T>
    class vector {


    public:
        /**
         * TODO
         * a type for actions of the elements of a vector, and you should write
         *   a class named const_iterator with same interfaces.
         */
         /**
          * you can see RandomAccessIterator at CppReference for help.
          */
        T* head;
        long maxsize = 2;
        long num = 0;

        //迭代器

        class const_iterator;
        class iterator {
        public:

            int pin;
            vector* belong;
            /**
             * TODO add data members
             *   just add whatever you want.
             */


        public:
            /**
             * return a new iterator which pointer n-next elements
             * as well as operator-
             */
            iterator(int p, vector* _b) : pin(p), belong(_b) {}

            iterator operator+(const int& n) const {
                //TODO
                return iterator(pin + n, belong);


            }
            iterator operator-(const int& n) const {
                //TODO

                return iterator(pin - n, belong);


            }
            // return the distance between two iterators,
            // if these two iterators point to different vectors, throw invaild_iterator.
            int operator-(const iterator& rhs) const {
                //TODO
                if (belong != rhs.belong) throw sjtu::invalid_iterator();
                return pin - rhs.pin;


            }
            iterator& operator+=(const int& n) {
                //TODO
                pin += n;
                return (*this);


            }
            iterator& operator-=(const int& n) {
                //TODO
                pin -= n;
                return (*this);
            }
            /**
             * TODO iter++
             */
            iterator operator++(int) {
                iterator tmp = (*this);
                pin++;
                return tmp;

            }
            /**
             * TODO ++iter
             */
            iterator& operator++() {
                pin++;
                return (*this);
            }
            /**
             * TODO iter--
             */
            iterator operator--(int) {
                iterator tmp = (*this);
                pin--;
                return tmp;
            }
            /**
             * TODO --iter
             */
            iterator& operator--() {
                pin--;
                return (*this);
            }
            /**
             * TODO *it
             */
            T& operator*() const {
                return belong->head[pin];
            }
            /**
             * a operator to check whether two iterators are same (pointing to the same memory address).
             */
            bool operator==(const iterator& rhs) const {
                if (pin == rhs.pin && belong == rhs.belong) return true;
                else return false;

            }
            bool operator==(const const_iterator& rhs) const {
                if (pin == rhs.pin && belong == rhs.belong) return true;
                else return false;

            }
            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator& rhs) const {
                if (pin == rhs.pin && belong == rhs.belong) return false;
                else return true;

            }
            bool operator!=(const const_iterator& rhs) const {
                if (pin == rhs.pin && belong == rhs.belong) return false;
                else return true;

            }
        };
        /**
         * TODO
         * has same function as iterator, just for a const object.
         */
        class const_iterator {
        public:

            int pin;
            const vector* belong;
            /**
             * TODO add data members
             *   just add whatever you want.
             */


        public:
            /**
             * return a new iterator which pointer n-next elements
             * as well as operator-
             */
            const_iterator(int p, const vector* _b) : pin(p), belong(_b) {}
            const_iterator operator+(const int& n) const {
                //TODO

                return iterator(pin + n, belong);

            }
            const_iterator operator-(const int& n) const {
                //TODO
                return iterator(pin - n, belong);



            }
            // return the distance between two iterators,
            // if these two iterators point to different vectors, throw invaild_iterator.
            int operator-(const const_iterator& rhs) const {
                //TODO
                if (belong != rhs.belong) throw sjtu::invalid_iterator();
                return pin - rhs.pin;


            }
            const_iterator& operator+=(const int& n) {
                //TODO
                pin += n;
                return (*this);


            }
            const_iterator& operator-=(const int& n) {
                //TODO
                pin -= n;
                return (*this);
            }
            /**
             * TODO iter++
             */
            const_iterator operator++(int) {
                const_iterator tmp = (*this);
                pin++;
                return tmp;

            }
            /**
             * TODO ++iter
             */
            const_iterator& operator++() {
                pin++;
                return (*this);
            }
            /**
             * TODO iter--
             */
            const_iterator operator--(int) {
                const_iterator tmp = (*this);
                pin--;
                return tmp;
            }
            /**
             * TODO --iter
             */
            const_iterator& operator--() {
                pin--;
                return (*this);
            }
            /**
             * TODO *it
             */
            const T& operator*() const {
                return belong->head[pin];
            }
            /**
             * a operator to check whether two iterators are same (pointing to the same memory address).
             */
            bool operator==(const iterator& rhs) const {
                if (pin == rhs.pin && belong == rhs.belong) return true;
                else return false;

            }
            bool operator==(const const_iterator& rhs) const {
                if (pin == rhs.pin && belong == rhs.belong) return true;
                else return false;

            }
            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator& rhs) const {
                if (pin == rhs.pin && belong == rhs.belong) return false;
                else return true;

            }
            bool operator!=(const const_iterator& rhs) const {
                if (pin == rhs.pin && belong == rhs.belong) return false;
                else return true;

            }


        };


        //三巨头



        /**
         * TODO Constructs
         * Atleast two: default constructor, copy constructor
         */
        vector()
        {
            size_t memsize = 2*sizeof(T);
            num = 0;
            //cout << memsize<<endl<<endl;
            head = (T*)operator new[](memsize);

        }
        vector(const vector& other) {
            size_t memsize = sizeof(T) * other.size();
            head = (T*)operator new[](memsize);
            num = other.num;
            int i;
            for (T* p = head, *q = other.head, i = 0; i < num; i++, p++, q++) new (p) T(*q);

        }
        /**
         * TODO Destructor
         */
        ~vector()
        {
            //delete[]head;
            T* p = head;
            for (int i = 0; i < num; i++)
            {

                (*p).~T();
                p++;
            }
            operator delete[](head);
        }


        void doublesize()
        {
            maxsize = maxsize * 2;
            T* q = head;
            head = (T*)operator new[](maxsize * sizeof(T));
            for (int i = 0; i < num; i++)
            {
               // head[i] = q[i];
                new (head+i) T(q[i]);

            }
            T* p = q;
            for (int i = 0; i < num; i++)
            {
                
                (*p).~T();
                p++;
            }
            operator delete[](q);
        }






        /**
         * TODO Assignment operator
         */

        vector& operator=(const vector& other)
        {
            if (this != &other)
            {
                num = other.num;

                maxsize = other.maxsize;
                T* q = head;
                head = new T[maxsize];
                for (int i = 0; i < num; i++)
                {
                    head[i] = other.head[i];
                }
                T* p = q;
                for (int i = 0; i < num; i++)
                {

                    (*p).~T();
                    p++;
                }
                operator delete[](q);
                return (*this);
            }
            else
            {
                                return (*this);

            }
            
        }
        /**
         * assigns specified element with bounds checking
         * throw index_out_of_bound if pos is not in [0, size)
         */
        T& at(const size_t& pos)
        {
            if (pos < 0 || pos >= size()) throw sjtu::index_out_of_bound();

            return head[pos];

        }
        const T& at(const size_t& pos) const {
            if (pos < 0 || pos >= size()) throw sjtu::index_out_of_bound();
            return head[pos];
        }
        /**
         * assigns specified element with bounds checking
         * throw index_out_of_bound if pos is not in [0, size)
         * !!! Pay attentions
         *   In STL this operator does not check the boundary but I want you to do.
         */
        T& operator[](const size_t& pos) {
            if (pos < 0 || pos >= size()) throw sjtu::index_out_of_bound();
            return head[pos];

        }
        const T& operator[](const size_t& pos) const {
            if (pos < 0 || pos >= size()) throw sjtu::index_out_of_bound();
            return head[pos];
        }
        /**
         * access the first element.
         * throw container_is_empty if size == 0
         */
        const T& front() const {
            if (num == 0) throw sjtu::container_is_empty();
            return head[0];
        }
        /**
         * access the last element.
         * throw container_is_empty if size == 0
         */
        const T& back() const {
            if (num == 0) throw sjtu::container_is_empty();
            return head[num - 1];

        }
        /**
         * returns an iterator to the beginning.
         */
        iterator begin() {

            return iterator(0, this);
        }
        const_iterator cbegin() const {

            return const_iterator(0, this);

        }
        /**
         * returns an iterator to the end.
         */
        iterator end() {
            return iterator(num, this);


        }
        const_iterator cend() const {
            return const_iterator(num, this);

        }


        /**
         * checks whether the container is empty
         */
        bool empty() const {
            if (num == 0) return true;
            else return false;
        }
        /**
         * returns the number of elements
         */
        size_t size() const {
            return num;
        }
        /**
         * clears the contents
         */
        void clear() {
            num = 0;
            T* p = head;
            for (int i = 0; i < num; i++)
            {

                (*p).~T();
                p++;
            }
            //operator delete[](head);
        }
        /**
         * inserts value before pos
         * returns an iterator pointing to the inserted value.
         */
        iterator insert(iterator pos, const T& value) {

            if (num == maxsize) doublesize();

            for (int i = num; i > pos.pin; i--)
            {
                head[i] = head[i - 1];

            }
            num++;
            head[pos.pin] = value;
            return pos;
        }
        /**
         * inserts value at index ind.
         * after inserting, this->at(ind) == value
         * returns an iterator pointing to the inserted value.
         * throw index_out_of_bound if ind > size (in this situation ind can be size because after inserting the size will increase 1.)
         */
        iterator insert(const size_t& ind, const T& value) {
            if (ind<0 || ind>num) throw sjtu::index_out_of_bound();
            if (num == maxsize) doublesize();
            for (int i = num; i > ind; i--)
            {
                head[i] = head[i - 1];

            }
            num++;

            head[ind] = value;

            return iterator(ind, this);
        }
        /**
         * removes the element at pos.
         * return an iterator pointing to the following element.
         * If the iterator pos refers the last element, the end() iterator is returned.
         */
        iterator erase(iterator pos) {

            for (int i = pos.pin; i < num - 1; i++)
            {
                head[i] = head[i + 1];
            }
            num--;
            return pos;

        }
        /**
         * removes the element with index ind.
         * return an iterator pointing to the following element.
         * throw index_out_of_bound if ind >= size
         */
        iterator erase(const size_t& ind) {
            if (ind < 0 || ind >= num) throw sjtu::index_out_of_bound();

            for (int i = ind; i < num - 1; i++)
            {
                head[i] = head[i + 1];
            }
            num--;
            return iterator(ind, this);

        }
        /**
         * adds an element to the end.
         */
        void push_back(const T& value) {
            if (num == maxsize) doublesize();
            T* rear = head + num;
            new (rear) T(value);
            num++;
        }
        /**
         * remove the last element from the end.
         * throw container_is_empty if size() == 0
         */
        void pop_back() {
            if (num == 0) throw sjtu::container_is_empty();
            T* p = head + num - 1;
            (*p).~T();
            num--;

        }
    };


}

#endif
