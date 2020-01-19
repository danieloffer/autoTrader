/**
 * avl_tree.hpp
 * this module's purpose is to provide an avl tree data structure
 **/

#ifndef AVL_TREE
#define AVL_TREE

#include <logger.hpp>
#include <vector>

using namespace std;


namespace autoTrader
{
#define MAXIMUM(a,b) (((a) >= (b)) ? (a) : (b))
#define GET_HEIGHT(node, direction) ((node)->children[(direction)]) ? (node)->children[(direction)]->height : 0
#define BALANCE_FACTOR(root) ((long)(GET_HEIGHT((root), LEFT)) - (long)(GET_HEIGHT((root), RIGHT)))

enum E_CHILDREN
{
    LEFT = 0,
    RIGHT = 1,
    MAX_CHILDREN = 2
};
#define GET_SIDE(cmp_func, a, b, param) (cmp_func((a), (b), (param)) >= 0) ? LEFT : RIGHT

enum E_ROTATION_CASE
{
    LEFT_LEFT,
    LEFT_RIGHT,
    RIGHT_LEFT,
    RIGHT_RIGHT,
    BALANCED
};

template <typename T> 
class AvlTree
{
public:
    typedef int (*compFunc)(T *a, T *b, void *param); //function to sort the tree by. return < 0 if a < b, > 0 if a > b, 0 if a = b
    typedef int (*findFunc)(T *a, T *b, void *param); // function to find element by
    typedef int (*actionFunc)(T *data, void *param); // function to perform on each element
   
    explicit AvlTree(compFunc func, void *param);
    ~AvlTree();
    int insert(T *data);
    void remove(T *data);
    T *getElement(void *data, findFunc func, void *param);
    vector<T *> getMultiElement(void *data, findFunc func, void *param);
    size_t size();
    int isEmpty();
    int forEach(actionFunc func, void *param);
    
private:
    struct AvlTreeNode
    {
        AvlTreeNode(T *data): data(new T(*data)), height(1){children[LEFT] = NULL; children[RIGHT] = NULL;} // T must have a Cctor
        ~AvlTreeNode(){delete data;}
        T *data;
        size_t height;
        AvlTreeNode *children[2];
    };

