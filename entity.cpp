#include "entity.h"
#include "battle.h"
    bool entity:: jokeractive = false;
   void entity::setname(const string& n )
   {
    name = n;
   }
    string entity:: getname()const
    {
        return name;
    }
    void entity::sethpmax(int h)
    {
        hpmax = (h>0?  h : 1);
        if(hp>hpmax)
        {
            hp = hpmax;
        }
    }
    int entity::gethpmax()const
    {
        return hpmax;
    }
    void entity::sethp(int h)
    {
        hp = h ;
        if(hp<0)
        {
            hp= 0 ;   
        }
       if(hp>hpmax)
        {
            hp = hpmax;
        }

    }
    int entity::gethp()const
    {
        return hp ;
    }
    bool entity::isalive()const
    {
        return hp>0;

    }
    void entity::setrageneed(int n)
    {
        rageneed = (n> 0 ? n : 3);
    }
    int entity::getrageneed()const
    {
        return rageneed;
    }
    void entity::increaserage()
    {
         rage++;
    }
    bool entity::canuserage ()const
    {
        return (rage>=rageneed - 1);
    }
    void entity:: resetrage()
    {
        rage = 0;
    }
    void entity:: damage(int dmg)
    {
          if (jokeractive)
          {
            heal(dmg);
          }
          else
          {
           sethp(hp-dmg);
          }
    }
    void entity :: startdopping()
    {
        doppinground = 2 ;
        cout<<getname()<< " dopping 20% more  damage for 2 round !"<<endl;
    }
      void entity :: tickdopping()
      {
        if(doppinground > 0 )
        {
            doppinground--;

            if(doppinground == 0)
            cout<<getname()<< " dopping wore off  !"<<endl;
        }
        
      }

    int entity :: calcdamage(int damag)
    {
        if(doppinground > 0 )
        return damag +  (damag * 20/100);
        return damag;

    }
    void entity :: heal(int amount )
    {
         if (jokeractive)
          {
             sethp(hp-amount);
          }
          else
          {
                sethp(hp + amount);
                cout<< getname()<<" Healed + "<< amount << " HP ["<< hp <<"/"<<hpmax<<"]"<<endl;
          }
    }
    void entity:: startheal(int amount , int rounds)
    {
        healtaha = amount ;
        healpertaha = rounds;
    }
    void  entity ::  tickheal()
    {
      if(healpertaha>0)
      {
        
        heal(healtaha);
        healpertaha --;
      }

    }
