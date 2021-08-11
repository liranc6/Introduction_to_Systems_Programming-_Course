#ifndef GENERIC_LIST_H
#define GENERIC_LIST_H


#include <iostream>


namespace mtm
{

    template<class T>
    struct GenericNode
    {
        T element;
        GenericNode<T>* next;

        /**
        * constructor: creates a new unconnected node with a templated element
        */
        GenericNode(const T in_element) :element(in_element), next(NULL) {}
    };

    template<class T>
    class GenericList
    {
        GenericNode<T>* head_of_list;

        /**
        * allocateAndCopyGenericLinkedList: recieves a starting node and copies the node and all the nodes
        *                           after it to a new list
        *
        * @param first_node - a pointer to a  generic node that symbolises the beginning of a list
        * @return -  a generic node pointer to the beginning of the copied list
        */
        static GenericNode<T>* allocateAndCopyGenericLinkedList(const GenericNode<T>* first_node);


        /**
        * destroyGenericLinkedList: recieves a starting node and destroys the node and all the nodes after it
        *
        * @param first_node - a pointer to a  generic node that symbolises the beginning of a list
        */
        static void destroyGenericLinkedList(GenericNode<T>* first_node);

    public:
        /**
        * constructor: creates an empty list by setting the pointer to the head of the list to null
        */
        GenericList();

        /**
        * destructor: destroys all the nodes in the list
        */
        ~GenericList();

        /**
        * copy constructor: calls the function allocateAndCopyGenericLinkedList on the recieved list and sets the
        *                   head of the copied list to be the current head_of_list
        */
        GenericList(const GenericList& student_list);

        /**
        * copy assignment: destroys the current list with the function destroyGenericLinkedList and sets
        *               the head of the list to a copy of the recieved list.
        */
        GenericList& operator=(const GenericList& generic_list);


        /**
        * addElementToGenericListSortedByRising: inserts the element into the list in a sorted fashion using the
        *                       regular '<' operator to compare with the elements already in the list.
        *
        * @param element - a templated variable that will be inserted as the element in a node in the list.
        */
        void addElementToGenericListSortedByRising(const T element);

        /**
        * addElementToEndOfList: inserts the element to the end of the list
        *
        * @param element - a templated variable that will be inserted as the element in a node in the list.
        */
        void addElementToEndOfList(const T element);

        /**
        * removeNodeWithElement: searches the list for an element equal to the recieved variable and deletes that
        *                       node from the linked list, the comparison is done with the '==' operator.
        *
        * @param element - a const templated variable equal to the element of the node to be removed.
        * @return true - if the node was found and removed.
        *         false - if no node with this element is found in the list.
        */
        bool removeNodeWithElement(const T element);

        /**
        * printEntireList: goes over the list and prints to the recieved out stream the element in each node,
        *                   the printing is done with the '<<' operator
        *
        * @param os - the stream to which the list will be printed
        */
        void printEntireList(std::ostream& os) const;

        /**
        * checkIfElementIsInList:goes over the list and compares the element of each node with the recieved templated
        *                       variable using the '==' operator,if such a node is found the function exits.
        *
        * @param element - a templated variable that will be compared with the elements of the list
        * @return  true - if a node with an element equal to the recieved element is found
        *          false - if no such node is found
        */
        bool checkIfElementIsInList(const T element) const;

        /**
        * getFirstNode: returns the first node
        *
        * @return  a pointer to the first node in the list
        *
        */
        GenericNode<T>* getFirstNode();

        /**
        * getFirstNode: returns the first node
        *
        * @return  a const pointer to the first node in the list
        *
        */
        const GenericNode<T>* getFirstNode() const;
    };

    template<class T>
    GenericList<T>::GenericList()
    {
        head_of_list = NULL;
    }


    template<class T>
    GenericList<T>::~GenericList()
    {
        destroyGenericLinkedList(head_of_list);
    }


    template<class T>
    GenericList<T>::GenericList(const GenericList<T>& student_list)
    {
        head_of_list = allocateAndCopyGenericLinkedList(student_list.head_of_list);
    }