    static void destroySubTree(AvlTreeNode *node);
    static size_t getSubTreeSize(AvlTreeNode *node);
    AvlTreeNode *insertRec(AvlTreeNode *currentNode, AvlTreeNode *newNode);
    static void updateHeight(AvlTreeNode *node);
    static E_ROTATION_CASE getRotationCase(AvlTreeNode *node);
    AvlTreeNode *rotateSide(AvlTreeNode *node, E_CHILDREN side);
    AvlTreeNode *balance(AvlTreeNode *root);
    static int recForEach(actionFunc func, void *param, AvlTreeNode *node);    
    AvlTreeNode *root;
    compFunc sortedByFunc;
    void *param;
    SingleLogger *log;
};

template <typename T>
void AvlTree<T>::updateHeight(AvlTreeNode *node)
{
	node->height = (MAXIMUM(GET_HEIGHT(node, LEFT), 
								GET_HEIGHT(node, RIGHT)) + 1);
}

template <typename T>
E_ROTATION_CASE AvlTree<T>::getRotationCase(AvlTreeNode *node)
{	
	if ((BALANCE_FACTOR(node) > 1) && (BALANCE_FACTOR(node->children[LEFT]) > 0))
	{
		return LEFT_LEFT;
	}
	
	if ((BALANCE_FACTOR(node) > 1) && (BALANCE_FACTOR(node->children[LEFT]) < 0))
	{
		return LEFT_RIGHT;	
	}
	
	if ((BALANCE_FACTOR(node) < -1) && (BALANCE_FACTOR(node->children[RIGHT]) > 0))
	{
		return RIGHT_LEFT;
	}
	
	if ((BALANCE_FACTOR(node) < -1) && (BALANCE_FACTOR(node->children[RIGHT]) < 0))
	{
		return RIGHT_RIGHT;
	}
	
	return BALANCED;
}

template <typename T>
typename AvlTree<T>::AvlTreeNode *AvlTree<T>::rotateSide(AvlTreeNode *node, E_CHILDREN side)
{
	typename AvlTree<T>::AvlTreeNode *pivot = node->children[!side];
	
	root->children[!side] = pivot->children[side];
	pivot->children[side] = node;
	
	updateHeight(node);
	updateHeight(pivot);
	
	return pivot;	
}

template <typename T>
typename AvlTree<T>::AvlTreeNode *AvlTree<T>::balance(AvlTreeNode *node)
{
	switch (getRotationCase(node))
	{
		case LEFT_LEFT:
			node = this->rotateSide(node, RIGHT);
			break;
		case LEFT_RIGHT:
			node->children[LEFT] = this->rotateSide(node->children[LEFT], LEFT);
			node = this->rotateSide(node, RIGHT);
			break;
		case RIGHT_LEFT:
			node->children[RIGHT] = this->rotateSide(node->children[RIGHT], RIGHT);
			node = this->rotateSide(node, LEFT);
			break;
		case RIGHT_RIGHT:
			node = this->rotateSide(node, LEFT);
			break;
		default:
			break;
	}
	
	return node;
}

template <typename T> 
AvlTree<T>::AvlTree(compFunc func, void *param): root(NULL), sortedByFunc(func), param(param), log(Logger::getInstance())
{
    log->LOG("AvlTree ctor");
}
template <typename T>
void AvlTree<T>::destroySubTree(AvlTreeNode *node)
{
    if (node)
    {
        destroySubTree(node->children[LEFT]);
        destroySubTree(node->children[RIGHT]);

        delete node->data;
    }
}

template <typename T> 
AvlTree<T>::~AvlTree()
{
    log->LOG("AvlTree dtor");
    
    destroySubTree(root->children[LEFT]);
    destroySubTree(root->children[RIGHT]);

    delete root;
}

template <typename T>
typename AvlTree<T>::AvlTreeNode *AvlTree<T>::insertRec(AvlTreeNode *currentNode, AvlTreeNode *newNode)
{
    E_CHILDREN side = LEFT;

    if (!currentNode)
    {
        return newNode;
    }

    side = GET_SIDE(sortedByFunc, currentNode->data, newNode->data, param);
    currentNode->children[side] = insertRec(currentNode->children[side], newNode);
    updateHeight(currentNode);

    return balance(currentNode);
}

template <typename T> 
int AvlTree<T>::insert(T *data)
{
    AvlTreeNode *newNode = new AvlTreeNode(data);
    if (!newNode)
    {
        return 1;
    }

    root = insertRec(root, newNode);

    return 0;
}

template <typename T> 
void AvlTree<T>::remove(T *data)
{

}

template <typename T>
T *AvlTree<T>::getElement(void *data, findFunc func, void *param)
{
    return new T();
}

template <typename T>
vector<T *> AvlTree<T>::getMultiElement(void *data, findFunc func, void *param)
{
    return new vector<T *>();
}

template <typename T>
size_t AvlTree<T>::getSubTreeSize(AvlTreeNode *node)
{
    if (!node)
    {
        return 0;
    }

    return (1 + (getSubTreeSize(node->children[LEFT]) + getSubTreeSize(node->children[RIGHT])));
}

template <typename T>
size_t AvlTree<T>::size()
{
    return getSubTreeSize(root);
}

template <typename T>
int AvlTree<T>::isEmpty()
{
    return !root;
}

template <typename T>
int AvlTree<T>::recForEach(actionFunc func, void *param, AvlTreeNode *node)
{
    int res = 0;
    
    if (!node)
    {
        return res;
    }

    res = recForEach(func, param, node->children[LEFT]);

    if (res)
    {
        return res;
    }

    res = func(node->data, param);

    if (res)
    {
        return res;
    }

    res = recForEach(func, param, node->children[RIGHT]);

    return res;
}

template <typename T>
int AvlTree<T>::forEach(actionFunc func, void *param)
{
    int res = 0;

    if (!is_empty<T>())
    {
        res = recForEach(func, param, root);
    }
    return res;
}

}//namespace autoTrader

#endif //AVL_TREE