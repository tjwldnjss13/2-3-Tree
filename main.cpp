#include <iostream>
using namespace std;

template <typename T>
class _23Tree;


template <typename T>
class TreeNode {
    friend class _23Tree<T>;
private:
    T *data;
    TreeNode<T> *left;
    TreeNode<T> *mid;
    TreeNode<T> *right;
    int depth;
    int numData;
    const int maxNumData = 2;
public:
    TreeNode<T>(T data_ = 0) {
        data = new T[maxNumData];
        this->data[0] = data_;
        this->data[1] = NULL;
        this->left = NULL;
        this->mid = NULL;
        this->right = NULL;
        this->depth = 0;
        this->numData = 1;
    }
    void addNumData() {
        numData++;
    }
};

template <typename T>
class _23Tree {
private:
    TreeNode<T> *root;
public:
    _23Tree<T>(T data_ = 0) {
        root = new TreeNode<T>(data_);
    }
    void buildTree() {

    }

    /* Function to insert a new data.
       If duplicated, do nothing.     */
    void insertData(T data) {
        // It works only if not duplicated.
        if (searchNode(root, data) == NULL) {
            TreeNode<T> *parent = NULL;
            TreeNode<T> *current = root;

            // Find the right leaf place for new data
            while (current != NULL) {
                parent = current;

                // When parent has 1 data.
                if (parent->numData == 1) {
                    if (data < parent->data[0])
                        current = parent->left;
                    else
                        current = parent->right;
                }

                // When parent has 2 data.
                else if (parent->numData == 2) {
                    if (data < parent->data[0])
                        current = parent->left;
                    else if (parent->data[0] < data && data < parent->data[1])
                        current = parent->mid;
                    else if (parent->data[1] < data)
                        current = parent->right;
                }
            }

            // Put the new data in the right place.
            // If needed, move the old data to it's parent.

            // When leaf has 1 data.
            if (parent->numData == 1) {
                if (data < parent->data[0]) {
                    int tmp = parent->data[0];
                    parent->data[0] = data;
                    parent->data[1] = tmp;
                }
                else
                    parent->data[1] = data;
                parent->numData = 2;
            }

            // When leaf has 2 data.
            else if (parent->numData == 2) {
                // Part to split node.

                splitNode(parent, data);

                /*
                if (data < parent->data[0])
                    parent->left = node;
                else if (parent->data[0] < data && data < parent->data[1])
                    parent->mid = node;
                else if (parent->data[1] < data)
                    parent->right = node;
                node->depth = parent->depth + 1;
                */

            }
            cout << "Inserted " << data << endl;
        }
    }

