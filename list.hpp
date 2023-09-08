#ifndef SJTU_LIST_HPP
#define SJTU_LIST_HPP

#include "exceptions.hpp"
#include "algorithm.hpp"



#include <climits>
#include <cstddef>

namespace sjtu {
    /**
     * a data container like std::list
     * allocate random memory addresses for data and they are doubly-linked in a list.
     */
    template<typename T>
    class list {
    protected:
        class node {
        public:
            /**
             * add data members and constructors & destructor
             */

            T* data;
            node* next;
            node* pre;
            node() : data(nullptr), pre(nullptr), next(nullptr) { }
            node(const T& _val, node* _prev = nullptr, node* _next = nullptr)
            {

                data = (T*)operator new(sizeof(T));
                new(data)T(_val);
            }

            ~node() {
                if (data)
                {
                    delete (data);

                }
            }

        };

    public:
        node* head;
        node* tail;
        int mysize;
        /**
         * add data members for linked list as protected members
         */

         /**
          * insert node cur before node pos
          * return the inserted node cur
          */
        node* inserttt(node* pos, node* cur) {

            cur->pre = pos->pre;
            cur->next = pos;

            pos->pre->next = cur;
            pos->pre = cur;
            mysize++;
            if (pos == head)
                head = cur;
            return cur;

        }
        /**
         * remove node pos from list (no need to delete the node)
         * return the removed node pos
         */
        node* erase(node* pos) {
            pos->pre->next = pos->next;
            pos->next->pre = pos->pre;
            return pos;

        }

    public:


        class const_iterator;
        class iterator {
        public:
            /**
             * TODO add data members
             *   just add whatever you want.
             */
            node* pin;
            list* belong;

        public:

            iterator() : pin(nullptr), belong(nullptr) {}

            //iterator(node* p) : pin(p) {}
            iterator(node* p, list* _b) : pin(p), belong(_b) {}

            /**
             * iter++
             */
            node* get()
            {
                return pin;
            }
            iterator operator++(int) {
                if (pin == belong->tail) throw sjtu::runtime_error();

                iterator tmp = (*this);
                pin = pin->next;
                return tmp;

            }
            /**
             * ++iter
             */
            iterator& operator++() {//end不能++
                if (pin == belong->tail) throw sjtu::runtime_error();
                pin = pin->next;
                return (*this);
            }
            /**
             * iter--
             */

            iterator operator--(int) {//begin不能--
                if (pin == belong->head) throw sjtu::runtime_error();

                iterator tmp = (*this);
                pin = pin->pre;
                return tmp;
            }


            /**
             * --iter
             */


            iterator& operator--() {
                if (pin == belong->head) throw sjtu::runtime_error();

                pin = pin->pre;
                return (*this);
            }

            /**
             * TODO *it
             * remember to throw if iterator is invalid
             */
            T& operator *() const {
                if (pin == nullptr || pin == belong->tail)
                {
                    throw sjtu::invalid_iterator();
                }
                return *(pin->data);

            }
            /**
             * TODO it->field
             * remember to throw if iterator is invalid
             */

            T* operator ->() const noexcept {
                if (pin == nullptr)
                {
                    throw sjtu::invalid_iterator();
                }
                return pin->data;

            }


            /**
             * a operator to check whether two iterators are same (pointing to the same memory).
             */
            bool operator==(const iterator& rhs) const {
                return pin == rhs.pin;
            }
            bool operator==(const const_iterator& rhs) const {
                return pin == rhs.pin;

            }
            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator& rhs) const {
                return pin != rhs.pin;


            }
            bool operator!=(const const_iterator& rhs) const {
                return pin != rhs.pin;

            }
        };
        /**
         * TODO
         * has same function as iterator, just for a const object.
         * should be able to construct from an iterator.
         */
        class const_iterator {
        public:
            /**
             * TODO add data members
             *   just add whatever you want.
             */
            const node* pin;
            const list* belong;
        public:
            /**
             * iter++
             */

            const_iterator() {}



            const_iterator(iterator rhs)
            {
                pin = rhs.pin;
                belong = rhs.belong;
            }





            const_iterator(const node* p, const list* _b) : pin(p), belong(_b) {}

            /**
             * iter++
             */

