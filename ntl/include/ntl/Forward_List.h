#include <initializer_list>
#include <assert.h>

namespace ntl
{
	template<typename T>
	struct Forward_List_Node
	{
		Forward_List_Node() = default;
		Forward_List_Node(T value) noexcept
		{
			data = value ;
			next = nullptr;
		}

		T data = T{};
		Forward_List_Node<T>* next = nullptr;
	};

	template<typename T>
	class Forward_List
	{
	public:
		Forward_List() = default;

		Forward_List(const Forward_List<T>& other);
		Forward_List<T>& operator=(const Forward_List<T>& other);
		
		Forward_List(Forward_List<T>&& other);
		Forward_List<T>& operator=(Forward_List<T>&& other);

		Forward_List(const std::initializer_list<T>& list);

		~Forward_List();

		void assign(const std::initializer_list<T>& list);
		void assign(size_t count, T value);

		void push_front(T value);

		void pop_front();

		T& front();

		bool empty();
		size_t size();

		void insert(size_t index, T value);

		void erase(size_t index);

		void clear();

	private:
		Forward_List_Node<T>* _head = nullptr;
		size_t _size = 0;
	};

	// Construction
	template<typename T>
	Forward_List<T>::Forward_List(const Forward_List<T>& other)
	{
		auto it1 = other._head;
		auto it2 = this->_head;
		for (size_t i = 0; i < other._size; ++i)
		{
			auto node = new Forward_List_Node<T>{ it1->data };
			if (i == 0)
			{
				this->_head = node;
				it2 = node;
			}
			it2->next = node;
			it2 = node;
			it1 = it1->next;

			++this->_size;
		}
	}

	template<typename T>
	Forward_List<T>& Forward_List<T>::operator=(const Forward_List<T>& other)
	{
		auto it1 = other._head;
		auto it2 = this->_head;
		for (size_t i = 0; i < other._size; ++i)
		{
			auto node = new Forward_List_Node<T>{ it1->data };
			if (i == 0)
			{
				this->_head = node;
				it2 = node;
			}
			it2->next = node;
			it2 = node;
			it1 = it1->next;

			++this->_size;
		}
		return *this;
	}

	template<typename T>
	Forward_List<T>::Forward_List(Forward_List<T>&& other)
	{
		this->_head = other._head;
		this->_size = other._size;

		other._head = nullptr;
		other._size = 0;
	}

	template<typename T>
	Forward_List<T>& Forward_List<T>::operator=(Forward_List<T>&& other)
	{
		this->_head = other._head;
		this->_size = other._size;

		other._head = nullptr;
		other._size = 0;

		return *this;
	}

	template<typename T>
	Forward_List<T>::Forward_List(const std::initializer_list<T>& list)
	{
		auto it = list.end();
		--it;
		for (size_t i = 0; i < list.size(); ++i, --it)
			this->push_front(*it);
	}
 
	// Destruction
	template<typename T>
	Forward_List<T>::~Forward_List()
	{
		this->clear();
	}


	// API
	template<typename T>
	void Forward_List<T>::assign(size_t count, T value)
	{
		for (size_t i = 0; i < count; ++i)
			this->push_front(value);
	}

	template<typename T>
	void Forward_List<T>::assign(const std::initializer_list<T>& list)
	{
		auto it = list.end();
		--it;
		for (size_t i = 0; i < list.size(); ++i, --it)
			this->push_front(*it);
	}

	template<typename T>
	void Forward_List<T>::push_front(T value)
	{
		auto node = new Forward_List_Node<T>(value);
		node->next = _head;
		_head = node;
		++_size;
	}

	template<typename T>
	void Forward_List<T>::pop_front()
	{
		assert(!this->empty() && "List is empty");

		auto deleted_node = _head;
		_head = deleted_node->next;

		delete deleted_node;
		--_size;
	}

	template<typename T>
	T& Forward_List<T>::front()
	{
		assert(!this->empty() && "List is empty");

		return _head->data;
	}

	template<typename T>
	bool Forward_List<T>::empty()
	{
		return _size == 0;
	}

	template<typename T>
	size_t Forward_List<T>::size()
	{
		return _size;
	}

	template<typename T>
	void Forward_List<T>::insert(size_t index, T value)
	{
		if (index == 0)
		{
			this->push_front(value);
			return;
		}

		auto it = _head;
		while (--index)
			it = it->next;

		auto node = new Forward_List_Node<T>{ value };
		node->next = it->next;
		it->next = node;
		++_size;
	}

	template<typename T>
	void Forward_List<T>::erase(size_t index)
	{
		if (_size == 0)
			return;

		if (index == 0)
		{
			this->pop_front();
			return;
		}

		auto it = _head;
		while (--index)
			it = it->next;

		auto deleted_node = it->next;
		it->next = deleted_node->next;
		delete deleted_node;

		--_size;
	}

	template<typename T>
	void Forward_List<T>::clear()
	{
		if (this->empty())
			return;

		auto it = _head;
		while (_head != nullptr)
		{
			it = _head;
			_head = it->next;
			delete it;
			--_size;
		}
	}
}