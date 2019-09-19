/* Your code here! */
#include "dsets.h"
#include <vector>

/**
	Creates n unconnected root nodes at the end of the vector.
	@param num The number of nodes to create
*/
void DisjointSets::addelements(int num)
{
  for(int i = 0; i < num; i++) {
    v.push_back(-1);
  }
}

/**
	This function should compress paths and works as described in lecture.
	@param elem The element to find
	@return The index of the root of the up-tree in which elem resides
*/
int DisjointSets::find(int elem)
{
  if(v[elem] < 0) {
    return elem;
  }
  else {
    int root = find(v[elem]);
    v[elem] = root;
    return root;
  }
}

/**
	This function should be implemented as union-by-size.

	That is, when you setunion two disjoint sets,
	the smaller (in terms of number of nodes) should point at the larger.
	This function works as described in lecture,
	except that you should not assume that the arguments to
	setunion are roots of existing v.

	Your setunion function SHOULD find the roots of its arguments
	before combining the trees.
	If the two sets are the same size, make the tree containing the second argument
	point to the tree containing the first.

	@param a Index of the first element to union
	@param b Index of the second element to union
*/
void DisjointSets::setunion(int a, int b)
{
  int r1 = find(a);
  int r2 = find(b);

  int newSize = v[r1] + v[r2];

  if(v[r1] < v[r2]) {
    v[r2] = r1;
    v[r1] = newSize;
  }
  else {
    v[r1] = r2;
    v[r2] = newSize;
  }
}

/**
	This function should return the number of nodes in the up-tree containing the element.
	@param elem The elem to return size of
*/
int DisjointSets::size(int elem)
{
  return v[find(elem)] * -1;
}
