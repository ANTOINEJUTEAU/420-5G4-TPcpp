#include "book.h"
#include <sstream>

//Constructeur par defaut pour Book

Book::Book()
    : title(""),
      author(""),
      isbn(""),
      isAvailable(true),
      borrowerId(""){

      }

// Constructeur avec paramètres pour Book
Book::Book(const string& title, const string& author, const string& isbn)
    : title(title),
      author(author),
      isbn(isbn),
      isAvailable(true),
      borrowerId("") {
}


//getter titre Book
string Book::getTitle() const {
    return title;
}

//getter auteur Book
string Book::getAuthor() const {
    return author;
}

//getter isbn Book
string Book::getISBN() const {
    return isbn;
}

//getter disponibilité Book
bool Book::getAvailability()const{
    return isAvailable;
}

//getter borrowerId
string Book::getBorrowerId()const{
    return borrowerId;
}

// Setter du titre
void Book::setTitle(const string& title) {
    this->title = title;
}

// Setter de l'auteur
void Book::setAuthor(const string& author) {
    this->author = author;
}

// Setter de l'isbn
void Book::setISBN(const string& isbn) {
    this->isbn = isbn;
}

// Setter de la disponibilité
void Book::setAvailability(bool available) {
    this->isAvailable = available;
}

// Setter du titre
void Book::setBorrowerId(const string& borrowerId) {
    this->borrowerId = borrowerId;
}

//Emprunter un livre
void Book::checkOut(const string& borrowerId) {
    if (isAvailable) {
        setBorrowerId(borrowerId);
        setAvailability(false);
    }
}

//Retourner un livre
void Book::returnBook(){
    setBorrowerId("");
    setAvailability(true);
}

//Methode toString
string Book::toString() const {
    string resultat = "Titre: " + title + "\n";
    resultat += "Auteur: " + author + "\n";
    resultat += "ISBN: " + isbn + "\n";

    if(isAvailable){
        resultat += "Statu: Disponible\n" ;
    } else {
        resultat += "Statu: Emprunté par : " + borrowerId + "\n";
    }

    return resultat;
}

string Book::toFileFormat() const {
    string resultat = title + "|" + author + "|" + isbn + "|";

    if(isAvailable){
        resultat += "1|";
    }else{
        resultat += "0|" + borrowerId;
    }

    return resultat;
}

void Book::fromFileFormat(const string& line) {
    string disponibilite;
    istringstream stream(line);

    getline(stream, title, '|');
    getline(stream, author, '|');
    getline(stream, isbn, '|');
    getline(stream, disponibilite, '|');

    isAvailable = (disponibilite == "1");

    getline(stream, borrowerId);
}