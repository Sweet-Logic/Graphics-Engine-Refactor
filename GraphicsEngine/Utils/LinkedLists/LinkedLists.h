#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

template<class T>
class LinkedList
{
public:
    struct Node
	{
		T value;

		Node* A; //Next node
	};

    int m_count = 0;
	Node* m_head;
    Node* GetHead()
    {
        return m_head;
    }
    void Add(T value)
	{
        ++m_count;
		Node* newNode = new Node();
		newNode->value = value;
		if(m_head == nullptr)
		{
			m_head = newNode;
			return;
		}
		Node* node = m_head;
		while (node != nullptr && node->A != nullptr)
		{
			node = node->A;
		};
		node->A = newNode;
	}

	void AddBegin(T value)
	{
        ++m_count;
		Node* newNode = new Node();
		if(m_head == nullptr)
		{
			m_head = newNode;
			m_head->value = value;
			return;
		}
		m_head->A = newNode;
		m_head = newNode;
	}

    Node* FindNode(T value)
    {
        Node* curr = m_head;

		while (curr != nullptr && curr->value != value)
		{
			if (curr->value == value)
			{
				return curr;
			}
			curr = curr->A;
		}
        return nullptr;
    }

    T* Find(bool(func)(LinkedList<T>::Node*))
    {
        //T* result = nullptr;
        Node* curr = m_head;
        bool result = false;
        while(curr != m_head && (result = (func)(curr)) == false && curr = curr->A)
        if(result)
            return &curr->value;
        return nullptr;
    }
    
    bool RemoveNode(Node* node)
    {
        if(node != nullptr)
        {
            Node* a = node->A;
            if(node == m_head)
            {
                m_head = a;
            }
            node->A = nullptr;

            

            delete node;
            node = nullptr;
            --m_count;
            return true;
        }
        return false;
    }

    bool RemoveNode(T value)
    {
        Node* curr = m_head;

        while(curr != m_tail && curr->value != value  && curr = curr->B)
        if(curr->value == value)
        {
            return RemoveNode(curr);
        }
        return false;
    }

};

#endif //!_LINKED_LIST_H_