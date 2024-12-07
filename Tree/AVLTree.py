class Node:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None
        self.height = 0

    def in_order_traversal(self):
        elements = []
        if self.left:
            elements += self.left.in_order_traversal()
        elements.append(self.key)
        if self.right:
            elements += self.right.in_order_traversal()
        return elements

class AVLTree:
    def __init__(self):
        self.root = None
    
    def get_height(self, node):
        return 0 if not node else node.height
    
    def get_balanced_factor(self, node):
        return 0 if not node else (self.get_height(node.left) - self.get_height(node.right))
    
    def get_min_node(self, node):
        return node if not node.left else self.get_min_node(node.left)
    
    def search(self, key):
        x = self.root
        while x is not None and key != x.key:
            if key < x.key:
                x = x.left
            else:
                x = x.right
        return x
    
    def insert(self, root, key):
        if not root:
            return Node(key)
        elif key < root.key:
            root.left = self.insert(root.left, key)
        else:
            root.right = self.insert(root.right, key)
        
        root.height = 1 + max(self.get_height(root.left), self.get_height(root.right))

        bf = self.get_balanced_factor(root)

        if bf > 1 and key < root.left.key:
            return self.right_rotate(root)
        
        if bf < -1 and key > root.right.key:
            return self.left_rotate(root)
        
        if bf > 1 and key > root.left.key:
            root.left = self.left_rotate(root.left)
            return self.right_rotate(root)
    
        if bf < -1 and key < root.right.key:
            root.right = self.right_rotate(root.right)
            return self.left_rotate(root)
        return root

    def delete(self, root, key):
        if not root:
            return root
        elif key < root.key:
            root.left = self.delete(root.left, key)
        elif key > root.key:
            root.right = self.delete(root.right, key)
        else:
            if not root.left:
                return root.right
            elif not root.right:
                return root.left
            else:
                temp = self.get_min_node(root.right)
                root.key = temp.key
                root.right = self.delete(root.right, temp.key)

        root.height = 1 + max(self.get_height(root.left), self.get_height(root.right))

        bf = self.get_balanced_factor(root)
        if bf > 1 and self.get_balanced_factor(root.left) >= 0:
            return self.right_rotate(root)
        
        if bf < -1 and self.get_balanced_factor(root.right) <= 0:
            return self.left_rotate(root)
        
        if bf > 1 and self.get_balanced_factor(root.left) < 0:
            root.left = self.left_rotate(root.left)
            return self.right_rotate(root)
        
        if bf < -1 and self.get_balanced_factor(root.right) > 0:
            root.right = self.right_rotate(root.right)
            return self.left_rotate(root)

        return root
    
    def left_rotate(self, node):
        B = node.right
        Y = B.left

        B.left = node
        node.right = Y

        node.height = 1 + max(self.get_height(node.left), self.get_height(node.right))
        B.height = 1 + max(self.get_height(B.left), self.get_height(B.right))
        
        return B
    
    def right_rotate(self, node):
        A = node.left
        Y = A.right

        A.right = node
        node.left = Y

        node.height = 1 + max(self.get_height(node.left), self.get_height(node.right))
        A.height = 1 + max(self.get_height(A.left), self.get_height(A.right))

        return A     
def print_search_result(result):
    return 'found' if result else 'not found'    
    
def main():
    av1 = AVLTree()
    keys = [50, 25, 75, 15, 35, 60, 120, 10, 68, 90, 125, 83, 100]
    for key in keys:
        av1.root = av1.insert(av1.root, key)
    print(av1.root.in_order_traversal())
    av1.root = av1.delete(av1.root, 120)
    print(av1.root.in_order_traversal())
    result = av1.search(10)
    print(f'Search for: {print_search_result(result)}')
    
main()


    
        

    