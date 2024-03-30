#include<vector>
#include<iostream>

using namespace std;

/* Functional requirements:
    * 1. User should be able to set daily goals for calories, steps and distance.
    * 2. User should be able to track daily health metrics like steps, calories, distance, heartbeats.
    * 3. User should be able to track daily goals and see how many goals are achieved.
    * 4. User should be able to see weekly and monthly analytics.
    * 5. User should be able to get notifications for motivation.
    * 6. User should be able to store daily goals metrics in database.
*/

class HealthMetrics {
public:
    int steps;
    int caloriesBurned;
    double distance; // in kilometers
    int heartBeats;
};

class IMetricGoal {
    bool is_achieved;
public:
    IMetricGoal() : is_achieved(false) {}
    virtual void setAchieved() {
        is_achieved = true;
    }
    virtual bool getAchieved() {
        return is_achieved;
    }
};

class CalorieGoal : public IMetricGoal {
    int goalCalories;
    int currCalories;
public:
    CalorieGoal(int goalCalories = 2000, int currCalories = 0) : goalCalories(goalCalories), currCalories(currCalories) {}
    bool updateCalories(int calories) {
        currCalories = calories;
        if(currCalories >= goalCalories) {
            setAchieved();
        }
        return getAchieved();
    }
};

class StepGoal : public IMetricGoal {

    int goalSteps;
    int currSteps;
public:
    StepGoal(int goalSteps = 10000, int currSteps = 0) : goalSteps(goalSteps), currSteps(currSteps) {}
    bool updateSteps(int steps) {
        currSteps = steps;
        if(currSteps >= goalSteps) {
            setAchieved();
        }
        return getAchieved();
    }
};

class DistanceGoal : public IMetricGoal {
    double goalDistance;
    double currDistance;
public:
    DistanceGoal(double goalDistance = 5, double currDistance = 0) : goalDistance(goalDistance), currDistance(currDistance) {}
    bool updateDistance(double distance) {
        currDistance = distance;
        if(currDistance >= goalDistance) {
            setAchieved();
        }
        return getAchieved();
    }
};

class DailyGoalsMetrics {

    vector<IMetricGoal*> goals;
public:
    DailyGoalsMetrics(int calorieGoal, int stepGoal, double distanceGoal) {
        goals.push_back(new CalorieGoal(calorieGoal));
        goals.push_back(new StepGoal(stepGoal));
        goals.push_back(new DistanceGoal(distanceGoal));
    }
    void updateMetrics(HealthMetrics healthMetrics) {
        for(auto goal: goals) {
            if(CalorieGoal* calorieGoal = dynamic_cast<CalorieGoal*>(goal)) {
                calorieGoal->updateCalories(healthMetrics.caloriesBurned);
            } else if(StepGoal* stepGoal = dynamic_cast<StepGoal*>(goal)) {
                stepGoal->updateSteps(healthMetrics.steps);
            } else if(DistanceGoal* distanceGoal = dynamic_cast<DistanceGoal*>(goal)) {
                distanceGoal->updateDistance(healthMetrics.distance);
            }
        }
    }
    int getAchievedCount() {
        int count = 0;
        for(auto goal: goals) {
            if(goal->getAchieved()) {
                count++;
            }
        }
        return count;
    }
};

class IFitnessTrackerService {
public:
    virtual HealthMetrics getHealthMetrics() = 0;
};

class AppleFitnessTrackerService : public IFitnessTrackerService {
public:
    HealthMetrics getHealthMetrics();
};

class DailyGoalsService {
    DailyGoalsMetrics* dailyGoalsMetrics;
    IFitnessTrackerService* fitnessTrackerService;
    DBConnection* dbConn;
public:
    DailyGoalsService(DailyGoalsMetrics* dailyGoalsMetrics, IFitnessTrackerService* fitnessTrackerService, DBConnection* dbConn) : dailyGoalsMetrics(dailyGoalsMetrics), fitnessTrackerService(fitnessTrackerService), dbConn(dbConn){
    }

    void updateGoals() {
        HealthMetrics healthMetrics = fitnessTrackerService->getHealthMetrics();
        dailyGoalsMetrics->updateMetrics(healthMetrics);
    }

    void updateDailyGoalsToDB() {
        // updateDailyGoals to database.
        // Write Date, no. of goals achieved, calories, steps, distance, avg hearbeat.
    }
};

class NotificationService {
    NotificationService(DailyGoalsMetrics* dailyGoalsMetrics)  {
        // Based on some specific times, issue motivation/reminder notifications.
        // Query dailyGoalsMetrics for current status of goals.
    }
};

class DBConnection {
    // Connect to DB and store daily goals metrics.
};

class DailyAnalytics {
    int date;
    int goalsAchieved;
    int calories;
    int steps;
    double distance;
    int avgHeartBeat;
};

class AnalyticsService {
    DailyGoalsMetrics* dailyGoalsMetrics;
    DBConnection* dbConn;
public:
    AnalyticsService(DailyGoalsMetrics* dailyGoalsMetrics, DBConnection* dbConn) {
        // Query dailyGoalsMetrics for current status of goals.
    }
    vector<DailyAnalytics> getWeeklyAnalytics() {
        // Query DB for weekly data.
    }
    vector<DailyAnalytics> getMonthlyAnalytics() {
        // Query DB for weekly data.
    }
};
