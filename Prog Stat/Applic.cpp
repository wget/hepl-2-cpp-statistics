#include <iostream>
using namespace std;
//#include "EtudeStatDescriptive.h"
//#include "ExceptionBase.h"
//#include "Data1D.h"
#include <QApplication>
#include "EtudeStatDescriptive.h"
//#include "Echantillon.h"
QApplication* a;

int main(int argc,char* argv[])
{

printf("Début de l'applic\n");
a = new QApplication(argc,argv);
//try
//{
//Echantillon E;
//E.Affiche();
EtudeStatDescriptive E(argc,argv);
//}
//catch (ExceptionBase e)
//{
//cout << "Err. " << e.getMessage() << endl;
//}
}
