#ifndef _Tree_H
typedef TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;

SearchTree MakeEmpty(SearchTree T);
Position Find(char X,SearchTree T);
Position FindMin(SearchTree T);
Position FindMax(SearchTree T);
SearchTree Insert(char X,SearchTree T);
SearchTree Delete(char X,SearchTree T);
char Retrieve(Position P);

#endif
struct TreeNode
{
    char data;
    SearchTree Left;
    SearchTree Right;
};

SearchTree MakeEmpty(SearchTree T){//主要用于初始化
    if(T!=NULL){
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }
    return NULL;
}

Position Find(char X,SearchTree T){
    if(T==NULL)return NULL;
    if(X<T->data)return Find(X,T->Left);
    else if(X>T->data)return Find(X,T->Right);
    else return T;
}

Position FindMin(SearchTree T){
    if(T==NULL)return NULL;
    else if(T->Left==NULL)return T;
    else return FindMin(T->Left);
}

Position FindMax(SearchTree T){
    if(T!=NULL){
        while(T->Right!=NULL){
            T=T->Right;
        }
    }
    return T;
}

SearchTree Insert(char X,SearchTree T){
    if(T==NULL){//原树为空
        T=malloc(sizeof(struct TreeNode));
        if(T==NULL){
            printf("Creat Node Error.");//没有成功建立结点
        }
        else{//创建新结点
            T->data=X;
            T->Left=T->Right=NULL;
        }
    }
    else if(X<T->data){
        T->Left=Insert(X,T->Left);
    }
    else if(X>T->data){
        T->Right=Insert(X,T->Right);
    }
    //关于插入重复结点值得处理方法这里不讨论
    return T;
}

SearchTree Delete(char X,SearchTree T){
    Position TempCell;
    if(T==NULL){
        printf("No NOde need to Delete");//没有结点需要删除
    }
    else if(X<T->data){//Go Left
        T->Left=Delete(X,T->Left);
    }
    else if(X>T->data){//Go Right
        T->Right=Delete(X,T->Right);
    }
    //这里只给出了待删除结点最多有一个孩子结点的情况，有两个孩子结点的情况较复杂，不讨论
    else{//找到待删除得结点（上述代码可以用Find函数代替）
        TempCell=T;//暂存T结点
        if(T->Left==NULL){
            T=T->Right;
        }
        else if(T->Right==NULL){
            T=T->Left;
        }
        free(TempCell);//删除
    }
    return T;
}



