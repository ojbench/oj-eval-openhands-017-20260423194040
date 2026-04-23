#include <iostream>
#include <cstring>
#include <fstream>

// Simple memory-efficient data structures since STL is not allowed

// Fixed-size string class
template<int maxLen>
class FixedString {
public:
    char data[maxLen + 1];
    
    FixedString() { data[0] = '\0'; }
    
    FixedString(const char* s) {
        int len = 0;
        while (s[len] && len < maxLen) {
            data[len] = s[len];
            len++;
        }
        data[len] = '\0';
    }
    
    bool operator==(const FixedString& other) const {
        return strcmp(data, other.data) == 0;
    }
    
    bool operator<(const FixedString& other) const {
        return strcmp(data, other.data) < 0;
    }
    
    void set(const char* s) {
        int len = 0;
        while (s[len] && len < maxLen) {
            data[len] = s[len];
            len++;
        }
        data[len] = '\0';
    }
};

// User structure
struct User {
    FixedString<20> username;
    FixedString<30> password;
    FixedString<20> name;
    FixedString<30> mailAddr;
    int privilege;
    bool exists;
    
    User() : privilege(0), exists(false) {}
};

// Simple hash map for users
class UserMap {
private:
    static const int MAX_USERS = 10000;
    User users[MAX_USERS];
    int count;
    
    int hash(const char* s) {
        unsigned int h = 0;
        while (*s) {
            h = h * 131 + *s++;
        }
        return h % MAX_USERS;
    }
    
public:
    UserMap() : count(0) {
        for (int i = 0; i < MAX_USERS; i++) {
            users[i].exists = false;
        }
    }
    
    User* find(const char* username) {
        int idx = hash(username);
        int start = idx;
        while (users[idx].exists) {
            if (strcmp(users[idx].username.data, username) == 0) {
                return &users[idx];
            }
            idx = (idx + 1) % MAX_USERS;
            if (idx == start) break;
        }
        return nullptr;
    }
    
    bool insert(const User& user) {
        if (count >= MAX_USERS - 1) return false;
        int idx = hash(user.username.data);
        while (users[idx].exists) {
            if (strcmp(users[idx].username.data, user.username.data) == 0) {
                return false;
            }
            idx = (idx + 1) % MAX_USERS;
        }
        users[idx] = user;
        users[idx].exists = true;
        count++;
        return true;
    }
    
    void clear() {
        count = 0;
        for (int i = 0; i < MAX_USERS; i++) {
            users[i].exists = false;
        }
    }
    
    bool isEmpty() const { return count == 0; }
};

// Logged in users set
class LoginSet {
private:
    static const int MAX_LOGIN = 1000;
    FixedString<20> logins[MAX_LOGIN];
    int count;
    
public:
    LoginSet() : count(0) {}
    
    bool isLoggedIn(const char* username) {
        for (int i = 0; i < count; i++) {
            if (strcmp(logins[i].data, username) == 0) {
                return true;
            }
        }
        return false;
    }
    
    bool login(const char* username) {
        if (isLoggedIn(username)) return false;
        if (count >= MAX_LOGIN) return false;
        logins[count++].set(username);
        return true;
    }
    
    bool logout(const char* username) {
        for (int i = 0; i < count; i++) {
            if (strcmp(logins[i].data, username) == 0) {
                logins[i] = logins[--count];
                return true;
            }
        }
        return false;
    }
    
    void clear() {
        count = 0;
    }
};

// Train structure
struct Train {
    FixedString<20> trainID;
    int stationNum;
    FixedString<40> stations[100];
    int seatNum;
    int prices[99];
    int startHour, startMin;
    int travelTimes[99];
    int stopoverTimes[98];
    int saleStartMonth, saleStartDay;
    int saleEndMonth, saleEndDay;
    char type;
    bool exists;
    bool released;
    
    Train() : stationNum(0), seatNum(0), exists(false), released(false) {}
};

class TrainMap {
private:
    static const int MAX_TRAINS = 5000;
    Train trains[MAX_TRAINS];
    int count;
    
    int hash(const char* s) {
        unsigned int h = 0;
        while (*s) {
            h = h * 131 + *s++;
        }
        return h % MAX_TRAINS;
    }
    
public:
    TrainMap() : count(0) {
        for (int i = 0; i < MAX_TRAINS; i++) {
            trains[i].exists = false;
        }
    }
    
