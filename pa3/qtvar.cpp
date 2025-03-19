#include "qtvar.h"

bool qtvar::prunable(Node* node, const int tol) const {
     if (node == NULL) {
	 	return false;
	 } 
	//  	return (node->var <= tol);

	if (node->SE == NULL && node->SW == NULL && node->NE == NULL && node->NW == NULL) {
		if (node->var <= tol) {
			return true;
		}
		return false;
	} else {
		return prunable(node->NW, tol) && prunable(node->NE, tol) && prunable(node->SE, tol) && prunable(node->SW, tol) ;
	}

}


