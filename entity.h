#ifndef ENTITY_H

#define ENTITY_H
#include <iostream>
#include <string>
using namespace std;


class entity
{
    protected:
    string name;
    int hp;
    int hpmax;

    int rage;
    int rageneed;
    
    int doppinground = 0;
    
    int healtaha = 0 ;
    int healpertaha = 0;
    
    public:
    static bool jokeractive;
    void setname(const string&);
    string getname()const;
    void sethpmax(int);
    int gethpmax()const;
    void sethp(int);
    int gethp()const;
    bool isalive()const;
    void setrageneed(int);
    int getrageneed()const;
    void increaserage();
    bool canuserage ()const;
    void resetrage();
    void damage(int);
    void startdopping();
    void tickdopping();
    int calcdamage(int );
    void heal(int );
    void startheal(int , int );
    void tickheal();
    int gettaha() const 
    {
        return healtaha ;
    }


};

#endif 