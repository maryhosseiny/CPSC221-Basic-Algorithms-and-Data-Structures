/**
 *
 * quadtree (pa3)
 * quadtree.cpp
 * This file will be used for grading.
 *
 */

#include "quadtree.h"
using namespace std;

// Node constructor, given.
quadtree::Node::Node(pair<int, int> ul, int d, RGBAPixel a, double v)
    : upLeft(ul), dim(d), avg(a), var(v), NW(nullptr), NE(nullptr), SE(nullptr), SW(nullptr) {}

// quadtree destructor, given.
quadtree::~quadtree() {
    clear();
}
// quadtree copy constructor, given.
quadtree::quadtree(const quadtree& other) {
    copy(other);
}
// quadtree assignment operator, given.
quadtree& quadtree::operator=(const quadtree& rhs) {
    if (this != &rhs) {
        clear();
        copy(rhs);
    }
    return *this;
}

quadtree::quadtree(PNG& imIn) {
    stats imStats = stats(imIn);
    pair<int, int> ul(0,0);
    int dim = imIn.width(); //imIn.width();
    edge = pow(2, dim);
    
    root = buildTree(imStats, ul, dim);
}

quadtree::Node* quadtree::buildTree(stats& s, pair<int, int> ul, int dim) {
    Node* curr = new Node(ul, dim, s.getAvg(ul, dim), s.getVar(ul, dim));
    if (dim == 0) {
        curr->NW = curr->NE = curr->SE = curr->SW = NULL;
        return curr;
    }
    
    int halfDim = dim - 1;
    curr->NW = buildTree(s, ul, halfDim);
    curr->SW = buildTree(s, make_pair(ul.first, ul.second + pow(2,halfDim)), halfDim);
    curr->SE = buildTree(s, make_pair(ul.first + pow(2,halfDim), (ul.second + pow(2,halfDim))), halfDim);
    curr->NE = buildTree(s, make_pair(ul.first + pow(2,halfDim), ul.second), halfDim);
    return curr;
    
    

    // int halfDim = dim / 2;
    // curr->NW = buildTree(s, ul, halfDim);
    // curr->NE = buildTree(s, make_pair(ul.first, ul.second + halfDim), halfDim);
    // curr->SE = buildTree(s, make_pair(ul.first + halfDim, ul.second + halfDim), halfDim);
    // curr->SW = buildTree(s, make_pair(ul.first + halfDim, ul.second), halfDim);
    // return curr;

}

PNG quadtree::render() const {
	PNG image = PNG(edge, edge);
    renderHelper(image, root);
    return image;    
}

void quadtree::renderHelper(PNG& img, Node* node) const {
    if (node == NULL){
	    return;
	} else if (node->NW != NULL) {
        renderHelper(img, node->NW);
        renderHelper(img, node->NE);
        renderHelper(img, node->SE);
        renderHelper(img, node->SW);
    } else {  
        // int length = pow(2, node->dim);
        int x = node->upLeft.first;
        int y = node->upLeft.second;
        for (int i = x; i < x + edge && i <= edge; i++) { //
            for (int j = y; j < y + edge && j <= edge; j++) { //
                if (img.getPixel(i, j) != nullptr) {
                    *img.getPixel(i, j) = node->avg;
                }
            }
        }
    }

	// int length = pow(2, node->dim);
    // int x = node->upLeft.first;
    // int y = node->upLeft.second;
    // for (int i = x ; i <= (x+length) ; i++){
	// 	for (int j = y ; j <= (y+length) ; j++){
	// 	    *img.getPixel(i,j) = node->avg;
	// 	}
	// }
    // }
}


int quadtree::idealPrune(const int leaves) const {
    return idealPruneRecursive(leaves, 0, 255*255*3+1);
}

