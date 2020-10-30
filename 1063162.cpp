// But: Une caisse entregistreuse qui va:
//      1. Accepter le montant à payer - limite maximum de $20.00.
//      2. Arrondir ce montant en fonction des règles du gouvernement du Canada.
//      3. Afficher le montant à payer.
//      4. Calculer le montant à remettre.
//      5. Afficher le montant à remettre en fonction de coupures qu'il faut remettre.
//      6. Demander à l'utilisateur si il ou elle veut continuer à effectuer des transactions.
// Auteur: Harley Lounsbury
// Date: 19/09/2018


// Importer la librairie IOSTREAM qui permet d'afficher d'afficher ou ramasser des données.
#include <iostream>

// Pour l'utilisation de fixed et setprecision() - afficher des nombres avec virgule flottante à 2 chiffres après la virgule. 
#include <iomanip>

// Inclure l'espace de noms std.
using namespace std;

// Le point d'entré du programme, la fonction main().
int main()
{
   // La fonction setlocale permet d'afficher de caractères accentués.
   setlocale(LC_ALL, "");

   // Active l'affichage de réels à seulement 2 chiffres après la virgule.
   cout << fixed << setprecision(2);

   // Déclaration de variables.

   // Constante pour le prix maximum.

   const int iLIMITESUP = 20;

   // Constante pour le prix minimum.
   const int iLIMITEINF = 0;

   // Les données fournies par l'utilisateur.
   double dPrixDeVente;
   double dMontantDonne;
   char cSortie;

   // Variable pour afficher le montant à remettre.
   double dMontantARemettre;

   // Variables pour répresenter de montants en entier - utilisés pour la manipulation de chiffres.
   // Cette technique utilise essentiellement le nombre de centimes pour effectuer des calculs.
   int iPrixDeVente;
   int iMontantDonne;
   int iMontantARemettre;
   int iArrondissement;


   // Booléen qui va servir pour sortir de la boucle, dans le cas que l'utilisateur ne veut pas continuer.
   bool bSortie = true;  
   
   // Tout le programme est encapsulé dans la boucle do/while. 
   // La boucle est dépendante au booléen bSortie.
   // Quand on va demander a l'utilisateur si il ou elle veut continuer, une réponse négative va changer bSortie à false, et on va terminer!
   do
   {
      // Demander à l'utilisateur le montant à payer.
      cout << "Entrez le montant à payer (maximum $" << iLIMITESUP << "): ";
      cin >> dPrixDeVente;
      // Variable de type entier pour calculer l'arrondissement et le nombre de chaque coupure à remettre.
      // Les deux calculs s'agissent d'une solution de contournement pour la précision de chiffres.
      // Les calculs se fait avec des facteurs aussi importants, car aprés de nombreuses analyses, il y avait encore certains chiffres qui ne voulaient pas coopérer.
      // S'il y a des nombres qui ne fonctionnent pour des raisons de précision, je ne les trouve pas.
      iPrixDeVente = dPrixDeVente * 1000000;
      iPrixDeVente = iPrixDeVente / 10000;

      // On doit s'assurer que le montant entré est entre 0 et 20. Sinon, le programme demande à nouveau la question. 
      while (iPrixDeVente < (iLIMITEINF * 100) || iPrixDeVente > (iLIMITESUP * 100))
      {
         cout << "Le montant que vous avez entré n'est pas valide." << endl;
         cout << "Entrez le montant à payer (maximum $" << iLIMITESUP << "): ";
         cin >> dPrixDeVente;
         // Variable de type entier pour calculer l'arrondissement et le nombre de chaque coupure à remettre.
         // Les deux calculs s'agissent d'une solution de contournement pour la précision de chiffres.
         iPrixDeVente = dPrixDeVente * 100000000;
         iPrixDeVente = iPrixDeVente / 1000000;

      }
      

      // Modulo pour isoler le dernier chiffre.
      iArrondissement = iPrixDeVente % 1000 % 100 % 10;
         
      // Switch pour arrondir le montant à payer.
      switch (iArrondissement)
      {
      // Si le dernier chiffre est 1, $0.01 est enlevé du montant. 
      case 1:
         dPrixDeVente -= 0.01;
         break;
      // Si le dernier chiffre est 2, $0.02 est enlevé du montant.
      case 2:
         dPrixDeVente -= 0.02;
         break;
      // Si le dernier chiffer est 3, $0.02 est ajouté au montant.
      // Le même concept est appliqué pour chaque possibilité.
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
         // Demander à l'utilisateur le montant donné.
         cout << "Entrez le montant donné (maximum $" << iLIMITESUP << ", minimum $" << dPrixDeVente << "): ";
         cin >> dMontantDonne;
         
         // Initialiser l'entier qui répresente le montant donné pour calculer.
         // Les deux calculs s'agissent d'une solution de contournement pour la précision des chiffres.
         iMontantDonne = dMontantDonne * 100000000;
         iMontantDonne = iMontantDonne / 1000000;

         // Ajout de de contraint quand j'ai constaté que XX.40 ne fonctionnait pas. 
         if (iMontantDonne % 1000 % 100 % 10 == 9)
         {
            iMontantDonne += 1;
         }

         // Pour s'assurer les contraintes.
         // Erreur est affichée si:
         // Le montant donné est inférieur au prix.
         // Le montant donné est supérieur à $20.00.
         // Si le dernier chiffre n'est pas 0 ou 5. Cette dernière contrainte m'a donné du trouble au départ, car même si il est déjà 0, il n'est pas 5!
         // J'ai décidé de continuer les manipulations de chiffres avec les montants representatifs (entiers).
         if ((iMontantDonne < iPrixDeVente) || (iMontantDonne > (iLIMITESUP * 100)) || ( (iMontantDonne % 1000 % 100 % 10 != 0) && (iMontantDonne % 1000 % 100 % 10 != 5) ))
         {
            cout << "Erreur : valeur dépassant les limites (maximum $" << iLIMITESUP << ", minimum $" << dPrixDeVente << ")" << endl;
            cout << "\t : ou contient des cennes." << endl;
         }
      } while ((iMontantDonne < iPrixDeVente) || (iMontantDonne > (iLIMITESUP * 100)) || ((iMontantDonne % 1000 % 100 % 10 != 0) && (iMontantDonne % 1000 % 100 % 10 != 5)));
            
         
      // Calculer le montant à remettre.
      dMontantARemettre = dMontantDonne - dPrixDeVente;

      // Déclarer et initialiser un entier qui répresante le montant à remettre pour calculer les coupures d'argent.
      iMontantARemettre = dMontantARemettre * 100000000;
      iMontantARemettre = iMontantARemettre / 1000000;

      // L'addition de 1 est une manipulation pour certains cas que $0.05 ne voulait pas s'afficher (ex. 0.95 est réprésenté par 0.949999999999). 
      // Ou dans certains cas, un montant à remettre avec 0.25, réprésenté dans le programme comme 0.24, disait de remettre 2 x 0.10 et 1 x 0.05.
      // J'avais crée une solution de contournement pour les 0.05, mais avec plus de tests, j'ai réalisé que la solution devait être plus tôt. 
      if (iMontantARemettre % 1000 % 100 % 10 == 4 || iMontantARemettre % 1000 % 100 % 10 == 9)
      {
         iMontantARemettre += 1;
      }

      // Afficher le montant à remettre.
      cout << "Il faut remettre: $" << dMontantARemettre << endl;
         
      // Une série de if, qui vont déterminer si le coupure d'argent est nécessaire, et afficher le nombre du coupure qu'il faut.
      // À chaque if, le coupure affiché est enlevé du iMontantARemettre pour créer un entonnoir du plus grand au plus petit coupure.
      // Les deux premiers cas sont seulement présent si jamais on voudrait accepter des transactions plus grand. (On va devoir changer iLIMITESUP).

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

      // La question pour terminer la boucle. Si 'n' ou 'N' sont entrés, bSortie est changé pour false, et on quitte le programme. 
      cout << "Voulez-vous continuer (o/n) ? ";
      cin >> cSortie;
      if (cSortie == 'n' || cSortie == 'N')
      {
         bSortie = false;
      }
      else
      {
         // Si l'utilisateur veut continuer d'effectuer des transactions, la commande cls va éffacer la transaction précéndante.
         system("cls");
      }
   } while (bSortie);

   // Intégrer une pause dans la programme, qui va demander à l'utilisateur de d'appuyer sur une touche.
   system("pause");

   // Quand le programme termine, la valeur 0 est retournée qui veut dire que ca s'est passé sans erreur.
   return 0;
}