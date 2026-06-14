#ifndef BATTLE_H
#define BATTLE_H
#include "player.h"
#include <vector>

class Battle
{
    std::vector<Player> team1;
    std::vector<Player> team2;
    std::vector<int> lockcountteam1;
    std::vector<int> lockcountteam2;
    std::vector<int> scorpionteam1;
    std::vector<int> scorpionteam2;
    std::vector<int> poisonhidecounter1;
    std::vector<int> poisonhidecounter2;
    bool team1first;
    int showteam = -1;
    int showidx = -1;

    int nowround;
 
    int getenergyteam1()const;
    int getenergyteam2()const;
    void showteamstatus(const std::vector<Player>& team)const;
    bool haslivinghero(const std::vector<Player>& team)const;
    void chooseteam(vector<Player>&  , int  , const vector<Player>& );


    int livingcount (const std::vector<Player>& team)const;
    int chooseattacker (const std::vector<Player>& team);
    int chooseTarget (const std::vector<Player>& team);

   void playturn( std::vector<Player>&  , std::vector<Player>&  ,bool  ,int );
   void updaterage();

   int chooseally (const std::vector<Player>&  );
public:

Battle();

void start();


};

#endif 
