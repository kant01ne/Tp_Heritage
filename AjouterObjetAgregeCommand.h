/*************************************************************************
                           ObjetAgrege  -  description
                             -------------------
    début                : 20 déc. 2013
    copyright            : (C) 2013 par kantoine
*************************************************************************/

//---------- Interface de la classe <ObjetAgrege> (fichier ObjetAgrege.h) ------
#if ! defined ( AJOUTEROBJETAGREGECOMMANDE_H_ )
#define AJOUTEROBJETAGREGECOMMANDE_H_

//--------------------------------------------------- Interfaces utilisées
#include "Modele.h"
#include "Command.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <ObjetAgrege>
//
//
//------------------------------------------------------------------------

class AjouterObjetAgregeCommand : public Command
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
	 AjouterObjetAgregeCommand (vector<string> flisteObjet, string fname,string fcommande);
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

    virtual ~AjouterObjetAgregeCommand ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
string name,commande;
vector<string> listeObjet;
};

//--------------------------- Autres définitions dépendantes de <AjouterObjetAgregeCommand>

#endif // AjouterObjetAgregeCommand_H_