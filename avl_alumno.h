#ifndef AVL_ALUMNO_H_
#define AVL_ALUMNO_H_

#include <string>
#include <sstream>
#include <iostream>

#include "alumno.h"

template <class T> class AVL;

template <class T>
class TreeNode {
private:
	Alumno *persona;//T value;

	//TreeNode *left, *right;
  //int level, balance;

  
  TreeNode<T> *leftMatricula,*rightMatricula;
  int levelMatricula, balanceMatricula;

  friend class AVL<T>;

public:
	TreeNode(Alumno*);
	void add(Alumno*);
	//bool find(T) const;
  bool findMatricula(std::string) const;
	void removeChilds();
	void inorderMatricula(std::stringstream&) const;
	void preorderMatricula(std::stringstream&) const;
  //int max_depth();
  int max_depth_mat();
  TreeNode<T>* check_tree_mat(std::string*, TreeNode<T>*, bool*);
  TreeNode<T>* balance_tree_mat();
  TreeNode<T>* rot_left_mat(TreeNode<T>*);
  TreeNode<T>* rot_right_mat(TreeNode<T>*);
  TreeNode<T>* rot_left_right_mat(TreeNode<T>*);
  TreeNode<T>* rot_right_left_mat(TreeNode<T>*);

};

template <class T>
TreeNode<T>::TreeNode(Alumno *per):persona(per),leftMatricula(0),rightMatricula(0),levelMatricula(0),balanceMatricula(0) {std::cout<<"ZZZZZZZZZZZZZZ"<<std::endl;}

template <class T>
void TreeNode<T>::add(Alumno *per) {
  if(per->getMatricula()<persona->getMatricula())
  {
    if(leftMatricula != 0)
      leftMatricula->add(per);
    else
      leftMatricula = new TreeNode<T> (per);
  }
  else
  {
    if(rightMatricula != 0)
      rightMatricula->add(per);
    else
      rightMatricula = new TreeNode<T> (per);
  }
}

/*template <class T>
bool TreeNode<T>::find(T val) {
  if(val == value)
    return true;
  else if(val < value)
    return(left!=0 && left->find(val));
  else if(val > value)
    return (right!=0 && right->find(val));
	return false;
}*/

template <class T>
bool TreeNode<T>::findMatricula(std::string mat) const
{
  if(mat == persona->getMatricula())
    return true;
  else if(mat < persona->getMatricula())
    return(leftMatricula!=0 && leftMatricula->findMatricula(persona->getMatricula()));
  else if(mat > persona->getMatricula())
    return (rightMatricula!=0 && rightMatricula->findMatricula(persona->getMatricula()));
	return false;
}

template <class T>
void TreeNode<T>::removeChilds() {
  if(rightMatricula != 0)
  {
    rightMatricula->removeChilds(); 
    delete rightMatricula;
    rightMatricula = 0;
  }
  if(leftMatricula != 0)
  {
    leftMatricula->removeChilds(); 
    delete leftMatricula;
    leftMatricula = 0;
  }
}