    /* Function to split the node because it's full while inserting. */
    void splitNode(TreeNode<T> *node, T data, TreeNode<T> *child_1 = NULL, TreeNode<T> *child_2 = NULL, TreeNode<T> *child_3 = NULL, TreeNode<T> *child_4 = NULL) {
        if (node != NULL) {
            T minVal, midVal, maxVal;

            // Select the data to move upward(parent).
            if (data < node->data[0]) {
                minVal = data;
                midVal = node->data[0];
                maxVal = node->data[1];
            }
            else if (data < node->data[1]) {
                minVal = node->data[0];
                midVal = data;
                maxVal = node->data[1];
            }
            else {
                minVal = node->data[0];
                midVal = node->data[1];
                maxVal = data;
            }


            cout << "Current node's first data is " << node->data[0] << endl;

            cout << "Root's first data is " << root->data[0] << endl;
            cout << "Root has " << root->numData << " data" << endl;
            if (root->right != NULL)
                cout << "Root's right child's first data " << root->right->data[0] << endl;
            //if (getParent(node->data[0]) != NULL)
            //    cout << "Current's parent's first data is " << getParent(node->data[0])->data[0] << endl;




            // When selected leaf is root
            if (node == root) {
                cout << "Current node is root" << endl;
                TreeNode<T> *root_new = new TreeNode<T>(midVal);
                TreeNode<T> *right_new = new TreeNode<T>(maxVal);

                root_new->left = node;
                root_new->left->data[0] = minVal;
                root_new->left->data[1] = NULL;
                root_new->right = right_new;
                root = root_new;

                root->left->left = child_1;
                root->left->mid = NULL;
                root->left->right = child_2;

                root->right->left = child_3;
                root->right->mid = NULL;
                root->right->right = child_4;

                root->left->depth = root->depth + 1;
                root->right->depth = root->depth + 1;
            }

            // When selected leaf is not root
            else if (getParent(node->data[0]) != NULL) {
                cout << "Current node is a leaf, not root" << endl;
                TreeNode<T> *parent = getParent(node->data[0]);

                // When parent has 1 data.
                if (parent->numData == 1) {
                    cout << "Parent has 1 data." << endl;
                    // When the node is parent's left child.
                    if (node == parent->left) {
                        cout << "Current node is parent's left child." << endl;
                        TreeNode<T> *mid_new = new TreeNode<T>(maxVal);

                        T tmp = parent->data[0];
                        parent->data[0] = midVal;
                        parent->data[1] = tmp;
                        parent->numData = 2;

                        parent->mid = mid_new;
                        parent->left->data[0] = minVal;
                        parent->left->data[1] = NULL;
                        parent->left->numData = 1;

                        parent->left->left = child_1;
                        parent->left->right = child_2;
                        parent->mid->left = child_3;
                        parent->mid->right = child_4;

                        parent->mid->depth = parent->depth + 1;
                    }

                    // When the node is parent's right child.
                    else if (node == parent->right) {
                        cout << "Current node is parent's right child." << endl;
                        TreeNode<T> *right_new = new TreeNode<T>(maxVal);

                        parent->data[1] = midVal;
                        parent->numData = 2;

                        parent->right = right_new;
                        parent->mid = node;
                        parent->mid->data[0] = minVal;
                        parent->mid->data[1] = NULL;
                        parent->mid->numData = 1;

                        parent->mid->left = child_1;
                        parent->mid->right = child_2;
                        right_new->left = child_3;
                        right_new->right = child_4;

                        parent->right->depth = parent->depth + 1;
                    }
                }

                // When parent has 2 data.
                else if (parent->numData == 2) {
                    cout << "Parent has 2 data." << endl;

                    TreeNode<T> *left_old = parent->left;
                    TreeNode<T> *mid_old = parent->mid;
                    TreeNode<T> *right_old = parent->right;

                    // When the node is parent's left child.
                    if (node == parent->left) {
                        cout << "Current node is parent's left child." << endl;
                        TreeNode<T> *left_new_1 = node;
                        left_new_1->data[0] = minVal;
                        left_new_1->data[1] = NULL;
                        TreeNode<T> *left_new_2 = new TreeNode<T>(maxVal);
                        left_new_2->depth = left_new_1->depth;

                        cout << "Entering to another splitNode function." << endl;
                        splitNode(parent, midVal, left_new_1, left_new_2, parent->mid, parent->right);

                        left_new_1->depth++;
                        left_new_2->depth++;
                        parent->mid->depth++;
                        parent->right->depth++;
                    }

                    // When the node is parent's middle child.
                    else if (node == parent->mid) {
                        cout << "Current node is parent's middle child." << endl;
                        TreeNode<T> *mid_new_1 = node;
                        mid_new_1->data[0] = minVal;
                        mid_new_1->data[1] = NULL;
                        TreeNode<T> *mid_new_2 = new TreeNode<T>(maxVal);
                        mid_new_2->depth = mid_new_1->depth;

                        cout << "Entering to another splitNode function." << endl;
                        splitNode(parent, midVal, parent->left, mid_new_1, mid_new_2, parent->right);

                        parent->left->depth++;
                        mid_new_1->depth++;
                        mid_new_2->depth++;
                        parent->right->depth++;
                    }

                    // When the node is parent's right child.
                    else if (node == parent->right) {
                        cout << "Current node is parent's right child." << endl;
                        TreeNode<T> *right_new_1 = node;
                        right_new_1->data[0] = minVal;
                        right_new_1->data[1] = NULL;
                        TreeNode<T> *right_new_2 = new TreeNode<T>(maxVal);
                        right_new_2->depth = right_new_1->depth;


                        cout << "Entering to another splitNode function." << endl;
                        splitNode(parent, midVal, parent->left, parent->mid, right_new_1, right_new_2);

                        parent->left->depth++;
                        parent->right->depth++;
                        right_new_1->depth++;
                        right_new_2->depth++;
                    }
                }
            }
        }
    }

    /* Function to move the old data to it's parent. */
    /*
     void moveNodeToParent(TreeNode<T> *current, T data_) {
        TreeNode<T> *parent = findParent(current);
        int _1, _2, _3;
        if (data_ < current->data[0]) {
            _1 = data_;
            _2 = current->data[0];
            _3 = current->data[1];
        }
        else if (current->data[0] < data_ && data_ < current->data[1]) {
            _1 = current->dat[0];
            _2 = data_;tree.insertData(20);
            _3 = current->data[1];
        }
        else if (current->data[1] < data_) {
            _1 = current->data[0];
            _2 = current->data[1];
            _3 = data_;
        }
        // 올라온 값을 받을 부모의 값이 1개인 경우
        if (parent->numData == 1) {
            // 중간값을 부모로 올리고, 부모의 값들을 정렬
            if (parent->data[0] < _2) {
                parent->data[1] = _2;
                parent->numData++;
            }
            else {
                int tmp = parent->data[0];
                parent->data[0] = _2;
                parent->data[1] = tmp;
                parent->numData++;
            }
            // 현재 node의 남은 값들을 분리해서, 부모의 child로 재분배
            if (current == parent->right) {
                parent->right = new TreeNode<T>(_3);
                parent->mid = current;
                current->data[0] = _1;
                current->data[1] = NULL;
                parent->numData++;
                current->numData--;
            }
            else if (current == parent->left) {
                parent->mid = new TreeNode<T>(_3);
                parent->left = current;
                current->data[0] = _1;
                current->data[1] = NULL;
                parent->numData++;
                current->numData--;
            }
        }
        // 올라온 값을 받을 부모의 값이 가득 차있는 경우
        else if (parent->numData == 2) {
            TreeNode<T> *parent_splited = new TreeNode<T>();
            if (current == parent->left) {
                parent_splited->data[0] = parent->data[1];

                parent_splited->right = parent->right;
                parent_splited->left = parent->mid;
                parent->mid = NULL;

                parent->right = new TreeNode<T>(_3);
                current->data[0] = _1;
                current->data[1] = NULL;
                current->numData--;

                if (parent != root)
                    moveNodeToParent(parent, _2);
                else {
                    TreeNode<T> *root_new = new TreeNode<T>()

                }
            }
            else if (current == parent->mid) {

            }
            else if (current == parent->right) {

            }
        }
    }
    */

