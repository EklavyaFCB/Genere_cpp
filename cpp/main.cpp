//
//  Genere_CPP.cpp
//  Project de Programation
//  Exercice 6, Semaine 3
//
//  Created by Eklavya Sarkar on 25/03/14.
//  Copyright (c) 2014 Eklavya Sarkar. All rights reserved.
//
/*  This programming projet creates a list of numbers based on the value of the inputs given. The list of numbers
//  are the y-axis value of the points of a sinusodial or square signal.
*/


#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

//Les prototypes des fonctions sont dans les lignes suivantes

int ReadEntier(int &unEntier, char argv[]);

double ReadDouble(double &unDouble, char argv[]);

void sinusodiale (double signal[], int nombre, double amplitude, double offset, double bruit);

void carre (double signal[], int nombre, double amplitude, double offset, double bruit);

double bruitGenere(double bruit);

int main(int argc, char *argv[]) {
    
    /*Les paramètres de la fonctions main(int argc, char *argv[]) permettent de passer des
    arguments depuis la ligne de commande lorsqu'on lance le programme depuis le terminal.*/
    
    srand(static_cast<unsigned int>(time(NULL))); //On initalise la fonction srand() pour générer plus tard le bruit, dans les fonctions sinusodiale et carré. On utilise srand pour ne pas avoir la même suite de nombres aléatoires.
    
    
    if ((argc-1)!=5) { //Vérification de la présence de tout les paramètres
        cerr << "Il faut exactement cinq paramètres en argument." << endl;
        return 1; //S'il n'y a pas 5 arguments, la fonction return arrête la boucle et sort de la fonction main avec un exit code de 1.
    }
    
//  1e argument - la forme
    
    string forme(argv[1]);
    
//  2e argument - le nombre
    
    int unEntier; //Déclaration général d'un entier - ceci sera utilisé pour la conversion en int de l'argument "nombre".
    
    ReadEntier(unEntier, argv[2]); //Appel à la fonction de conversion
    
    int nombre(unEntier); //Validation du nombre de points utilisé pour définir la période du signal. Il vaut la valeur de l'argument 2, convertie en int.
    
    if ((nombre<8) || (nombre>256)) { //On définit les bornes du nombre
        cerr << "L'argument deux (nombre) n'est pas dans la borne de 8 a 256." << endl;
        return 1; //Si l'argument n'est pas dans la borne, ceci arrête la boucle et sort de la fonction main avec un exit code de 1.
    }

    
//  3e argument - l'amplitude
    
    double unDouble; //Déclaration général d'un double - ceci sera utilisé pour les conversions de tout les arguments en doubles, c'est-à-dire, l'amplitude, l'offset et le bruit.
    
    ReadDouble(unDouble, argv[3]); //Appel à la fonction de conversion
    
    double amplitude(unDouble/2); //Validation de l'amplitude du signal. Il vaut la valeur de l'argument 3, convertie en double.
    
    if ((amplitude<0.0) || (amplitude>5.0)){ //On définit les bornes de l'amplitude, qui vont de 0 à 10, même si on écrit 0 à 5, car on divise la valeur de l'argument par deux juste avant. Exemple: unDouble/2 = 5 -> unDouble = 10, la borne vaut bien 10.
        cerr << "L'argument trois (amplitude) n'est pas dans la borne de 0 a 10." << endl;
        return 1; //Si l'argument n'est pas dans la borne, ceci arrête la boucle et sort de la fonction main avec un exit code de 1.
    }

// 4e argument - l'offset
    
    ReadDouble(unDouble, argv[4]); //Appel à la fonction de conversion
    
    double offset(unDouble); //Validation de l'offset du signal. Il vaut la valeur de l'argument 4, convertie en double.

    if ((offset<-5.0) || (offset>5.0)) { //On définit les bornes de l'offset
        cerr << "L'argument 4 (offset) n'est pas dans la borne de -5 a 5." << endl;
        return 1; //Si l'argument n'est pas dans la borne, ceci arrête la boucle et sort de la fonction main avec un exit code de 1.
    }

// 5e argument - le bruit
    
    ReadDouble(unDouble, argv[5]); //Appel à la fonction de conversion
    
    double bruit(unDouble); //Validation du bruit du signal. Il vaut la valeur de l'argument 5, convertie en double.
    
    if ((bruit<0.0) || (bruit>10.0)) { //On définit les bornes du bruit
        cerr << "L'argument 5 (bruit) n'est pas dans la borne de 0 a 10." << endl;
        return 1; //Si l'argument n'est pas dans la borne, ceci arrête la boucle et sort de la fonction main avec un exit code de 1.
    }
    
//
    
    double signal[nombre]; //On définit le tableau qui contiendra les différentes valeurs calculés du signal en "nombre" points.
    
    if (forme == "s") { //Appel à la fonction sinusodiale si le premier arguement est 's'
        sinusodiale(signal, nombre, amplitude, offset, bruit);
    }
    
    else if (forme == "c"){ //Appel à la fonction carré si le premier argument est 'c'
       carre(signal, nombre, amplitude, offset, bruit);
    }
    
    else { //Le message d'erreur si le premier argument ne correspond pas aux deux formes valides, 's' et 'c'
        cerr << "Ceci n'est pas une forme valable." << endl;
    }


//  Dans les lignes suivantes, on crée le fichier texte
        
    
    string const nomFichier("../../../../F_periode.txt"); //On définit le path et nom du fichier texte. Le path est relatif en fonction de l'exécutable. Chaque "../" permet de "remonter" dans les dossiers pour en venir là où on veut créer le fichier texte. 
    
    ofstream monFlux; //Déclaration d'un flux permettant d'écrire dans le fichier
    
    monFlux.open(nomFichier.c_str()); //On ouvre le flux
    
    if(monFlux) {
        
        for (int i(0);i<nombre;i++) {
        monFlux << signal[i] << endl; //On écrit les valeurs du tableau signal ligne-par-ligne dans le fichier texte
        }
    
    }
     
    else { //Le message d'erreur si un erreur a lieu lors de la création du fichier
        cerr << "ERREUR: Impossible de creer le fichier." << endl;
    }

    monFlux.close(); //On ferme le flux
    
    return 0; //Si la fonction main se déroule sans problème, la boucle se termine avec un exit code de 1.
    
} // Fin de la fonction main