int quadtree::idealPruneRecursive(int const leaves, int minTolerance, int maxTolerance) const {
    if (minTolerance > maxTolerance) {
        return minTolerance;
    }
    int tolerance = pruneSize((minTolerance+maxTolerance)/2);
    if (tolerance == leaves) {
        if (tolerance == pruneSize(((minTolerance+maxTolerance)/2)-1)) {
            return idealPruneRecursive(leaves, 0, ((minTolerance+maxTolerance)/2)-1);
        }
        return ((minTolerance+maxTolerance)/2);
    } else if (tolerance < leaves) {
        return idealPruneRecursive(leaves, minTolerance, ((minTolerance+maxTolerance)/2)-1);
    } else if (tolerance > leaves) {
        return idealPruneRecursive(leaves, ((minTolerance+maxTolerance)/2)+1, maxTolerance);
    }


    // if (minTolerance >= maxTolerance) {
    //     return minTolerance;
    // }
    // int tolerance = pruneSize((minTolerance + maxTolerance) / 2);
    // if (tolerance == leaves) {
    //     if (minTolerance == 0 || pruneSize((minTolerance + maxTolerance) / 2 - 1) != leaves) {
    //         return (minTolerance + maxTolerance) / 2;
    //     }
    //     return idealPruneRecursive(leaves, minTolerance, (minTolerance + maxTolerance) / 2 - 1);
    // } else if (tolerance < leaves) {
    //     return idealPruneRecursive(leaves, minTolerance, (minTolerance + maxTolerance) / 2);
    // } else {
    //     return idealPruneRecursive(leaves, (minTolerance + maxTolerance) / 2 + 1, maxTolerance);
    // }
}

//DONE
int quadtree::pruneSize(const int tol) const {
    return pruneSizeHelper(root, tol);
}

//DONE
int quadtree::pruneSizeHelper(Node* node, const int tol) const {
    if (node == nullptr) {
        return 0;
    } else if (prunable(node, tol)) {
        return 1;
    } else {
        return pruneSizeHelper(node->NW, tol) + pruneSizeHelper(node->NE, tol) +
               pruneSizeHelper(node->SE, tol) + pruneSizeHelper(node->SW, tol);
    }
}

//DONE
void quadtree::prune(const int tol) {
    pruneHelper(root, tol);
}

//DONE
void quadtree::pruneHelper(Node* node, const int tol) {
    if (node == NULL) {
        return;
    } else if (prunable(node->SE, tol) && prunable(node->SW, tol) && prunable(node->NE, tol) &&	prunable(node->NW, tol)) {
		clearSubTrees(node);
	} else {
        pruneHelper(node->NW, tol);
        pruneHelper(node->NE, tol);
		pruneHelper(node->SE, tol);
		pruneHelper(node->SW, tol);
	}
}

//DONE 
void quadtree::clearSubTrees(Node * root){
	clear(root->NW);
    clear(root->NE);
    clear(root->SE);
	clear(root->SW);
	root->NW = NULL;
    root->NE = NULL;
	root->SE = NULL;
	root->SW = NULL;	
}

//DONE
void quadtree::clear() {
    clear(root);
}

//DONE
void quadtree::clear(Node* curr) {
    if (curr->NW == NULL && curr->NE == NULL && curr->SW == NULL && curr->SE == NULL) {
		delete curr;
        curr = nullptr;
	} else {
        clear(curr->NW);
        clear(curr->NE);
        clear(curr->SW);
        clear(curr->SE);
    }
}

void quadtree::copy(const quadtree& orig) {
    if (orig.root == nullptr){
        root = nullptr;
    } else {
        //root = new Node(orig.root->upLeft, orig.root->dim, orig.root->avg, orig.root->var);
        copyNode(root, orig.root);
    }
}

void quadtree::copyNode(Node*& currNode, Node * otherNode) {
    if (otherNode == nullptr){
        currNode = nullptr;
        return;
    } else {
     
     currNode = new Node(otherNode->upLeft, otherNode->dim, otherNode->avg, otherNode->var);
     copyNode(currNode->NW, otherNode->NW);
     copyNode(currNode->NE, otherNode->NE);
     copyNode(currNode->SW, otherNode->SW);
     copyNode(currNode->SE, otherNode->SE);
    } 

}