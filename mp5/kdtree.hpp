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

	//if first point's dim < second's dim smaller dim is true, else not 
     if(first[curDim] < second[curDim]) {
       return true;
     }
     else if(first[curDim] > second[curDim]) {
       return false;
     }

	 //using the point class's operator < to check for equalities.
	 else
		 return first < second;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */

	double d1 = 0;
	double d2 = 0;

	//iterate through values < Dim and calculate the euclidean distance for currBest, and potential
	for(int i = 0; i < Dim; i++) {
		d1 += (target[i] - currentBest[i])*(target[i] - currentBest[i]);
		d2 += (target[i] - potential[i])*(target[i] - potential[i]);
	}

	//if the distance is less for target then do not replace, else replace with potential
    if (d1 < d2) {
       return false;
     }
     else if(d1 > d2){
       return true;
     }
	//use the point class's operator overload to compare for point equalities
	else
		return potential < currentBest;
}
/**
 * buildTree function. This is where the k-d tree is built.
 * This function takes in a start point, an end point and the dimension.
 * It returns a KDTreeNode pointer.
 */
template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::buildTree(int start, int end, int dimension)
{
	if(start > end) return NULL;

	//find median
	int median = (start + end)/2;
	
	//call to quickselect
	quickSelect(start, end, median, dimension);

	//assign new point
	KDTreeNode* p = new KDTreeNode(treePoints[median]);

	//recursively travel left and right to create the tree
	p->left = buildTree(start, median - 1, (dimension+1) % Dim);
	p->right = buildTree(median + 1, end, (dimension+1) % Dim);

	//return the root pointer
	return p;
}

/**
 * implementation of the quickselect function.
 * The implementation is similar to the wikipedia link provided on the MP page.
 * Takes in a start point, an end point, kth index, and the dimension.
 */
template <int Dim>
void KDTree<Dim>::quickSelect(int start, int end, int k, int dimension)
{
	if(start > end) return;
	int pivotIndex = partition(start, end, (start+end)/2, dimension);
	if(k < pivotIndex)
		return quickSelect(start, pivotIndex-1, k, dimension);
	if(k > pivotIndex)
		return quickSelect(pivotIndex+1, end, k, dimension);
}

/**
 * partition function for quickselect.
 * partitions our vector into two parts: those less than the certain elements, and those greater than or equal to the element.
 * takes in a start point, an end point, a pivotIndex, dimension.
 */
template <int Dim>
int KDTree<Dim>::partition(int start, int end, int pivotIndex, int dimension)
{
	Point<Dim> value = treePoints[pivotIndex];
	std::swap(treePoints[pivotIndex], treePoints[end]);
	int storeIndex = start;
	for(int i = start; i < end; i++) {
		if(smallerDimVal(treePoints[i], value, dimension)) {
			std::swap(treePoints[storeIndex], treePoints[i]);
			storeIndex++;
		}
	}
	std::swap(treePoints[end], treePoints[storeIndex]);
	return storeIndex;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
	treePoints = newPoints;
	if(newPoints.size() == 0) {
		root = NULL;
		return;
	}
	
	//function all to build tree to recursively build tree via quickselect algorithm
	root = buildTree(0, newPoints.size() - 1, 0);
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */

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
void KDTree<Dim>::clear(KDTreeNode* subRoot)
{
	//base case
	if(subRoot == NULL) return;

	//recursively destroy the tree
	clear(subRoot->left);
	clear(subRoot->right);

	//the actual removal of the subroot
	delete subRoot;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

	//initialize a point for the nearest point, a dist for checking certain conditions in the nnsHelper
	Point<Dim> nearest;
	double dist = -1;

	//call to the nnsHelper
	nnsHelper(root, query, nearest, dist, 0);
	return nearest;
}

/**
 * Nearest neighbour helper function: within
 * This function checks whether the distance between the current[dimension] and query[dimension] is in range
 */
template <int Dim>
bool KDTree<Dim>::within(Point<Dim> query, Point<Dim> current, double dist, int dimension) const {
  return (dist+query[dimension] >= current[dimension] && query[dimension] - dist <= current[dimension]);
}

/**
 * Nearest neighbor helper function: nnsHelper
 * takes in the root, a query point, a check point (c), the dist, the dimension
 * finds the nearest neighbor to the query point.
 */
template <int Dim>
void KDTree<Dim>::nnsHelper(KDTreeNode* croot, const Point<Dim>& query, Point<Dim>& c, double &dist, int dimension) const
{
  if(!croot) return;

  // of the query is smaller than point at the root, and the left node exists recurse left
  if(smallerDimVal(query, croot->point, dimension)) {

	  //smallerDim value ensures that we only have to travel the left side while going down the tree
	  if(croot->left) {
		  nnsHelper(croot->left, query, c, dist, (dimension+1)%Dim);
	  }
	  // while going down check for the dist flag, if its less than 0 or shouldreplace returns true, change your current best c to croot->point
	  if(dist < 0 || shouldReplace(query, c, croot->point)) {
		  c = croot->point;
		  dist = 0;

		  //calculate the euclidean distance
		  for(int i = 0; i < Dim; i++) {
			  dist += (query[i]-c[i])*(query[i]-c[i]);
		  }
		  //the actual distance is sqrt of the calculated dist above
		  dist = std::sqrt(dist);
	  }
	  
	//while going up after reaching the bottom if dist < 0 or a point within range of radius, traverse the right side
	  if(croot->right && (dist < 0 || within(query, croot->point, dist, dimension))) {
		  nnsHelper(croot->right, query, c, dist, (dimension+1)%Dim);
	  }
  }

  //else if originally our query point was to the right of the root, and the right exists, traverse right
  else {
	  //since root is smaller than the query in this case we recurse to the right side
	  if(croot->right) {
		  nnsHelper(croot->right, query, c, dist, (dimension+1)%Dim);
	  }
	  
	  //similar logic to above
	  if(dist < 0 || shouldReplace(query, c, croot->point)) {
		  c = croot->point;
		  dist = 0;
		  for(int i = 0; i < Dim; i++) {
			  dist += (query[i]-c[i])*(query[i]-c[i]);
		  }
		  dist = std::sqrt(dist);
	  }

	  //if while going up a point to the left is within range, then traverse left and check
	  if(croot->left && within(query, croot->point, dist, dimension)) {
		  nnsHelper(croot->left, query, c, dist, (dimension+1)%Dim);
	  }
  }
}
