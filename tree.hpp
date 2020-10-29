
#ifndef TREE_HPP
#define TREE_HPP

template<typename T>
struct Node {
    T value;
    Node* left = nullptr;
    Node* right = nullptr;


    ~Node() {
        delete left;
        delete right;
    }
};

template<typename T>
class Tree {

    public :

        const Node<T>* root() const { return _root; }

        ~Tree() { delete _root; }

    private :

        Node<T>* _root = nullptr;
};


#endif // TREE_HPP
