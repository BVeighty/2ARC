#ifndef IP_REGLES_H
#define IP_REGLES_H
#include <string>

class ip_regles
{
    public:
        ip_regles();
        virtual ~ip_regles();
        int get_regle(std::string ip);

    protected:
    private:
        std::string **table;
        int nbligne = 0;
        int nbcolone = 2;
};

#endif // IP_REGLES_H
