#pragma once
#include<iostream>
#include<stack>
#include<queue>
using namespace std;
template<class T>
//����������Ľڵ�ṹ��
struct BinaryTreeNode
{
	BinaryTreeNode <T>* _left;
	BinaryTreeNode <T>* _right;
	T _data;
//�������ڵ�Ĺ��캯��,��ȥ�����ûṹ����ѭ��
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
	//�޲εĹ��캯��
	BinaryTree()
		:_root(NULL)
	{}
	//���εĹ��캯��
	BinaryTree( T* a,size_t size,size_t index, const T& Invalid)
	{
		_root=_CreateBinaryTree(a,size,index,Invalid);
	}

//���������
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
//�ݹ��������������
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
//�ǵݹ��������
	void PrevOrder_NonR()
	{
	 stack<Node*> s;
	 Node* cur=_root;
	 while(cur||!s.empty())
	 {
	   if(cur)
	   {//�Ƚ����������������ѹջ
	     cout<<cur->_data <<" ";
		 s.push(cur);
		 cur=cur->_left;
	   }
	   else
	   {//��������Ϊ��ʱ��ʼ����������
	    cur=s.top ();
		s.pop();
		cur=cur->_right;
	   }
	 }
	}


	//�ݹ��������������
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
//�ǵݹ��������
	void InOrder_NonR()
	{
	  Node* cur=_root;
	  stack<Node*> s;
		  while(cur||!s.empty())//cur�ǿջ���ջ�ǿ�
		  {
			if(cur)
			{
			  s.push(cur);//���ڵ��ջ������������
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

	//�ݹ��������
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

	//�ǵݹ�������
	void PostOrder_NonR()
	{
	  stack<Node*> s;
	  Node* cur=_root;
	  Node* prev=NULL;//���ñ�־��
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

	//�������������
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
	
	//��������ڵ�ĸ���
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

	//�����������
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

	//�ݹ��������Ҷ�ӽڵ�ĸ���
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

	cout<<"����ݹ������";
	bt.PrevOrder();
	cout<<endl;
	cout<<"����ǵݹ������";
	bt.PrevOrder_NonR();
	cout<<endl;

	cout<<"����ݹ������";
	bt.InOrder();
	cout<<endl;
	cout<<"����ǵݹ������";
	bt.InOrder_NonR();
	cout<<endl;

	cout<<"����ݹ������";
	bt.PostOrder();
	cout<<endl;
	cout<<"����ǵݹ������";
	bt.PostOrder_NonR();
	cout<<endl;

	cout<<"���������������";
	bt.Leve1Order();
	cout<<endl;

	cout<<"�������Ĵ�С��"<<bt.Size()<<endl;
	cout<<"����������ȣ�"<<bt.Depth()<<endl;
	cout<<"������Ҷ�ӽڵ������"<<bt.LeafSize()<<endl;
}


int main()
{
	test();
  getchar();
  return 0;
}

