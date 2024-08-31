// --------------------- TEXT ANALYZER --------------------//

#include <iostream>
#include <algorithm> // For std::remove_if, std::unique
#include <vector>
#include <cstring>   // For strlen
using namespace std;

// Define escape sequences for text color
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"

// ------------------------Encryption And Decryption Class------------------------------------------
class EncryptDecrypt {
public:
    // ------------------------Encrypt Message------------------------------------------
    void encrypt(string &str) {
        int key = 5;
        for (char &c : str) {
            c = c + key;
        }
        cout << "\n\tThe Encrypted Text is : " << RED << str << RESET << "\n\n";
    }
    
    // ------------------------Decrypt Message------------------------------------------
    void decrypt(string &str) {
        int key = 5;
        for (char &c : str) {
            c = c - key;
        }
        cout << "\n\tThe Decrypted Text is : " << GREEN << str << RESET << "\n\n";
    }
};

// ------------------------Text Modifier Class------------------------------------------
class TextAnalyzer {
private:
    string str;

public:
    TextAnalyzer(const string &inputText) : str(inputText) {}
    
    // ------------------------REMOVE NUMBERS------------------------------------------
    void RemoveNumbers() {
        cout << "Written Text:\n" << str << "\n\n";
        str.erase(remove_if(str.begin(), str.end(), ::isdigit), str.end());
        cout << YELLOW << "\nWithout Numbers Text : " << RESET << str << "\n\n";
    }
    
    // ------------------------REMOVE SPACES------------------------------------------
    void RemoveSpaces() {
        cout << "Written Text:\n" << str << "\n\n";
        auto new_end = unique(str.begin(), str.end(), [](char a, char b) { return a == ' ' && b == ' '; });
        str.erase(new_end, str.end());
        cout << YELLOW << "\nWithout Extra Spaces Text : " << RESET << str << "\n\n";
    }
    
    // -------------------------UPPER CASE ----------------------------------------
    void UpperCase() {
        cout << "Written Text:\n" << str << "\n\n";
        for (char &c : str) {
            if (islower(c))
                c = toupper(c);
        }
        cout << YELLOW << "\nUpper Case Text is : " << RESET << str << "\n\n";
    }
    
    // -------------------------LOWER CASE -----------------------------------------
    void LowerCase() {
        cout << "Written Text:\n" << str << "\n\n";
        for (char &c : str) {
            if (isupper(c))
                c = tolower(c);
        }
        cout << YELLOW << "\nLower Case Text is : " << RESET << str << "\n\n";
    }
    
    // --------------------------NUMBER OF CHARACTERS-------------------------------
    int CountCharacters() {
        return str.length();
    }
    
    // --------------------------NUMBER OF WORDS------------------------------------
    int CountWords() {
        int numberofwords = 1;
        for (size_t i = 0; i < str.length(); i++) {
            if (str[i] == ' ')
                numberofwords++;
        }
        return numberofwords;
    }
    
    // --------------------------NUMBER OF SENTENCES--------------------------------
    int CountSentences() {
        int numberofsentences = 0;
        for (size_t i = 0; i < str.length(); i++) {
            if (str[i] == '.' && str[i + 1] == ' ')
                numberofsentences++;
        }
        return numberofsentences;
    }

    const string &getText() const { return str; }
    string &getText() { return str; }
    
    // -----------------------------FOUNDED EMAILS-----------------------------------
    void FindAndDisplayEmails() {
        cout << "Written Text:\n" << str << "\n\n";
        vector<string> emails;
        size_t pos = 0;
        while ((pos = str.find('@', pos)) != string::npos) {
            size_t start = pos, end = pos;
            while (start > 0 && str[start - 1] != ' ')
                start--;
            while (end < str.length() && str[end] != ' ')
                end++;
            emails.push_back(str.substr(start, end - start));
            pos = end;
        }

        if (emails.empty()) {
            cout << "Emails found in the text:\n";
            cout << "No emails\n";
        } else {
            cout << "Emails found in the text:\n";
            for (const auto &email : emails)
                cout << GREEN << email << RESET << endl;
        }
    }
};

// ------------------------Member Class------------------------------------------
class Member {
private:
    static int nextId; // Static variable to keep track of the next available ID
    int id;
    string name;
    string email;

public:
    Member(const string &name, const string &email) : id(nextId++), name(name), email(email) {}

