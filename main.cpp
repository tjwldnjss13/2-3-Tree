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
        cout << "It's time to insert " << data << endl;
        // It works only if not duplicated.
        if (searchNode(root, data) == NULL) {
            cout << "It's not duplicated. Able to insert " << data << "!" << endl;
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
                cout << "(Inserting to the node that has 1 data)" << endl;
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
                cout << "(Inserting to the node that already has 2 data)" << endl;
                cout << "We should split the node." << endl;
                // Part to split node.
                splitNode(parent, data);
            }
            cout << "Inserted " << data << endl;
        }
    }

    /* Function to split the node because it's full while inserting. */
    TreeNode<T> *splitNode(TreeNode<T> *node, T data, TreeNode<T> *child_1 = NULL, TreeNode<T> *child_2 = NULL, TreeNode<T> *child_3 = NULL, TreeNode<T> *child_4 = NULL) {
        if (node != NULL) {
            TreeNode<T> *ret_right_new;
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

            cout << "[Current node's first data is " << node->data[0] << "]" << endl;

            cout << "[Root's first data is " << root->data[0] << "]" << endl;
            cout << "[Root has " << root->numData << " data]" << endl;
            if (root->right != NULL)
                cout << "[Root's right child's first data " << root->right->data[0] << "]" << endl;

            // When selected leaf is root
            if (node == root) {
                cout << "Current node is root" << endl;
                TreeNode<T> *root_new = new TreeNode<T>(midVal);
                TreeNode<T> *right_new = new TreeNode<T>(maxVal);

                root_new->left = node;
                root_new->left->data[0] = minVal;
                root_new->left->data[1] = NULL;
                root_new->left->numData = 1;
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

                ret_right_new = root->right;

                cout << "New root!!!" << endl;
                cout << "New root has " << root->numData << " datas." << endl;
                cout << "And new root's first data is " << root->data[0] << endl;
            }

            // When selected leaf is not root
            else if (getParent(node->data[0]) != NULL) {
                cout << "Current node is just a node, not root" << endl;
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
                        parent->left->mid = NULL;
                        parent->left->right = child_2;
                        parent->mid->left = child_3;
                        parent->mid->mid = NULL;
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
                        parent->mid->mid = NULL;
                        parent->mid->right = child_2;

                        parent->right->left = child_3;
                        parent->right->mid = NULL;
                        parent->right->right = child_4;
                        /*
                        right_new->left = child_3;
                        right_new->mid = NULL;
                        right_new->right = child_4;
                        */

                        parent->right->depth = parent->depth + 1;
                    }
                }

                // When parent has 2 data.
                else if (parent->numData == 2) {
                    cout << "Parent has 2 data." << endl;
                    TreeNode<T> *parent_new;

                    TreeNode<T> *right_old = parent->right;
                    TreeNode<T> *mid_old = parent->mid;
                    TreeNode<T> *left_old = parent->left;

                    // When the node is parent's left child.
                    if (node == parent->left) {
                        cout << "Current node is parent's left child." << endl;
                        TreeNode<T> *left_new_1 = left_old;
                        left_new_1->data[0] = minVal;
                        left_new_1->data[1] = NULL;
                        left_new_1->numData = 1;
                        TreeNode<T> *left_new_2 = new TreeNode<T>(maxVal);
                        left_new_2->depth = left_new_1->depth;

                        TreeNode<T> *mid_new = parent->mid;
                        TreeNode<T> *right_new = parent->right;

                        cout << "-----Entering to another splitNode function (LEFT)-----" << endl;
                        parent_new = splitNode(parent, midVal, left_new_1, left_new_2, mid_new, right_new);
                        cout << "-----Escaping the splitNode function (LEFT)-----" << endl;

                        cout << "########################    " << parent_new->data[0] << endl;

                        TreeNode<T> *gparent_new =  getParent(parent->data[0]);

                        /////////////////////////////////////////////////////////////////////////
                        parent->left = left_new_1;
                        parent->right = left_new_2;
                        parent_new->left = mid_new;
                        parent_new->right = right_new;

                        parent->left->depth = parent->depth + 1;
                        parent->right->depth = parent->depth + 1;
                        parent_new->left->depth = parent_new->depth + 1;
                        parent_new->right->depth = parent_new->depth + 1;
                        /////////////////////////////////////////////////////////////////////////

                        /*
                        if (gparent_new->numData == 1) {
                            gparent_new->left->left = left_new_1;
                            gparent_new->left->right = left_new_2;
                            gparent_new->right->left = mid_new;
                            gparent_new->right->right = right_new;
                            cout << "#################  " << gparent_new->right->left->data[0] << endl;
                        }
                        else if (gparent_new->numData == 2) {
                            if (parent == gparent_new->left) {
                                cout << "Parent is Grand parent's left child." << endl;
                                gparent_new->left->left = left_new_1;
                                gparent_new->left->right = left_new_2;
                                gparent_new->mid->left = mid_new;
                                gparent_new->mid->right = right_new;
                            }
                            else if (parent == gparent_new->mid) {
                                cout << "Parent is Grand parent's mid child." << endl;
                                gparent_new->mid->left = left_new_1;
                                gparent_new->mid->right = left_new_2;
                                gparent_new->right->left = mid_new;
                                gparent_new->right->right = right_new;
                            }
                        }
                        */

                        cout << "111111111 " << root->data[0] << endl;
                        cout << "222222222 " << root->left->data[0] << endl;
                        cout << "333333333 " << root->left->right->data[0] << endl;
                        //cout << "444444444 " << root->left->right->left->data[0] << endl;


                        /*
                        gparent_new->left->left = left_new_1;
                        gparent_new->left->right = left_new_2;
                        gparent_new->right->left = mid_new;
                        gparent_new->right->right = right_new;
                        */

                        /*
                        left_new_1->depth = getParent(left_new_1->data[0])->depth + 1;
                        left_new_2->depth = getParent(left_new_2->data[0])->depth + 1;
                        mid_new->depth = getParent(mid_new->data[0])->depth + 1;
                        right_new->depth = getParent(right_new->data[0])->depth + 1;
                        */

                        ret_right_new = gparent_new->right;
                    }

                    // When the node is parent's middle child.
                    else if (node == parent->mid) {
                        cout << "Current node is parent's middle child." << endl;
                        TreeNode<T> *mid_new_1 = mid_old;
                        mid_new_1->data[0] = minVal;
                        mid_new_1->data[1] = NULL;
                        mid_new_1->numData = 1;
                        TreeNode<T> *mid_new_2 = new TreeNode<T>(maxVal);
                        mid_new_2->depth = mid_new_1->depth;

                        TreeNode<T> *left_new = parent->left;
                        TreeNode<T> *right_new = parent->right;

                        cout << "-----Entering to another splitNode function (MIDDLE)-----" << endl;
                        parent_new = splitNode(parent, midVal, left_new, mid_new_1, mid_new_2, right_new);
                        cout << "-----Escaping the splitNode function (MIDDLE)-----" << endl;

                        cout << "########################    " << parent_new->data[0] << endl;

                        TreeNode<T> *gparent_new = getParent(parent->data[0]);

                        /////////////////////////////////////////////////////////////
                        parent->left = left_new;
                        parent->right = mid_new_1;
                        parent_new->left = mid_new_2;
                        parent_new->right = right_new;

                        parent->left->depth = parent->depth + 1;
                        parent->right->depth = parent->depth + 1;
                        parent_new->left->depth = parent_new->depth + 1;
                        parent_new->right->depth = parent_new->depth + 1;
                        /////////////////////////////////////////////////////////////

                        /*
                        if (gparent_new->numData == 1) {

                            gparent_new->left->left = left_new;
                            gparent_new->left->mid = NULL;
                            gparent_new->left->right = mid_new_1;
                            gparent_new->right->left = mid_new_2;
                            gparent_new->right->mid = NULL;
                            gparent_new->right->right = right_new;

                        }
                        else if (gparent_new->numData == 2) {
                            if (parent == gparent_new->left) {

                                gparent_new->left->left = left_new;
                                gparent_new->left->right = mid_new_1;
                                gparent_new->mid->left = mid_new_2;
                                gparent_new->mid->right = right_new;

                            }
                        else if (parent == gparent_new->mid) {
                                gparent_new->mid->left = left_new;
                                gparent_new->mid->right = mid_new_1;
                                gparent_new->right->left = mid_new_2;
                                gparent_new->right->right = right_new;
                            }
                        }
                        */

                        cout << "111111111 " << root->data[0] << endl;
                        cout << "222222222 " << root->left->data[0] << endl;
                        cout << "333333333 " << root->left->right->data[0] << endl;
                        //cout << "444444444 " << root->left->right->left->data[0] << endl;

                        /*
                        gparent_new->left->right = mid_new_1;
                        gparent_new->right->left = mid_new_2;
                        */

                        /*
                        left_new->depth = getParent(left_new->data[0])->depth + 1;
                        mid_new_1->depth = getParent(mid_new_1->data[0])->depth + 1;
                        mid_new_2->depth = getParent(mid_new_2->data[0])->depth + 1;
                        right_new->depth = getParent(right_new->data[0])->depth + 1;
                        */

                        ret_right_new = gparent_new->right->left;
                    }

                    // When the node is parent's right child.
                    else if (node == parent->right) {
                        cout << "Current node is parent's right child." << endl;
                        TreeNode<T> *right_new_1 = right_old;
                        right_new_1->data[0] = minVal;
                        right_new_1->data[1] = NULL;
                        right_new_1->numData = 1;
                        TreeNode<T> *right_new_2 = new TreeNode<T>(maxVal);
                        right_new_2->depth = right_new_1->depth;

                        TreeNode<T> *left_new = parent->left;
                        TreeNode<T> *mid_new = parent->mid;

                        cout << "-----Entering to another splitNode function (RIGHT)-----" << endl;
                        parent_new = splitNode(parent, midVal, left_new, mid_new, right_new_1, right_new_2);
                        cout << "-----Escaping the splitNode function (RIGHT)-----" << endl;

                        cout << "Current's left child's first data is " << parent->left->data[0] << endl;

                        TreeNode<T> *gparent_new = getParent(parent->data[0]);

                        //////////////////////////////////////////////////////////////
                        parent->left = left_new;
                        parent->right = mid_new;
                        parent_new->left = right_new_1;
                        parent_new->right = right_new_2;

                        parent->left->depth = parent->depth + 1;
                        parent->right->depth = parent->depth + 1;
                        parent_new->left->depth = parent_new->depth + 1;
                        parent_new->right->depth = parent_new->depth + 1;

                        ///////////////////////////////////////////////////////////////

                        /*
                        if (gparent_new->numData == 1) {
                            gparent_new->left->left = left_new;
                            gparent_new->left->right = mid_new;
                            gparent_new->right->left = right_new_1;
                            gparent_new->right->right = right_new_2;
                        }
                        else if (gparent_new->numData == 2) {
                            if (parent == gparent_new->left) {
                                gparent_new->left->left = left_new;
                                gparent_new->left->right = mid_new;
                                gparent_new->mid->left = right_new_1;
                                gparent_new->mid->right = right_new_2;
                            }
                            else if (parent == gparent_new->mid) {
                                gparent_new->mid->left = left_new;
                                gparent_new->mid->right = mid_new;
                                gparent_new->right->left = right_new_1;
                                gparent_new->right->right = right_new_2;
                            }
                        }
                        */

                        /*
                        gparent_new->mid->left = left_new;
                        gparent_new->mid->right = mid_new;
                        gparent_new->right->left = right_new_1;
                        gparent_new->right->right = right_new_2;
                        */

                        /*
                        left_new->depth = getParent(left_new->data[0])->depth + 1;
                        mid_new->depth = getParent(mid_new->data[0])->depth + 1;
                        right_new_1->depth = getParent(right_new_1->data[0])->depth + 1;
                        right_new_2->depth = getParent(right_new_1->data[0])->depth + 1;
                        */

                        ret_right_new = gparent_new->right;
                    }
                }
            }
            return ret_right_new;
        }
        return NULL;
    }

    /* Function to return the node that already has target data.
       If not exists, return NULL.                               */
    TreeNode<T> *searchNode(TreeNode<T> *current, T data) {
        if (current == NULL) {
            cout << "This node is NULL:(" << endl;
            if (current == root)
                cout << "And this is root???" << endl;
            return NULL;
        }
        for (int i=0; i<current->numData; i++) {
            if (current->data[i] == data) {
                return current;
            }
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
        else {
            cout << "What the hell is this case???" << endl;
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

            while (true) {
                if (current->numData == 1) {
                    if (data == current->data[0])
                        break;
                    else {
                        cout << "(Finding parent which has 1 data)" << endl;
                        parent = current;
                        if (data < parent->data[0])
                            current = parent->left;
                        else
                            current = parent->right;
                    }
                }
                else if (current->numData == 2) {
                    if (data == current->data[0] || data == current->data[1])
                        break;
                    else {
                        cout << "(Finding parent which has 2 data)" << endl;
                        parent = current;
                        if (data < parent->data[0])
                            current = parent->left;
                        else if (parent->data[0] < data && data < parent->data[1])
                            current = parent->mid;
                        else if (parent->data[1] < data)
                            current = parent->right;
                    }
                }
            }
            cout << "Found it! Current node's parent's first data is " << parent->data[0] << endl;
            return parent;
        }
        else {
            cout << "There's no such data as " << data << endl;
            return NULL;
        }
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
            cout << "     ";
        }
        else {
            for (int i=0; i<current->depth; i++) {
                cout << "          ";
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
        }
        if (current == root && current->left == NULL && current->mid == NULL && current->right == NULL)
            cout << endl;
    }

    /* Function to print the entire tree. */
    void printTree() {
        printTreeUtil(root, 0);
        cout << endl;
    }

    int getDepth(T data) {
        TreeNode<T> *node = searchNode(root, data);
        return node->depth;
    }
};

int main() {

    _23Tree<int> tree(50);

    int arr[] = {25, 752, 61, 72, 27, 72, 918, 2, 4, 724, 351, 43, 98, 139, 142, 62, 123, 754, 1, 51, 983, 263, 723, 624, 1, 7524, 623, 83, 235, 8, 4, 457, 34, 6583, 32, 865, 354, 76, 4, 6583, 3, 34};

    for (int i=0; i<sizeof(arr)/sizeof(int); i++) {
        tree.insertData(arr[i]);
        tree.printTree();
        cout << "====================================" << endl;
    }

    cout << endl << "<<Print final tree>>" << endl;
    tree.printTree();


    return 0;
}
