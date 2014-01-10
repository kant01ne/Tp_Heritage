/*************************************************************************
                           Rectangle  -  description
                             -------------------
    début                : 20 déc. 2013
    copyright            : (C) 2013 par kantoine
*************************************************************************/

//---------- Interface de la classe <Rectangle> (fichier Rectangle.h) ------
#if ! defined ( AJOUTERRECTANGLECOMMANDE_H_ )
#define AJOUTERRECTANGLECOMMANDE_H_

//--------------------------------------------------- Interfaces utilisées
#include "Modele.h"
#include "Command.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Rectangle>
//
//
//------------------------------------------------------------------------

class AjouterRectangleCommand : public Command
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
	 AjouterRectangleCommand (string fname,string fcommande, int fx1, int fy1,int fx2,int fy2);
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

    virtual ~AjouterRectangleCommand ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
string name,commande;
int x1,y1,x2,y2;
};

//--------------------------- Autres définitions dépendantes de <AjouterRectangleCommand>

#endif // AjouterRectangleCommand_H_