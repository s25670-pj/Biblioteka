#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const string booksFileName = "ksiazki.txt";
const string usersFileName = "uzytkownicy.txt";

void logging(vector <string>& booksList, vector <string>& usersList);
bool loginAttempt(vector <string> usersList, string nickname, string password);
void showUsers(vector <string>& usersList);
void showBooks(vector <string> books);
void rentBook(vector <string>& booksList, string holderNickname);
void returnBook(vector <string>& booksList, string holderNickname);
void addUser(vector <string>& usersList);
void addBook(vector <string>& booksList);
void showAdminMenu(vector <string>& booksList, vector <string>& usersList);
void showMenu(vector <string>& booksList, string nickname);
void updateFiles(vector <string>& booksList);
void updateFiles(vector <string>& booksList, vector <string>& usersList);

int main()
{
    fstream booksFile, usersFile;
    
    string line;
    vector <string> usersList;
    vector <string> booksList;

    booksFile.open(booksFileName, ios::in);
    usersFile.open(usersFileName, ios::in);

    if (!booksFile.good() || !booksFile.good())
        cout << "Nie znaleziono pliku!";
    else
    {
        while (!usersFile.eof())
        {
            getline(usersFile, line);
            usersList.push_back(line);
        }
        while (!booksFile.eof())
        {
            getline(booksFile, line);
            booksList.push_back(line);
        }  
    }

    booksFile.close();
    usersFile.close();

    logging(booksList, usersList);

    return 0;
}

void logging(vector <string>& booksList, vector <string>& usersList)
{
    string nickname, password;
    
    cout << "Podaj login: " << endl;
    getline(cin, nickname);
    cout << "Podaj haslo: " << endl;
    getline(cin, password);

    if (loginAttempt(usersList, nickname, password) && nickname != "" && password != "")
    {
        if (nickname == "admin")
            showAdminMenu(booksList, usersList);
        else
            showMenu(booksList, nickname);
    }
    else
    {
        system("CLS");
        cout << "Nieprawdlowe dane, kliknij ENTER aby sprobowac ponownie.";
        getchar();
        logging(booksList, usersList);
    }   
}

void showBooks(vector <string> booksList)
{
    int commaCounter;

    vector <char> title;
    vector <char> author;
    vector <char> availability;
    vector <char> rentDate;
    vector <char> holderName;

    for (unsigned int i = 0; i < booksList.size(); i++)
    {
        commaCounter = 0;
        cout << "Pozycja nr " << booksList[i][0] << endl;

        for (unsigned int j = 0; j < booksList[i].length(); j++)
        {
            if (commaCounter == 1)
            {
                if (booksList[i][j] != ';')
                    title.push_back(booksList[i][j]);
            }
            else if (commaCounter == 2)
            {
                if (booksList[i][j] != ';')
                    author.push_back(booksList[i][j]);
            }
            else if (commaCounter == 3)
            {
                if (booksList[i][j] != ';')
                    availability.push_back(booksList[i][j]);
            }
            else if (commaCounter == 4)
            {
                if (booksList[i][j] != ';')
                    rentDate.push_back(booksList[i][j]);
            }
            else if (commaCounter == 5)
            {
                if (booksList[i][j] != ';')
                    holderName.push_back(booksList[i][j]);
            }

            if (booksList[i][j] == ';')
                commaCounter++;
        }

        cout << "Tytul: ";
        for (unsigned int k = 0; k < title.size(); k++)
        {
            cout << title[k];
        }
        cout << endl;
        title.clear();

        cout << "Autor: ";
        for (unsigned int l = 0; l < author.size(); l++)
        {
            cout << author[l];
        }
        cout << endl;
        author.clear();

        cout << "Status: ";
        for (unsigned int m = 0; m < availability.size(); m++)
        {
            cout << availability[m];
        }
        cout << endl;
        availability.clear();

        cout << "Ostatni raz wypozyczona: ";
        for (unsigned int n = 0; n < rentDate.size(); n++)
        {
            cout << rentDate[n];
        }
        cout << endl;
        rentDate.clear();

        cout << "Przez: ";
        for (unsigned int o = 0; o < holderName.size(); o++)
        {
            cout << holderName[o];
        }
        cout << endl;
        holderName.clear();

        cout << endl;
    }
}

