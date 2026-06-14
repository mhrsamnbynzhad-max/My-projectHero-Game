#include "player.h"
#include <iostream>
skill :: skill(string n , int dmg , int cost , bool sp , skilltype t )
{
    name = n ;
    damage = dmg;
    energycost = cost;
    special = sp;
    type = t ;
}


 Player :: Player()
 {
 }
     Player ::   Player(string heroname , int maxhp, int rageneedvalue ,  skill s1 , skill s2 , skill rs,string sentence)
     {

        setname(heroname);
        hpmax =maxhp;
        hp= maxhp;
        rage = 0 ;
        rageneed = rageneedvalue ;
        sk1 = s1;
        sk2 = s2;
        ragesk = rs;
        ragesentence  = sentence ;
        healpertaha = 0;
        healtaha = 0 ;
        doppinground = 0 ;

     }
      skill Player :: getsk1()const
      {
        return sk1;
      }
      skill Player :: getsk2()const
      {
        return sk2;
      }
      skill Player :: getrageskill()const
      {
        return ragesk;

      }

      string Player :: getragesentence()const
      {
        return ragesentence;
      }

      void Player :: showskill()const
      {
        cout<<"\n1)"<<sk1.name <<" Damage "<<sk1.damage <<"Energy "<<sk1.energycost;
        cout<<"\n2)"<<sk2.name <<" Damage "<<sk2.damage <<"Energy "<<sk2.energycost;
        cout<<"\n3)"<<ragesk.name <<" Damage "<<ragesk.damage <<"Energy "<<ragesk.energycost;

      }

      skill Player :: chooseskill()const
      {
        int choose;
        cin>>choose;
        if(choose  == 1)
            return sk1;
            if(choose  == 2)
            return sk2;
        return ragesk;
            
     
      }
 bool Player :: canspecial()const
 {
  return specialcooldown == 0;
 }
      void Player :: setspecialcooldown(int v )
      {
          specialcooldown =  v ;
      }
      void Player :: tickspecialcooldown()
      {
        if(specialcooldown > 0)
        {
          specialcooldown -- ;
        }
      }

     



