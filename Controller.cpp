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
	if (mots.size()==0)
	{
		cout << "ERR" << endl << " #Invalid Parameters"<<endl;
		return false;
	}
	if (mots.size()==1)
	{
		if (mots[0]=="LIST")
		{
			this->EnumererObjet();
			return true;
		}
		if (mots[0]=="CLEAR")
		{
			this->ExecuterCommand(new ClearCommand(modele));
			return true;
		}
		if (mots[0]=="UNDO")
		{
			this->Undo();
			return true;
		}
		if (mots[0]=="REDO")
		{
			this->Redo();
			return true;
		}
	}
	else if ( (mots.size()==2) and (mots[0]=="SAVE")  )
	{
		modele.Sauvegarder(mots[1]);
	}
	else if ( (mots.size()==2) && (mots[0]=="LOAD")  )
	{
		this->ExecuterCommand(new ChargerCommand(mots[1], this));
		return true;
	}
	else if ( (mots.size()==4) && (mots[0]=="MOVE") && (atoi(mots[2].c_str())) && (atoi(mots[3].c_str())) && (this->ObjetExistant(mots[1])) )
	{
		this->ExecuterCommand( new TranslaterCommand(atoi(mots[2].c_str()),atoi(mots[3].c_str()),mots[1].c_str() ) );
		return true;
	}
	else if ( (mots[0]=="DELETE") && (mots.size()>1) )
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
	else if ( (mots[0]=="OA") && (mots.size()>2) && (!this->ObjetExistant(mots[1])) )
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
	else if ( (mots[0]=="C") and (mots.size()==5) and (atoi(mots[2].c_str())) and (atoi(mots[3].c_str())) and (atoi(mots[4].c_str())>0) and (!this->ObjetExistant(mots[1])) )
	{
		this->ExecuterCommand(new AjouterCercleCommand(mots[1],commande,
													 	 atoi(mots[2].c_str()),
													 	 atoi(mots[3].c_str()),
														 atoi(mots[4].c_str())
													));
		return true;
	}

	else if ( (mots[0]=="R") && (mots.size()==6) && (atoi(mots[2].c_str())) && (atoi(mots[3].c_str())) && (atoi(mots[4].c_str())) && (atoi(mots[5].c_str())) && (!this->ObjetExistant(mots[1])) )
	{
		this->ExecuterCommand(new AjouterRectangleCommand(mots[1],commande,
														atoi(mots[2].c_str()),
														atoi(mots[3].c_str()),
														atoi(mots[4].c_str()),
														atoi(mots[5].c_str())
		));
		return true;
	}
	else if ( (mots[0]=="L") && (mots.size()==6) && (atoi(mots[2].c_str())) && (atoi(mots[3].c_str())) && (atoi(mots[4].c_str())) && (atoi(mots[5].c_str())) && (!this->ObjetExistant(mots[1])) )
	{
		this->ExecuterCommand(new AjouterLigneCommand(mots[1],commande,
														atoi(mots[2].c_str()),
														atoi(mots[3].c_str()),
														atoi(mots[4].c_str()),
														atoi(mots[5].c_str())
		));
		return true;
	}
	else if ( (mots[0]=="PL") && (mots.size()>=4) && (mots.size() % 2 == 0) && (!this->ObjetExistant(mots[1])) )
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
	modele.Execute(command);
} //----- Fin de Méthode

void Controller::Undo()
//Algorithme :
{
	cout << "OK"<< endl;
	modele.Undo();
}

void Controller::Redo()
//Algorithme :
{
	cout << "OK"<< endl;
	modele.Redo();
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
	cout << "# Loading new empty model"<< endl;
} //----- Fin de Méthode



void Controller::Charger(string url)
// Algorithme :
{
	ifstream fichier(url.c_str());
	if ( !fichier.fail() )
	{
		modele.Vider();
		cout << "# Loading new empty model"<< endl;
		string commande;
		while(getline(fichier,commande))
		{
			Validation(commande);
		}
		cout << "# Model loaded" << endl;
	}
	else
	{
		cout << "# File do not exist" << endl;
	}

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


#ifdef MAP
    cout << "Appel au destructeur de <Controller>" << endl;
#endif
} //----- Fin de ~Controller


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
