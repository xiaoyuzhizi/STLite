/**
 * implement a container like std::map
 */
#ifndef SJTU_MAP_HPP
#define SJTU_MAP_HPP

 // only for std::less<T>
#include <functional>
#include <cstddef>
#include "utility.hpp"
#include "exceptions.hpp"



namespace sjtu {

	template<
		class Key,
		class T,
		class Compare = std::less<Key>
	> class map {
	public:




		bool Equal(const Key& x, const Key& y) const { return !(Compare()(x, y) || Compare()(y, x)); }

		/**
		 * the internal type of data.
		 * it should have a default constructor, a copy constructor.
		 * You can use sjtu::map as value_type by typedef.
		 */
		typedef pair<const Key, T> value_type;
		/**
		 * see BidirectionalIterator at CppReference for help.
		 *
		 * if there is anything wrong throw invalid_iterator.
		 *     like it = map.begin(); --it;
		 *       or it = map.end(); ++end();
		 */

		struct node
		{
			value_type* data;
			node* l, * r;
			size_t h;



			
			node(value_type* _data, node* _l, node* _r)
				:data(new value_type(_data)), l(_l), r(_r), h(1) {}

			~node() { delete data; }
			node(const value_type& _data)
				:data(new value_type(_data)), h(1), l(nullptr), r(nullptr) {}
			node() :data(nullptr), h(0), l(nullptr), r(nullptr) {}

		};
		size_t geth(node* t) { return t ? t->h : 0; }

		node* nai;

		node* rt;
		size_t siz;
		void LL(node*& t)
		{
			node* tLC = t->l;
			t->l = tLC->r;
			tLC->r = t;
			t->h = std::max(geth(t->l), geth(t->r)) + 1;
			tLC->h = std::max(geth(tLC->l), geth(tLC->r)) + 1;
			t = tLC;
		}
		


		

		void RR(node*& t)
		{
			node* tRC = t->r;
			t->r = tRC->l;
			tRC->l = t;
			t->h = std::max(geth(t->l), geth(t->r)) + 1;
			tRC->h = std::max(geth(tRC->l), geth(tRC->r)) + 1;
			t = tRC;
		}
		
		
		

		void oempty(node*& t)
		{
			makeempty(t->l);
			makeempty(t->r);
			delete t;
			t = nullptr;
		}


		void ocopy(node*& self, node* other)
		{
			self = new node(*(other->data));

			copy(self->l, other->l);
			self->h = other->h;

			copy(self->r, other->r);
		}


		

		void makeempty(node*& t)
		{
			if (t == nullptr)
			{
				return;

			}
			//node* tmp = t;
			oempty(t);

		}
		

		

		void copy(node*& self,  node* other)
		{
			if (other == nullptr)
			{
				self = nullptr;
				return;
			}
			ocopy(self, other);

		}


		


		





		node* insertt(const value_type& x, node*& t)
		{
			node* ret = nullptr;
			if (t == nullptr)
			{
				t = new node(x);
				return t;
			}
			else if (!Compare()(x.first, t->data->first))
			{
				ret = insertt(x, t->r);
				if (geth(t->l) - geth(t->r) == -2)//右子树太深
				{
					if (!Compare()(t->r->data->first, x.first))//右左
					{
						LL(t->r);
						RR(t);

					}
					else RR(t);
				}
			}
			else if (Compare()(x.first, t->data->first))
			{
				ret = insertt(x, t->l);
				if (geth(t->l) - geth(t->r) == 2)
				{
					if (!Compare()(x.first, t->l->data->first))
					{
						RR(t->l);
						LL(t);
					}
					else LL(t);
				}
			}
			else if (Equal(x.first, t->data->first))
			{
				return t;

			}
			
			
			t->h = std::max(geth(t->l), geth(t->r)) + 1;
			return ret;

		}

		node* findd(const Key& x) const
		{
			//return dofind(x, rt);


			node* t = rt;
			


			while (t != nullptr && (!Equal(t->data->first, x)))
			{
				if (Compare()(x, t->data->first))
				{
					t = t->l;
				}
				else
				{
					t = t->r;

				}
				
			}
			if (t == nullptr) return nai;

			return t;
		}
		node* getnxt(value_type* target, node* t, node* ret,int op=1) const
		{
			node* pos = t;


			while (Compare()(target->first, pos->data->first))
			{
				ret = pos;
				pos = pos->l;
			}
			if (!Equal(target->first, pos->data->first))
			{
				ret = getnxt(target, pos->r, ret);
			}
			else
			{
				if (pos->r)
				{
					ret = pos->r;
					while (ret->l != nullptr) ret = ret->l;
				}
			}
			return ret;
		}
		
		bool notfind(const Key& key)
		{
			node* t = findd(key);
			return (t == nai);
		}

		node* getpre(value_type* target, node* t, node* ret, int op = 0) const
		{
			node* pos = t;

			while (Compare()(pos->data->first, target->first))
			{
				ret = pos;
				pos = pos->r;
			}
			if (!Equal(pos->data->first, target->first))
			{
				ret = getpre(target, pos->l, ret);
			}
			else
			{
				if (pos->l)
				{
					ret = pos->l;
					while (ret->r != nullptr) ret = ret->r;
				}
			}
			return ret;
		}
		/*node* GetPre(node* x)const {
			node* t = x->l;
			if (t != nullptr) {
				while (t->r != nullptr) t = t->r;
				return t;
			}
			t = x;
			while (t != rt && t->fa->rch != t) t = t->fa;
			return (t == nil ? NULL : t->fa);
		}*/
		

		



		/*void remove(node* x)
		{
			if (x == nullptr) return;

			remove(x->)
		}*/

		bool subr(node*& t)
		{
			if (geth(t->l) == geth(t->r)) { --t->h; return false; }

			if (geth(t->l) - geth(t->r) == 1)  return true;
			if (geth(t->l->r) > geth(t->l->l))
			{
				RR(t->l);
				LL(t);
				return false;

			}
			LL(t);
			if (geth(t->l) == geth(t->r)) return false;
			else return true;
		}
		bool subl(node*& t)
		{
			if (geth(t->l) == geth(t->r)) { --t->h; return false; }

			if (geth(t->r) - geth(t->l) == 1)  return true;
			if (geth(t->r->l) > geth(t->r->r))
			{
				LL(t->r);
				RR(t);
				return false;

			}
			RR(t);
			if (geth(t->l) == geth(t->r)) return false;
			else return true;
		}



		bool Adjust(node*& t, int sub)//true表示这个子树高度没变
		{
			if (sub)
			{
				return subr(t);

			}
			else
			{
				return subl(t);

			}


		}

		void change(node*& minrnew, node*& minr)
		{
			minrnew->h = minr->h;
			minrnew->l = minr->l;
			minrnew->r = minr->r;
		}



		bool erasee(const Key& x, node*& t)//子树高度不变 true；子树高度减小 false
		{
			if (t == nullptr) return true;
			if (Equal(x, t->data->first))
			{
				if (t->l  && t->r )
				{
					node* minr = t->r, * minrf = t;
					while (minr->l != nullptr)
					{
						minrf = minr;
						minr = minr->l;

					}


					node* minrnew = new node(*minr->data);

					change(minrnew, minr);

					if (minrf->l == minr) minrf->l = minrnew;
					else minrf->r = minrnew;



					change(minr, t);

					node* d = t;

					t = minr;
					delete d;
					if (!erasee(minr->data->first, minr->r)) return Adjust(t, 1);
					return true;
					
					
					
					
					

				}
				else
				{

					node* old = t;
					t = (t->l != nullptr) ? t->l : t->r;
					delete old;
					return false;

				}
			}

			if (!Compare()(x, t->data->first))
			{
				if (erasee(x, t->r)) return true;
				return Adjust(t, 1);
				
				
				
			}
			if (Compare()(x, t->data->first))
			{
				if (erasee(x, t->l)) return true;
				return Adjust(t, 0);
			}


		}

		class const_iterator;
		class iterator {
		public:
			friend class map;

			map* belong;
			node* p;

			/**
			 * TODO add data members
			 *   just add whatever you want.
			 */
		public:
			iterator() {
				// TODO
				belong = nullptr;
				p = nullptr;

			}
			iterator(const iterator& other) {
				// TODO
				belong = other.belong;
				p = other.p;

			}
			iterator(map* qq, node* ww) :belong(qq), p(ww) {}

			/**
			 * TODO iter++
			 */
			iterator operator++(int) {
				if (belong == nullptr  || p == belong->nai || p==nullptr)
					throw invalid_iterator();
				iterator ret = *this;
				p = belong->getnxt(p->data, belong->rt, belong->nai,1);

				return ret;

			}
			/**
			 * TODO ++iter
			 */
			iterator& operator++() {
				if (belong == nullptr  || p == belong->nai || p == nullptr)
					throw invalid_iterator();

				p = belong->getnxt(p->data, belong->rt, belong->nai,1);

				return *this;

			}
			/**
			 * TODO iter--
			 */
			iterator operator--(int) {
				if (belong == nullptr  || *this == belong->begin() || p == nullptr)
					throw invalid_iterator();
				iterator ret = *this;
				if (this->p == belong->nai)
				{
					if (belong->rt == nullptr) p=belong->nai;
					else
					{
						node* t = belong->rt;
						while (t->r != nullptr) t = t->r;
						p= t;
					}
					
					
					
					

				}
				else
				{
					p = belong->getpre(p->data, belong->rt, belong->nai,0);

				}

				return ret;
			}
			/**
			 * TODO --iter
			 */
			iterator& operator--() {
				if (belong == nullptr  || *this == belong->begin() || p == nullptr)
					throw invalid_iterator();

				if (p == belong->nai)
				{
					if (belong->rt == nullptr) p = belong->nai;
					else
					{
						node* t = belong->rt;
						while (t->r != nullptr) t = t->r;
						p = t;
					}

				}
				else
				{
					p = belong->getpre(p->data, belong->rt, belong->nai,0);

				}

				return *this;

			}



			/**
			 * a operator to check whether two iterators are same (pointing to the same memory).
			 */
			value_type& operator*() const {
				if ( belong == nullptr || p == belong->nai || p == nullptr)
				{
					throw invalid_iterator();

				}
				return *(p->data);
			}
			bool operator!=(const const_iterator& rhs) const { return (p != rhs.p || belong != rhs.belong); }

			bool operator==(const iterator& rhs) const { return (p == rhs.p && belong == rhs.belong); }
			bool operator==(const const_iterator& rhs) const { return (p == rhs.p && belong == rhs.belong); }
			/**
			 * some other operator for iterator.
			 */
			bool operator!=(const iterator& rhs) const { return (p != rhs.p || belong != rhs.belong); }

			/**
			 * for the support of it->first.
			 * See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
			 */
			value_type* operator->() const noexcept {
				if ( belong == nullptr || p == belong->nai || p == nullptr)
				{
					throw invalid_iterator();

				}
				return p->data;

			}
		};
		class const_iterator {
			// it should has similar member method as iterator.
			//  and it should be able to construct from an iterator.
		public:
			friend class map;

			// data members.
			const map* belong;
			node* p;

		public:
			const_iterator() {
				// TODO
				belong = nullptr;
				p = nullptr;
			}
			const_iterator(const const_iterator& other) {
				// TODO
				belong = other.belong;
				p = other.p;
			}
			const_iterator(const iterator& other) {
				// TODO
				belong = other.belong;
				p = other.p;
			}
			const_iterator(const map* qq,node* ww) :belong(qq), p(ww) {}

			// And other methods in iterator.
			// And other methods in iterator.
			// And other methods in iterator.

			/**
			 * TODO iter++
			 */
			const_iterator operator++(int) {
				if (belong == nullptr || p == nullptr || p == belong->nai)
					throw invalid_iterator();
				const_iterator ret = *this;
				p = belong->getnxt(p->data, belong->rt, belong->nai,1);

				return ret;

			}
			/**
			 * TODO ++iter
			 */
			const_iterator& operator++() {
				if (belong == nullptr || p == belong->nai || p == nullptr)
					throw invalid_iterator();

				p = belong->getnxt(p->data, belong->rt, belong->nai,1);

				return *this;

			}
			/**
			 * TODO iter--
			 */
			const_iterator operator--(int) {
				if (belong == nullptr || p == nullptr || *this == belong->cbegin())
					throw invalid_iterator();
				const_iterator ret = *this;
				if (p == belong->nai)
				{
					if (belong->rt == nullptr) p = belong->nai;
					else
					{
						node* t = belong->rt;
						while (t->r != nullptr) t = t->r;
						p = t;
					}

				}
				else
				{
					p = belong->getpre(p->data, belong->rt, belong->nai,1);

				}

				return ret;
			}
			/**
			 * TODO --iter
			 */
			const_iterator& operator--() {
				if (belong == nullptr || p == nullptr || *this == belong->cbegin())
					throw invalid_iterator();

				if (p == belong->nai)
				{
					if (belong->rt == nullptr) p = belong->nai;
					else
					{
						node* t = belong->rt;
						while (t->r != nullptr) t = t->r;
						p = t;
					}

				}
				else
				{
					p = belong->getpre(p->data, belong->rt, belong->nai,0);

				}

				return *this;

			}



			/**
			 * a operator to check whether two iterators are same (pointing to the same memory).
			 */
			value_type& operator*() const {
				if ( belong == nullptr || p == nullptr || p == belong->nai)
				{
					throw invalid_iterator();

				}
				return *(p->data);
			}
			bool operator!=(const const_iterator& rhs) const { return (p != rhs.p || 0 || belong != rhs.belong); }

			bool operator==(const iterator& rhs) const { return ( p == rhs.p && belong == rhs.belong); }
			bool operator==(const const_iterator& rhs) const { return ( p == rhs.p && belong == rhs.belong); }
			/**
			 * some other operator for iterator.
			 */
			bool operator!=(const iterator& rhs) const { return (p != rhs.p || belong != rhs.belong); }

			/**
			 * for the support of it->first.
			 * See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
			 */
			value_type* operator->() const noexcept {
				if ( belong == nullptr || p == nullptr || p == belong->nai)
				{
					throw invalid_iterator();
					 
				}
				return p->data;

			}

		};
		/**
		 * TODO two constructors
		 */
		map() {
			rt = nullptr;
			nai = new node();
			siz = 0;
		}
		map(const map& other) {
			//makeempty(rt);

			nai = new node();

			copy(rt, other.rt);
			siz = other.siz;



		}
		/**
		 * TODO assignment operator
		 */
		map& operator=(const map& other) {
			if (this == &other)
			{
				return (*this);

			}
			siz = other.siz;

			makeempty(rt);

			copy(rt, other.rt);
			return (*this);

		}
		/**
		 * TODO Destructors
		 */
		~map() {
			makeempty(rt);
			siz = 0;

			delete nai;

		}




		/**
		 * TODO
		 * access specified element with bounds checking
		 * Returns a reference to the mapped value of the element with key equivalent to key.
		 * If no such element exists, an exception of type `index_out_of_bound'
		 */
		T& at(const Key& key) {
			node* t = findd(key);
			if (t == nai)
			{
				throw index_out_of_bound();

			}
			else
			{
				return t->data->second;
			}

		}
		const T& at(const Key& key) const {
			node* t = findd(key);
			if (t == nai)
			{
				throw index_out_of_bound();

			}
			else
			{
				return t->data->second;
			}


		}
		/**
		 * TODO
		 * access specified element
		 * Returns a reference to the value that is mapped to a key equivalent to key,
		 *   performing an insertion if such key does not already exist.
		 */




		T& operator[](const Key& key) {
			
			if (notfind(key))
			{
				node* t = insertt(value_type(key, T()), rt);
				siz++;
				return t->data->second;

			}
			else
			{
				node* t = findd(key);
				return t->data->second;

			}

		}
		/**
		 * behave like at() throw index_out_of_bound if such key does not exist.
		 */
		const T& operator[](const Key& key) const {
			node* t = findd(key);
			if (t == nai)
			{
				
				
				throw index_out_of_bound();

			}
			
			
			return t->data->second;
			



		}




		/**
		 * return a iterator to the beginning
		 */
		iterator begin() {
			
			if (rt == nullptr) return iterator(this, nai);

			node* t = rt;
			while (t->l != nullptr) t = t->l;
			return iterator(this, t);


		}
		const_iterator cbegin() const {

			if (rt == nullptr) return const_iterator(this, nai);

			node* t = rt;
			while (t->l != nullptr) t = t->l;
			return const_iterator(this, t);

		}
		/**
		 * return a iterator to the end
		 * in fact, it returns past-the-end.
		 */
		iterator end() { return iterator(this, nai); }
		const_iterator cend() const { return const_iterator(this, nai); }
		/**
		 * checks whether the container is empty
		 * return true if empty, otherwise false.
		 */
		bool empty() const {
			if (siz) return false;
			else return true;


		}
		/**
		 * returns the number of elements.
		 */
		size_t size() const {
			return siz;

		}
		/**
		 * clears the contents
		 */
		void clear() {
			siz = 0;
			makeempty(rt);
			

		}
		/**
		 * insert an element.
		 * return a pair, the first of the pair is
		 *   the iterator to the new element (or the element that prevented the insertion),
		 *   the second one is true if insert successfully, or false.
		 */
		pair<iterator, bool> insert(const value_type& value) {
			node* pos = findd(value.first);
			if (pos != nai)
			{
				return pair<iterator, bool>(iterator(this, pos), false);
			}
			else
			{
				pos = insertt(value, rt);

				siz++;

				return pair<iterator, bool>(iterator(this, pos), true);
				
			}




		}
		/**
		 * erase the element at pos.
		 *
		 * throw if pos pointed to a bad element (pos == this->end() || pos points an element out of this)
		 */
		void erase(iterator pos) {
			if (pos.belong != this || pos.p == nai)
				throw invalid_iterator();
			siz--;

			erasee(pos.p->data->first, rt);


		}
		/**
		 * Returns the number of elements with key
		 *   that compares equivalent to the specified argument,
		 *   which is either 1 or 0
		 *     since this container does not allow duplicates.
		 * The default method of check the equivalence is !(a < b || b > a)
		 */


		size_t count(const Key& key) const
		{
			if (findd(key) == nai) return 0;
			else return 1;

		}


		/**
		 * Finds an element with key equivalent to key.
		 * key value of the element to search for.
		 * Iterator to an element with key equivalent to key.
		 *   If no such element is found, past-the-end (see end()) iterator is returned.
		 */
		iterator find(const Key& key) {

			
			
			return iterator(this, findd(key));

		}
		const_iterator find(const Key& key) const {

			
			return const_iterator(this, findd(key));


		}
	};

}

#endif
