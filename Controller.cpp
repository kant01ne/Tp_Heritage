/*************************************************************************
                           Controller  -  description
                             -------------------
    début                : 20 déc. 2013
    copyright            : (C) 2013 par kantoine
*************************************************************************/

//---------- Réalisation de la classe <Controller> (fichier Controller.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include "Controller.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iterator>
#include <cassert>
using namespace std;
#include <iostream>
#include <cstdlib>

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

bool Controller::Validation ( string commande )
// Algorithme :
{
	//Decoupe la commande en parametre et ressort chaque mots dans un vecteur de string : mots
	istringstream ss(commande);
	istream_iterator<string> begin(ss), end;
	vector<string> mots(begin, end);
	if (mots.size()==1)
	{
		if (mots[0]=="LIST")
		{
			this->EnumererObjet();
			return true;
		}
		if (mots[0]=="CLEAR")
		{
			this->Vider();
			return true;
		}
		if (mots[0]=="UNDO")
		{
			if (!undo.empty())
			{
				this->Undo();
			}
			else
			{
				cout<< "# No command to execute" <<endl;
			}
		return true;
		}
		if (mots[0]=="REDO")
		{
			if (!redo.empty())
			{
				this->Redo();
			}
			else
			{
				cout<< "# No command to execute" <<endl;
			}
			return true;
		}
	}
	else if ( (mots.size()==2) and ( (mots[0]=="SAVE") or (mots[0]=="LOAD") ) )
	{
		return true;
	}
	else if ( (mots.size()==4) and (mots[0]=="MOVE") and (atoi(mots[2].c_str())) and (atoi(mots[3].c_str())) and (this->ObjetExistant(mots[1])) )
	{
		this->ExecuterCommand( new TranslaterCommand(atoi(mots[2].c_str()),atoi(mots[3].c_str()),mots[1].c_str() ) );
		return true;
	}
	else if ( (mots[0]=="DELETE") and (mots.size()>1) )
	{
		unsigned int i;
		map<string,string> deleteMap;
		 //Ne supprime aucun objet si un objet n'existe pas
		for (i=1;i<mots.size();i++)
		{
			if (!this->ObjetExistant(mots[i]))
			//Si un objet n'existe pas on ne supprime rien
			{
				cout << "ERR"<< endl << "#At least one object do not exist : " << mots[i] << endl;
				return false;
			}
			deleteMap[mots[i].c_str()] = ""; //Reserve un espace pour stockage des commandes
									 //de recréation des objets avec Undo

		}//Fin du for
		this->ExecuterCommand( new DeleteCommand(deleteMap) );
		return true;
	}
	else if ( (mots[0]=="OA") and (mots.size()>2) and (!this->ObjetExistant(mots[1])) )
	{
		vector<string> agrege;
		for (unsigned int i=2; i<mots.size();i++)
		{

			agrege.push_back(mots[i]);
			if (!this->ObjetExistant(mots[i]))
			{

				cout << "ERR"<< endl << "#At least one object do not exist : " << mots[i] << endl;
				return false;
			}
		}
		this->ExecuterCommand( new AjouterObjetAgregeCommand(agrege,mots[1],commande));
		return true;
	}
	else if ( (mots[0]=="C") and (mots.size()==5) and (atoi(mots[2].c_str())) and (atoi(mots[3].c_str())) and (atoi(mots[4].c_str())) and (!this->ObjetExistant(mots[1])) )
	{
		this->ExecuterCommand(new AjouterCercleCommand(mots[1],commande,
													 	 atoi(mots[2].c_str()),
													 	 atoi(mots[3].c_str()),
														 atoi(mots[4].c_str())
													));
		return true;
	}

	else if ( (mots[0]=="R") and (mots.size()==6) and (atoi(mots[2].c_str())) and (atoi(mots[3].c_str())) and (atoi(mots[4].c_str())) and (atoi(mots[5].c_str())) and (!this->ObjetExistant(mots[1])) )
	{
		this->ExecuterCommand(new AjouterRectangleCommand(mots[1],commande,
														atoi(mots[2].c_str()),
														atoi(mots[3].c_str()),
														atoi(mots[4].c_str()),
														atoi(mots[5].c_str())
		));
		return true;
	}
	else if ( (mots[0]=="L") and (mots.size()==6) and (atoi(mots[2].c_str())) and (atoi(mots[3].c_str())) and (atoi(mots[4].c_str())) and (atoi(mots[5].c_str())) and (!this->ObjetExistant(mots[1])) )
	{
		this->ExecuterCommand(new AjouterLigneCommand(mots[1],commande,
														atoi(mots[2].c_str()),
														atoi(mots[3].c_str()),
														atoi(mots[4].c_str()),
														atoi(mots[5].c_str())
		));
		return true;
	}
	else if ( (mots[0]=="PL") and (mots.size()>=4) and (mots.size() % 2 == 0) and (!this->ObjetExistant(mots[1])) )
	{
		unsigned int i;
		for (i=2; i<mots.size();i++)
		{
			if (!atoi(mots[i].c_str())) //Test la validité des arguments integer
			{
				cout << "ERR"<< endl << " #Invalid Parameters"<<endl;
				return false;
			}
		}
		vector<pair<int,int> > lignes;
		pair<int,int> l;
		for (unsigned int i=3;i<mots.size(); i+=2)
			{
				l.first = atoi(mots[i-1].c_str());
				l.second = atoi(mots[i].c_str());
				lignes.push_back(l);//
			}
		this->ExecuterCommand(new AjouterPolyligneCommand(mots[1],commande,lignes));
		return true;
	}

	//Si aucune boucle possédant un retour True n'est rencontrée :
	cout << "ERR" << endl << " #Invalid Parameters"<<endl;
	return false;
} //----- Fin de Méthode


