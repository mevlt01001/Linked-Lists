#include <iostream>

class node{
public:
    int data;
    int balance;
    int level;
    node* parent;
    node* leftChild;
    node* rightChild;
    node(int data){
        this->data = data;
    }
};

node* rootNode = nullptr;

void inorderTravel(node* root){
    if(root == nullptr)return;
    inorderTravel(root->leftChild);
    std::cout<<root<<"("<<root->data<<") balance:"<<root->balance<<"  parent:"<<root->parent<<" leftChild:"<<root->leftChild<<" rightChild:"<<root->rightChild<<"\n";
    inorderTravel(root->rightChild);
}

int getMaxLevel(node* root, int level){
    if(root == nullptr) return level - 1;
    int leftMaxLevel = getMaxLevel(root->leftChild, level+1);
    int rightMaxLevel = getMaxLevel(root->rightChild, level+1);
    return std::max(leftMaxLevel, rightMaxLevel);
}

void setBalance(node* root){
    if(root == nullptr) return;
    int leftMaxChild = getMaxLevel(root->leftChild,1);
    int rightMaxChild = getMaxLevel(root->rightChild,1);
    int balance = leftMaxChild-rightMaxChild;
    root->balance = balance;
    setBalance(root->leftChild);
    setBalance(root->rightChild);
}

int whichRotation(node* pivot){
    /*
    return ?
    case 1 : LL,
    case 2 : LR,
    case 3 : RL,
    case 4 : RR,rotation.
    */
    int leftMaxLevel = getMaxLevel(pivot->leftChild,1);
    int rightMaxLevel = getMaxLevel(pivot->rightChild,1);
    if(leftMaxLevel > rightMaxLevel){//----------L-?
        int leftMaxLevel = getMaxLevel(pivot->leftChild->leftChild,1);
        int rightMaxLevel = getMaxLevel(pivot->leftChild->rightChild,1);
        if(leftMaxLevel > rightMaxLevel)return 1; else return 2;
    }else{//-------------------------------------R-?
        int leftMaxLevel = getMaxLevel(pivot->rightChild->leftChild,1);
        int rightMaxLevel = getMaxLevel(pivot->rightChild->rightChild,1);
        if(leftMaxLevel > rightMaxLevel)return 3; else return 4;
    }
}

node* getPivot(node* root){
    if(root==nullptr)return nullptr;
    getPivot(root->leftChild);
    if(root->balance > 1 || root->balance < -1)return root;
    return getPivot(root->rightChild);
}

node* addHelper(int data, node* root, node* parent){
    if(root == nullptr) return parent;
    else if(data < root->data) return addHelper(data, root->leftChild, root);
    else if(root->data < data) return addHelper(data, root->rightChild, root);
    else return nullptr;
}

void nodeReplace(node* stupidNode, node* destinationRoot){
    node* parent = addHelper(stupidNode->data,destinationRoot,destinationRoot->parent);
    if(stupidNode->data < parent->data){
        parent->leftChild = stupidNode;
    }else{
        parent->rightChild = stupidNode;
    }
    stupidNode->parent = parent;
}

void ll_rotation(node* pivot){
    node* pivotLeft = pivot->leftChild;
    node* stupidNode = nullptr;
    if(pivotLeft->rightChild != nullptr){
        stupidNode = pivotLeft->rightChild;
    }
    node* pivotParent = nullptr;
    bool pivotIsRootNode = false;
    if (pivot->parent != nullptr){
        pivotParent = pivot->parent;
    }else if(pivot == rootNode){
        pivotIsRootNode = true;
    }
    pivot->rightChild = nullptr;pivot->leftChild = nullptr;pivot->parent = nullptr;//all pivot's ties have been severed

    pivotLeft->rightChild = pivot;
    pivot->parent = pivotLeft;
    pivotLeft->parent = pivotParent;
    if(pivotParent != nullptr){
        if(pivotLeft->data < pivotParent->data){
            pivotParent->leftChild = pivotLeft;
        }else{
            pivotParent->rightChild = pivotLeft;
        }
    }else if(pivotIsRootNode){
        rootNode = pivotLeft;
    }
    if(stupidNode != nullptr){
        stupidNode->parent = nullptr;
        nodeReplace(stupidNode, pivot);
    }

    std::cout<<"ll_rotation was ran to fix for "<<pivot->data<<std::endl;
}
void rr_rotation(node* pivot){
    node* pivotRight = pivot->rightChild;
    node* stupidNode = nullptr;
    if(pivotRight->leftChild != nullptr){
        stupidNode = pivotRight->leftChild;
    }
    node* pivotParent = nullptr;
    bool pivotIsRootNode = false;
    if(pivot->parent != nullptr){
        pivotParent = pivot->parent;
    }else if(pivot == rootNode){
        pivotIsRootNode = true;
    }
    pivot->rightChild = nullptr;pivot->leftChild = nullptr;pivot->parent = nullptr;//all pivot's ties have been severed

    pivotRight->leftChild = pivot;
    pivot->parent = pivotRight;
    pivotRight->parent = pivotParent;
    if(pivotParent != nullptr){
        if(pivotRight->data < pivotParent->data){
            pivotParent->leftChild = pivotRight;
        }else{
            pivotParent->rightChild = pivotRight;
        }
    }else if(pivotIsRootNode){
        rootNode = pivotRight;
    }
    if(stupidNode != nullptr){
        stupidNode->parent = nullptr;
        nodeReplace(stupidNode, pivot);
    }

    std::cout<<"rr_rotation was ran to fix for "<<pivot->data<<std::endl;
}
void rl_rotation(node* pivot){
    node* secondPivot = pivot->leftChild;
    rr_rotation(secondPivot);
    ll_rotation(pivot);

    std::cout<<"rl_rotation was ran to fix for "<<pivot->data<<std::endl;
}
void lr_rotation(node* pivot){
    node* secondPivot = pivot->rightChild;
    ll_rotation(secondPivot);
    rr_rotation(pivot);
    std::cout<<"lr_rotation was ran to fix for "<<pivot->data<<std::endl;
}

void addElement(int data){
    node* pivot = getPivot(rootNode);
    int rotation;
    if(pivot != nullptr){
        rotation = whichRotation(pivot);
        if(rotation == 1){
            ll_rotation(pivot);
        }else if(rotation == 2){
            lr_rotation(pivot);
        }else if(rotation == 3){
            rl_rotation(pivot);
        }else {
            rr_rotation(pivot);
        }

    }
    node* newNode = new node(data);
    if(rootNode == nullptr){
        rootNode = newNode;
    }else{
        node* parent;
        if(data < rootNode->data){
            parent = addHelper(data, rootNode->leftChild, rootNode);
        }
        else if(rootNode->data < data){
            parent = addHelper(data, rootNode->rightChild, rootNode);
        }

        if(data < parent->data)parent->leftChild = newNode;
        else if(parent->data < data)parent->rightChild = newNode;
        newNode->parent = parent;
    }
    setBalance(rootNode);
}

int main(){

    int elements[] = {100,90,80,70,60,50,40,30,20,10};
    for(int i:elements)addElement(i);

    inorderTravel(rootNode);

    return 0;
}