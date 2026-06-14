#ifndef PLAYER_H
#define PLAYER_H
#include "entity.h"
#include <vector>
using namespace std;

enum skilltype { ATTACK , HEAL , DOPPING , REVIVE ,HEAL_ATTACK , HEAL_OVER_TIME , SPECIAL_HEAL};
struct skill
{
 string name;
 int damage;
 int energycost;
 bool special;
 skilltype type;
 skill(string n = "", int dmg = 0 , int cost = 0 , bool sp = false , skilltype t = ATTACK);

};

class Player : public entity
{
    skill sk1;
    skill sk2;
    skill ragesk;
    string ragesentence;
    int specialcooldown = 0 ;

    
    public:
   
    int jokercooldown = 0 ;
    Player();
       Player(string heroname , int maxhp, int rageneed ,  skill s1 , skill s2 , skill rs,string sentence);
      skill getsk1()const;
      skill getsk2()const;
      skill getrageskill()const;

      string getragesentence()const;

      void showskill()const;

      skill chooseskill()const;
      bool canspecial()const;
      void setspecialcooldown(int );
      void tickspecialcooldown();

};


#endif 