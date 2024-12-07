#include <iostream>
#include <cmath>
using namespace std;
struct TreeNode{
    int data;
    int height;
    TreeNode *left, *right;
};
typedef TreeNode* BST;
BST create_avl_tree(int root){
    BST Tree = new TreeNode;
    if(Tree == nullptr){
        cout <<"Not enough memory.\n";
        return nullptr;
    }
    Tree->height = 1;
    Tree->left = nullptr;
    Tree->right = nullptr;
    Tree->data = root;
    return Tree;
}
int get_height(BST Node){
    return (!Node) ? 0 : Node->height;
}
int get_balanced_factor(BST Node){
    if(!Node){
        return 0;
    }
    return get_height(Node->left) - get_height(Node->right);
}
BST find_min_node(BST Node){
    if(!Node->left){
        return Node;
    }
    return find_min_node(Node->left);
}
BST left_rotate(BST Node){
    BST B = Node->right;
    BST Y = B->left;

    B->left = Node;
    Node->right = Y;

    B->height = 1 + max(get_height(B->left), get_height(B->right));
    Node->height = 1 + max(get_height(Node->left), get_height(Node->right));
    return B;
}
BST right_rotate(BST Node){
    BST A = Node->left;
    BST Y = A->right;

    A->right = Node;
    Node->left = Y;

    A->height = 1 + max(get_height(A->left), get_height(A->right));
    Node->height = 1 + max(get_height(Node->left), get_height(Node->right));
    return A;
}
BST insert_node(BST Node, int value){
    if(!Node){
        return create_avl_tree(value);
    }
    if(value < Node->data){
        Node->left = insert_node(Node->left, value);
    } else if(value > Node->data){
        Node->right = insert_node(Node->right, value);
    } 
    return Node;

    Node->height = 1 + max(get_height(Node->right), get_height(Node->left));
    int bf = get_balanced_factor(Node);

    if(bf > 1 && value < Node->left->data){
        return right_rotate(Node);
    }
    if(bf < -1 && value > Node->right->data){
        return left_rotate(Node);
    }
    if(bf > 1 && value > Node->left->data){
        Node->left = left_rotate(Node->left);
        return right_rotate(Node);
    }
    if(bf < -1 && value < Node->right->data){
        Node->right = left_rotate(Node->right);
        return right_rotate(Node);
    }
    return Node;
}
bool find_value(BST Tree, int value){
    if(Tree != nullptr){
        if(Tree->data == value){
            return true;
        }
        return find_value(Tree->left, value) || find_value(Tree->right, value);
    }
    return false;
}
BST delete_node(BST Node, int value){
    if(!Node){ 
        return nullptr; //No value found
    }
    if(value < Node->data){
        Node->left = delete_node(Node->left, value);
    } else if(value > Node->data){
        Node->right = delete_node(Node->right, value);
    } else {
        if(!Node->left && !Node->right){
            return nullptr;
        }
        if(!Node->left){
            return Node->right;
        }
        if(!Node->right){
            return Node->left;
        }
        BST temp = find_min_node(Node->right);
        Node->data = temp->data;
        Node->right = delete_node(Node->right, temp->data);
    }
    Node->height = 1 + max(get_height(Node->left), get_height(Node->right)); 
    int bf = get_balanced_factor(Node);

    if(bf > 1 && get_balanced_factor(Node->left) >= 0){
        return right_rotate(Node);
    }
    if(bf < -1 && get_balanced_factor(Node->right) <= 0){
        return left_rotate(Node);
    }
    if(bf > 1 && get_balanced_factor(Node->left) < 0){
        Node->left = left_rotate(Node->left);
        return right_rotate(Node);
    }
    if(bf < -1 && get_balanced_factor(Node->right) > 0){
        Node->right = right_rotate(Node->right);
        return left_rotate(Node);
    }
    return Node;
}
void in_order_traversal(BST Tree){
    if(Tree){
        in_order_traversal(Tree->left);
        cout << Tree->data <<' ';
        in_order_traversal(Tree->right);
    }
}
int main(){
    int A[13] = {50, 70};
    BST avl = nullptr;
    for(int i = 0; i < 2; i++){
        avl = insert_node(avl, A[i]);
    }
    in_order_traversal(avl);
    BST av = delete_node(avl, 50);
    cout <<endl;
    in_order_traversal(av);
    cout <<"\n\n";
    av = delete_node(av, 70);
    in_order_traversal(av);
    return 0;
}