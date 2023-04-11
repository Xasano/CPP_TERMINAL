#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <string.h>
#include <string>
#include <fstream>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
 
using namespace std;

/* Programme créé pour le laboratoire 1 pour le cours 8INF342:Système d'exploitation à l'UQAC
Auteur : Léa MULLIEZ & Bastien LEFUMEUX */

// /!\ ATTENTION /!\ Bien penser à partir du programme proprement en écrivant 'stop' lorsque l'utilisateur a fini d'utiliser le programme /!\ ATTENTION /!\ 

int main()
{  
   
   ofstream h("historique.txt"); // création du fichier historique.txt et ouverture
   h.close();// fermeture du fichier historique.txt

   int nbr_command = 1;
// ---------------------------------------------------------------------------

    while(true)
    {
        string result;
        bool proc_back = false; // Variable qui permet de vérifier si l'utilisateur veux lancer une commande en arrière plan à l'aide de '&'
 
        std::cout << "LEFUMEUX MULLIEZ< "; // C'est ce qui va être tout le temps à côté dans le teminal lorsqu'on voudra entrer une commande. Ex : LEFUMEUX MULLIEZ<
        char command[128]; // création variable char limiter a 128 character
        cin.getline(command,128); //Le programme accodre que 128 charactères à l'utilisateur pour entrer la commande voulue.
        pid_t pid_temp; // stock le pid 
        string command_string = command; // transform la variable command en string

         if (command_string == "stop")
         {
           return 0;
         }

// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------

        if(command_string == "historique"){ // vérifie si la commadn historique est taper
           ifstream historique("historique.txt"); // ouvre le fichier historique.txt
            for(int i =0; i<8;i++){ // parcours de 0 a 8
               if(i<nbr_command){ // si i est inférieur a nbr command 
                  string s; // string temporaire
                  getline(historique, s); // récupère la ligne et la met dans s
                  cout<< s << endl; // affiche la variable temporaire s
               }
            }
            historique.close();
      }else if(strlen(command) != 0) //Condition qui va nous permettre de vérifier si l'utilisateur a inscrit quelque chose dans le terminal
        {   
           vector<char*>args; // vector = fourre tout (== String)
           char* prog = strtok(command, " "); // Va prendre que le premier argument que l'utilisateur a donné (Exemple : "Xasano< Hello world !" => prog ici va être égal à Hello)
           char* tmp = prog;

           while ( tmp != NULL )
           {
              if(strcmp(tmp,"&") == 0){ 
                  proc_back = true;
               }
               else{  
                  args.push_back( tmp );
               }
               tmp = strtok( NULL, " " );
           }    

           char** argv = new char*[args.size()+1];

           for ( int k = 0; k < args.size(); k++ )
           {
              argv[k] = args[k];
           }

           argv[args.size()] = NULL;

           if(prog[0] == '.')
           {        
              std::system(args[0]);
           }
           else
           {
              pid_t kidpid = fork();
              pid_temp = kidpid;

              if(kidpid < 0)
              {
                 perror("Could not fork");
                 return -1;
              }
              else if (kidpid == 0) // child
              {
                 execvp(prog,argv);
              }
              else
              {
                  if(!proc_back){
                     if(waitpid(kidpid,0,0) <0 )
                     {
                        return -1;
                     }
                  }
              }
          }
      }

      

      
      if(nbr_command>100){ // quand le nombre de commmand dépasse 100
         ifstream historique("historique.txt"); // ouvre le fichier historique .txt
         string temp_h[100]; // crée un tableau de string de 100 case
         string nbr_string = std::to_string(nbr_command); // transform le nombre de commande en string
         temp_h[0] = nbr_string+"  "+command_string+"  "+std::to_string(pid_temp); // met a la premier case le nbr de command executer, la command taper, le pid de la command
         
         for(int i = 1;i<100;i++){ // parcours de 1 a 100
            string s; // crée une string temporaire
            getline(historique, s); // récupère la ligne et la marque dans s
            temp_h[i]=s; // remplie le tableau avec la ariable s
         } 
         historique.close(); // ferme la fichier historique.txt
         ofstream historique_int("historique.txt"); // écrase le fichier historique.txt et l'ouvre

         for(int i = 0;i<100;i++){ // parcours de 0 a 100
            historique_int<<temp_h[i]<<endl; // rempli le fichier historique.txt
         }

         historique_int.close(); // ferme le fichier historique.txt

      }else{ // si nbr command inferieur a 100

         ifstream historique("historique.txt");// ouvre le fichier historique .txt
         string temp_h[100]; // crée un tableau de string de 100 case
         string nbr_string = std::to_string(nbr_command); // transform le nombre de commande en string
         temp_h[0] = nbr_string+"  "+command_string+"  "+std::to_string(pid_temp); // met a la premier case le nbr de command executer, la command taper, le pid de la command
         
         for(int i = 1;i<nbr_command;i++){// parcours de 1 a nbr command
            string s;// crée une string temporaire
            getline(historique, s);// récupère la ligne et la marque dans s
            temp_h[i]=s;// remplie le tableau avec la ariable s
         }
         historique.close();// ferme le fichier historique.txt
         ofstream historique_int("historique.txt");// écrase le fichier historique.txt et l'ouvre

         for(int i = 0;i<nbr_command;i++){ // parcours de 0 a nbr de command 
            historique_int<<temp_h[i]<<endl;// rempli le fichier historique.txt
         }

         historique_int.close();// ferme le fichier historique.txt

      }

      nbr_command++; // incrémentation de nbr command
      

      
  }
   remove( "historique.txt" ); // supprime le fichier historique.txt
      return 0;     
}