    void DisplayInfo() const {
        cout << "\nMember ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Email: " << email << endl;
    }

    int getId() const { return id; }
    const string &getName() const { return name; }
    const string &getEmail() const { return email; }
};

// Initialize static member variable
int Member::nextId = 1;

// ------------------------Menu Class------------------------------------------
class Menu {
private:
    TextAnalyzer &analyzer;
    EncryptDecrypt encryptDecrypt;
    vector<Member> members;
    string encryptedText; // Store the encrypted text

public:
    Menu(TextAnalyzer &analyzerRef) : analyzer(analyzerRef) {}

    void DisplayOptions() {
        cout << "\nSelect an option:\n";
        cout << "1. Convert to Upper Case\n";
        cout << "2. Convert to Lower Case\n";
        cout << "3. Encrypt Your Text\n";
        cout << "4. Decrypt Your Text\n";
        cout << "5. Remove Extra Spacing\n";
        cout << "6. Remove all Numbers\n";
        cout << "7. Find and Display Email Addresses\n";
        cout << "8. Display Text Information\n";
        cout << "9. Register a New Member\n";
        cout << "0. Press 0 to Exit\n";
    }

    void ProcessChoice(int choice) {
        switch (choice) {
            case 1:
                analyzer.UpperCase();
                break;
            case 2:
                analyzer.LowerCase();
                break;
            case 3:
                encryptedText = analyzer.getText(); // Store the original text
                cout << "Written Text:\n" << analyzer.getText() << "\n\n";
                encryptDecrypt.encrypt(encryptedText);
                break;
            case 4:
                if (!encryptedText.empty()) {
                    cout << "Written Text:\n" << encryptedText << "\n\n";
                    encryptDecrypt.decrypt(encryptedText);
                    analyzer.getText() = encryptedText; // Update the text in the analyzer
                } else {
                    cout << "\n\t\"No text has been encrypted yet!\"\n" << endl;
                }
                break;
            case 5:
                analyzer.RemoveSpaces();
                break;
            case 6:
                analyzer.RemoveNumbers();
                break;
            case 7:
                analyzer.FindAndDisplayEmails();
                break;
            case 8:
                DisplayTextInformation();
                break;
            case 9:
                RegisterMember();
                break;
            default:
                cout << "\n\t\"Please Enter a Valid Choice !\"\n" << endl;
        }
    }

    void DisplayTextInformation() {
        cout << "\nText Information:\n";
        cout << "Number of characters: " << analyzer.CountCharacters() << endl;
        cout << "Number of words: " << analyzer.CountWords() << endl;
        cout << "Number of sentences: " << analyzer.CountSentences() << endl;
    }

    void RegisterMember() {
        string name, email;
        cout << "Enter name: ";
        getline(cin, name);
        cout << "Enter email: ";
        getline(cin, email);

        Member newMember(name, email);
        members.push_back(newMember);

        cout << "\nNew member registered successfully:\n";
        newMember.DisplayInfo();

        // Display the member's information at the top
        cout << "\nMember Information:\n";
        newMember.DisplayInfo();
    }
};

int main() {
    cout << RED << "\n------------------------ TEXT TOOL --------------------\n" << RESET;
    cout << YELLOW << "|                        PROJECT MADE BY:       \t  |" << RESET << endl;
    cout << YELLOW << "|                   \"SYED MOHAMMAD HUZAIFA\"  \t  |" << RESET << endl;
    cout << YELLOW << "|                   \"MUHAMMAD TAHA JAMALI\"\t\t  |" << RESET << endl;
    cout << YELLOW << "|                   \"SYED OWAIS TARIQ\"  \t  |" << RESET;
    cout << RED << "\n-----------------------------------------------------------\n" << RESET;

    string inputText;
    cout << "Enter the text: ";
    getline(cin, inputText);

    TextAnalyzer analyzer(inputText);
    Menu menu(analyzer);

    int choice;
    do {
        menu.DisplayOptions();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Ignore newline character left in the buffer
        if (choice != 0) {
            menu.ProcessChoice(choice);
        }
    } while (choice != 0);

    cout << "\n\t\"Thank you for using Text Analyzer!\"\n\n";
    return 0;
}