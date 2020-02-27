#include <iostream>

template <class T>
class LinkedList {
private:
    class Node {
    public:
        Node* next;
        Node* prev;
        T data;
        // For the sentinal
        Node(): data(T()), prev(this), next(this) {}
        Node(T data, Node* before)
                : data(data) {
            prev = before;
            next = before->next;
            prev->next = this;
            next->prev = this;
        }
        ~Node() {
            prev->next = next;
            next->prev = prev;
            next = nullptr;
            prev = nullptr;
        }
        void setBefore(Node* before) {
            prev = before;
            before->next = this;
        }
        void setAfter(Node* after) {
            next = after;
            after->prev = this;
        }
        Node(Node const&)            = delete;
        Node& operator=(Node const&) = delete;
    };

    class NodeIterator : public std::iterator<std::bidirectional_iterator_tag, Node> {
        Node* node;
    public:
        int pointer;
        NodeIterator(Node* node): node(node), pointer(-1) {}
        NodeIterator(const NodeIterator& iter): node(iter.node) {}
        NodeIterator& operator++() {
            node = node->next;
            pointer++;
            return *this;
        }
        NodeIterator operator++(int) {NodeIterator tmp(*this); operator++(); return tmp;}
        NodeIterator& operator--() {
            node = node->prev;
            pointer--;
            return *this;
        }
        NodeIterator operator--(int) {NodeIterator tmp(*this); operator--(); return tmp;}
        bool operator==(const NodeIterator& rhs) {return node == rhs.node;}
        bool operator!=(const NodeIterator& rhs) {return node != rhs.node;}
        Node& operator*() {return *node;}
    };

    NodeIterator iter;
    Node* sentinal;
    void moveIter(int index, bool getEnd=false) {
        if (index < 0) {
            index += length;
        }
        if (index < 0 or length < index or (not getEnd and length == index)) {
            throw std::out_of_range("List doesn't contain that item.");
        }
        for (;iter.pointer > index; iter--) {}
        for (;iter.pointer < index; iter++) {}
    }
public:
    int length;
    LinkedList(): length(0), iter(sentinal) {
        sentinal->prev = sentinal;
        sentinal->next = sentinal;
    }
    ~LinkedList() {
        clear();
    }
    LinkedList(LinkedList const&)            = delete;
    LinkedList& operator=(LinkedList const&) = delete;

    T get(int index) {
        moveIter(index);
        return (&*iter)->data;
    }

    void set(int index, T data) {
        moveIter(index);
        (&*iter)->data = data;
    }

    void del(int index) {
        moveIter(index);
        iter--;
        delete (&*iter)->next;
    }

    void append(T data) {
        insert(data, length);
    }

    void extend(LinkedList list) {
        if (list.length > 0) {
            Node* listSentinal = list.sentinal;
            sentinal->prev->setAfter(listSentinal->next);
            listSentinal->prev->setAfter(sentinal);
        }
    }

    void insert(T data, int index) {
        moveIter(index, true);
        iter--;
        new Node(data, &*iter);
        length++;
    }

    void remove(T data) {
        moveIter(index(data));
        iter--;
        delete (&*iter)->next;
    }

    T pop(int index=-1) {
        moveIter(index);
        iter--;
        Node* node = (&*iter)->next;
        T data = node->data;
        delete node;
        length--;
        return data;
    }

    int index(T data) {
        moveIter(0);
        for (;&*iter != sentinal; iter++) {
            if ((&*iter)->data == data) {
               return iter.pointer;
            }
        }
        return -1;
    }

    int count(T data) {
        int amount = 0;
        
    }

    void sort(T data) {

    }

    void reverse() {

    }

    void clear() {
        while (sentinal->next != sentinal) {
            delete sentinal->next;
        }
        length = 0;
    }
};

int main() {
    LinkedList<char> list;
    list.append('h');
    list.append('l');
    list.append('l');
    list.append('l');
    list.append('o');
    list.insert('e', 1);
    std::cout << list.pop(2) << list.get(-1) << '\n';
    for (int i=0; i < list.length; i++) {
        std::cout << list.get(i);
    }
    std::cout << '\n';
    list.clear();
}