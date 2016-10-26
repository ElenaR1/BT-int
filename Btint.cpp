//https://www.youtube.com/watch?v=ozBhVQNSJ9E&index=15&list=PLTxllHdfUq4d-DE16EDkpeb8Z68DU7Z_Q paul programming
#include <iostream>
#include <string.h>
#include <assert.h>

using namespace std;

struct node {
	int data;
	node* left;//we create 2 pointers. The pointer left points to a node
	node*right;
};
class bst {
private:
	node*root;
	node*parent;
	node*child;
	node*leaf;
	node*createLeaf(int newdata)
	{
		node*n = new node;
		n->data = newdata;
		n->left = NULL;
		n->right = NULL;
		return n;
	}
	void addLeafPrivate(int addData, node* curPtr)
	{

		if (root == NULL)
		{
			root = createLeaf(addData);//it points to the newly created leaf(to the return value of the function). Natam nakudeto
			//i  n sochi
		}
		else if (addData < root->data)
		{
			if (curPtr->left != NULL)//ako 1viq element nalqvo sochi kum neshto
			{
				addLeafPrivate(addData, curPtr->left);
			}
			else
			{
				curPtr->left = createLeaf(addData);//we make the left pointer point to a newly created node
			}
		}
		else if (addData > root->data)
		{
			if (curPtr->right != NULL)//ako 1viq element nalqvo sochi kum neshto
			{
				addLeafPrivate(addData, curPtr->right);
			}
			else
			{
				curPtr->right = createLeaf(addData);//we make the left pointer point to a newly created node
			}
		}
		else {
			cout << "the data " << addData << " has already been added" << endl;
		}
	}
	//kak raboti
	void printInOrderPrivate(node* ptr)
	{
		if (root != NULL)
		{
			if (ptr->left != NULL)
			{
				printInOrderPrivate(ptr->left);
			}
			cout << ptr->data << endl;//shte cout-ne data-ta na na posledniq element kum koito sochi tekushtiq ptr
			if (ptr->right != NULL)
			{
				printInOrderPrivate(ptr->right);
			}
		}
		else
		{
			cout << "the tree is empty" << endl;
		}
	}

