#ifndef PORT_REGLES_H
#define PORT_REGLES_H
#include <string>


class port_regles
{
    public:
        port_regles();
        virtual ~port_regles();
        int get_regle(std::string port);
    protected:

    private:
        std::string **table;
        int nbligne = 0;
        int nbcolone = 2;
};

#endif // PORT_REGLES_H