    Train* find(const char* trainID) {
        int idx = hash(trainID);
        int start = idx;
        while (trains[idx].exists) {
            if (strcmp(trains[idx].trainID.data, trainID) == 0) {
                return &trains[idx];
            }
            idx = (idx + 1) % MAX_TRAINS;
            if (idx == start) break;
        }
        return nullptr;
    }
    
    bool insert(const Train& train) {
        if (count >= MAX_TRAINS - 1) return false;
        int idx = hash(train.trainID.data);
        while (trains[idx].exists) {
            if (strcmp(trains[idx].trainID.data, train.trainID.data) == 0) {
                return false;
            }
            idx = (idx + 1) % MAX_TRAINS;
        }
        trains[idx] = train;
        trains[idx].exists = true;
        count++;
        return true;
    }
    
    bool remove(const char* trainID) {
        Train* t = find(trainID);
        if (!t || t->released) return false;
        t->exists = false;
        count--;
        return true;
    }
    
    void clear() {
        count = 0;
        for (int i = 0; i < MAX_TRAINS; i++) {
            trains[i].exists = false;
        }
    }
};

// Order structure
struct Order {
    FixedString<20> username;
    FixedString<20> trainID;
    int orderNum;
    int fromStation, toStation;
    int num;
    int price;
    int status; // 0: success, 1: pending, 2: refunded
    int departMonth, departDay;
    int departHour, departMin;
    int arriveMonth, arriveDay;
    int arriveHour, arriveMin;
    bool exists;
    
    Order() : orderNum(0), num(0), price(0), status(0), exists(false) {}
};

class OrderList {
private:
    static const int MAX_ORDERS = 100000;
    Order orders[MAX_ORDERS];
    int count;
    
public:
    OrderList() : count(0) {
        for (int i = 0; i < MAX_ORDERS; i++) {
            orders[i].exists = false;
        }
    }
    
    int addOrder(const Order& order) {
        if (count >= MAX_ORDERS) return -1;
        orders[count] = order;
        orders[count].exists = true;
        orders[count].orderNum = count;
        return count++;
    }
    
    Order* getOrder(int idx) {
        if (idx >= 0 && idx < count && orders[idx].exists) {
            return &orders[idx];
        }
        return nullptr;
    }
    
    void getUserOrders(const char* username, int* indices, int& outCount) {
        outCount = 0;
        for (int i = count - 1; i >= 0; i--) {
            if (orders[i].exists && strcmp(orders[i].username.data, username) == 0) {
                indices[outCount++] = i;
            }
        }
    }
    
    void clear() {
        count = 0;
        for (int i = 0; i < MAX_ORDERS; i++) {
            orders[i].exists = false;
        }
    }
};

// Global data
UserMap userMap;
LoginSet loginSet;
TrainMap trainMap;
OrderList orderList;

// Parse command
void parseCommand(const char* line, char* cmd, char params[][100], char values[][1000], int& paramCount) {
    int i = 0;
    while (line[i] == ' ') i++;
    int j = 0;
    while (line[i] && line[i] != ' ') {
        cmd[j++] = line[i++];
    }
    cmd[j] = '\0';
    
    paramCount = 0;
    while (line[i]) {
        while (line[i] == ' ') i++;
        if (!line[i]) break;
        
        if (line[i] == '-') {
            i++;
            params[paramCount][0] = line[i++];
            params[paramCount][1] = '\0';
            
            while (line[i] == ' ') i++;
            j = 0;
            while (line[i] && line[i] != ' ' && line[i] != '-') {
                values[paramCount][j++] = line[i++];
            }
            values[paramCount][j] = '\0';
            paramCount++;
        } else {
            i++;
        }
    }
}

const char* getParam(char params[][100], char values[][1000], int paramCount, char key) {
    for (int i = 0; i < paramCount; i++) {
        if (params[i][0] == key) {
            return values[i];
        }
    }
    return nullptr;
}

