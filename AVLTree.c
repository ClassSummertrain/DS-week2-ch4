typedef struct Node{//树结点
    int val;//数据域
    struct Node * left;//左孩子
    struct Node * right;//右孩子
}TreeNode;

TreeNode* getTreeNode(int val) {//构造树结点
    TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
    if(!node) return NULL;
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int getTreeHeight(TreeNode* tree) {//获取树高度
    if(!tree) return 0;
    int hl = getTreeHeight(tree->left);
    int hr = getTreeHeight(tree->right);
    return (hl>hr?hl:hr)+1;
}
TreeNode* rightRotate(TreeNode* tree) { // 注意顺序，否则可能丢失节点
    TreeNode* tmp = tree->left;  // 右旋：原树根的左节点将成为新根
    tree->left = tmp->right;
    tmp->right = tree;
    return tmp;
}TreeNode* leftRotate(TreeNode* tree) {
    TreeNode* tmp = tree->right;  // 左旋：树的右节点将成为新根
    tree->right = tmp->left;
    tmp->left = tree;    // 原树根成为新树根的左节点
    return tmp;
}
TreeNode* leftRightRotate(TreeNode* tree) {
    tree->left = leftRotate(tree->left); // 注意是树的左节点
    return rightRotate(tree);
}
TreeNode* rightLeftRotate(TreeNode* tree) {
    tree->right = rightRotate(tree->right);
    return leftRotate(tree);
}
TreeNode* balanceTree(TreeNode * tree, int insertVal) {
    int hl = getTreeHeight(tree->left);
    int hr = getTreeHeight(tree->right);
    if (hr>=hl+2) {
        if (insertVal>tree->right->val) tree = leftRotate(tree); else tree = rightLeftRotate(tree);
    }
    if (hl>=hr+2) {
        if (insertVal>tree->left->val) tree = leftRightRotate(tree); else tree = rightRotate(tree);
    }
    return tree;
}

TreeNode* insertTreeNode(TreeNode * tree, int insertVal) {
    if(!tree) return getTreeNode(insertVal);
    else if (insertVal > tree->val) {
        tree->right = insertTreeNode(tree->right, insertVal);
        return balanceTree(tree, insertVal);
    } else if (insertVal < tree->val){
        tree->left = insertTreeNode(tree->left, insertVal);
        return balanceTree(tree, insertVal);
    }
    return tree;
}
TreeNode* deleteTreeNode(TreeNode* tree, int deleteVal) {
    if (!tree){ printf("Not find the Node whose value is %d", deleteVal); return tree; }
    if (deleteVal>tree->val) {
        tree->right = deleteTreeNode(tree->right, deleteVal);
        if (getTreeHeight(tree->left) - getTreeHeight(tree->right)>=2) {  //是否旋转

            if (getTreeHeight(tree->left->left)>getTreeHeight(tree->left->right)) {  // 旋转形式判定
                tree =  rightRotate(tree);
            } else {
                tree = leftRightRotate(tree);
            }
        }
    } else if (deleteVal<tree->val) {
        tree->left = deleteTreeNode(tree->left, deleteVal);
        if (getTreeHeight(tree->right)-getTreeHeight(tree->left)>=2) {
            if (getTreeHeight(tree->right->right)>getTreeHeight(tree->right->left)) {
                return leftRotate(tree);
            } else {
                return rightLeftRotate(tree);
            }
        }
    } else {
        if (tree->left && tree->right) {
            int hl = getTreeHeight(tree->left), hr = getTreeHeight(tree->right);
            if (hl>hr) {
                TreeNode* tmpFather = tree->left;
                TreeNode* tmp = tree->left->right;
                if (!tmp) {
                    tmpFather->right = tree->right;
                    free(tree);
                    return tmpFather;// 重点检查
                } else {
                    while (tmp->right) {  //查找最右子节点
                        tmpFather = tmp;
                        tmp = tmp->right;
                    }
                    tree->val = tmp->val;
                    tmpFather->right = tmp->left ? tmp->left : NULL; //最右子节点是否有左子树（只有两种情况：左子树存在和不存在）
                    return tree;
                }
            } else {
                TreeNode* tmpFather = tree->right;
                TreeNode* tmp = tmpFather->left;
                if (!tmp) {
                    tmpFather->left = tree->left;
                    free(tree);
                    return tmpFather;
                } else {
                    while (tmp->left) {  // 与上相同
                        tmpFather = tmp;
                        tmp = tmp->left;
                    }
                    tree->val = tmp->val;
                    tmpFather->left = tmp->right ? tmp->right : NULL;
                    return tree;
                }
            }
        } else {
            return tree->left?tree->left:tree->right;
        }

    }
    return tree;
}