    /* Function to return the node that already has target data.
       If not exists, return NULL.                               */
    TreeNode<T> *searchNode(TreeNode<T> *current, T data) {
        if (current == NULL)
            return NULL;
        for (int i=0; i<current->numData; i++) {
            if (current->data[i] == data)
                return current;
        }
        if (current->numData == 1) {
            if (data < current->data[0])
                searchNode(current->left, data);
            else
                searchNode(current->right, data);
        }
        else if (current->numData == 2) {
            if (data < current->data[0])
                searchNode(current->left, data);
            else if (current->data[0] < data && data < current->data[1])
                searchNode(current->mid, data);
            else if (current->data[1] < data)
                searchNode(current->right, data);
        }
    }

    /* Function to return the node's parent.
       If not exists(node==root), return NULL. */
    TreeNode<T> *getParent(T data) {
        cout << "I'm trying to find " << data << "'s parent." << endl;
        if (searchNode(root, data) != NULL) {
            cout << "The current node exists." << endl;
            TreeNode<T> *parent = NULL;
            TreeNode<T> *current = root;
            parent = current;
            while (true) {
                if (parent->numData == 1) {
                    cout << "Wrong??" << endl;
                    if (data == parent->data[0])
                        break;
                    else {
                        cout << "Finding parent which has 1 data" << endl;
                        parent = current;
                        if (data < parent->data[0])
                            current = parent->left;
                        else
                            current = parent->right;
                    }
                }
                else if (parent->numData == 2) {
                    if (data == parent->data[0] || data == parent->data[1])
                        break;
                    else {
                        cout << "Finding parent which has 2 data." << endl;
                        parent = current;
                        if (data < parent->data[0])
                            current = parent->left;
                        else if (parent->data[0] < data && data < parent->data[1])
                            current = parent->mid;
                        else if (parent->data[1] < data)
                            current = parent->right;
                    }
                }
                /*
                if (parent->numData == 1) {
                    cout << "Finding parent which has 1 data" << endl;
                    if (data < parent->data[0])
                        current = parent->left;
                    else
                        current = parent->right;
                }
                else if (parent->numData == 2) {
                    //cout << "Finding parent which has 2 data." << endl;
                    if (data < parent->data[0])
                        current = parent->left;
                    else if (parent->data[0] < data && data < parent->data[1])
                        current = parent->mid;
                    else if (parent->data[1] < data)
                        current = parent->right;
                }
                */
            }
            cout << "Found it! Current node's parent's first data is " << parent->data[0] << endl;
            return parent;
        }
        else
            return NULL;
    }

    void deleteData(T data) {

    }

    void preorder(TreeNode<T> *current) {
        if (current != NULL) {
            visit(current);
            preorder(current->left);
            preorder(current->mid);
            preorder(current->right);
        }
    }
    void visit(TreeNode<T> *current) {
        for (int i=0; i<current->numData; i++)
            cout << current->data[i] << " ";
    }

    /* Function to help printing the tree. */
    void printTreeUtil(TreeNode<T> *current, int midFlag) {
        if (current->right != NULL) {
            printTreeUtil(current->right, 0);
            cout << endl;
        }

        if (midFlag) {
            cout << "-----";
        }
        else {
            for (int i=0; i<current->depth; i++) {
                cout << "----------";
            }
        }

        for (int i=0; i<2; i++) {
            if (current->data[i] != NULL) {
                cout << current->data[i];
                if (i == 0)
                    cout << ":";
            }
            else
                cout << "@@";
        }
        if (current->mid != NULL) {
            printTreeUtil(current->mid, 1);
        }
        if (current->left != NULL) {
            cout << endl;
            printTreeUtil(current->left, 0);
            cout << endl;
        }
        if (current == root && current->left == NULL && current->mid == NULL && current->right == NULL)
            cout << endl;
    }

    /* Function to print the entire tree. */
    void printTree() {
        printTreeUtil(root, 0);
    }
};

int main() {
    _23Tree<int> tree(10);

    for (int i=20; i<500; i+=10) {
        tree.insertData(i);
        tree.printTree();
        cout << "===========================================" << endl;
    }

    cout << "<<Print tree>>" << endl;
    tree.printTree();

    return 0;
}