    template<class T>
    GenericList<T>& GenericList<T>::operator=(const GenericList<T>& generic_list)
    {
        if (this == &generic_list)
        {
            return *this;
        }

        GenericNode<T>* temp = allocateAndCopyGenericLinkedList(generic_list.head_of_list);
        destroyGenericLinkedList(head_of_list);
        head_of_list = temp;
        return *this;
    }




    template<class T>
    void GenericList<T>::addElementToGenericListSortedByRising(const T element)
    {
        GenericNode<T>* new_node = new GenericNode<T>(element);

        if (head_of_list == NULL)
        {
            head_of_list = new_node;
            return;
        }

        GenericNode<T>* current_node = head_of_list;
        GenericNode<T>* previous_node = NULL;

        while (current_node != NULL)
        {
            if (element < current_node->element)
            {
                break;
            }
            else
            {
                previous_node = current_node;
                current_node = current_node->next;
            }
        }

        if (previous_node == NULL)
        {
            new_node->next = head_of_list;
            head_of_list = new_node;
        }
        else
        {
            new_node->next = previous_node->next;
            previous_node->next = new_node;
        }
    }

    template<class T>
    void GenericList<T>::addElementToEndOfList(const T element)
    {
        GenericNode<T>* new_node = new GenericNode<T>(element);
        if (head_of_list == NULL)
        {
            head_of_list = new_node;
            return;
        }

        GenericNode<T>* current_node = head_of_list;
        while (current_node->next != NULL)
        {
            current_node = current_node->next;
        }
        current_node->next = new_node;
    }

    template<class T>
    bool GenericList<T>::removeNodeWithElement(const T element)
    {
        GenericNode<T>* current_node = head_of_list;
        GenericNode<T>* previous_node = NULL;

        while (current_node != NULL)
        {
            if (current_node->element == element)
            {
                if (previous_node == NULL)
                {
                    head_of_list = current_node->next;
                }
                else
                {
                    previous_node->next = current_node->next;
                }
                delete current_node;
                return true;
            }

            previous_node = current_node;
            current_node = current_node->next;
        }

        return false;
    }


    template<class T>
    void GenericList<T>::printEntireList(std::ostream& os) const
    {
        GenericNode<T>* current_node = head_of_list;

        while (current_node != NULL)
        {
            os << current_node->element << std::endl;
            current_node = current_node->next;
        }
    }


    template<class T>
    bool GenericList<T>::checkIfElementIsInList(const T element) const
    {
        GenericNode<T>* current_node = head_of_list;
        while (current_node != NULL)
        {
            if (current_node->element == element)
            {
                return true;
            }
            current_node = current_node->next;
        }
        return false;
    }

    template<class T>
    GenericNode<T>* GenericList<T>::getFirstNode()
    {
        return head_of_list;
    }

    template<class T>
    const GenericNode<T>* GenericList<T>::getFirstNode() const
    {
        return head_of_list;
    }


    //the static helper functions


    template<class T>
    GenericNode<T>* GenericList<T>::allocateAndCopyGenericLinkedList(const GenericNode<T>* first_node)
    {
        if (first_node == NULL)
        {
            return NULL;
        }
        GenericNode<T>* head_of_copy_list = new GenericNode<T>(first_node->element);

        GenericNode<T>* current_node = first_node->next;
        GenericNode<T>* new_copy_node = head_of_copy_list;
        while (current_node != NULL)
        {
            new_copy_node->next = new GenericNode<T>(current_node->element);
            new_copy_node = new_copy_node->next;
            current_node = current_node->next;
        }

        return head_of_copy_list;
    }


    template<class T>
    void GenericList<T>::destroyGenericLinkedList(GenericNode<T>* first_node)
    {
        GenericNode<T>* current_node;
        while (first_node != NULL)
        {
            current_node = first_node;
            first_node = first_node->next;
            delete current_node;
        }
    }

}

#endif //GENERIC_LIST_H