#include <iostream>
#include <fstream>
#include <string>

#include "avl_alumno.h"
#include "alumno.h"

void plantarAlumnos(AVL<Alumno>*);

int main()
{
  /*AVL<int> arbol;
  arbol.add(8);
  arbol.add(14);
  arbol.add(6);
  arbol.add(1);
  std::cout<<arbol.inorder();*/
  
  AVL<Alumno> *student_tree;
  plantarAlumnos(student_tree);
}

void plantarAlumnos(AVL<Alumno> *tree)
{
  std::ifstream reader("datos_alumnos.csv"); 
  if(reader.is_open())
  {
    while(reader.good())
    {
      std::string l1,l2,l3,l4,l5;
      getline(reader,l1,',');
      getline(reader,l2,',');
      getline(reader,l3,',');
      getline(reader,l4,',');
      getline(reader,l5,'\n');
      //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      //Cambiar para crear el objeto solo si la matricula, l2, no se encuentra en el arbol
      std::cout<<"AAAAAAAAAA"<<std::endl;
      Alumno *temporal = new Alumno(l1,l2,std::stof(l3),std::stof(l4),std::stof(l5));
      std::cout<<"BBBBBBBB"<<std::endl;
      tree->add(temporal);
      std::cout<<"CCCCCCCCCCC"<<std::endl;
    }
  }
  else
    std::cout<<"ERROR: No se puede abrir el archivo"<<std::endl;
}