/**
 * avl_tree.hpp
 * this module's purpose is to provide a templated avl tree data structure
 **/

#ifndef AVL_TREE
#define AVL_TREE

#include <logger.hpp>
#include <vector>

using namespace std;


namespace autoTrader
{
#define MAXIMUM(a,b) (((a) >= (b)) ? (a) : (b))

//Get the height of the child specified,0 if there is no child in that direction
#define GET_HEIGHT(node, direction) ((node)->children[(direction)]) ? (node)->children[(direction)]->height : 0

//Get the balance factor of a tree node. The balance factor is the difference between the height of the left child
//and the right child of the node
#define BALANCE_FACTOR(root) (static_cast<long>(GET_HEIGHT((root), LEFT)) - static_cast<long>(GET_HEIGHT((root), RIGHT)))

//Get the child that is the result of the tree's compare function
#define GET_SIDE(cmp_func, a, b, param) (cmp_func((a), (b), (param)) >= 0) ? LEFT : RIGHT

enum E_CHILDREN
{
    LEFT = 0,
    RIGHT = 1,
    MAX_CHILDREN = 2
};

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
   
    /*
    *An AvlTree Ctor.
    *param func - a compare function to sort the tree by.
    *param param - a parameter that can be passed to the comp/find/action funcs
    */
    explicit AvlTree(compFunc func, void *param);

    /*
    *An Avltree Dtor
    *Destroys the data in the tree
    */
    ~AvlTree();

    /*
    *Insert data of type T to the tree
    * param data - a pointer to the data we wish to the tree to save
    * The tree holds copies of the data sent to it.
    * Returns 0 if successful, 1 otherwise 
    */
    int insert(T *data);

    /*
    *Removes a node from the tree
    *param datawToRemove - removes the data that the parameter is pointing to.
    *destroys the data the node was pointing to
    */
    void remove(T *dataToRemove);

    /*
    *Find a node in the tree based on the findFunc. If more that one node matches the data, the first
    *occurrence will be returned
    *param dataToFind - the data we want to find in the tree
    *Returns a pointer to the data if exists, NULL otherwise
    */
    T *find(T *datatoFind);

    /*
    *Find multiple node based on the findFunc.
    *param dataToFind - the data we want to find in the tree
    *Returns a vector of pointers to the data found in the tree, an empty vector if none match the param
    */
    vector<T *> multiFind(T *datatoFind);

    /*
    *Returns the size of the tree
    *O(n)
    */
    size_t size();

    /*
    *Returns 1 if the tree is empty, 0 otherwise
    * O(1)
    */
    int isEmpty();

    /*
    *Perform an action on each node of the tree
    *param func - The actionFunc to perform on the node
    param param - a parameter to pass to the actionFunc
    *Returns 0 for success, any other int for failure of one of the function calls
    *If the function fails for a node, the forEach function stops iterating at that node and returns the result
    */
    int forEach(actionFunc func, void *param);
    
private:

    // A struct of an individual node of the AvlTree
    struct AvlTreeNode
    {
        /*
        *AvlTreeNode Ctor. Duplicates the data passed to it
        *param data - a pointer to a data of type T for the node to hold
        */
        AvlTreeNode(T *data): data(new T(*data)), height(1){children[LEFT] = NULL; children[RIGHT] = NULL;} // T must have a Cctor

        /*
        *AvlTreeNode Dtor
        *deletes the data it points to. If T is a class that contains non POD members, it must have a Dtor
        */
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
    T *recFind(AvlTreeNode *currentNode, T *dataToFind);
    void recMultiFind(AvlTreeNode *currentNode, T *dataToFind, vector<T *> *vec);
    AvlTreeNode *findAndRemove(AvlTreeNode *currentNode, T *dataToRemove); 
    AvlTreeNode *removeNode(AvlTreeNode *currentNode); 
    AvlTreeNode *getNext(AvlTreeNode *currentNode, AvlTreeNode **nextToReturn);

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
	
	node->children[!side] = pivot->children[side];
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

        delete node;
    }
}

template <typename T> 
AvlTree<T>::~AvlTree()
{
    log->LOG("AvlTree dtor");

    if (root)
    {
        destroySubTree(root->children[LEFT]);
        destroySubTree(root->children[RIGHT]);

        delete root;
    }
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
typename AvlTree<T>::AvlTreeNode *AvlTree<T>::getNext(AvlTreeNode *currentNode, AvlTreeNode **nextToReturn)
{
    if (!currentNode->children[LEFT])
	{
		*nextToReturn = currentNode;
		
		return currentNode->children[RIGHT];
	}
	
	currentNode->children[LEFT] = getNext(currentNode->children[LEFT], nextToReturn);
	
	updateHeight(currentNode);
	
	return balance(currentNode);
}

template <typename T> 
typename AvlTree<T>::AvlTreeNode *AvlTree<T>::removeNode(AvlTreeNode *nodeToRemove)
{
    AvlTreeNode *temp = NULL;
    if (!nodeToRemove->children[RIGHT])
    {
        temp = nodeToRemove->children[LEFT];
        delete nodeToRemove;
        
        return temp;
    }

    nodeToRemove->children[RIGHT] = getNext(nodeToRemove->children[RIGHT], &temp);
    temp->children[LEFT] = nodeToRemove->children[LEFT];
    temp->children[RIGHT] = nodeToRemove->children[RIGHT];
    delete nodeToRemove;

    updateHeight(temp);

    return balance(temp);
}

template <typename T> 
typename AvlTree<T>::AvlTreeNode *AvlTree<T>::findAndRemove(AvlTreeNode *currentNode, T *dataToRemove)
{
    int res = sortedByFunc(currentNode->data, dataToRemove, param);
    if (!res)
    {
        return removeNode(currentNode);
    }

    E_CHILDREN side = (res >= 0) ? LEFT : RIGHT;

    currentNode->children[side] = this->findAndRemove(currentNode->children[side], dataToRemove);

    updateHeight(currentNode);

    return balance(currentNode);
}

template <typename T> 
void AvlTree<T>::remove(T *dataToRemove)
{
    root = this->findAndRemove(root, dataToRemove);
}

template <typename T>
T *AvlTree<T>::recFind(AvlTreeNode *currentNode, T *dataToFind)
{
    if (!currentNode)
    {
        return NULL;
    }

    int res = sortedByFunc(currentNode->data, dataToFind, param);
    if (!res)
    {
        return currentNode->data;
    }

    E_CHILDREN side = (res >= 0) ? LEFT : RIGHT;

    return this->recFind(currentNode->children[side], dataToFind);
}

template <typename T>
T *AvlTree<T>::find(T *datatoFind)
{
    return this->recFind(root, datatoFind);
}

template <typename T>
void AvlTree<T>::recMultiFind(AvlTreeNode *currentNode, T *dataToFind, vector<T *> *vec)
{
    if (!currentNode)
    {
        return;
    }

    int res = sortedByFunc(currentNode->data, dataToFind, param);
    if (!res)
    {
        vec->push_back(currentNode->data);
    }

    E_CHILDREN side = (res >= 0) ? LEFT : RIGHT;

    this->recMultiFind(currentNode->children[side], dataToFind, vec);
}

template <typename T>
vector<T *> AvlTree<T>::multiFind(T *dataToFind)
{
    vector<T *> vec;

    this->recMultiFind(root, dataToFind, &vec);

    return vec;
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