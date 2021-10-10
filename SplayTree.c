//
//  SplayTree.h
//  SplayTree
 
#ifndef SplayTree_h
#define SplayTree_h
 
#include <stdio.h>
#include <stdlib.h>
typedef struct SplayTree *PSplayTree;
typedef int ElemType;
 
struct SplayTree {
    ElemType elem;
    PSplayTree left;
    PSplayTree right;
};
 
static PSplayTree NullNode;
 
/* 初始化 */
PSplayTree Initialize();
/* 插入 */
PSplayTree Insert(PSplayTree T,ElemType Item);
/* 删除 */
PSplayTree Remove(PSplayTree T,ElemType Item);
/* 遍历 */
void Travel(PSplayTree T);
 
#endif /* SplayTree_h */

//
//  SplayTree.c
//  SplayTree
//
//  Created by Wuyixin on 2017/6/30.
//  Copyright © 2017年 Coding365. All rights reserved.
//
 
 
/* 根据关键值Item展开 */
static PSplayTree Splay(PSplayTree T, ElemType Item);
/* 左旋转 */
static PSplayTree SingleRotateLeft(PSplayTree T);
/* 右旋转 */
static PSplayTree SingleRotateRight(PSplayTree T);
 
/* 根据关键值Item展开 */
static PSplayTree Splay(PSplayTree X, ElemType Item){
    /* 左边树与右边树 */
    static struct SplayTree header;
    /* 左边树最大值与右边树最小值 */
    static PSplayTree LeftTreeMax,RightTreeMin;
    
    header.left = header.right = NullNode;
    LeftTreeMax = RightTreeMin = &header;
    
    /* NullNode赋值为Item，当查找到Item值或者进行值树的底部时终止循环 */
    NullNode->elem = Item;
   
    while (Item != X->elem) {
        if (Item < X->elem){
            if (Item < X->left->elem)
                X = SingleRotateLeft(X);
            /* 到达底部 */
            if (X->left == NullNode)
                break;
            /* 链接右边 */
            RightTreeMin->left = X;
            RightTreeMin = X;
            X = X->left;
        }else{
            if (Item > X->right->elem)
                X = SingleRotateRight(X);
            if (X->right == NullNode)
                break;
            /* 链接左边 */
            LeftTreeMax->right = X;
            LeftTreeMax = X;
            X = X->right;
        }
    }
    
    /* 组装 */
    LeftTreeMax->right = X->left;
    RightTreeMin->left = X->right;
    X->left = header.right;
    X->right = header.left;
    
    
    return X;
}
 
/* 左旋转 */
static PSplayTree SingleRotateLeft(PSplayTree T){
    PSplayTree T2 = T->left;
    T->left = T2->right;
    T2->right = T;
    
    return T2;
}
/* 右旋转 */
static PSplayTree SingleRotateRight(PSplayTree T){
    PSplayTree T2 = T->right;
    T->right = T2->left;
    T2->left = T;
    return T2;
}
 
/* 初始化 */
PSplayTree Initialize(){
    if (NullNode == NULL){
        NullNode = malloc(sizeof(struct SplayTree));
        if (NullNode == NULL)
            exit(EXIT_FAILURE);
        NullNode->left = NullNode->right = NullNode;
    }
    
    return NullNode;
}
/* 插入 */
PSplayTree Insert(PSplayTree T,ElemType Item){
    PSplayTree NewNode;
    NewNode = malloc(sizeof(struct SplayTree));
    if (NewNode == NULL)
        exit(EXIT_FAILURE);
    NewNode->elem = Item;
    
    if (T == NullNode) {
        NewNode->left = NewNode->right = NullNode;
        T = NewNode;
    }else{
        T = Splay(T, Item);
        
        if (Item < T->elem){
            NewNode->left = T->left;
            NewNode->right = T;
            T->left = NullNode;
            T = NewNode;
        }else if (Item > T->elem){
            NewNode->right = T->right;
            NewNode->left = T;
            T->right = NullNode;
            T = NewNode;
        }else if(Item == T->elem){
            /* 重复值不做插入 */
            free(NewNode);
        }
 
    }
    
    
    return T;
    
}
/* 删除 */
PSplayTree Remove(PSplayTree T,ElemType Item){
    PSplayTree NewTree;
    if (T != NullNode){
        T = Splay(T, Item);
        if (Item == T->elem){
            /* 找到该项 */
            if (T->left == NullNode){
                /* 左子树是空，右子树成为新树 */
                NewTree = T->right;
                
            }else{
                /* 左子树成为新树根 对新树展开，由于Item大于新树的任何节点。所以展开的过程会沿着有路径进行 */
                /* 一直到最右边的树叶节点，所以展开之后得到的树，其右子树肯定是空树 */
                NewTree = T->left;
                NewTree = Splay(NewTree, Item);
                NewTree->right = T->right;
            }
            free(T);
            T = NewTree;
        }
    }
    
    return T;
}
 
 
void Travel(PSplayTree T){
    if (T != NullNode){
        Travel(T->left);
        printf("%d ",T->elem);
        Travel(T->right);
    }
}
 
 
