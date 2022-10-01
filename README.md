# Generic tree
General purpose tree library.
1. include Generic tree.h
2. to construct a Generic tree you need to specify the following:
   - The number of nodes in the tree.
   - add edge between nodes and corresponding weight.

3. Example usage:
   - Tree A (n);// tree of size n;
   - A.add_edge(a,b,wt);// edge between a and b , wt edge weight
   - A.kth_ancestor(a,k); // return kth ancestor of a.
   - A.LCA(a,b); // return lca for node a and b.
   - A.eluer(a);//do eluer dsf by making a as root node, intialize eluer array
   - A.level(a);// return level of a node