	void simplePrintPrivate(node* subTreeRoot)
	{
		if (subTreeRoot == NULL)
		{
			return;
		}
		else
		{
			cout << subTreeRoot->data << " ";
			simplePrintPrivate(subTreeRoot->left);
			simplePrintPrivate(subTreeRoot->right);
		}
	}
	node* returnNodePrivate(int ddata,node* ptr)
	{
		if (ptr != NULL)
		{
			if (ptr->data == ddata)
			{
				return ptr;
			}
			else
			{
				if (ddata < ptr->data)
				{
					return returnNodePrivate(ddata, ptr->left);
				}
				else {
					return returnNodePrivate(ddata, ptr->right);
				}
			}
		}
		else
		{
			return NULL;
		}
	}
	int findSmallestDataPrivate(node*subTreeRoot)
	{
		if (subTreeRoot == NULL)
		{
			cout << "tree is empty \n";
			return -100;
		}
		else
		{
			if (subTreeRoot->left != NULL)
			{
				return findSmallestDataPrivate(subTreeRoot->left);
			}
			return subTreeRoot->data;
		}
	}
	void removeRootMatch()
	{
		if (root != NULL)
		{
			node* delPtr = root;//it points to where the root ptr is pointing
			int rootData = root->data;
			int smallestRightSubTreeData;
			//root has 0 children
			if (root->left == NULL&&root->right == NULL)
			{
				root = NULL;//we make root ptr point to null
				delete delPtr;//we delete the node that used to be the root node by delete the delPtr which points to the 1st elem
			}
			//it has 1 child
			else if (root->left == NULL&&root->right != NULL)
			{
				root = root->right;//the root ptr is pointing to the root's right child now.The new root is the right child
				//the delPtr is still pointing to the root and we have to delete it
				delPtr->right = NULL;//we are completely disconnecting the root node from the tree
				delete delPtr;
				cout << "the root node with data " << rootData << " was deleted and the new root contains data: " << root->data;
			}
			else if (root->left != NULL&&root->right == NULL)
			{
				root = root->left;//the root ptr is pointing to the root's right child now.The new root is the right child
								   //the delPtr is still pointing to the root and we have to delete it
				delPtr->left = NULL;//we are completely disconnecting the root node from the tree
				delete delPtr;
				cout << "the root node with data " << rootData << " was deleted and the new root contains data: " << root->data;
			}
			//it has 2 children
			else
			{
				smallestRightSubTreeData = findSmallestDataPrivate(root -> right);//it will find the smallest data in the right subtree
				removeNodePrivate(smallestRightSubTreeData,root);//it removes the node that contains this value
				root->data = smallestRightSubTreeData;
				cout << "the root containing " << rootData << " was overwritten with data "<<root->data << endl;
			}
		}
		else 
		{
			cout << "empty";
		}
	}
	void removeMatch(node*parent, node*match, bool left)//the node we're looking for is gonna be matched with the match ptr
		//if bool is true that means that the match node is the left child of the parent node if it doesn't is the right child
	{
		if (root != NULL)
		{
			node*delPtr;
			int matchData = match->data;//we grab the data that is contained in the current node that we want to delete
			int smallestRightsubtreeData;//in case the node we want to del has 2 children
			//case 0 our matching node has 0 children
			if (match->left == NULL&&match->right == NULL)
			{
				delPtr = match;
				left == true ? parent->left = NULL : parent->right = NULL;//parent node-a izobshto ne se svurzva s match node-a
				delete delPtr;
				cout << "the node containing " << matchData << "was removed" << endl;
			}
			//1 child
			else if(match->left == NULL&&match->right != NULL)
			{
				left == true ? parent->left = match->right : parent->right = match->right;
				match->right = NULL;//we disconnect our node from the tree
				delPtr = match;
				delete delPtr;
				cout << "the node containing " << matchData << "was removed" << endl;
			}
			else if (match->left != NULL&&match->right == NULL)
			{
				left == true ? parent->left = match->left : parent->right = match->left;
				match->left = NULL;//we disconnect our node from the tree
				delPtr = match;
				delete delPtr;
				cout << "the node containing " << matchData << "was removed" << endl;
			}
			//2 children
			else
			{
				smallestRightsubtreeData = findSmallestDataPrivate(match->right);
				removeNodePrivate(smallestRightsubtreeData,match);//we remove the node containing this variable
				match->data = smallestRightsubtreeData;//we don't exactly delete the math node but we overwrite its data value
			}
		}
		else
		{
			cout << "empty";
		}
	}
	void removeNodePrivate(int removeData, node* parent)
	{
		if (root != NULL)
		{
			if (root->data == removeData)
			{
				removeRootMatch();
			}
			else
			{
				if (removeData < parent->data&&parent->left != NULL)
				{
					parent->left->data == removeData ?
						removeMatch(parent,parent->left,true):
						removeNodePrivate(removeData, parent->left);
				}
				else if (removeData > parent->data&&parent->right != NULL)
				{
					parent->right->data == removeData ?
						removeMatch(parent,parent->right,false):
						removeNodePrivate(removeData, parent->right);
				}
				else
				{
					cout << "the data " << removeData << "is not in the tree";
				}
			}
		}
		else
		{
			cout << "the tree is empty" << endl;
		}
	}
	//ne razbiram
	void removeSubTree(node *ptr)
	{
		if (ptr != NULL)
		{
			if (ptr->left != NULL)
			{
				removeSubTree(ptr->left);
			}
			if (ptr->right != NULL)
			{
				removeSubTree(ptr->right);
			}
			cout <<"deleting the node containing the data "<< ptr->data << endl;
			delete ptr;//tozi na dunoto. No kak se triqt i drugite ??
		}
	}
public:
	bst()
	{
		root = NULL;
	}
	void addLeaf(int newData)
	{
		addLeafPrivate(newData, root);
	}
	void printInOrder()
	{
		printInOrderPrivate(root);
	};
	void simplePrint()
	{
		simplePrintPrivate(root);
	}
	node* returnNode(int ddata)
	{
		return returnNodePrivate(ddata, root);// trqbva da si return-em zashtoto si e takava funkciqta
	}
	int returnRootData()
	{
		if (root != NULL)
		{
			return root->data;
		}
		else
		{
			return -1000;
		}
	}
	void printChildren(int Data)
	{
		node *ptr = returnNode(Data);//shte point-va kum tozi node koito sudurja tazi Data
		if (ptr != NULL)
		{
			cout << "parent node = " << ptr->data << endl;
			//a<b ? code1:code2
			ptr->left == NULL ?
				cout << "left child = NULL\n" :
				cout << "left child = " << ptr->left->data << endl;

			
			ptr->right == NULL ?
				cout << "right child = NULL\n" :
				cout << "right child = " << ptr->right->data << endl;
		}
		else
		{
			cout << "the data " << Data << "is not in the tree"<<endl;
		}
	}
	int findSmallestData()
	{
		return findSmallestDataPrivate(root);
	}
	void removeNode(int removeData)
	{
		removeNodePrivate(removeData, root);
	}
	~bst()
	{
		removeSubTree(root);
	}
};
int main()
{
	bst t1;
	t1.addLeaf(10);
	t1.addLeaf(12);
	t1.addLeaf(15);
	t1.addLeaf(16);
	t1.addLeaf(8);
	t1.addLeaf(6);
	//t1.printInOrder();
	t1.simplePrint();
	cout << endl;
	//t1.printChildren(t1.returnRootData());
	//cout<<t1.findSmallestData();
//	t1.removeNode(15);
//	t1.simplePrint();

	//tova mai ne raboti pravilno
	/*int treeData[10] = { 20,7,8,19,40,3,32,1,11,22 };
	for (size_t i = 0; i < 10; i++)
	{
		t1.addLeaf(treeData[i]);
	}
	t1.simplePrint();
	cout << endl;
	t1.printInOrder();//ne raboti
	cout << endl;
	cout << endl;
	for (size_t i = 0; i < 10; i++)
	{
		t1.printChildren(treeData[i]);
		cout << endl;
	*/
	return 0;
}
