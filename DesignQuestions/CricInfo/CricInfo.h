#include<vector>
#include<string>
#include<unordered_map>

using namespace std;

/* Design a Cric Info app:
FR:
1. Teams, match histories
2. Ball by ball commentary of the match
3. Stats at players, team, tournament level
4. In a tournament -> each team has a playing squad of 16 players.
5. In a match -> each team has a playing 11.
*/

class Player {
    string name;
    int playerId;
    int age;
    string role;
    int totalRuns;
    int totalWickets;
    int totalMatches;
    double battingAverage;
    double bowlingAverage;
    double strikeRate;
    double economy;
};

class BatsmanMatchStat {
    int playerId;
    int runs;
    int ballsFaced;
    int fours;
    int sixes;
    double strikeRate;
};

class BowlerMatchStats {
    int playerId;
    int wickets;
    int runs;
    int balls;
    int maidenOvers;
    double economy;
};

class Extras {
    int wides;
    int noBalls;
    int byes;
    int legByes;
};

enum WicketType {
    BOWLED,
    CAUGHT,
    LBW,
    RUN_OUT,
    STUMPED,
    HIT_WICKET,
    RETIRED_HURT,
    RETIRED_OUT,
    OBSTRUCTING_THE_FIELD
};

class Comment {
    int commentId
    string comment;
    int ball;
};

class Inning {
    int inningId;
    int battingTeamId;
    int bowlingTeamId;
    int totalRuns; 
    int totalWickets;
    int totalBowlsFaced;
    vector<BatsmanMatchStat> batsmanStats;
    vector<BowlerMatchStats> bowlerStats;
    vector<Extras> extras;
    vector<Comment> commentary;
};

enum matchResult {
    TEAM1_WIN,
    TEAM2_WIN,
    DRAW
};

class Match {
    vector<Inning*> innings;
    int matchId;
    int tournamentId;
    vector<int> playingTeams[2];
    string date;
    matchResult result;
};

enum TournamentState {
    NOT_STARTED,
    IN_PROGRESS,
    COMPLETED
};

class Tournament {
    int tournamentId;
    string name;
    string startDate;

    vector<int> playingTeams;
    vector<int> matches;
    TournamentState state;
    int tournamentWinner;
};

class Team {
    int teamId;
    string name;
    vector<int> players;
    vector<int> matches;
};

class TournamentDao {
    unordered_map<int, Tournament> tournaments;
};

class PlayerDao {
    unordered_map<int, Player> players;
};

class MatchDao {
    unordered_map<int, Match> matches;
};

class CricBuzzSystem {
    TournamentDao tournamentDao;
    PlayerDao playerDao;
    MatchDao matchDao;

public:
    void addTournament();
    void addMatch();

    int getTournamentWinner();
    // List last 5 comments.
    vector<Comment> getComment() {

    };

};