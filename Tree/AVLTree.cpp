#include <iostream>
#include <algorithm>
using namespace std;
struct TreeNode{
    int data;
    int height = 1;
    TreeNode *left = nullptr; 
    TreeNode *right = nullptr;
    TreeNode(int data) : data(data) {}
};
typedef TreeNode* AVL;
class Tree{
    public:
        AVL Node = nullptr;
        int get_height(AVL Node){ return (!Node) ? 0 : Node->height;}
        int get_balanced_factor(AVL Node){
            if(!Node) return 0;
            return get_height(Node->left) - get_height(Node->right);
        }
        int find_min_value(AVL Node){
            if (!Node->left) return Node->data;
            return find_min_value(Node->left);
        }
        AVL create_node(int value){
            AVL newNode = new(nothrow) TreeNode(value);
            if(!newNode){
                cout <<"Not enough memory.\n";
                return nullptr;
            }
            return newNode;
        }
        bool find(AVL Node, int value){
            if(!Node) return false;
            if(value == Node->data) return true;
            if(value < Node->data) return find(Node->left, value);
            return find(Node->right, value);
        }
        void push(int value){
            if(!find(Node, value)){
                Node = insert_node(Node, value);
            } else {
                cout <<"The value is in the tree.\n";
            }
        }
        void pop(int value){
            if(find(Node, value)){
                Node = delete_node(Node, value);
            } else {
                cout <<"The value isn't in the tree.\n";
            }
        }
        AVL left_rotate(AVL Node){
            AVL B = Node->right;
            AVL Y = B->left;

            B->left = Node;
            Node->right = Y;

            B->height = 1 + max(get_height(B->left), get_height(B->right));
            Node->height = 1 + max(get_height(Node->left), get_height(Node->right));
            return B;
        }
        AVL right_rotate(AVL Node){
            AVL A = Node->left;
            AVL Y = A->right;

            A->right = Node;
            Node->left = Y;

            A->height = 1 + max(get_height(A->left), get_height(A->right));
            Node->height = 1 + max(get_height(Node->left), get_height(Node->right));
            return A;
        }
        AVL insert_node(AVL Node, int value){
            if(!Node) Node = create_node(value);
            if(value < Node->data) Node->left = insert_node(Node->left, value);
            if(value > Node->data) Node->right = insert_node(Node->right, value);

            Node->height = 1 + max(get_height(Node->left), get_height(Node->right));
            int bf = get_balanced_factor(Node);

            if(bf > 1 && value < Node->left->data){
                return right_rotate(Node);
            } else if(bf > 1 && value > Node->left->data){
                Node->left = left_rotate(Node->left);
                return right_rotate(Node);
            } else if(bf < -1 && value > Node->right->data){
                return left_rotate(Node);
            } else if(bf < -1 && value < Node->right->data){
                Node->right = right_rotate(Node->right);
                return left_rotate(Node);
            }
            return Node;
        }
        AVL delete_node(AVL Node, int value){
            if(!Node) return nullptr;
            if(value < Node->data) Node->left = delete_node(Node->left, value);
            else if(value > Node->data) Node->right = delete_node(Node->right, value);
            else {
                if(!Node->left && !Node->right){
                    return nullptr;
                } else if(!Node->left){
                    return Node->right;
                } else if(!Node->right){
                    return Node->left;
                }
                int temp = find_min_value(Node->right);
                Node->data = temp;
                Node->right = delete_node(Node->right, temp);
            }
            Node->height = 1 + max(get_height(Node->left), get_height(Node->right));
            int bf = get_balanced_factor(Node);

            if(bf > 1 && get_balanced_factor(Node->left) >= 0){
                return right_rotate(Node);
            } else if(bf > 1 && get_balanced_factor(Node->left) < 0){
                Node->left = left_rotate(Node->left);
                return right_rotate(Node);
            } else if(bf < -1 && get_balanced_factor(Node->right) <= 0){
                return left_rotate(Node);
            } else if(bf < -1 && get_balanced_factor(Node->right) > 0){
                Node->right = right_rotate(Node->right);
                return left_rotate(Node);
            }
            return Node;
        }
        void in_order_traversal(AVL Node){
            if(Node){
                in_order_traversal(Node->left);
                cout << Node->data <<' ';
                in_order_traversal(Node->right);
            }
        }
        void pre_order_traversal(AVL Node){
            if(Node){
                cout << Node->data <<' ';
                pre_order_traversal(Node->left);
                pre_order_traversal(Node->right);
            }
        }
};
int main()
{
    int A[4] = {4, 3, 1, 2};
    int sizeA = sizeof(A) / sizeof(A[0]);
    Tree avl;
    for(int i = 0; i < sizeA; i++){
        avl.push(A[i]);
    }
    avl.pop(1);
    cout <<"The tree is: ";
    avl.pre_order_traversal(avl.Node);
    return 0;
}
