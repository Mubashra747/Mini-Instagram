#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Post {
    string content;
    Post* next;
    Post(string content, Post* next = nullptr) {
        this->content = content;
        this->next = nullptr;
    }
};

struct Message {
    string content;
    Message* next;
    Message(string content, Message* next = nullptr) {
        this->content = content;
        this->next = nullptr;
    }
};

struct User {
    string name;
    string password;
    string city;
    Post* posts;
    Message* messages;
    vector<User*> friends;
    User(string name, string password, string city, Post* posts = nullptr, Message* messages = nullptr) {
        this->name = name;
        this->password = password;
        this->city = city;
        this->posts = posts;
        this->messages = messages;
    }
};

struct FriendRequest {
    string requester;
    FriendRequest* next;
    FriendRequest(string requester, FriendRequest* next = nullptr) {
        this->requester = requester;
        this->next = nullptr;
    }
};

struct Notification {
    string message;
    Notification* next;
    Notification(string message, Notification* next = nullptr) {
        this->message = message;
        this->next = nullptr;
    }
};

class UserManager {
private:
    vector<User*> userList;
    FriendRequest* requestQueue;
    Notification* notificationQueue;

public:
    UserManager() : requestQueue(nullptr), notificationQueue(nullptr) {}

    void addUser(string name, string password, string city) {
        for (User* user : userList) {
            if (user->name == name) {
                cout << "Username already exists!" << endl;
                return;
            }
        }
        User* newUser = new User(name, password, city);
        userList.push_back(newUser);
        cout << "User registered successfully!" << endl;
    }

    User* findUser(string name) {
        for (User* user : userList) {
            if (user->name == name) {
                return user;
            }
        }
        return nullptr;
    }

    bool login(string name, string password) {
        User* user = findUser(name);
        if (user != nullptr && user->password == password) {
            cout << "Login successful!" << endl;
            return true;
        }
        cout << "Invalid username or password!" << endl;
        return false;
    }

    void createPost(string userName, string content) {
        User* user = findUser(userName);
        if (user != nullptr) {
            Post* newPost = new Post(content, user->posts);
            user->posts = newPost;
            cout << "Post created!" << endl;
        }
        else {
            cout << "User not found!" << endl;
        }
    }

    void sendMessage(string fromUser, string toUser, string content) {
        User* sender = findUser(fromUser);
        User* receiver = findUser(toUser);
        if (sender != nullptr && receiver != nullptr) {
            Message* newMessage = new Message(content, sender->messages);
            sender->messages = newMessage;
            cout << "Message sent!" << endl;
        }
        else {
            cout << "User not found!" << endl;
        }
    }

    void displayPosts(string userName) {
        User* user = findUser(userName);
        if (user != nullptr) {
            Post* current = user->posts;
            cout << "Posts by " << userName << ":" << endl;
            while (current != nullptr) {
                cout << current->content << endl;
                current = current->next;
            }
        }
        else {
            cout << "User not found!" << endl;
        }
    }

    void sendFriendRequest(string fromUser, string toUser) {
        User* requester = findUser(fromUser);
        User* requestee = findUser(toUser);
        if (requester != nullptr && requestee != nullptr) {
            FriendRequest* newRequest = new FriendRequest(fromUser, requestQueue);
            requestQueue = newRequest;
            cout << "Friend request sent from " << fromUser << " to " << toUser << "!" << endl;
        }
        else {
            cout << "User not found!" << endl;
        }
    }

    void acceptFriendRequest(string fromUser, string toUser) {
        User* requester = findUser(fromUser);
        User* requestee = findUser(toUser);
        if (requester != nullptr && requestee != nullptr) {
            requester->friends.push_back(requestee);
            requestee->friends.push_back(requester);
            cout << toUser << " accepted the friend request from " << fromUser << "!" << endl;

            FriendRequest* temp = requestQueue;
            FriendRequest* prev = nullptr;
            while (temp != nullptr) {
                if (temp->requester == fromUser) {
                    if (prev == nullptr) {
                        requestQueue = temp->next;
                    }
                    else {
                        prev->next = temp->next;
                    }
                    delete temp;
                    break;
                }
                prev = temp;
                temp = temp->next;
            }
        }
        else {
            cout << "User not found!" << endl;
        }
    }