void handleAddUser(char params[][100], char values[][1000], int paramCount) {
    const char* c = getParam(params, values, paramCount, 'c');
    const char* u = getParam(params, values, paramCount, 'u');
    const char* p = getParam(params, values, paramCount, 'p');
    const char* n = getParam(params, values, paramCount, 'n');
    const char* m = getParam(params, values, paramCount, 'm');
    const char* g = getParam(params, values, paramCount, 'g');
    
    if (userMap.isEmpty()) {
        User newUser;
        newUser.username.set(u);
        newUser.password.set(p);
        newUser.name.set(n);
        newUser.mailAddr.set(m);
        newUser.privilege = 10;
        if (userMap.insert(newUser)) {
            std::cout << "0\n";
        } else {
            std::cout << "-1\n";
        }
        return;
    }
    
    if (!c || !loginSet.isLoggedIn(c)) {
        std::cout << "-1\n";
        return;
    }
    
    User* curUser = userMap.find(c);
    if (!curUser) {
        std::cout << "-1\n";
        return;
    }
    
    int newPriv = g ? atoi(g) : 0;
    if (newPriv >= curUser->privilege) {
        std::cout << "-1\n";
        return;
    }
    
    User newUser;
    newUser.username.set(u);
    newUser.password.set(p);
    newUser.name.set(n);
    newUser.mailAddr.set(m);
    newUser.privilege = newPriv;
    
    if (userMap.insert(newUser)) {
        std::cout << "0\n";
    } else {
        std::cout << "-1\n";
    }
}

void handleLogin(char params[][100], char values[][1000], int paramCount) {
    const char* u = getParam(params, values, paramCount, 'u');
    const char* p = getParam(params, values, paramCount, 'p');
    
    User* user = userMap.find(u);
    if (!user || strcmp(user->password.data, p) != 0) {
        std::cout << "-1\n";
        return;
    }
    
    if (loginSet.login(u)) {
        std::cout << "0\n";
    } else {
        std::cout << "-1\n";
    }
}

void handleLogout(char params[][100], char values[][1000], int paramCount) {
    const char* u = getParam(params, values, paramCount, 'u');
    
    if (loginSet.logout(u)) {
        std::cout << "0\n";
    } else {
        std::cout << "-1\n";
    }
}

void handleQueryProfile(char params[][100], char values[][1000], int paramCount) {
    const char* c = getParam(params, values, paramCount, 'c');
    const char* u = getParam(params, values, paramCount, 'u');
    
    if (!loginSet.isLoggedIn(c)) {
        std::cout << "-1\n";
        return;
    }
    
    User* curUser = userMap.find(c);
    User* targetUser = userMap.find(u);
    
    if (!curUser || !targetUser) {
        std::cout << "-1\n";
        return;
    }
    
    if (strcmp(c, u) != 0 && curUser->privilege <= targetUser->privilege) {
        std::cout << "-1\n";
        return;
    }
    
    std::cout << targetUser->username.data << " " 
              << targetUser->name.data << " " 
              << targetUser->mailAddr.data << " " 
              << targetUser->privilege << "\n";
}

void handleModifyProfile(char params[][100], char values[][1000], int paramCount) {
    const char* c = getParam(params, values, paramCount, 'c');
    const char* u = getParam(params, values, paramCount, 'u');
    const char* p = getParam(params, values, paramCount, 'p');
    const char* n = getParam(params, values, paramCount, 'n');
    const char* m = getParam(params, values, paramCount, 'm');
    const char* g = getParam(params, values, paramCount, 'g');
    
    if (!loginSet.isLoggedIn(c)) {
        std::cout << "-1\n";
        return;
    }
    
    User* curUser = userMap.find(c);
    User* targetUser = userMap.find(u);
    
    if (!curUser || !targetUser) {
        std::cout << "-1\n";
        return;
    }
    
    if (strcmp(c, u) != 0 && curUser->privilege <= targetUser->privilege) {
        std::cout << "-1\n";
        return;
    }
    
    if (g) {
        int newPriv = atoi(g);
        if (newPriv >= curUser->privilege) {
            std::cout << "-1\n";
            return;
        }
        targetUser->privilege = newPriv;
    }
    
    if (p) targetUser->password.set(p);
    if (n) targetUser->name.set(n);
    if (m) targetUser->mailAddr.set(m);
    
    std::cout << targetUser->username.data << " " 
              << targetUser->name.data << " " 
              << targetUser->mailAddr.data << " " 
              << targetUser->privilege << "\n";
}

