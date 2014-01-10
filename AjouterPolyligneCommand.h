/*************************************************************************
                           Polyligne  -  description
                             -------------------
    début                : 20 déc. 2013
    copyright            : (C) 2013 par kantoine
*************************************************************************/

//---------- Interface de la classe <Polyligne> (fichier Polyligne.h) ------
#if ! defined ( AJOUTERPOLYLIGNECOMMANDE_H_ )
#define AJOUTERPOLYLIGNECOMMANDE_H_

//--------------------------------------------------- Interfaces utilisées
#include "Modele.h"
#include "Command.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Polyligne>
//
//
//------------------------------------------------------------------------

class AjouterPolyligneCommand : public Command
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
	 AjouterPolyligneCommand (string fname,string fcommande, vector<pair<int,int> > fligne);
     // Mode d'emploi :
     //
     // Contrat :
     //


	void Execute (Modele& fmodele);
    // Mode d'emploi :
    //
    // Contrat :
    //

    void Undo (Modele& fmodele);
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~AjouterPolyligneCommand ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
string name,commande;
vector<pair<int,int> > lignes;
};

//--------------------------- Autres définitions dépendantes de <AjouterPolyligneCommand>

#endif // AjouterPolyligneCommand_H_