            const_iterator operator++(int) {
                if (pin == belong->tail) throw sjtu::runtime_error();

                const_iterator tmp = (*this);
                pin = pin->next;
                return tmp;

            }
            /**
             * ++iter
             */
            const_iterator& operator++() {
                if (pin == belong->tail) throw sjtu::runtime_error();

                pin = pin->next;
                return (*this);
            }
            /**
             * iter--
             */
            const_iterator operator--(int) {
                if (pin == belong->head) throw sjtu::runtime_error();

                const_iterator tmp = (*this);
                pin = pin->pre;
                return tmp;
            }
            /**
             * --iter
             */
            const_iterator& operator--() {
                if (pin == belong->head) throw sjtu::runtime_error();

                pin = pin->pre;
                return (*this);
            }

            /**
             * TODO *it
             * remember to throw if iterator is invalid
             */


            const T& operator *() const {
                if (pin == nullptr || pin == belong->tail)
                {
                    throw sjtu::invalid_iterator();
                }
                return *(pin->data);

            }
            /**
             * TODO it->field
             * remember to throw if iterator is invalid
             */
            T* operator ->() const noexcept {
                if (pin == nullptr)
                {
                    throw sjtu::invalid_iterator();
                }

                return pin->data;

            }


            /**
             * a operator to check whether two iterators are same (pointing to the same memory).
             */
            bool operator==(const iterator& rhs) const {
                return pin == rhs.pin;
            }
            bool operator==(const const_iterator& rhs) const {
                return pin == rhs.pin;

            }
            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator& rhs) const {
                return pin != rhs.pin;




            }
            bool operator!=(const const_iterator& rhs) const {
                return pin != rhs.pin;

            }

        };
        /**
         * TODO Constructs
         * Atleast two: default constructor, copy constructor
         */
        list() {
            tail = (node*)operator new(sizeof(node));
            head = tail;
            tail->next = head;
            head->pre = tail;

            mysize = 0;



        }

        list(const list& other) {
            tail = (node*)operator new(sizeof(node));
            head = tail;
            tail->next = head;
            head->pre = tail;

            if (other.mysize != 0)
            {



                node* p = other.head;



                node* x = (node*)operator new(sizeof(node));
                x->data = (T*)operator new(sizeof(T));
                new(x->data)T(*(p->data));

                x->pre = tail;
                x->next = tail;
                tail->next = x;
                tail->pre = x;

                head = x;



                //x->pre = x;
                p = p->next;
                while (p != other.tail)
                {
                    node* x = (node*)operator new(sizeof(node));
                    x->data = (T*)operator new(sizeof(T));
                    new(x->data)T(*(p->data));
                    x->pre = tail->pre;
                    x->next = tail;
                    tail->pre->next = x;
                    tail->pre = x;
                    p = p->next;
                }
            }



            mysize = other.mysize;



        }

        /**
         * TODO Destructor
         */

        virtual ~list() {
            if (mysize == 0)
            {


                operator delete (tail);

            }
            else
            {
                node* q = head;
                //node* p = q;

                while (q != tail)
                {
                    node* p = q;
                    q = q->next;
                    (*(p->data)).~T();
                    operator delete (p->data);

                    operator delete (p);
                    //mysize--;
                }
                //node* p = q;
                operator delete (tail);



            }



        }
        /**
         * TODO Assignment operator
         */
         //begin迭代器不会失效，end迭代器也不会失效；但是在this是空链表时，begin会失效，依旧指在原来的位置，即现在的end位置；中段的迭代器全部失效
         //先写一般情况，到时候看看特殊情况能否自动自洽

        list& operator=(const list& other) {

            if (this != &other)
            {
                if (other.mysize == 0)
                {
                    node* p = head;
                    //p = p->next;

                    while (p != tail)
                    {
                        node* q = p->next;
                        //node* p = q;
                        (*(p->data)).~T();
                        operator delete (p->data);

                        operator delete (p);
                        p = q;
                    }
                    head = tail;
                    mysize = 0;
                    return (*this);
                }


                if (mysize == 0)
                {

                    node* p = other.head;
                    head = (node*)operator new(sizeof(node));
                    head->data = (T*)operator new(sizeof(T));
                    new(head->data)T(*(p->data));

                    head->next = tail;
                    tail->pre = head;
                    head->pre = tail;
                    tail->next = head;


                    p = p->next;

                    while (p != other.tail)
                    {
                        node* x = (node*)operator new(sizeof(node));
                        x->data = (T*)operator new(sizeof(T));
                        new(x->data)T(*(p->data));
                        x->pre = tail->pre;
                        x->next = tail;
                        tail->pre->next = x;
                        tail->pre = x;
                        p = p->next;
                    }
                    mysize = other.mysize;

                    return (*this);



                }


                node* q = head->next;
                (*(head->data)).~T();

                for (int i = 0; i < mysize - 1; i++)
                {
                    node* p = q->next;
                    //node* p = q;
                    (*(q->data)).~T();
                    operator delete (q->data);

                    operator delete (q);
                    q = p;
                }



                node* p = other.head;
                new(head->data)T(*(p->data));
                head->pre = tail;
                head->next = tail;
                tail->next = head;
                tail->pre = head;



                //x->pre = x;


                p = p->next;

                while (p != other.tail)
                {
                    node* x = (node*)operator new(sizeof(node));
                    x->data = (T*)operator new(sizeof(T));
                    new(x->data)T(*(p->data));
                    x->pre = tail->pre;
                    x->next = tail;
                    tail->pre->next = x;
                    tail->pre = x;
                    p = p->next;
                }
                mysize = other.mysize;

                return (*this);




            }
            else
            {
                return(*this);
            }









        }

        /**
         * access the first / last element
         * throw container_is_empty when the container is empty.
         */


        const T& front() const {
            if (mysize == 0)  throw sjtu::container_is_empty();
            return *head->data;


        }
        const T& back() const {
            if (mysize == 0)  throw sjtu::container_is_empty();


            return *tail->pre->data;

        }
        /**
         * returns an iterator to the beginning.
         */
        iterator begin() {
            return iterator(head, this);
        }
        const_iterator cbegin() const {
            return const_iterator(head, this);


        }
        /**
         * returns an iterator to the end.
         */
        iterator end() {
            return iterator(tail, this);


        }
        const_iterator cend() const {
            return const_iterator(tail, this);


        }
        /**
         * checks whether the container is empty.
         */
        virtual bool empty() const {
            if (mysize > 0) return false;
            else return true;

        }
        /**
         * returns the number of elements
         */
        virtual size_t size() const {
            return mysize;

        }

        /**
         * clears the contents
         */


        virtual void clear() {

            node* q = head;




            for (int i = 0; i < mysize; i++)
            {
                node* p = q;
                q = q->next;
                (*(p->data)).~T();
                operator delete (p->data);

                operator delete (p);
            }
            head = tail;
            mysize = 0;

        }

        /**
         * insert value before pos (pos may be the end() iterator)
         * return an iterator pointing to the inserted value
         * throw if the iterator is invalid
         */



        virtual iterator insert(iterator pos, const T& value) {

            if (pos.get() == nullptr || this != pos.belong)
            {
                throw sjtu::invalid_iterator();
            }

            node* p = (node*)operator new(sizeof(node));
            p->data = (T*)operator new(sizeof(T));
            new (p->data) T(value);


            //p->data = value;
            p->next = pos.get();
            p->pre = pos.get()->pre;
            pos.get()->pre->next = p;
            pos.get()->pre = p;
            mysize++;
            if (pos.pin == head)
            {
                head = p;
            }

            return iterator(p, this);

        }
        /**
         * remove the element at pos (the end() iterator is invalid)
         * returns an iterator pointing to the following element, if pos pointing to the last element, end() will be returned.
         * throw if the container is empty, the iterator is invalid
         */

        virtual iterator erase(iterator pos) {
            if (mysize == 0)
                throw sjtu::container_is_empty();
            if (pos.get() == nullptr || pos.get() == tail)
                throw sjtu::invalid_iterator();
            if (pos.pin == head)
            {
                head = head->next;
            }
            pos.get()->pre->next = pos.get()->next;
            pos.get()->next->pre = pos.get()->pre;
            node* q = pos.get()->next;
            mysize--;
            (*(pos.pin->data)).~T();
            operator delete (pos.pin->data);

            //(pos.pin->data).(~T);
            operator delete (pos.get());
            return iterator(q, this);
        }
        /**
         * adds an element to the end
         */
        void push_back(const T& value) {
            if (mysize == 0)
            {
                head = (node*)operator new(sizeof(node));

                head->data = (T*)operator new(sizeof(T));
                //tail = head;
                new (head->data) T(value);

                //head->data = value;
                head->next = tail;
                head->pre = tail;
                tail->next = head;
                tail->pre = head;

                mysize++;

            }
            else
            {

                node* x = (node*)operator new(sizeof(node));
                x->data = (T*)operator new(sizeof(T));
                new (x->data) T(value);


                // x->data = value;

                x->pre = tail->pre;
                x->next = tail;
                //x->next = head;
                //head->pre = x;
                tail->pre->next = x;
                tail->pre = x;


                //x->next = head;
                mysize++;

            }






        }
        /**
         * removes the last element
         * throw when the container is empty.
         */
        void pop_back() {//尾指针失效检验：不会失效
            if (mysize == 0)  throw sjtu::container_is_empty();

            if (mysize == 1)
            {
                (*(head->data)).~T();
                operator delete (head->data);

                operator delete (head);
                head = tail;
                tail->next = tail;
                tail->pre = tail;


                mysize--;
            }
            else
            {

                mysize--;
                node* p = tail->pre;
                tail->pre->pre->next = tail;
                tail->pre = tail->pre->pre;


                (*(p->data)).~T();
                operator delete (p->data);

                operator delete (p);
            }

        }
        /**
         * inserts an element to the beginning.
         */
         //检验begin迭代器是否会失效：会失效

        void push_front(const T& value) {


            node* x = (node*)operator new(sizeof(node));
            x->data = (T*)operator new(sizeof(T));

            new (x->data) T(value);

            //x->data = value;
            x->pre = tail;
            x->next = head;

            //x->next = head;
            //head->pre = x;
            tail->next = x;

            head->pre = x;
            head = x;

            mysize++;



        }
        /**
         * removes the first element.
         * throw when the container is empty.
         */
        void pop_front() {
            if (mysize == 0)
                throw sjtu::container_is_empty();
            /*if (mysize == 1)
            {
                (head->data).~T();

                operator delete (head);
                head = tail;
                mysize--;
            }*/
            else
            {
                mysize--;
                node* p = head;
                head->next->pre = tail;
                tail->next = head->next;
                head = head->next;
                (*(p->data)).~T();
                operator delete (p->data);

                operator delete (p);
            }

        }

        /**
         * sort the values in ascending order with operator< of T
         */

         /*主体部分要求实现接口(括号里为要求实现的复杂度)：
             sort(O(nlogn))
             merge(O(n + m))
             reverse(O(n))
             unique(O(n))*/



             /*void sortt(node* begin, node* end)
             {
                 int len = end - begin;
                 if (len <= 1) return;
                 node* i = begin, * j = end - 1;
                 node pivot = *(begin + (len + 1) / 2 - 1);
                 while (j - i >= 0) {
                     while (i->data < pivot.data) i++;
                     while (pivot.data < j->data) j--;
                     if (j - i >= 0) {
                         T tmp = i->data;
                         i->data = j->data;
                         j->data = tmp;

                         i++, j--;
                     }
                 }
                 if (j - begin > 0) sortt(begin, i);
                 if (end - i > 1) sortt(i, end);
             }*/
        void link(node*& a, node*& b)
        {
            if (b == nullptr)
                return;


            a->pre->next = b;
            b->pre->next = a;
            node* tmp;
            tmp = a->pre;


            a->pre = b->pre;
            b->pre = tmp;


        }
        /*void del(node* p,node* h)
        {
            if (p == h)
            {
                p->pre->next = p->next;
                p->next->pre = p->pre;
                head = head->next;
            }
            else
            {
               if (p == tail)
                {
                    p->pre->next = p->next;
                    p->next->pre = p->pre;
                    tail = tail->pre;
                }
                else
                {
                    p->pre->next = p->next;
                    p->next->pre = p->pre;
                }
            }

        }*/
        void add(node*& newh, node*& p)
        {
            if (newh == nullptr)
            {
                newh = p;
                newh->next = newh;
                newh->pre = newh;

            }
            else
            {
                newh->pre->next = p;
                p->next = newh;
                p->pre = newh->pre;
                newh->pre = p;

            }
        }

        void sortt(node*& h)
        {


            if (h == nullptr || h->next == h)
            {
                return;
            }
            //T* pivot;
            //pivot = (T*)operator new(sizeof(T));
            //////node* x = (node*)operator new(sizeof(node));

            //new (pivot) T(h->data);

           // T pivot = h->data;
            node* p = h->next;
            node* newh = nullptr;
            while (p != h)
            {
                node* q = p->next;

                if (!(*p->data < (*h->data)))
                {
                    p->pre->next = p->next;
                    p->next->pre = p->pre;

                    add(newh, p);

                }
                p = q;
            }

            /*T* tmp;
            tmp = (T*)operator new( sizeof(T));*/
            ////node* x = (node*)operator new(sizeof(node));

            //new (tmp) T(h->data);

            //
            ////tmp = h->data;
            //h->data = h->pre->data;
            //h->pre->data = *tmp;
            h = h->next;

            sortt(h);
            sortt(newh);
            link(h, newh);
        }


        //sort之后迭代器不会失效
        void sort() {
            tail->pre->next = head;
            head->pre = tail->pre;
            sortt(head);
            tail->next = head;
            tail->pre = head->pre;
            head->pre->next = tail;
            head->pre = tail;



        }
        /**
         * merge two sorted lists into one (both in ascending order)
         * compare with operator< of T
         * container other becomes empty after the operation
         * for equivalent elements in the two lists, the elements from *this shall always precede the elements from other
         * the order of equivalent elements of *this and other does not change.
         * no elements are copied or moved
         */


         //迭代器失效情况检验：merge前建立的迭代器会附着在之前的点上；merge后建立的迭代器会附着在现在的点上；说明head的值变化了
         //this的begin与end都不会失效，但是other会变成一个end指向的空节点，begin仍然指向原处
        void merge(list& other) {
            if (mysize != 0 && other.mysize != 0)
            {
                node* p = head;
                node* q = other.head;
                node* now;
                /*head->pre = nullptr;
                tail->next = nullptr;
                other.head->pre = nullptr;
                other.tail->next = nullptr;*/
                if (*q->data < *p->data)
                {
                    head = now = q;
                    q = q->next;
                }
                else
                {
                    head = now = p;
                    p = p->next;
                }

                while (p != tail && q != other.tail)
                {
                    if (*q->data < *p->data)
                    {
                        now->next = q;
                        q->pre = now;
                        now = q;
                        q = q->next;
                    }
                    else
                    {
                        now->next = p;
                        p->pre = now;
                        now = p;
                        p = p->next;
                    }
                }
                if (p != tail)
                {
                    now->next = p;
                    p->pre = now;
                }
                else
                {
                    now->next = q;
                    q->pre = now;

                    other.tail->pre->next = tail;
                    tail->pre = other.tail->pre;
                    //tail = other.tail;

                }

                head->pre = tail;
                tail->next = head;

                other.head = other.tail;
                other.tail->pre = other.tail;
                other.tail->next = other.tail;
                mysize += other.mysize;
                other.mysize = 0;
            }

            if (mysize == 0 && other.mysize != 0)
            {
                head = other.head;
                other.head = other.tail;
                other.tail->pre->next = tail;
                tail->pre = other.tail->pre;
                head->pre = tail;
                tail->next = head;
                other.tail->pre = other.tail;
                other.tail->next = other.tail;
                mysize = other.mysize;
                other.mysize = 0;
            }


        }
        /**
         * reverse the order of the elements
         * no elements are copied or moved
         */
         //迭代器情况检验：end的值始终不变，begin会失效说明改变的是连接方式，地址不曾改变

        void reverse() {
            node* p = head;
            node* tmp;
            while (p != tail)
            {
                node* q = p->next;
                tmp = p->pre;
                p->pre = p->next;
                p->next = tmp;
                p = q;
            }
            head = p->pre;
            tmp = p->pre;
            p->pre = p->next;
            p->next = tmp;



        }
        /**
         * remove all consecutive duplicate elements from the container
         * only the first element in each group of equal elements is left
         * use operator== of T to compare the elements.
         */
        void unique() {
            node* p = head->next;
            while (p != tail)
            {
                node* q = p->next;
                if (*p->data == *p->pre->data)
                {
                    p->pre->next = p->next;
                    p->next->pre = p->pre;
                    (*(p->data)).~T();
                    operator delete(p->data);

                    operator delete(p);
                    mysize--;
                }
                p = q;
            }


        }
    };


}

#endif //SJTU_LIST_HPP