void Controller::ExecuterCommand ( Command *command )
// Algorithme :
{
	cout << "OK"<< endl;
	command->Execute(modele);
	undo.push(command);
} //----- Fin de Méthode

void Controller::Undo()
//Algorithme :
{
	cout << "OK"<< endl;
	undo.top()->Undo(modele);//Execute la fonction Undo de la derniere commande stocké dans la pile
	redo.push(undo.top());//Copie la commande de la pile undo vers redo
	undo.pop();//Supprime la commande de la pile undo
}

void Controller::Redo()
//Algorithme :
{
	cout << "OK"<< endl;
	redo.top()->Execute(modele);//Execute la fonction Execute de la derniere commande stocké dans la pile
	undo.push(redo.top());//Copie la commande de la pile undo vers redo
	redo.pop();//Supprime la commande de la pile undo
}

bool Controller::ObjetExistant(string objet)
// Algorithme :
{
	return modele.ObjetExistant(objet);
} //----- Fin de Méthode

void Controller::EnumererObjet()
// Algorithme :
{
	modele.EnumererCommande();
} //----- Fin de Méthode

void Controller::Vider()
// Algorithme :
{
	cout << "OK"<< endl;
	modele.Vider();
	cout << "# Chargement d'un nouveau modèle vide"<< endl;
} //----- Fin de Méthode



void Controller::Charger(string url)
// Algorithme :
{
	cout << "OK"<< endl;
	modele.Vider();
	cout << "# Chargement d'un nouveau modèle vide"<< endl;
	fichier = ifstream(url);//TODO continuer le chargement d'un fichier

} //----- Fin de Méthode

void Controller::Sauvegarder(string url)
// Algorithme :
{

} //----- Fin de Méthode



//------------------------------------------------- Surcharge d'opérateurs
Controller & Controller::operator = ( const Controller & unController )
// Algorithme :
//
{
	return *this;
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Controller::Controller ( const Controller & unController )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Controller>" << endl;
#endif
} //----- Fin de Controller (constructeur de copie)


Controller::Controller ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Controller>" << endl;
#endif
} //----- Fin de Controller


Controller::~Controller ( )
// Algorithme :
//
{
	for (int i = redo.size();i>0;i--)
	{
		delete redo.top();
	}
	for (int i = redo.size();i>0;i--)
	{
		delete undo.top();
	}


#ifdef MAP
    cout << "Appel au destructeur de <Controller>" << endl;
#endif
} //----- Fin de ~Controller


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
