#include "../include/ip_regles.h"
#include <iostream>
#include <cstdio>
#include <fstream>

using namespace std;

ip_regles::ip_regles()
{
    string regles = "./config/ips.conf";
    int posi =0;

    fstream conf(regles.c_str());

    if(conf)
    {
        string content;
        // recuperation du nombre de regles écrite dans le fichier de configuration
        while(getline(conf, content)) 
        {
                if(content.length() == 0 )
                {
                    continue;
                }
                else
                {
                    if (content.at(0) == '#')
                    {
                        continue;
                    }
                    else
                    {
                        nbligne ++;
                    }
                }
        }


    }
    conf.close();


    fstream recup(regles.c_str());
    // création du tableau de regle et traitement des donnée des fichier de regles
    if(recup) 
    {
        string content;
        table = new string* [nbligne];
        for (int i = 0; i < nbligne; i++)
        {
            table[i]= new string [nbcolone];
        }




        while(getline(recup, content))
        {

            if(content.length() == 0 )
            {
                continue;
            }
            else
            {
                if (content.at(0) == '#')
                {
                    continue;
                }
                else
                {
                    // traitement d'une ligne de rêgle non commenté
                    string ip ="";
                    string regle ="";
                    for(int i = 0; i < content.length(); i++) 
                    {
                        if(( 48 <= int(content.at(i)))and( int(content.at(i)) <= 57))
                        {
                            ip = ip + content.at(i);

                        }
                        if(int(content.at(i)) == 46)
                        {
                            ip = ip + content.at(i);
                        }
                        if ((65 <= int(content.at(i))) and (int(content.at(i)) <= 90))
                        {
                            regle = regle + content.at(i);
                        }
                        if ((97 <= int(content.at(i))) and (int(content.at(i)) <= 122))
                        {
                            regle = regle + content.at(i);
                        }
                    }
                    //remplisage du tableau de regles
                    table[posi][0] = ip;
                    table[posi][1] = regle;
                    if(posi < nbligne)
                    {
                        posi++;
                    }

                }
            }
        }

    }

    recup.close();
}

ip_regles::~ip_regles()
{
    
}

//methode de recuperation des regles
int ip_regles::get_regle(string ip)
{
    for(int i = 0 ; i < nbligne; i++)
    {
        if(table[i][0] == ip)
        {
            if(table[i][1] == "True")
            {
                return 0;
            }
            else if (table[i][1] == "False")
            {
                return 1;
            }
        }
    }
    return 0;
}