void rentBook(vector <string>& booksList, string holderNickname)
{
    char choice;
    unsigned int size;
    string dd, mm, yyyy, date;

    showBooks(booksList);

    cout << "Podaj nr ksiazki, ktora chcesz wypozyczyc: ";
    cin >> choice;

    system("CLS");

    for (unsigned int i = 0; i < booksList.size(); i++)
    {
        if (choice == booksList[i][0])
        {
            if (booksList[i].find("wypozyczona") != string::npos)
            {
                system("CLS");
                cout << "Niestety wybrana pozycja jest zajeta, kliknij ENTER aby ponowic probe";
                getchar(); getchar();
                rentBook(booksList, holderNickname);
            }
            else
            {
                system("CLS");
                cout << "Wprowadz date wypozyczenia" << endl;
                cout << "Dzien (dd): ";
                cin >> dd;
                cout << "Miesiac (mm): ";
                cin >> mm;
                cout << "Rok (rrrr): ";
                cin >> yyyy;

                date =  dd + "/" + mm + "/" + yyyy;

                size = booksList[i].size();
                booksList[i] = booksList[i].erase(size - 21, size) + "wypozyczona;" + date + ";" + '"' + holderNickname + '"';
            }
        }
    }
}

void returnBook(vector <string>& booksList, string holderNickname)
{
    char choice;
    unsigned int size;
    string date;

    showBooks(booksList);

    cout << "Podaj nr ksiazki, ktora chcesz zworcic: ";
    cin >> choice;

    system("CLS");

    for (unsigned int i = 0; i < booksList.size(); i++)
    {
        if (choice == booksList[i][0])
        {
            if (booksList[i].find("dostepna") != string::npos || booksList[i].find('"' + holderNickname + '"') == string::npos)
            {
                system("CLS");
                cout << "Nie mozesz zwrocic ksiazki ktora jest dostepna lub nie jest przypisana do Ciebie, kliknij ENTER aby ponowic probe.";
                getchar(); getchar();
                returnBook(booksList, holderNickname);
            }
            else
            {
                size = booksList[i].size();

                for (unsigned int j = size - holderNickname.length() - 13; j < size - holderNickname.length() - 2; j++)
                {
                    date.push_back(booksList[i][j]);
                }

                booksList[i] = booksList[i].erase(size - holderNickname.length() - 25, size) + "dostepna;" + date + '"' + holderNickname + '"';
            }
        }
    }
}

void showUsers(vector <string>& usersList)
{
    int commaCounter;

    vector <char> nickname;
    vector <char> password;

    for (unsigned int i = 0; i < usersList.size(); i++)
    {
        commaCounter = 0;
        cout << "ID nr " << usersList[i][0] << endl;

        for (unsigned int j = 0; j < usersList[i].length(); j++)
        {
            if (commaCounter == 1)
            {
                if (usersList[i][j] != ';')
                    nickname.push_back(usersList[i][j]);
            }
            else if (commaCounter == 2)
            {
                if (usersList[i][j] != ';')
                    password.push_back(usersList[i][j]);
            }

            if (usersList[i][j] == ';')
                commaCounter++;
        }

        cout << "Nazwa uzytkownika: ";
        for (unsigned int k = 0; k < nickname.size(); k++)
        {
            cout << nickname[k];
        }
        cout << endl;
        nickname.clear();

        cout << "Haslo: ";
        for (unsigned int l = 0; l < password.size(); l++)
        {
            cout << password[l];
        }
        cout << endl;
        password.clear();

        cout << endl;
    }
}

void addUser(vector <string>& usersList)
{
    string nickname, password, newUser;
    int newUserID = usersList.size() + 1;

    cin.ignore();

    cout << "Podaj nazwe nowego uzytkownika: ";
    getline(cin, nickname);
    cout << "Podaj haslo: ";
    getline(cin, password);

    newUser = to_string(newUserID) + ";" + nickname + ";" + password;
    usersList.push_back(newUser);
}

void addBook(vector <string>& booksList)
{
    string title, author, newBook;
    int newBookID = booksList.size() + 1;

    cin.ignore();

    cout << "Podaj tytul ksiazki: ";
    getline(cin, title);
    cout << "Podaj autora: ";
    getline(cin, author);

    newBook = to_string(newBookID) + ";" + title + ";" + author + ";dostepna;nigdy;nikogo";
    booksList.push_back(newBook);
}

bool loginAttempt(vector <string> usersList, string nickname, string password)
{
    bool appear = false;

    for (unsigned int i = 0; i < usersList.size(); i++)
    {
        if (usersList[i].find(nickname + ";" + password) != string::npos)
        {
            appear = true;
        }
    }

    if (appear)
        return true;
    else
        return false;
}