//  Les définitions des fonctions sont dans les lignes suivantes


//  La fonction de conversion entier

//  Elle essaie de convertir certains paramètres d'entrée du format chaine de caractères aux nombres entier

int ReadEntier(int &unEntier, char argv[]) { //La fonction utilise le int unEntier et l'entrée choisi du tableau des paramètres comme input
    
    istringstream tmpStr;
    bool conversionOK(true);
    
    unEntier=0;
    
    tmpStr.str(argv); //On assigne l’argument à tmpStr
    tmpStr >> unEntier; //On essaie de le convertir en un int
    if (tmpStr.fail()) { //Le message d'erreur si la conversion échoue
        cerr<< "L'argument " << "\"" << argv << "\"" << " n'est pas un entier." << endl;
        conversionOK = false;
        return 1; //S'il y a une erreur, le return arrête la boucle et sort de la fonction avec un exit code de 1.
    }
    
    return unEntier; //La fonction retourne unEntier converti
}

//  La fonction de conversion double

//  Elle essaie de convertir certains paramètres d'entrée du format chaine de caractères aux nombres double

double ReadDouble(double &unDouble, char argv[]) { //La fonction utilise le double unDouble et l'entrée choisi du tableau des paramètres comme input
    
    istringstream tmpStr;
    bool conversionOK(true);
    
    unDouble=0.0;
    
    tmpStr.str(argv); //On assigne l’argument à tmpStr
    tmpStr >> unDouble; //On essaie de le convertir en un double
    if (tmpStr.fail()) { //Le message d'erreur si la conversion échoue
        cerr<< "L'argument " << "\"" << argv << "\"" << " n'est pas un double." << endl;
        conversionOK = false;
        return 1; //S'il y a une erreur, le return arrête la boucle et sort de la fonction avec un exit code de 1.
    }
    
    return unDouble; //La fonction retourne unDouble converti
}

//  La fonction sinusodiale

//  Elle calcule les valeurs des points du signal sinusoide et les mets dans un tableau ensuite affiché

void sinusodiale (double signal[], int nombre, double amplitude, double offset, double bruit) { //La fonction utilise le tableau signal, et les valeurs des paramètres entrés comme input
    
    //On génére d'abord le bruit en utilisant le générateur de nombre aléatoires initialisé au début et la fonction bruitGenere
    
    double bruitCree; //On initialise le double dans laquelle on mettra la valeur (aléatoire) du bruit généré par la fonction bruitGenere
    
    //On calcule la valeur du signal en utilisant les arguemnts donnés en ajoutant aussi le bruit
    
    for (int i(0); i<nombre; i++) {
        
        bruitCree = bruitGenere(bruit); //On appelle la fonction bruitGenere, qui nous mets une nouvelle valeur du bruit géneré dans bruitCree
        
        signal[i] = (amplitude * sin(M_PI * 2 * ((double)i/(double)nombre)) + offset) + bruitCree; //On calcule les valeurs des points et on les mets dans un tableau
        
        cout << signal[i] << endl; //On affiche le tableau des valeurs
    }
    
}

//  La fonction carré

//  Elle calcule les valeurs des points du signal carré et les mets dans un tableau ensuite affiché

void carre (double signal[], int nombre, double amplitude, double offset, double bruit) { //La fonction utilise le tableau signal, et les valeurs des paramètres entrés comme input
    
    //On génére d'abord le bruit en utilisant le générateur de nombre aléatoires (initialisé au début de la fonction main) et la fonction bruitGenere
    
    double bruitCree; //On initialise le double dans laquelle on mettra la valeur (aléatoire) du bruit généré par la fonction bruitGenere
    
    for (int i(0); i<(nombre/2); i++) { //On calcule les valeur positives du signal en utilisant les arguements donnés en ajoutant le bruit
        
        bruitCree = bruitGenere(bruit); //On appelle la fonction bruitGenere, qui nous mets une nouvelle valeur du bruit géneré dans bruitCree
        
        signal[i] = (amplitude + offset) + bruitCree; //On calcule les valeurs positives des points et on les mets dans un tableau
        
        cout << signal[i] << endl; //On affiche le tableau des valeurs
    }
    
    for(int i(nombre/2); i<nombre; i++) { //On calcule les valeur négatives du signal en utilisant les arguements donnés en ajoutant le bruit
        
        bruitCree = bruitGenere(bruit); //On appelle la fonction bruitGenere, qui nous mets une nouvelle valeur du bruit géneré dans bruitCree
        
        signal[i] = -((amplitude + offset) + bruitCree); //On calcule les valeurs négatives des points et on les mets dans un tableau
        
        cout << signal[i] << endl; //On affiche le tableau des valeurs
    }
    
}

//  La fonction bruit

//  Elle crée un bruit qui est utilisé dans les fonctions sinusodiale ou carré

double bruitGenere(double bruit) { //La fonction utilise le bruit entré en paramètre comme input
    
    double bruitCree = (rand() % 100) * (bruit/100); //On définit les bornes des nombres aléatoires
    
    bruitCree = bruitCree - bruit/2; //On définit pour de bon la valeur du bruit
    
    return bruitCree; //On retourne le bruit crée
}
