#include "qtcount.h"

bool qtcount::prunable(Node* node, const int tol) const {
	return prunableHelper(node, tol, node->avg);
}

bool qtcount::prunableHelper(Node* node, const int tol, RGBAPixel avgNode) const {
   if (node == NULL) {
		return false;
	}
	if (node->SE == NULL && node->SW == NULL && node->NE == NULL && node->NW == NULL){
		if ((pow((node->avg.r - avgNode.r),2) + pow((node->avg.g - avgNode.g),2) + pow((node->avg.b - avgNode.b),2)) <= tol) {
			return true;
		}
		return false;
	} else {
		return prunable(node->SE, tol) && prunable(node->SW, tol) && prunable(node->NE, tol) && prunable(node->NW, tol);
	}
	// return true;
}