    void displayMessages(string userName) {
        User* user = findUser(userName);
        if (user != nullptr) {
            Message* current = user->messages;
            cout << "Messages for " << userName << ":" << endl;
            while (current != nullptr) {
                cout << current->content << endl;
                current = current->next;
            }
        }
        else {
            cout << "User not found!" << endl;
        }
    }

    void displayUserProfile(string userName) {
        User* user = findUser(userName);
        if (user != nullptr) {
            cout << "User Profile:" << endl;
            cout << "Name: " << user->name << endl;
            cout << "City: " << user->city << endl;
            cout << "Friends: ";
            for (User* friendUser : user->friends) {
                cout << friendUser->name << " ";
            }
            cout << endl;
        }
        else {
            cout << "User not found!" << endl;
        }
    }

    void displayNotifications() {
        Notification* current = notificationQueue;
        if (current == nullptr) {
            cout << "No notifications." << endl;
            return;
        }
        cout << "Notifications:" << endl;
        while (current != nullptr) {
            cout << current->message << endl;
            current = current->next;
        }
    }

    void addNotification(string message) {
        Notification* newNotification = new Notification(message, notificationQueue);
        notificationQueue = newNotification;
    }

    void userMenu() {
        int choice;
        string name, password, city, content, friendName;
        do {
            cout << "\n--- Mini Instagram Menu ---" << endl;
            cout << "1. Sign Up" << endl;
            cout << "2. Log In" << endl;
            cout << "3. Create Post" << endl;
            cout << "4. Send Message" << endl;
            cout << "5. Display Posts" << endl;
            cout << "6. Send Friend Request" << endl;
            cout << "7. Accept Friend Request" << endl;
            cout << "8. Display Messages" << endl;
            cout << "9. Display User Profile" << endl;
            cout << "10. Display Notifications" << endl;
            cout << "0. Exit" << endl;
            cout << "Choose an option: ";
            cin >> choice;

            switch (choice) {
            case 1:
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter password: ";
                cin >> password;
                cout << "Enter city: ";
                cin >> city;
                addUser(name, password, city);
                break;
            case 2:
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter password: ";
                cin >> password;
                if (login(name, password)) {
                    addNotification(name + " logged in.");
                }
                break;
            case 3:
                cout << "Enter your name: ";
                cin >> name;
                cout << "Enter post content: ";
                cin.ignore();
                getline(cin, content);
                createPost(name, content);
                break;
            case 4:
                cout << "Enter your name: ";
                cin >> name;
                cout << "Enter recipient's name: ";
                cin >> friendName;
                cout << "Enter message content: ";
                cin.ignore();
                getline(cin, content);
                sendMessage(name, friendName, content);
                break;
            case 5:
                cout << "Enter your name: ";
                cin >> name;
                displayPosts(name);
                break;
            case 6:
                cout << "Enter your name: ";
                cin >> name;
                cout << "Enter friend's name: ";
                cin >> friendName;
                sendFriendRequest(name, friendName);
                break;
            case 7:
                cout << "Enter requester's name: ";
                cin >> friendName;
                cout << "Enter your name: ";
                cin >> name;
                acceptFriendRequest(friendName, name);
                break;
            case 8:
                cout << "Enter your name: ";
                cin >> name;
                displayMessages(name);
                break;
            case 9:
                cout << "Enter your name: ";
                cin >> name;
                displayUserProfile(name);
                break;
            case 10:
                displayNotifications();
                break;
            case 0:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
            }
        } while (choice != 0);
    }
};

int main() {
    UserManager app;
    app.userMenu();
    return 0;
}
