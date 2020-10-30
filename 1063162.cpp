// But: Une caisse entregistreuse qui va:
//      1. Accepter le montant � payer - limite maximum de $20.00.
//      2. Arrondir ce montant en fonction des r�gles du gouvernement du Canada.
//      3. Afficher le montant � payer.
//      4. Calculer le montant � remettre.
//      5. Afficher le montant � remettre en fonction de coupures qu'il faut remettre.
//      6. Demander � l'utilisateur si il ou elle veut continuer � effectuer des transactions.
// Auteur: Harley Lounsbury
// Date: 19/09/2018


// Importer la librairie IOSTREAM qui permet d'afficher d'afficher ou ramasser des donn�es.
#include <iostream>

// Pour l'utilisation de fixed et setprecision() - afficher des nombres avec virgule flottante � 2 chiffres apr�s la virgule. 
#include <iomanip>

// Inclure l'espace de noms std.
using namespace std;

// Le point d'entr� du programme, la fonction main().
int main()
{
   // La fonction setlocale permet d'afficher de caract�res accentu�s.
   setlocale(LC_ALL, "");

   // Active l'affichage de r�els � seulement 2 chiffres apr�s la virgule.
   cout << fixed << setprecision(2);

   // D�claration de variables.

   // Constante pour le prix maximum.

   const int iLIMITESUP = 20;

   // Constante pour le prix minimum.
   const int iLIMITEINF = 0;

   // Les donn�es fournies par l'utilisateur.
   double dPrixDeVente;
   double dMontantDonne;
   char cSortie;

   // Variable pour afficher le montant � remettre.
   double dMontantARemettre;

   // Variables pour r�presenter de montants en entier - utilis�s pour la manipulation de chiffres.
   // Cette technique utilise essentiellement le nombre de centimes pour effectuer des calculs.
   int iPrixDeVente;
   int iMontantDonne;
   int iMontantARemettre;
   int iArrondissement;


   // Bool�en qui va servir pour sortir de la boucle, dans le cas que l'utilisateur ne veut pas continuer.
   bool bSortie = true;  
   
   // Tout le programme est encapsul� dans la boucle do/while. 
   // La boucle est d�pendante au bool�en bSortie.
   // Quand on va demander a l'utilisateur si il ou elle veut continuer, une r�ponse n�gative va changer bSortie � false, et on va terminer!
   do
   {
      // Demander � l'utilisateur le montant � payer.
      cout << "Entrez le montant � payer (maximum $" << iLIMITESUP << "): ";
      cin >> dPrixDeVente;
      // Variable de type entier pour calculer l'arrondissement et le nombre de chaque coupure � remettre.
      // Les deux calculs s'agissent d'une solution de contournement pour la pr�cision de chiffres.
      // Les calculs se fait avec des facteurs aussi importants, car apr�s de nombreuses analyses, il y avait encore certains chiffres qui ne voulaient pas coop�rer.
      // S'il y a des nombres qui ne fonctionnent pour des raisons de pr�cision, je ne les trouve pas.
      iPrixDeVente = dPrixDeVente * 1000000;
      iPrixDeVente = iPrixDeVente / 10000;

      // On doit s'assurer que le montant entr� est entre 0 et 20. Sinon, le programme demande � nouveau la question. 
      while (iPrixDeVente < (iLIMITEINF * 100) || iPrixDeVente > (iLIMITESUP * 100))
      {
         cout << "Le montant que vous avez entr� n'est pas valide." << endl;
         cout << "Entrez le montant � payer (maximum $" << iLIMITESUP << "): ";
         cin >> dPrixDeVente;
         // Variable de type entier pour calculer l'arrondissement et le nombre de chaque coupure � remettre.
         // Les deux calculs s'agissent d'une solution de contournement pour la pr�cision de chiffres.
         iPrixDeVente = dPrixDeVente * 100000000;
         iPrixDeVente = iPrixDeVente / 1000000;

      }
      

      // Modulo pour isoler le dernier chiffre.
      iArrondissement = iPrixDeVente % 1000 % 100 % 10;
         
      // Switch pour arrondir le montant � payer.
      switch (iArrondissement)
      {
      // Si le dernier chiffre est 1, $0.01 est enlev� du montant. 
      case 1:
         dPrixDeVente -= 0.01;
         break;
      // Si le dernier chiffre est 2, $0.02 est enlev� du montant.
      case 2:
         dPrixDeVente -= 0.02;
         break;
      // Si le dernier chiffer est 3, $0.02 est ajout� au montant.
      // Le m�me concept est appliqu� pour chaque possibilit�.
      case 3:
         dPrixDeVente += 0.02;
         break;
      case 4:
         dPrixDeVente += 0.01;
         break;
      case 6:
         dPrixDeVente -= 0.01;
         break;
      case 7:
         dPrixDeVente -= 0.02;
         break;
      case 8:
         dPrixDeVente += 0.02;
         break;
      case 9:
         dPrixDeVente += 0.01;
         break;
      default:
         break;
      }
      
      // La boucle s'assure que le montant respecte les contraintes et, sinon, repose la question.
      do
      {
         // Demander � l'utilisateur le montant donn�.
         cout << "Entrez le montant donn� (maximum $" << iLIMITESUP << ", minimum $" << dPrixDeVente << "): ";
         cin >> dMontantDonne;
         
         // Initialiser l'entier qui r�presente le montant donn� pour calculer.
         // Les deux calculs s'agissent d'une solution de contournement pour la pr�cision des chiffres.
         iMontantDonne = dMontantDonne * 100000000;
         iMontantDonne = iMontantDonne / 1000000;

         // Ajout de de contraint quand j'ai constat� que XX.40 ne fonctionnait pas. 
         if (iMontantDonne % 1000 % 100 % 10 == 9)
         {
            iMontantDonne += 1;
         }

         // Pour s'assurer les contraintes.
         // Erreur est affich�e si:
         // Le montant donn� est inf�rieur au prix.
         // Le montant donn� est sup�rieur � $20.00.
         // Si le dernier chiffre n'est pas 0 ou 5. Cette derni�re contrainte m'a donn� du trouble au d�part, car m�me si il est d�j� 0, il n'est pas 5!
         // J'ai d�cid� de continuer les manipulations de chiffres avec les montants representatifs (entiers).
         if ((iMontantDonne < iPrixDeVente) || (iMontantDonne > (iLIMITESUP * 100)) || ( (iMontantDonne % 1000 % 100 % 10 != 0) && (iMontantDonne % 1000 % 100 % 10 != 5) ))
         {
            cout << "Erreur : valeur d�passant les limites (maximum $" << iLIMITESUP << ", minimum $" << dPrixDeVente << ")" << endl;
            cout << "\t : ou contient des cennes." << endl;
         }
      } while ((iMontantDonne < iPrixDeVente) || (iMontantDonne > (iLIMITESUP * 100)) || ((iMontantDonne % 1000 % 100 % 10 != 0) && (iMontantDonne % 1000 % 100 % 10 != 5)));
            
         
      // Calculer le montant � remettre.
      dMontantARemettre = dMontantDonne - dPrixDeVente;

      // D�clarer et initialiser un entier qui r�presante le montant � remettre pour calculer les coupures d'argent.
      iMontantARemettre = dMontantARemettre * 100000000;
      iMontantARemettre = iMontantARemettre / 1000000;

      // L'addition de 1 est une manipulation pour certains cas que $0.05 ne voulait pas s'afficher (ex. 0.95 est r�pr�sent� par 0.949999999999). 
      // Ou dans certains cas, un montant � remettre avec 0.25, r�pr�sent� dans le programme comme 0.24, disait de remettre 2 x 0.10 et 1 x 0.05.
      // J'avais cr�e une solution de contournement pour les 0.05, mais avec plus de tests, j'ai r�alis� que la solution devait �tre plus t�t. 
      if (iMontantARemettre % 1000 % 100 % 10 == 4 || iMontantARemettre % 1000 % 100 % 10 == 9)
      {
         iMontantARemettre += 1;
      }

      // Afficher le montant � remettre.
      cout << "Il faut remettre: $" << dMontantARemettre << endl;
         
      // Une s�rie de if, qui vont d�terminer si le coupure d'argent est n�cessaire, et afficher le nombre du coupure qu'il faut.
      // � chaque if, le coupure affich� est enlev� du iMontantARemettre pour cr�er un entonnoir du plus grand au plus petit coupure.
      // Les deux premiers cas sont seulement pr�sent si jamais on voudrait accepter des transactions plus grand. (On va devoir changer iLIMITESUP).

      if (iMontantARemettre / 10000 >= 1)
      {
         cout << iMontantARemettre / 10000 << " x $100" << endl;
         iMontantARemettre -= 10000;
      }
      if (iMontantARemettre / 5000 == 1)
      {
         cout << "1 x $50" << endl;
         iMontantARemettre -= 5000;
      }
      if (iMontantARemettre / 1000 == 2)
      {
         cout << "1 x $20" << endl;
         iMontantARemettre -= 2000;
      }
      if (iMontantARemettre / 1000 == 1)
      {
         cout << "1 x $10" << endl;
         iMontantARemettre -= 1000;
      }
      if (iMontantARemettre / 500 == 1)
      {
         cout << "1 x $5" << endl;
         iMontantARemettre -= 500;
      }
      if (iMontantARemettre / 200 == 2)
      {
         cout << "2 x $2" << endl;
         iMontantARemettre -= 400;
      }
      if (iMontantARemettre / 200 == 1)
      {
         cout << "1 x $2" << endl;
         iMontantARemettre -= 200;
      }
      if (iMontantARemettre / 100 == 1)
      {
         cout << "1 x $1" << endl;
         iMontantARemettre -= 100;
      }
      if (iMontantARemettre / 25 == 3)
      {
         cout << "3 x 25 cents" << endl;
         iMontantARemettre -= 75;
      }
      if (iMontantARemettre / 25 == 2)
      {
         cout << "2 x 25 cents" << endl;
         iMontantARemettre -= 50;
      }
      if (iMontantARemettre / 25 == 1)
      {
         cout << "1 x 25 cents" << endl;
         iMontantARemettre -= 25;
      }
      if (iMontantARemettre / 10 == 2)
      {
         cout << "2 x 10 cents" << endl;
         iMontantARemettre -= 20;
      }
      if (iMontantARemettre / 10 == 1)
      {
         cout << "1 x 10 cents" << endl;
         iMontantARemettre -= 10;
      }
      if ((iMontantARemettre) / 5 == 1)
      {
         cout << "1 x 5 cents" << endl;
      }

      // La question pour terminer la boucle. Si 'n' ou 'N' sont entr�s, bSortie est chang� pour false, et on quitte le programme. 
      cout << "Voulez-vous continuer (o/n) ? ";
      cin >> cSortie;
      if (cSortie == 'n' || cSortie == 'N')
      {
         bSortie = false;
      }
      else
      {
         // Si l'utilisateur veut continuer d'effectuer des transactions, la commande cls va �ffacer la transaction pr�c�ndante.
         system("cls");
      }
   } while (bSortie);

   // Int�grer une pause dans la programme, qui va demander � l'utilisateur de d'appuyer sur une touche.
   system("pause");

   // Quand le programme termine, la valeur 0 est retourn�e qui veut dire que ca s'est pass� sans erreur.
   return 0;
}