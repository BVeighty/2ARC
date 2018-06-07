#include "../include/port_regles.h"
#include <iostream>
#include <cstdio>
#include <fstream>


using namespace std;

port_regles::port_regles()
{
    string regles = "./config/port.conf";
    int posi =0;

    fstream conf(regles.c_str());

    if(conf)
    {
        string content;
        while(getline(conf, content)) // recuperation du nombre de regles écrite dans le fichier de configuration
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
    if(recup) // création du tableau de regle et traitement des donnée des fichier de regles
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

                    string port ="";
                    string regle ="";
                    for(int i = 0; i < content.length(); i++) // traitement d'une ligne de rêgle non commenté
                    {
                        if(( 48 <= int(content.at(i)))and( int(content.at(i)) <= 57))
                        {
                            port = port + content.at(i);

                        }
                        if ((65 <= int(content.at(i))) and (int(content.at(i)) <= 90))
                        {
                            regle = regle + content.at(i);
                        }
                        if ((97 <= int(content.at(i))) and (int(content.at(i)) <= 122))
                        {
                            regle = regle + content.at(i);
                        }
                    }//remplisage du tableau de regles
                    table[posi][0] = port;
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

port_regles::~port_regles()
{
    //delete this;
}

int port_regles::get_regle(string port)
{

    for(int i = 0; i < nbligne; i++)
    {
        if(table[i][0] == port)
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
    return 1;
}