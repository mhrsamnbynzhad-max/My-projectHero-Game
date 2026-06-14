#include "Battle.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
using namespace std;

Player whdoctor();
Player createtaha();
Player createdanny();
Player createamin();
Player createtahabozorg();
Player createpooya();
Player createjoker();

int jokerounds = 0;

void Battle :: chooseteam(vector<Player>& team , int teamnum , const vector<Player>& pool)
{
    cout<<"TEAM" <<teamnum<< " choose your heros"<<endl;
    for(int i = 0 ; i < pool.size(); i++)
    {
            cout<<" "<<i +1 <<")"<<pool[i].getname()<<"HP"<<pool[i].gethpmax()<<" Rageneeded "<<pool[i].getrageneed()<<endl;
    }
    cout<<"Enter nimbers : (forexample 1 enter  2 enter 3 )";
    vector<int>chosen;
    for(int i = 0 ; i < 3 ; i ++)
    {
        int x ; 
        cin>> x;
        bool duplicate = false;
        for(int  j = 0 ; j <chosen.size(); j ++)
        
            if(chosen[j] == x-1)
            {
                duplicate = true;
                break;
            }
            if(duplicate)
            {
                cout<<"this hero befor choosen..."<<endl;
                i--;
                continue;
            }
            chosen.push_back(x-1);
        team.push_back(pool[x-1]);
    }
}

 Battle :: Battle()
 {
    nowround = 1 ;
    srand(time(nullptr));
   vector<Player>pool;
    pool.push_back(whdoctor());
    pool.push_back(createtaha());
    pool.push_back(createdanny());
    pool.push_back(createamin());
    pool.push_back(createtahabozorg());
    pool.push_back(createpooya());
    pool.push_back(createjoker());

    

    chooseteam(team1 , 1 ,pool);
    chooseteam(team2 ,2 , pool);
     
    lockcountteam1.resize(3);   
    lockcountteam2.resize(3);   
    scorpionteam1.resize(3);   
    scorpionteam2.resize(3);   
    poisonhidecounter1.resize(3);   
    poisonhidecounter2.resize(3);   
      

    team1first = rand() % 2;
 }

    int Battle :: getenergyteam1()const
    {
        if(nowround == 1)
        {
            return 5;
        }
        if(nowround == 2)
        {
            return 9;
        }
        return 10;

    }

    int Battle :: getenergyteam2()const
    {
        if(nowround == 1)
        {
            return 8;
        }
        if(nowround == 2)
        {
            return 9;
        }
        return 10;

    }
      void Battle :: showteamstatus(const std::vector<Player>& team)const
      {
          for ( int i = 0 ; i< team.size() ; i ++ )
          {
            cout<<i+1<<")"<<team[i].getname();
            if(!team[i].isalive())
            {
                cout<<"[DEAD]";

            }else{
               cout<< " HP"<<team[i].gethp()<<"/"<<team[i].gethpmax();
            }
            cout<<'\n';
          }
      }
    bool Battle :: haslivinghero(const std::vector<Player>& team)const
    {
        for (const auto& hero : team)
        {
            if(hero.isalive())
            {
                return true;
            }
        }
        return false;
    }

    int Battle :: livingcount (const std::vector<Player>& team)const
    {
        int count = 0 ;
         for (const auto& hero : team)
        {
            if(hero.isalive())
            {
               count++;
            }
        }
        
        return count;
    }
    int Battle :: chooseattacker (const std::vector<Player>& team)
    {
        int choose;
        while(true)
        {

          cout<<"\nChoose hero (1/3 , 0 = end ): ";
          cin>>choose;
          if(choose == 0 )
            return -1;

            choose -- ;
            if(choose>=0 && choose<team.size() && team[choose].isalive())
            {
                return choose;
            }

        
        }
    }
    int Battle :: chooseTarget (const std::vector<Player>& team)
    {
       
        int choose;
        while(true)
        {

          cout<<"Target(1-3): ";
          cin>>choose;
            choose -- ;
            if(choose>=0 && choose<team.size() && team[choose].isalive())
            {
                return choose;
            }

        
        }
    }
   int Battle :: chooseally (const std::vector<Player>& team  )
   {
           int choose ;
           while(true)
           {
            cout<<"Choose teammate(1-3)";
            cin>>choose;
            choose--;
            if(choose>= 0 && choose < team.size() && team[choose].isalive())
            {
                return choose;
            }
            cout<<"Invalid\n";
           }
   }
    

   void Battle :: playturn( std::vector<Player>& attackers , std::vector<Player>& defenders ,bool isteam1, int energy)
   {
     while(energy > 0 && haslivinghero(defenders))
     {
        cout<<"\nEnergy: "<<energy<<"\n";
        cout<<"\nAttackers:\n";
        showteamstatus(attackers);

        cout<<"\nDefenders:\n";
        showteamstatus(defenders);

        int attackerindex = chooseattacker(attackers);
        if(attackerindex == -1)
        {break;}
        if(isteam1)
        {
            if(poisonhidecounter1[attackerindex]>0)
            {
                cout<<"Hidden....!"<<endl;
                continue;
            }

        }
        else{
            if(poisonhidecounter2[attackerindex]>0)
            {
                cout<<"Hidden....!"<<endl;
                continue;
            }
        }
        
        int targetindex = chooseTarget(defenders);
        attackers[attackerindex].showskill();

        cout<<"\nChoose Skill: ";

        skill selected = attackers[attackerindex].chooseskill();
        
        if(selected.special && !attackers[attackerindex].canuserage())
        {
            cout<<"\nRage not ready: ";
            continue;
        }
        if(energy<selected.energycost)
        {
            cout<<"Not enough energy"<<endl;
            continue;
        }
        
        energy -= selected.energycost;
        
        if(selected.name == "Last Bullet")
        {
            int  dmg = 55;
            defenders[targetindex].damage(dmg);
          if(!defenders[targetindex].isalive())
          {
            dmg = dmg*2;
            defenders[targetindex].damage(dmg);
          }
                cout<<"Last Bullet nit  : "<<dmg<< endl;
                continue;

        }
       else if(selected.name == "Self hit")
        {
              int ally = chooseally(attackers);
              attackers[ally].damage(25);
              attackers[attackerindex].heal(75);
              cout<<"Self hit used"<<endl;
                continue;

        }
        if(selected.name == "Kidding")

        {
             int miss = rand()% 100 ;
             if(miss< 20)
             {
                cout<<"Kidding missed..."<<endl;
                continue;
             }
             defenders[targetindex].damage(60);
             cout<<"kidding :60 damage"<<endl;
                continue;

        }
        else if(selected.name == "Lajbaz")
        {
            vector<int>enemies;
            for(int i = 0 ; i<defenders.size() ; i++)
            {
                if(i != targetindex && defenders[i].isalive())
                {
                    enemies.push_back(i);
                }
            }
            if(!enemies.empty())
            {
                int r = enemies[rand()% enemies.size()];
                defenders[r].damage(100);
                cout<<"Lajbaz hit"<<defenders[r].getname()<<"for 100 damage "<<endl;
            }
            continue;
        }


        if(selected.name == "Lock")
        {
            vector<int>& countertable = isteam1 ? lockcountteam2 : lockcountteam1;
             int& counter = countertable[targetindex];
             float damage = 20;
             if(counter>0)
                damage = damage*1.6 ;
                counter++ ;
                defenders[targetindex].damage((int)damage);
                cout<<"Lock Attack hit : "<<damage << endl;
                   continue;
         

        }
        else if(selected.name == "Died fill")
        {
            defenders[targetindex].damage(50);
            int strongest = -1 ;
            for(int i = 0 ; i < defenders.size(); i++)
            {
                if(defenders[i].isalive())
                {
                    if(strongest == -1 ||attackers[i].gethp() > attackers[strongest].gethp() )
                    {
                        strongest =  i ;
                        
                    }
                }
            }
             if(strongest  != -1 && strongest != targetindex)
             {

                 defenders[strongest].damage(50);
             }

        }
        if(selected.name == "Scorpion")
        {
             
                vector<int>& table = isteam1 ?scorpionteam2 : scorpionteam1;
                table[targetindex]++;
                cout<<"Scorpion attached!"<<endl;

        }
        if(selected.name == "Dagger")
        {
            defenders[targetindex].damage(40);
                vector<int>& table = isteam1 ?scorpionteam2 : scorpionteam1;
                int count = table[targetindex];
                if(count>0)
                {
                    defenders[targetindex].damage(count*60);
                    cout<<"Scopions actived "<<count*60<<"bouns damaged....!"<<endl;
                }
                continue;

        }


       
        if(selected.name == "Ragbar")
        {
            for(int i  = 0 ; i <defenders.size(); i ++)
            {
                if(defenders[i].isalive())
                {
                    defenders[i].damage(30);
                }
            }
            cout<<"Ragbar hit all enemies!\n";
            continue;
        }
            else if(selected.name == "X_ray")
            {
                   defenders[targetindex].damage(90);
                   if(isteam1)
                   {
                    poisonhidecounter1[attackerindex]= 1;
                   }
                   else{
                    poisonhidecounter2[attackerindex]= 1;
                    cout<<"X-Ray used.. Taha is Hidden for 1 turn...!"<<endl;
                    continue;

                   }

            }
        if(selected.type == HEAL)
        {
            vector <int >alive;
            for( int i = 0 ; i <attackers.size(); i ++)
            {
                if(attackers[i].isalive())
                {
                    alive.push_back(i);
                }
            }
            int randheal = alive[rand() % alive.size()];
            attackers[randheal].heal(40);
            int targetidx = chooseTarget(defenders);
            defenders[targetidx].damage(attackers[attackerindex].calcdamage(selected.damage));
        }
        else if (selected.type == DOPPING)
        {
            int idx = chooseally(attackers);
            attackers[idx].startdopping();
        }
        else if(selected.type == HEAL_ATTACK)
        {
            int weakest = -1 ;
            for( int i = 0 ; i <attackers.size() ; i ++)
            {
                if(attackers[i].isalive())
                {
                   if( weakest == -1 ||attackers[i].gethp() < attackers[weakest].gethp() )
                 weakest = i ;
                }
                
            }
            if(weakest != -1)
            attackers[weakest].heal(20);


            defenders[targetindex].damage(attackers[attackerindex].calcdamage(30));
        }
        else if(selected.type == HEAL_OVER_TIME)

        {
            int ally = chooseally(attackers);
            attackers[ally].startheal(40 , 2 );
        }
        else if (selected.type == SPECIAL_HEAL )

        {
            if(attackers[attackerindex].getname() == "Agha Shahryar" )
            {
                  if(!attackers[attackerindex].canspecial())
                {
                         cout<<"Joker World not ready... "<<endl;
                         continue;
                } 
                if(entity::jokeractive)
                {
                    cout<<"Joker already active... "<<endl;
                         continue;
                }
                  entity :: jokeractive = true;
                   jokerounds= 2;
    
                 attackers[attackerindex].setspecialcooldown(4);
                cout<<"Joker World activated...!"<<endl;

                continue;

            }


           else if(attackers[attackerindex].getname() == "Pooya Kazhdom" )
            {
                if(!attackers[attackerindex].canspecial())
                {
                         cout<<"Special not ready... "<<endl;
                         continue;
                }  
                if(isteam1)
                {
                       poisonhidecounter1[attackerindex]= 3;

                }
                else{
                       poisonhidecounter2[attackerindex]= 3;

                }
                cout<<"Kazhdom disappeard...!"<<endl;
                 attackers[attackerindex].setspecialcooldown(4);
                continue;
                
            }


           else if(attackers[attackerindex].getname() == "Taha bozorg" )
            {
                  if(!attackers[attackerindex].canspecial())
                {
                         cout<<"Ultimate not ready... "<<endl;
                         continue;
                }
                int randomenemy;
                do
                {
                    randomenemy = rand()% defenders.size();

                } while (!defenders[randomenemy].isalive());
                showidx = randomenemy ;
                if(isteam1)
                showteam = 2;
                else
                showteam = 1;
                cout<<"Enemy marked for rvenge...!"<<endl;
                attackers[attackerindex].setspecialcooldown(4);
                continue;
                
             
            }

           else if(attackers[attackerindex].getname() == "Amin imni" )
            {
                 if(!attackers[attackerindex].canspecial())
                {
                         cout<<"Screen not ready... "<<endl;
                         continue;
                }
                vector<int>alive;
                for(int i = 0 ; i < defenders.size() ; i++)
                {
                    if(defenders[i].isalive())
                    alive.push_back(i);
                }
                int enemy = alive[rand()% defenders.size()];
                defenders[enemy].damage(250);
                cout<<"uncertainly scream hit enemy"<<endl;
                for (int i = 0 ; i<2 ; i++)
                {
                    int ally = chooseally(attackers);
                    attackers[ally].damage(30);
                }
                attackers[attackerindex].setspecialcooldown(3);
                continue;
            }
           else if(attackers[attackerindex].getname() == "Dr.white" )
           {
               if(!attackers[attackerindex].canspecial())
                {
                         cout<<"Operation not ready... "<<endl;
                         continue;
                }
                vector<int>dead;
                for(int i = 0 ; i<attackers.size(); i++)
                {
                    if(!attackers[i].isalive() && i != attackerindex)
                    {
                        dead.push_back(i);
                    }
                }
                    if(dead.empty())
                    {
                        cout<<"NOdead teammate..."<<endl;
                         continue;
                    }
                        cout<<"Choose teammate to revive..."<<endl;
                for(int i = 0 ; i<dead.size(); i++)
                {
                    cout<<i+1<<")"<<attackers[dead[i]].getname()<<endl;
                }
                int pik;
                cin>>pik;
                pik--;
                int target = dead[pik];
                attackers[target].sethp(200);
                attackers[target].resetrage();
                cout<<"Operation success.."<<attackers[target].getname()<<"revived with 200 HP"<<endl;
                 attackers[attackerindex].setspecialcooldown(4);
                continue;          
           }

             else if(attackers[attackerindex].getname() == "Danny Golang")
            {
                if(!attackers[attackerindex].canspecial())
                {
                         cout<<"SHeild not ready... "<<endl;
                         continue;
                }
                  int weakest = -1;
            for( int i = 0 ; i <attackers.size() ; i ++)
            {
                if(attackers[i].isalive())
                {
                   if( weakest == -1 ||attackers[i].gethp() < attackers[weakest].gethp() )
                   {
                 weakest = i ;
                   }
                }
                
            }
              if(weakest != -1)
            {
                          attackers[weakest].heal(200);
                          cout<<"Family sheild active on "<<attackers[weakest].getname()<<endl;
                          attackers[weakest].heal(250);
  
            }

            attackers[attackerindex].setspecialcooldown(4);
           }
             else if(attackers[attackerindex].getname() == "Taha")
             {
                if(!attackers[attackerindex].canspecial())
            {
                cout<<"Special heal not ready "<<endl;
                continue;
            }
            int weakest = -1;
            for( int i = 0 ; i <attackers.size() ; i ++)
            {
                if(attackers[i].isalive())
                {
                   if( weakest == -1 ||attackers[i].gethp() < attackers[weakest].gethp() )
                   {
                 weakest = i ;
                   }
                }
                
            }
            if(weakest != -1)
            {
                          attackers[weakest].heal(200);
                          cout<<"QUARANTINE ACTIVE : + 200 heal on weakest "<<endl;
  
            }

            attackers[attackerindex].setspecialcooldown(3);
             }
      
        }
       

       
        else{

        if(selected.special)
        {
            cout<<endl<<attackers[attackerindex].getragesentence()<<endl;
            attackers[attackerindex].resetrage();
        }

        defenders[targetindex].damage(selected.damage);

        cout<<attackers[attackerindex].getname()<<"used"<<selected.name <<endl;
        if(!defenders[targetindex].isalive())
            cout<< defenders[targetindex].getname()<<"died\n";
        
    } 
        
     }
   }
   void Battle ::updaterage()
   {
      for(int i = 0 ; i <team1.size() ; i ++)
      {
        if(team1[i].isalive() && !team1[i].canuserage())
        {
            team1[i].increaserage();
        }
      }
      for(int i = 0 ; i <team2.size() ; i ++)
      {
        if(team2[i].isalive() && !team2[i].canuserage())
        {
            team2[i].increaserage();
        }
      }
        
   }


   
   void  Battle :: start()
{
      while ( nowround <= 15 && haslivinghero(team1) &&haslivinghero(team2)) 
      {
          if(showidx != -1)
          {
            if(showteam ==1)
            {
                if(team1[showidx].isalive())
                {
                    if(team1[showidx].gethp()<360)
                    {
                        team1[showidx].sethp(0);
                    }
                else{
                    team1[showidx].damage(200);
                }
                cout<<"Brother Revenge exploded...\n";
                }
            }
            else{
                 if(team2[showidx].isalive())
                {
                    if(team2[showidx].gethp()<360)
                    {
                        team2[showidx].sethp(0);
                    }
                else{
                    team2[showidx].damage(200);
                }
                cout<<"Brother Revenge exploded...\n";
                }
            }
            showidx = -1;
            showteam = -1;
          }
          cout<< "\n========== ROUND " << nowround << " ==========\n";
          
          if (team1first) 
          {
              
              playturn(team1,team2, true,getenergyteam1());
              
              if (haslivinghero(team2)) 
              {
                  playturn(team2,team1,false ,getenergyteam2());
                }
            }
            else
            {
                
                playturn(team2,team1, false,getenergyteam2());
                
                if ( haslivinghero(team1)
            ) {
                
                playturn(team1,team2,true , getenergyteam1());
            }
        }
        for(int i = 0 ; i<team1.size(); i++)
        {
            if(team1[i].isalive())
            team1[i].damage(scorpionteam1[i]*20);

        }
         for(int i = 0 ; i<team2.size(); i++)
        {
            if(team2[i].isalive())
            team2[i].damage(scorpionteam2[i]*20);

        }

        updaterage();
         for(auto& p : team1) p.tickdopping();
         for(auto& p : team2) p.tickdopping();
        for(auto& p : team1) p.tickspecialcooldown();
        for(auto& p : team2) p.tickspecialcooldown();
        

        for(auto& p : team1) p.tickheal();
        for(auto& p : team2) p.tickheal();
       nowround++;
       if(entity :: jokeractive)
       {
        jokerounds--;
        if(jokerounds == 0)
        {
           entity :: jokeractive = false ;
            cout<<"Joker World returend to normal"<<endl;
        }
       }
       for(int i = 0 ; i < team1.size() ; i ++)
       {
           if(poisonhidecounter1[i]>0)
           {
                poisonhidecounter1[i]--;
                 if(poisonhidecounter1[i]==0)
                 {
                    vector<int >alive;
                   for(int j = 0 ; j < team2.size() ; j ++)
                   {
                       if(team2[j].isalive())
                       alive.push_back(j);
                   }
                   if(!alive.empty())
                   {
                     int r = alive[rand()%alive.size()];
                     team2[r].damage(450);
                     cout<<"Kazhdom returned....!"<<endl;
                   }
                 }
           }
       }
        for(int i = 0 ; i < team2.size() ; i ++)
       {
           if(poisonhidecounter2[i]>0)
           {
                poisonhidecounter2[i]--;
                 if(poisonhidecounter2[i]==0)
                 {
                    vector<int >alive;
                   for(int j = 0 ; j < team1.size() ; j ++)
                   {
                       if(team1[j].isalive())
                       alive.push_back(j);
                   }
                   if(!alive.empty())
                   {
                     int r = alive[rand()%alive.size()];
                     team1[r].damage(450);
                     cout<<"Kazhdom returned....!"<<endl;
                   }
                 }
           }
       }
    }

    int alive1 =livingcount(team1);

    int alive2 =livingcount(team2);

    cout << "\n===== RESULT =====\n";

    if (
        alive1 == 0 &&alive2 == 0 ) 
        {

        cout << "Draw\n";
    }
    else if (alive1 > alive2 ) 
    {

        cout << "Team 1 Wins\n";
    }
    else if ( alive2 > alive1 )
     {

        cout << "Team 2 Wins\n";
    }
    else 
    {

        cout << "Draw\n";
    }
}

