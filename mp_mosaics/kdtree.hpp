/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
     if (curDim < 0 || curDim > Dim) {
       return false;
     } else if (first[curDim] == second[curDim]) {
      return first < second;
    } else {
        return (first[curDim] < second[curDim]);
    }


}

template <int Dim>
double KDTree<Dim>::getDist(const Point<Dim>& target, const Point<Dim>& currentBest) const {

  double dist = 0;
  for (int i = 0; i < Dim; i++) {
    dist += pow((target[i]-currentBest[i]), 2);
  }

  dist = sqrt(dist);

  return dist;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     double currentDist = getDist(target, currentBest);
     double potentialDist = getDist(target, potential);


     if (currentDist == potentialDist) {
       return potential < currentBest;
     }
     return potentialDist < currentDist;
}

template <int Dim>
unsigned KDTree<Dim>::partition(vector<Point<Dim>>& newPoints, int dimension, unsigned left, unsigned right, unsigned pivotIndex) {

  Point<Dim> pivotValue = newPoints[pivotIndex];

  swap(newPoints[pivotIndex], newPoints[right]);

  unsigned storeIndex = left;

  for (unsigned i = left; i < right; i++) {
      if (smallerDimVal(newPoints[i], pivotValue, dimension)) {
        swap(newPoints[storeIndex], newPoints[i]);
        storeIndex++;
      }
  }
  swap(newPoints[right], newPoints[storeIndex]);
  return storeIndex;
}

template <int Dim>
Point<Dim>& KDTree<Dim>::select(vector<Point<Dim>>& newPoints, int dimension, unsigned left, unsigned right, unsigned k) {

    if (left == right) {
      return newPoints[left];
    }

    unsigned pivotIndex = k;
    pivotIndex = partition(newPoints, dimension, left, right, pivotIndex);

    if (k == pivotIndex) {
      return newPoints[k];
    } else if (k < pivotIndex) {
      return select(newPoints, dimension, left, pivotIndex - 1, k);
    } else {
      return select(newPoints, dimension, pivotIndex + 1, right, k);
    }


}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::helperKDTree(vector<Point<Dim>>& newPoints, int dimension, unsigned left, unsigned right) {
      if (newPoints.empty()  || left < 0 || right < left || right > newPoints.size()) {
        return NULL;
      }

      unsigned mid = (left + right) / 2;

      KDTreeNode* subroot = new KDTreeNode(select(newPoints, dimension % Dim, left, right, mid));

      size++;

      subroot->left = helperKDTree(newPoints, (dimension + 1) % Dim, left, mid - 1);
      subroot->right = helperKDTree(newPoints, (dimension + 1) % Dim, mid + 1, right);

      return subroot;
  }

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */


    vector<Point<Dim>> points;
    points.assign(newPoints.begin(), newPoints.end());
    size = 0;
    root = helperKDTree(points, 0, 0, newPoints.size() - 1);
}



template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
   copy(this->root, other.root);
   size = other.size;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
   if (this != NULL) {
     clear(root);
   }
   	copy(this->root, rhs.root);
   	size = rhs.size;
   	return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   clear(root);

}



template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query, KDTreeNode* subroot, int dimension) const {
  Point<Dim> currentBest = subroot->point;
  bool flag = false;

  if (subroot->left == NULL && subroot->right == NULL) {
    return subroot->point;
  }

  if (smallerDimVal(query, subroot->point, dimension)) {

    if (subroot->left != NULL)  {
      currentBest = findNearestNeighbor(query, subroot->left, (dimension + 1) % Dim);
    } else {
      currentBest = findNearestNeighbor(query, subroot->right, (dimension + 1) % Dim);
    }

    flag = true;
  } else {

    if (subroot->right != NULL)  {
      currentBest = findNearestNeighbor(query, subroot->right, (dimension + 1) % Dim);
    } else {
      currentBest = findNearestNeighbor(query, subroot->left, (dimension + 1) % Dim);
    }

    flag = false;
  }

  if (shouldReplace(query, currentBest, subroot->point)) {
    currentBest = subroot->point;
  }

  double radius = getDist(query, currentBest);

  double splitDist = fabs(subroot->point[dimension] - query[dimension]);

	if (splitDist <= radius) {

  		KDTreeNode * otherRoot;
      if(flag) {
        otherRoot = subroot->right;
      } else {
          otherRoot = subroot->left;
      }

  		if (otherRoot != NULL) {

    			Point<Dim> otherBest = findNearestNeighbor(query, otherRoot, (dimension + 1) % Dim);
    			if (shouldReplace(query, currentBest, otherBest)) {
              currentBest = otherBest;
          }

  		}
	}

  return currentBest;

}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    return findNearestNeighbor(query, root, 0);
}

template <int Dim>
void KDTree<Dim>::clear(KDTreeNode * subroot) {
	if (subroot == NULL) {
    return;
  }
	if (subroot->left != NULL) {
    clear(subroot->left);
  }
  if (subroot->right != NULL) {
    clear(subroot->right);
  }

	delete subroot;
	subroot = NULL;
}

template <int Dim>
void KDTree<Dim>::copy(KDTreeNode * subroot, KDTreeNode * other) {
	subroot = new KDTreeNode();
	subroot->point = other->point;
	copy(subroot->left, other->left);
	copy(subroot->right, other->right);
}
