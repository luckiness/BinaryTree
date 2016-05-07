#pragma once
#include<iostream>
#include<stack>
#include<queue>
using namespace std;
template<class T>
//定义二叉树的节点结构体
struct BinaryTreeNode
{
	BinaryTreeNode <T>* _left;
	BinaryTreeNode <T>* _right;
	T _data;
//二叉树节点的构造函数,若去掉引用会构成死循环
	BinaryTreeNode(T &data)
		:_left(NULL)
		,_right(NULL)
		,_data(data)
	{}
};

template<class T>
class BinaryTree
{
private:
	typedef BinaryTreeNode<T> Node;
	Node* _root;

public:
	//无参的构造函数
	BinaryTree()
		:_root(NULL)
	{}
	//带参的构造函数
	BinaryTree( T* a,size_t size,size_t index, const T& Invalid)
	{
		_root=_CreateBinaryTree(a,size,index,Invalid);
	}

//创造二叉树
Node* _CreateBinaryTree( T* a,size_t size,size_t &index,const T& Invalid)
{
	Node* root=NULL;
   if(a[index]!=Invalid&&index<size)
   {
	root=new Node(a[index]);
	root->_left=_CreateBinaryTree(a, size,++index,Invalid);
	root->_right=_CreateBinaryTree(a, size,++index,Invalid);
   }
   return root;
}
//递归先序遍历二叉树
void PrevOrder( )
{
	_PrevOrder(_root);
}
//
	void _PrevOrder(Node* root)
	{
		if(root==NULL)
			return;
		cout<<root->_data<<" ";
		_PrevOrder(root->_left );
		_PrevOrder(root->_right);
	}
//非递归先序遍历
	void PrevOrder_NonR()
	{
	 stack<Node*> s;
	 Node* cur=_root;
	 while(cur||!s.empty())
	 {
	   if(cur)
	   {//先将左子树遍历输出后压栈
	     cout<<cur->_data <<" ";
		 s.push(cur);
		 cur=cur->_left;
	   }
	   else
	   {//当左子树为空时开始访问右子树
	    cur=s.top ();
		s.pop();
		cur=cur->_right;
	   }
	 }
	}


	//递归中序遍历二叉树
	void InOrder()
	{
		_InOrder(_root);
	}
//
	void _InOrder(Node* root)
	{
	  if(root==NULL)
		  return;
	  _InOrder(root->_left );
	  cout<<root->_data <<" ";
	   _InOrder(root->_right );
	}
//非递归中序遍历
	void InOrder_NonR()
	{
	  Node* cur=_root;
	  stack<Node*> s;
		  while(cur||!s.empty())//cur非空或者栈非空
		  {
			if(cur)
			{
			  s.push(cur);//根节点进栈遍历左子书树
			  cur=cur->_left;
			}
			else
			{
			  Node* top=s.top();
			  cout<<top->_data<<" ";
			  s.pop();
			  cur=top->_right;
			}
		  }
		  cout<<endl;
	}

	//递归后续遍历
	void PostOrder()
	{
	_PostOrder(_root);
	}

	void _PostOrder(Node* root)
	{
	  if(root!=NULL)
	  {
	  _PostOrder(root->_left);
	  _PostOrder(root->_right);
	  cout<<root->_data<<" ";
	  }
	}

	//非递归后序遍历
	void PostOrder_NonR()
	{
	  stack<Node*> s;
	  Node* cur=_root;
	  Node* prev=NULL;//设置标志域
	  s.push(_root);
	  while(!s.empty())
	  {
			cur=s.top();
			//
			if((cur->_left ==NULL&&cur->_right ==NULL)
				||(prev!=NULL&&(prev==cur->_left ||prev ==cur->_right )))
			{
			  cout<<cur->_data<<" ";
			  prev=cur;
			  s.pop();
			}

			else
			{
			if(cur->_right!=NULL)
			  s.push(cur->_right);
		    if(cur->_left!=NULL)
 			  s.push(cur->_left); 
			}
	  }
	}

	//层序遍历二叉树
	void Leve1Order()
	{
	 queue<Node*>q;
	 if(_root!=NULL)
	 {
		 q.push(_root);
	 }
	while(!q.empty())
		{
		   Node* front=q.front();
		   cout<<front->_data <<" ";
		   if(front->_left!=NULL)
			q.push(front->_left);
		   if(front->_right!=NULL)
			q.push(front->_right);
		   q.pop();
		 }
	 cout<<endl;
	}
	
	//求二叉树节点的个数
	/*size_t Size()
	{
	return _Size(_root);

	}

	size_t _Size(Node* root)
	{
	  if(root==NULL)
		  return 0;
	  return 1+_Size(root->_left)+_Size(root->_right);
	}*/
	//
	size_t Size()
	{
	  return _Size(_root);
	}
	//
	size_t _Size(Node* root)
	{
	  static size_t Ssize=0;
	  if(root==NULL)
		  return 0;
	  ++Ssize;
	  _Size(root->_left);
	  _Size(root->_right);
	  return Ssize;
	}

	//二叉树的深度
	size_t Depth()
	{
	return _Depth(_root);
	}

	size_t _Depth(Node* root)
	{
		if(root==NULL)
		return 0;
	     size_t left=_Depth(root->_left )+1;
		 size_t right=_Depth(root->_right)+1;
		return (left>right)?left:right;
	}

	//递归求二叉树叶子节点的个数
	size_t LeafSize()
	{
	  return _LeafSize(_root);
	}

	//
	size_t _LeafSize(Node* root)
	{
	  if(root==NULL)
		  return 0;
	  if(root->_left  ==NULL&&root->_right ==NULL)
	  {
	    return 1;
	  }
	  return _LeafSize(root->_left )+_LeafSize(root->_right );
	}
};



void test()
{
	int arr[10]={1,2,3,'#','#',4,'#','#',5,6};
	BinaryTree<int>bt(arr,10,0,'#');

	cout<<"先序递归遍历：";
	bt.PrevOrder();
	cout<<endl;
	cout<<"先序非递归遍历：";
	bt.PrevOrder_NonR();
	cout<<endl;

	cout<<"中序递归遍历：";
	bt.InOrder();
	cout<<endl;
	cout<<"中序非递归遍历：";
	bt.InOrder_NonR();
	cout<<endl;

	cout<<"后序递归遍历：";
	bt.PostOrder();
	cout<<endl;
	cout<<"后序非递归遍历：";
	bt.PostOrder_NonR();
	cout<<endl;

	cout<<"层序遍历二叉树：";
	bt.Leve1Order();
	cout<<endl;

	cout<<"二叉树的大小："<<bt.Size()<<endl;
	cout<<"二叉树的深度："<<bt.Depth()<<endl;
	cout<<"二叉树叶子节点个数："<<bt.LeafSize()<<endl;
}


int main()
{
	test();
  getchar();
  return 0;
}

