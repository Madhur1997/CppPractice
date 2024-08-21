#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

/* 
FR:
1. Add an expense.
2. Add an expense in a group.
3. Get the balance of a user.
4. Get the balance of a user in a group.
5. Simplify debts in a group.
*/

class UserAccount {
    string name;
    int userId;
    int mobileNumber;
    string emailId;

public:
    UserAccount(string name, int userId, int mobileNumber, string emailId) : name(name), userId(userId), mobileNumber(mobileNumber), emailId(emailId) {}
};

class Group {
    string groupName;
    int groupId;
    vector<int> members;
public:
    Group(string groupName, int groupId, vector<int> members) : groupName(groupName), groupId(groupId), members(members) {}
    void addMember(int userId) {
        members.push_back(userId);
    }

    void removeMember(int userId) {
        for(auto iter=members.begin(); iter!=members.end(); iter++) {
            if(*iter == userId) {
                members.erase(iter);
                break;
            }
        }
    }
};

class Share {
    int userId;
    double amount;
};

class Expense {
    int expenseId;
    string timestamp;
    int paidBy;
    double amount;
    string description;
    vector<Share> shares;
public:
    Expense(int expenseId, int paidBy, double amount, string description, vector<Share> shares) : expenseId(expenseId), paidBy(paidBy), amount(amount), description(description), shares(shares) {}
};

// Indexes by user1-user2Id, groupId.
class ExpenseDao {
    unordered_map<int, vector<Expense>> individualExpenses, groupExpenses;
public:
    void addIndividualExpense(int relationId, Expense expense) {
        individualExpenses[relationId].push_back(expense);
    }

    void addGroupExpense(int relationId, Expense expense) {
        groupExpenses[relationId].push_back(expense);
    }

    vector<Expense> getExpenses(vector<int> userId, vector<int> relationIds) {
        vector<Expense> userExpenses;
        for(auto relationId:relationIds) {
            for(auto expense:expenses[relationId]) {
                if(expense.paidBy == userId) {
                    userExpenses.push_back(expense);
                }
                userExpenses.push_back(expense);
            }
        }
        return userExpenses;
    }

    vector<Expense> getGroupExpenses(, int userId, int groupId) {
        return expenses[groupId];
    }
};

// Maps userId to groupIds and other userIds.
class RelationshipDao {
    unordered_map<int, vector<int>> relations;
public:
    void addRelation(int userId, int relationId) {
        relations[userId].push_back(relationId);
    }

    vector<int> getRelations(int userId) {
        return relations[userId];
    }
};

enum BalanceStatus {
    POSITIVE,
    NEGATIVE,
    SETTLED
};

class UserBalanceDTO {
    int userId;
    double totalAmount;
    BalanceStatus status;
};

class SplitwiseManagementSystem {
    ExpenseDao* expenseDao;
    RelationshipDao* relationshipDao;
public:
    SplitwiseManagementSystem(ExpenseDao* expenseDao, RelationshipDao* relationshipDao) : expenseDao(expenseDao), relationshipDao(relationshipDao) {}

    void addIndividualExpense(int relationId, Expense expense) {
        expenseDao->addExpense(relationId, expense);
    }

    void addGroupExpense(int groupId, Expense expense) {
        expenseDao->addExpense(groupId, expense);
    }

    UserBalanceDTO getUserBalance(int userId) {
        vector<int> relationIds = relationshipDao->getRelations(userId);
        vector<int> userExpenses = expenseDao->getExpenses(userId, relationIds);

        double totalAmount = 0;
        for(auto expense:userExpenses) {
            for(auto share:expense.getShares()) {
                if(share.userId == userId) {
                    totalAmount += share.amount;
                }
            }
        }
        return UserBalanceDTO(userId, totalAmount);
    }

    UserBalanceDTO getGroupUserBalance(int userId) {

    }

};