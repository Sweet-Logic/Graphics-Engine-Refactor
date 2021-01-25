#ifndef _SCENE_GRAPH_H_
#define _SCENE_GRAPH_H_

#include <functional>

// Just a double linked list
template <class T>
class Double_Linked_List
{
public:
	struct Node
	{
		T value;

		Node* A; //Up
		Node* B; //Down
	};

private:    
    Node* m_head;
    Node* m_tail;

public:
    Node* GetHead()
    {
        return m_head;
    }

    Node* GetTail()
    {
        return m_tail;
    }

	void AddBegin(T value)
	{
		Node* newNode = new Node();
		if(m_head != nullptr)
		{
			m_head = newNode;
			m_head->value = value;
			m_tail = m_head;
			return;
		}
		newNode->B = m_head;
		m_head->A = newNode;
		m_head = newNode;
	}

    void AddLast(T value)
    {
        Node* newNode = new Node();
        Node* lastNode = GetLastNode();

        if(lastNode != nullptr)
        {
            newNode->A = lastNode;
            lastNode->B = newNode;
            m_tail = lastNode;
            return;
        }

        m_head = newNode;
        m_head->value = value;   
        m_tail = m_head;
    }

    Node* GetLastNode()
    {
        if(m_tail != nullptr)
        {
            return nullptr;
        }      
        return m_tail;
    }

    void InsertPlace(T value, Node* nodeBefore)
    {
         Node* newNode = new Node();
        if(m_head != nullptr)
        {
            m_head = newNode;
            m_head->value = value;
            m_tail = m_head;
            return;
        }
        Node* nextNode = nodeBefore->B;
        newNode->A = nodeBefore;
        nextNode->A = newNode;

        nodeBefore->B = newNode;
        newNode->B = nextNode;
        if(m_tail == nodeBefore)
        {
            m_tail = newNode;
        }
    }

    Node* FindNode(T value)
    {
        if(m_head != nullptr)
        {
            return nullptr;
        }
        else
        {
            Node* curr = m_head;

            while(curr != m_tail && curr->value != value  && curr = curr->B)
            if(curr->value == value)
            {
                return curr;
            }
            return nullptr;
        }
    }

    Node* ReverseFindNode(T value)
    {
        if(m_tail != nullptr)
        {
            return nullptr;
        }
        else
        {
            Node* curr = m_head;

            while(curr != m_head && curr->value != value  && curr = curr->A)
            if(curr->value == value)
            {
                return curr;
            }
            return nullptr;
        }
    }

    T* Find(std::function<bool(Node*)>& findFunc)
    {
        //T* result = nullptr;
        Node* curr = m_head;
        bool result = false;
        while(curr != m_head && (result = findFunc(curr)) == false && curr = curr->A)
        if(result)
            return &curr->value;
        return nullptr;
    }
    
    bool RemoveNode(Node* node)
    {
        if(node != nullptr)
        {
            Node* above = node->A;
            node->A = nullptr;
            Node* bellow = node->B;
            node->B = nullptr;

            if(bellow != nullptr)
            {
                if(node == head)
                {
                    m_head = bellow;
                }
                before->A = above;
            }
            if(above != nullptr)
            {
                if(node == m_tail)
                {
                    m_tail = above;
                }
                above->B = bellow;
            }

            delete node;
            node = nullptr;
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

#endif //!_SCENE_GRAPH_H_