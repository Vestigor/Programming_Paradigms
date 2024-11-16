/***********************************************************
* File:     problem.cpp
* Author:   Xiaolong Ma(马小龙)
* E-mail:   2353814@tongji.edu.com
* Compiler: CLion 2024
* Function: Manage User Profiles
* Date:     2024.11.16
* Update:   2024.11.16
***********************************************************/

#include <iostream>
#include <string>
#include <unordered_set>
#include <utility>

typedef unsigned long long ULL;

/***********************************************************
* Class Name:   UidManage
* Function:     A class for managing the generation and uniqueness of UIDs
* Description:  Ensures that each user receives a unique UID based on their rank (guest or user).
***********************************************************/
class UidManage {
private:
    std::unordered_set<ULL> existing_uids;
    ULL next_guest_uid = 50000001;
    ULL next_user_uid = 10000001;
public:
    ULL CreateUid(const std::string &rank);
};

/***********************************************************
* Function Name:   CreateUid
* Function:        Generate a new unique UID based on user rank
* Input Parameter: rank: The rank of the user ("guest" or "user")
* Returned Value:  The new unique UID
* Description:     The function ensures no two users share the same UID
***********************************************************/
ULL UidManage::CreateUid(const std::string &rank)
{
    ULL new_uid;
    if (rank == "guest")
        new_uid = next_guest_uid++;
    else
        new_uid = next_user_uid++;

    // Ensure the UID is unique by checking the existing_uids set
    while (existing_uids.find(new_uid) != existing_uids.end()) {
        if (rank == "guest") {
            new_uid = next_guest_uid++;
        }
        else {
            new_uid = next_user_uid++;
        }
    }
    existing_uids.insert(new_uid);// Store the new UID
    return new_uid;
}

/***********************************************************
* Class Name:   User_Prof
* Function:     Represents a user's profile including UID, rank, and match statistics
* Description:  Tracks user-specific data such as login times, played matches, and win ratios.
***********************************************************/
class User_Prof {
private:
    ULL uid; // User's unique identifier
    std::string name;
    int login_times;
    int played_matches;
    int won_matches;
    double won_ratio;
    std::string rank;
public:
    // Constructor to create a user profile with an auto-generated UID
    User_Prof(UidManage & uid_create,std::string user_name = "guest", std::string user_rank = "beginner")
        : name(std::move(user_name)), login_times(0), played_matches(0), won_matches(0), won_ratio(0.0), rank(std::move(user_rank))
    {
        // Generate a UID using the provided UID manager
        uid = uid_create.CreateUid(name);

    }

    ULL GetUid() const{return uid;}

    void Login(){login_times++;}

    void Logout();

    void AddMatch(bool won);

    bool Test_Equivalence(const User_Prof &other){return *this==other;}

    bool TestNotEquivalence(const User_Prof &other){return !Test_Equivalence(other);}

    bool operator==(const User_Prof &other) const;

    void PrintProfile() const;
};

/***********************************************************
* Function Name:   Logout
* Function:        Update user's rank based on match statistics
* Input Parameter: None
* Returned Value:  None
* Description:     Changes the user's rank when they log out, based on their performance
***********************************************************/
void User_Prof::Logout()
{
    // Check if the user has met the threshold for rank upgrade
    if (login_times >= 10 && won_matches >= 10) {
        if (won_ratio >= 0.7)
            rank = "expert";
        else if (won_ratio >= 0.5)
            rank = " professional";
        else
            rank = "beginner";
    }
}

/***********************************************************
* Function Name:   AddMatch
* Function:        Add a match result (win or loss) to the user's statistics
* Input Parameter: won: true if the user won, false if the user lost
* Returned Value:  None
* Description:     Increments played matches, won matches, and recalculates win ratio
***********************************************************/
void User_Prof::AddMatch(bool won)
{
    played_matches++;
    if (won) {
        won_matches++;
    }
    // Recalculate win ratio
    if (played_matches > 0)
        won_ratio = static_cast<double>(won_matches) / played_matches;
}

/***********************************************************
* Function Name:   operator==
* Function:        Compare two User_Prof objects for equality
* Input Parameter: other: The other User_Prof object to compare
* Returned Value:  true if all attributes are equal, false otherwise
***********************************************************/
bool User_Prof::operator==(const User_Prof &other) const
{
    return (uid == other.uid && name == other.name &&
            login_times == other.login_times &&
            played_matches == other.played_matches &&
            won_matches == other.won_matches &&
            won_ratio == other.won_ratio &&
            rank == other.rank);
}

/***********************************************************
* Function Name:   PrintProfile
* Function:        Print the user's profile to the console
* Input Parameter: None
* Returned Value:  None
* Description:     Displays user information, including UID, name, rank, and statistics
***********************************************************/
void User_Prof::PrintProfile() const
{
    std::cout << "UID: " << uid << "\n"
            << "Name: " << name << "\n"
            << "Rank: " << rank << "\n"
            << "Login Times: " << login_times << "\n"
            << "Played Matches: " << played_matches << "\n"
            << "Won Matches: " << won_matches << "\n"
            << "Win Ratio: " << won_ratio << "\n";
}

/***********************************************************
* Function Name:   main
* Function:        Demonstrates the functionality of UID management and user profile creation
* Input Parameter: None
* Returned Value:  0 on success
* Description:     Creates users with different ranks, logs them in, updates their profiles, and displays the information.
***********************************************************/
int main()
{
    // Create UID manager instance
    UidManage uid_create;

    // Create user profiles with different ranks
    User_Prof user1(uid_create,"Alice", "professional");
    User_Prof user2(uid_create,"Bob", "beginner");
    User_Prof user3(uid_create,"guest", "beginner");

    // Display profiles for each user
    std::cout << "User 1 Profile:\n";
    user1.PrintProfile();

    std::cout << "\nUser 2 Profile:\n";
    user2.PrintProfile();

    std::cout << "\nUser 3 Profile (guest):\n";
    user3.PrintProfile();

    // Create another guest user profile and display it
    User_Prof user4(uid_create,"guest", "beginner");
    std::cout << "\nUser 4 Profile (guest):\n";
    user4.PrintProfile();

    return 0;
}