void showAdminMenu(vector <string>& booksList, vector <string>& usersList)
{
    unsigned int choice;

    system("CLS");

    cout << "Wybierz opcje: " << endl;
    cout << "1) Wyswietl ksiazki" << endl;
    cout << "2) Wyswietl uzytkownikow" << endl;
    cout << "3) Dodaj uzytkownika" << endl;
    cout << "4) Dodaj ksiazke" << endl;
    cout << "0) Wyjdz" << endl;

    cin >> choice;

    switch (choice)
    {
    case 1:
        system("CLS");
        showBooks(booksList);
        cout << "Wcisnij ENTER aby powrocic do menu.";
        getchar(); getchar();
        showAdminMenu(booksList, usersList);
        break;
    case 2:
        system("CLS");
        showUsers(usersList);
        cout << "Wcisnij ENTER aby powrocic do menu.";
        getchar(); getchar();
        showAdminMenu(booksList, usersList);
        break;
    case 3:
        system("CLS");
        addUser(usersList);
        cout << "Dodoano nowego uzytkownika, kliknij ENTER aby poworcic do menu." << endl;
        getchar();
        showAdminMenu(booksList, usersList);
        break;
    case 4:
        system("CLS");
        addBook(booksList);
        cout << "Dodoano nowa ksiazke, kliknij ENTER aby poworcic do menu." << endl;
        getchar();
        showAdminMenu(booksList, usersList);
        break;
    case 0:
        system("CLS");
        cout << "Do widzenia";
        updateFiles(booksList, usersList);
        exit(0);
        break;
    default:
        break;
    }
}

void showMenu(vector <string>& booksList, string nickname)
{
    unsigned int choice;

    system("CLS");

    cout << "Wybierz opcje: " << endl;
    cout << "1) Wyswietl ksiazki" << endl;
    cout << "2) Wypozycz ksiazke" << endl;
    cout << "3) Zwroc ksiazke" << endl;
    cout << "0) Wyjdz" << endl;

    cin >> choice;

    switch (choice)
    {
    case 1:
        system("CLS");
        showBooks(booksList);
        cout << "Wcisnij ENTER aby powrocic do menu.";
        getchar(); getchar();
        showMenu(booksList, nickname);
        break;
    case 2:
        rentBook(booksList, nickname);
        system("CLS");
        cout << "Wybrana ksiazka zostala wypozyczona, kliknij ENTER aby powrocic do menu.";
        getchar(); getchar();
        showMenu(booksList, nickname);
        break;
    case 3:
        returnBook(booksList, nickname);
        system("CLS");
        cout << "Wybrana ksiazka zostala zworcona, kliknij ENTER aby powrocic do menu.";
        getchar(); getchar();
        showMenu(booksList, nickname);
        break;
    case 0:
        system("CLS");
        cout << "Do widzenia";
        updateFiles(booksList);
        exit(0);
        break;
    default:
        break;
    }
}

void updateFiles(vector <string>& booksList)
{
    fstream updateBooksFile;

    updateBooksFile.open(booksFileName, ios::out);

    if (!updateBooksFile.good())
    {
        cout << "Nie znaleziono pliku";
    }
    else
    {
        for (unsigned int i = 0; i < booksList.size(); i++)
        {
            if (i == booksList.size() - 1)
                updateBooksFile << booksList[i];
            else
                updateBooksFile << booksList[i] << endl;
        }
    }

    updateBooksFile.close();
}

void updateFiles(vector <string>& booksList, vector <string>& usersList)
{
    fstream updateBooksFile, updateUsersFile;
    
    updateBooksFile.open(booksFileName, ios::out);
    updateUsersFile.open(usersFileName, ios::out);

    if (!updateBooksFile.good() || !updateUsersFile.good())
    {
        cout << "Nie znaleziono pliku";
    }
    else
    {
        for (unsigned int i = 0; i < booksList.size(); i++)
        {
            if (i == booksList.size() - 1)
                updateBooksFile << booksList[i];
            else
                updateBooksFile << booksList[i] << endl;
        }

        for (unsigned int j = 0; j < usersList.size(); j++)
        {
            if (j == usersList.size() - 1)
                updateUsersFile << usersList[j];
            else
                updateUsersFile << usersList[j] << endl;
        }
    }

    updateBooksFile.close();
    updateUsersFile.close();
}