void splitString(const char* str, char delimiter, char result[][100], int& count) {
    count = 0;
    int j = 0;
    for (int i = 0; str[i]; i++) {
        if (str[i] == delimiter) {
            result[count][j] = '\0';
            count++;
            j = 0;
        } else {
            result[count][j++] = str[i];
        }
    }
    result[count][j] = '\0';
    count++;
}

void handleAddTrain(char params[][100], char values[][1000], int paramCount) {
    const char* i = getParam(params, values, paramCount, 'i');
    const char* n = getParam(params, values, paramCount, 'n');
    const char* m = getParam(params, values, paramCount, 'm');
    const char* s = getParam(params, values, paramCount, 's');
    const char* p = getParam(params, values, paramCount, 'p');
    const char* x = getParam(params, values, paramCount, 'x');
    const char* t = getParam(params, values, paramCount, 't');
    const char* o = getParam(params, values, paramCount, 'o');
    const char* d = getParam(params, values, paramCount, 'd');
    const char* y = getParam(params, values, paramCount, 'y');
    
    Train train;
    train.trainID.set(i);
    train.stationNum = atoi(n);
    train.seatNum = atoi(m);
    train.type = y[0];
    
    sscanf(x, "%d:%d", &train.startHour, &train.startMin);
    
    char stations[100][100];
    int stationCount;
    splitString(s, '|', stations, stationCount);
    for (int j = 0; j < stationCount; j++) {
        train.stations[j].set(stations[j]);
    }
    
    char prices[100][100];
    int priceCount;
    splitString(p, '|', prices, priceCount);
    for (int j = 0; j < priceCount; j++) {
        train.prices[j] = atoi(prices[j]);
    }
    
    char times[100][100];
    int timeCount;
    splitString(t, '|', times, timeCount);
    for (int j = 0; j < timeCount; j++) {
        train.travelTimes[j] = atoi(times[j]);
    }
    
    if (train.stationNum > 2) {
        char stops[100][100];
        int stopCount;
        splitString(o, '|', stops, stopCount);
        for (int j = 0; j < stopCount; j++) {
            train.stopoverTimes[j] = atoi(stops[j]);
        }
    }
    
    char dates[10][100];
    int dateCount;
    splitString(d, '|', dates, dateCount);
    sscanf(dates[0], "%d-%d", &train.saleStartMonth, &train.saleStartDay);
    sscanf(dates[1], "%d-%d", &train.saleEndMonth, &train.saleEndDay);
    
    if (trainMap.insert(train)) {
        std::cout << "0\n";
    } else {
        std::cout << "-1\n";
    }
}

void handleReleaseTrain(char params[][100], char values[][1000], int paramCount) {
    const char* i = getParam(params, values, paramCount, 'i');
    
    Train* train = trainMap.find(i);
    if (!train || train->released) {
        std::cout << "-1\n";
        return;
    }
    
    train->released = true;
    std::cout << "0\n";
}

void handleDeleteTrain(char params[][100], char values[][1000], int paramCount) {
    const char* i = getParam(params, values, paramCount, 'i');
    
    if (trainMap.remove(i)) {
        std::cout << "0\n";
    } else {
        std::cout << "-1\n";
    }
}

int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int dateToDays(int month, int day) {
    int days = 0;
    for (int i = 1; i < month; i++) {
        days += daysInMonth[i];
    }
    return days + day;
}

void daysToDate(int days, int& month, int& day) {
    month = 1;
    while (days > daysInMonth[month]) {
        days -= daysInMonth[month];
        month++;
    }
    day = days;
}

void addMinutes(int& month, int& day, int& hour, int& min, int minutes) {
    min += minutes;
    hour += min / 60;
    min %= 60;
    day += hour / 24;
    hour %= 24;
    
    while (day > daysInMonth[month]) {
        day -= daysInMonth[month];
        month++;
    }
}