template <class T>
void TreeNode<T>::inorderMatricula(std::stringstream &aux) const {
	if (leftMatricula != 0) {
		leftMatricula->inorderMatricula(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << persona->getMatricula();
	if (rightMatricula != 0) {
		rightMatricula->inorder(aux);
	}
}

template <class T>
void TreeNode<T>::preorderMatricula(std::stringstream &aux) const {
	aux << persona->getMatricula();
	if (leftMatricula != 0) {
		aux << " ";
		leftMatricula->preorderMatricula(aux);
	}
	if (rightMatricula != 0) {
		aux << " ";
		rightMatricula->preorderMatricula(aux);
	}
}

/*template <class T>
int TreeNode<T>::max_depth()
{
  int le=0, ri=0;
  if(left!=0)
    le = left->max_depth() + 1;
  if(right!=0)
    ri = right->max_depth()+1;
  if(le>ri)
    level = le;
  else 
    level = ri;
  balance = le - ri;
  return level;
}*/

template <class T>
int TreeNode<T>::max_depth_mat()
{
  int le=0, ri=0;
  if(leftMatricula!=0)
    le = leftMatricula->max_depth_mat() + 1;
  if(rightMatricula!=0)
    ri = rightMatricula->max_depth_mat()+1;
  if(le>ri)
    levelMatricula = le;
  else 
    levelMatricula = ri;
  balanceMatricula = le - ri;
  return levelMatricula;
}

//Checa si hay o no irregularidad
//a es el nodo balanceado
template <class T>
TreeNode<T>* TreeNode<T>::check_tree_mat(std::string *check_val,TreeNode<T> *parent, bool *checked)
{
  std::cout<<"node value "<<persona->getMatricula()<<" "<<levelMatricula<<" "<<balanceMatricula<<std::endl;
  TreeNode<T> *le=0, *ri=0, *a=0;
  if(leftMatricula != 0)
    le = leftMatricula->check_tree_mat(check_val,this,checked);
  if(rightMatricula!=0)
    ri = rightMatricula->check_tree_mat(check_val,this,checked);
  if(*checked == false)
  {
    if(balanceMatricula > 1)
    {
      a = balance_tree_mat();
      *check_val = persona->getMatricula();
      *checked = true;
      if(parent!=0)
      {
        std::cout<<"parent "<<parent->persona->getMatricula()<<" parent->left "<<parent->leftMatricula->persona->getMatricula()<<std::endl;
        parent->leftMatricula = a;
      }
    }
    else if(balanceMatricula < -1)
    {
      a = balance_tree_mat();
      *check_val = persona->getMatricula();
      *checked = true;
      if(parent!=0)
      {
        std::cout<<"parent "<<parent->persona->getMatricula()<<" parent->right "<<parent->rightMatricula->persona->getMatricula()<<std::endl;
        parent->rightMatricula = a;
      }
    }
  }
  return a;
}

template <class T>
TreeNode<T>* TreeNode<T>::balance_tree_mat()
{
  TreeNode<T> *a = this, *le = leftMatricula, *ri=rightMatricula;
  std::string old_value=persona->getMatricula();
  std::cout<<"a: "<<a->persona->getMatricula()<<" ";
  if(balanceMatricula>0)
  {
    if(le->balanceMatricula>0)
    {
      std::cout<<"rot_right "<<a->balanceMatricula<<" left "<<le->balanceMatricula<<std::endl;
      a=rot_right_mat(a);
    }
    else
    {
      std::cout<<"rot_left_right "<<a->balanceMatricula<<"left: "<<le->balanceMatricula<<std::endl;
      a = rot_left_right_mat(a);
    }
  }
  else
  {
    if(ri->balanceMatricula<0)
    {
      std::cout<<"rot_left "<<a->balanceMatricula<<"right: "<<ri->balanceMatricula<<std::endl;
      a=rot_left_mat(a);
    }
    else
    {
      std::cout<<"rot_right_left "<<a->balanceMatricula<<"right: "<<ri->balanceMatricula<<std::endl;
      a=rot_right_left_mat(a);
    }
  }
  std::cout<<"a value is "<<a->persona->getMatricula()<<std::endl;
  return a;
}

template <class T>
TreeNode<T>* TreeNode<T>::rot_left_mat(TreeNode<T>* a)
{
  TreeNode<T> *b, *temp=0;
  if(a->rightMatricula!=0)
  {
    b=a->rightMatricula;
    if(b->leftMatricula!=0)
      temp=b->leftMatricula;
    b->leftMatricula=a;
    if(temp!=0)
      a->rightMatricula=temp;
    else
      a->rightMatricula=0;
  }
  return b;
}

template <class T>
TreeNode<T>* TreeNode<T>::rot_right_mat(TreeNode<T>* a)
{
  TreeNode<T> *b, *temp=0;
  if(a->leftMatricula!=0)
  {
    b=a->leftMatricula;
    if(b->rightMatricula!=0)
      temp=b->rightMatricula;
    b->rightMatricula=a;
    if(temp!=0)
      a->leftMatricula=temp;
    else
      a->leftMatricula=0;
  }
  return b;
}

template <class T>
TreeNode<T>* TreeNode<T>::rot_left_right_mat(TreeNode<T>* a)
{
  a->leftMatricula=rot_left_mat(a->leftMatricula);
  a = rot_right_mat(a);
  return a;
}

template <class T>
TreeNode<T>* TreeNode<T>::rot_right_left_mat(TreeNode<T>* a)
{
  a->rightMatricula=rot_right_mat(a->rightMatricula);
  a = rot_left_mat(a);
  return a;
}

template <class T>
class AVL {
private:
  int amount;
	//TreeNode<T> *root;
  TreeNode<T> *rootMatricula;

public:
	AVL();
	~AVL();
	bool emptyMatricula();
	void add(Alumno*);
	//bool find(T) const; //-------------
  bool findMatricula(std::string) const;
	void removeAll();
	std::string inorderMatricula() const;
	std::string preorderMatricula() const;
};

template <class T>
AVL<T>::AVL()
{
  rootMatricula=0;
  amount=0;
}

template <class T>
AVL<T>::~AVL() {
	removeAll();
}

template <class T>
bool AVL<T>::emptyMatricula() {
  std::cout<<"XXXXXXXXX"<<std::endl;
	if(amount==0)
  {
    std::cout<<"XXXXXXXXX"<<std::endl;
    return true;
  }
  std::cout<<"XXXXXXXXX"<<std::endl;
  return false;
}

template<class T>
void AVL<T>::add(Alumno *per) 
{
  if(!emptyMatricula())
  {
    std::cout<<"11111111"<<std::endl;
    if(!rootMatricula->findMatricula(per->getMatricula()))
    {
      TreeNode<T> *temp;
      //T check_val;
      std::string check_val_mat;
      //bool aux;
      bool aux_mat;
      rootMatricula->add(per);
      rootMatricula->max_depth_mat();
      temp=rootMatricula->check_tree_mat(&check_val_mat,0,&aux_mat);
      std::cout<<"check values matricula "<<check_val_mat<<" vs "<<rootMatricula->persona->getMatricula()<<std::endl;
      if(check_val_mat==rootMatricula->persona->getMatricula())
        rootMatricula=temp;
      rootMatricula->max_depth_mat();
      amount++;
    }
  }
  else
    {
    std::cout<<"22222222222"<<std::endl;
    rootMatricula= new TreeNode<T>(per);
    amount++;
    }
}

template <class T>
void AVL<T>::removeAll() {
  if(rootMatricula!=0)
    rootMatricula->removeChilds();
  delete rootMatricula;
  rootMatricula = 0;
}

/*template <class T>
bool AVL<T>::find(T val) const {
  if(root!=0)
    return root->find(val);
  return false;
}*/

template <class T>
bool AVL<T>::findMatricula(std::string mat) const
{
  if(rootMatricula!=0)
    return rootMatricula->findMatricula(mat);
  return false;
}

template <class T>
std::string AVL<T>::inorderMatricula() const {
	std::stringstream aux;

	aux << "[";
	if (!emptyMatricula()) {
		rootMatricula->inorderMatricula(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string AVL<T>::preorderMatricula() const {
	std::stringstream aux;

	aux << "[";
	if (!emptyMatricula()) {
		rootMatricula->preorderMatricula(aux);
	}
	aux << "]";
	return aux.str();
}

#endif 
