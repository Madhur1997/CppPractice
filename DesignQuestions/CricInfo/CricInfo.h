#include<vector>
#include<string>
#include<unordered_map>

using namespace std;

/* Design a Cric Info app:
FR:
1. Teams, match histories
2. Ball by ball commentary of the match
3. Stats at players, team, tournament level
4. In a tournament -> each team has a playing squad
5. In a match -> each team has a playing 11.
*/

class Player {
    string name;
    int playerId;
    int teamId;
    vector<int> matchIds;
    vector<int> tournamentIds;
};

class PlayerRepository {

};

class Team {
    string name;
    int teamId;
    vector<int> playerIds;
    vector<int> matchIds;
public:
    Team(string name) : name(name) {}
    void addPlayer(int playerId);
    void removePlayer(int playerId);
    void addMatch(int matchId);
    void removeMatch(int matchId);
    void addTournament(int tournamentId);
    void removeTournament(int tournamentId);
};

class PlayingTeam {
    vector<int> playerIds;
    int teamId;

};

class PlayingSquad {
    vector<int> playerIds;
    int teamId;
};

enum WicketType {
    Bowled,
    RunOut,
    Caught,
    HitWicket,
    Stump,
    LBW
};

class BallStat {
    int ballNumber;
    int runsScored;
    bool wicket;
    WicketType wicket;
    string commentary;
};

class Inning {
    int inningsId;
    int teamId;
    vector<vector<BallStat>> overs;
    unordered_map<int, int> playerScores;
    vector<int> fallOfWickets;
    int totalScore;
    int totalWickets;
    int totalOvers;
};

class Match {
    int matchId;
    int team1Id, team2Id;
    MatchState state;
    MatchType type;
    vector<Inning> innings;
    Stadium stadium;
public:
    Match(int matchId, int team1Id, int team2Id, Stadium stadium) : matchId(matchId), team1Id(team1Id), team2Id(team2Id), stadium(stadium) {}
    void addBallStat(int inningNum, BallStat ballStat);
    void updateScore(int runs);
    void updateWickets();
    void updateOvers();
    void updatePlayerScore(int playerId, int runs);
    void getScore();
    void getWickets();
    void getOvers();
    void getPlayerScore(int playerId);
    BallStat getCommentary(int overNumber, int ballNumber);
    void updateMatchState(MatchState state);
};

class PlayerService {

};

class MatchService {

};

enum MatchState {
    NOT_STARTED,
    IN_PROGRESS,
    COMPLETED
};

enum MatchType {
    T20,
    ODI,
    TEST
};

enum MatchResult {
    TEAM1_WON,
    TEAM2_WON,
    DRAW
};

class Address {
public:
    string streetName;
    string city;
    string state;
    string country;
    int pincode;
};

class Stadium {
    Address address;
    string name;
    int stadiumId;
};


class Tournament {
    string name;
    vector<Team> teams;
    vector<Match> matches;
    vector<Player> players;
};

class TournamentRepository {

};

class TournameService {
    
};