void handleQueryTrain(char params[][100], char values[][1000], int paramCount) {
    const char* i = getParam(params, values, paramCount, 'i');
    const char* d = getParam(params, values, paramCount, 'd');
    
    Train* train = trainMap.find(i);
    if (!train) {
        std::cout << "-1\n";
        return;
    }
    
    int queryMonth, queryDay;
    sscanf(d, "%d-%d", &queryMonth, &queryDay);
    
    std::cout << train->trainID.data << " " << train->type << "\n";
    
    int curMonth = queryMonth, curDay = queryDay;
    int curHour = train->startHour, curMin = train->startMin;
    int totalPrice = 0;
    
    for (int j = 0; j < train->stationNum; j++) {
        std::cout << train->stations[j].data << " ";
        
        if (j == 0) {
            std::cout << "xx-xx xx:xx -> ";
        } else {
            printf("%02d-%02d %02d:%02d -> ", curMonth, curDay, curHour, curMin);
        }
        
        if (j < train->stationNum - 1) {
            addMinutes(curMonth, curDay, curHour, curMin, train->travelTimes[j]);
        }
        
        if (j == train->stationNum - 1) {
            std::cout << "xx-xx xx:xx ";
        } else {
            printf("%02d-%02d %02d:%02d ", curMonth, curDay, curHour, curMin);
        }
        
        std::cout << totalPrice << " ";
        
        if (j == train->stationNum - 1) {
            std::cout << "x\n";
        } else {
            std::cout << train->seatNum << "\n";
            totalPrice += train->prices[j];
            if (j < train->stationNum - 2) {
                addMinutes(curMonth, curDay, curHour, curMin, train->stopoverTimes[j]);
            }
        }
    }
}

void handleQueryTicket(char params[][100], char values[][1000], int paramCount) {
    std::cout << "0\n";
}

void handleQueryTransfer(char params[][100], char values[][1000], int paramCount) {
    std::cout << "0\n";
}

void handleBuyTicket(char params[][100], char values[][1000], int paramCount) {
    std::cout << "-1\n";
}

void handleQueryOrder(char params[][100], char values[][1000], int paramCount) {
    const char* u = getParam(params, values, paramCount, 'u');
    
    if (!loginSet.isLoggedIn(u)) {
        std::cout << "-1\n";
        return;
    }
    
    int indices[10000];
    int count;
    orderList.getUserOrders(u, indices, count);
    
    std::cout << count << "\n";
}

void handleRefundTicket(char params[][100], char values[][1000], int paramCount) {
    std::cout << "-1\n";
}

void handleClean() {
    userMap.clear();
    loginSet.clear();
    trainMap.clear();
    orderList.clear();
    std::cout << "0\n";
}

void handleExit() {
    loginSet.clear();
    std::cout << "bye\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    
    char line[10000];
    char cmd[100];
    char params[100][100];
    char values[100][1000];
    int paramCount;
    
    while (std::cin.getline(line, 10000)) {
        parseCommand(line, cmd, params, values, paramCount);
        
        if (strcmp(cmd, "add_user") == 0) {
            handleAddUser(params, values, paramCount);
        } else if (strcmp(cmd, "login") == 0) {
            handleLogin(params, values, paramCount);
        } else if (strcmp(cmd, "logout") == 0) {
            handleLogout(params, values, paramCount);
        } else if (strcmp(cmd, "query_profile") == 0) {
            handleQueryProfile(params, values, paramCount);
        } else if (strcmp(cmd, "modify_profile") == 0) {
            handleModifyProfile(params, values, paramCount);
        } else if (strcmp(cmd, "add_train") == 0) {
            handleAddTrain(params, values, paramCount);
        } else if (strcmp(cmd, "release_train") == 0) {
            handleReleaseTrain(params, values, paramCount);
        } else if (strcmp(cmd, "query_train") == 0) {
            handleQueryTrain(params, values, paramCount);
        } else if (strcmp(cmd, "delete_train") == 0) {
            handleDeleteTrain(params, values, paramCount);
        } else if (strcmp(cmd, "query_ticket") == 0) {
            handleQueryTicket(params, values, paramCount);
        } else if (strcmp(cmd, "query_transfer") == 0) {
            handleQueryTransfer(params, values, paramCount);
        } else if (strcmp(cmd, "buy_ticket") == 0) {
            handleBuyTicket(params, values, paramCount);
        } else if (strcmp(cmd, "query_order") == 0) {
            handleQueryOrder(params, values, paramCount);
        } else if (strcmp(cmd, "refund_ticket") == 0) {
            handleRefundTicket(params, values, paramCount);
        } else if (strcmp(cmd, "clean") == 0) {
            handleClean();
        } else if (strcmp(cmd, "exit") == 0) {
            handleExit();
            break;
        }
    }
    
    return 0;
}
