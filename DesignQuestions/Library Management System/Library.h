#include<iostream>
#include<vector>
#include<queue>

using namespace std;

enum BookFormat {
    HARDCOVER,
    PAPERBACK
};

enum ReservationStatus {
    AVAILABLE,
    ISSUED,
    AWAITING
};

class Address {
    string city;
    string street;
    string houseNumber;
    int pincode;
};

class BookItem {
    int itemNumber;
    BookFormat format;
    string customerId;
    ReservationStatus reservationStatus;
    time_t publicationDate;
    int rackNumber;

public:
    // Getter, Setters
};

class Book {
    string bookId;
    string author;
    string title;
    string metadata;
    vector<BookItem*> bookItems;
    queue<Customer*> customerReservations;
public:
    void addBookItem(BookItem* bookItem);
    void removeBookItem(BookItem* bookItem);
    void updateBookItem(BookItem* bookItem);
    void searchBookItem(BookItem* bookItem);
    void addCustomerReservation(Customer* customer);
    void removeCustomerReservation(Customer* customer);
    void updateCustomerReservation(Customer* customer);
    void searchCustomerReservation(Customer* customer);
};


class Person {
    string userId;
    string name;
    Address address;
    string email;
    string phone;
public:
    // Getter, Setters
    Person(int uin, string name, Address address, string email, string phone) : userId(userId), name(name), address(address), email(email), phone(phone) {}
    void updateAddress(Address address);
    void updateEmail(string email);
    void updatePhone(string phone);
};

class Customer : public Person {
    vector<BookItem*> checkedOutBooks;
    vector<BookItem*> reservedBooks;
public:
    void CheckoutBookItem(BookItem* bookItem);
    void ReturnBookItem(BookItem* bookItem);
    void ReserveBookItem(BookItem* bookItem);
    void UnReserveBookItem(BookItem* bookItem);
};

class Admin : public Person {
    vector<BookItem> BooksAdded;
public:
    void AddBookItem(BookItem* bookItem);
    void RemoveBookItem(BookItem* bookItem);
    void BlockMember(Customer* customer);
    void UnblockMember(Customer* customer);
};

class BookRepository {
    vector<Book*> books;
    static BookRepository* bookRepository;
    BookRepository() = default;
    BookRepository(const BookRepository & b) = delete;

public:
    BookRepository* getInstance();
    void addBook();
    void removeBook();
    void updateBook();
    void searchBook();
};

class CustomerRepository {
    vector<Customer*> customers;
    static CustomerRepository* customerRepository;
    CustomerRepository() = default;
    CustomerRepository(const CustomerRepository & u) = delete;
public:
    CustomerRepository* getInstance();
    void registerCustomer();
    void removeCustomer();
    void updateCustomer();
    void searchCustomer();
};

/*
Run as a cron job every day
Whenever a book item goes out of due date, issue a notification to the 
*/
class BookNotificationService {

};

class BookLendingService {
    BookRepository* bookRepository;
    CustomerRepository* customerRepository;

public:
    BookLendingService(BookRepository* bookRepository, CustomerRepository* customerRepository) : bookRepository(bookRepository), customerRepository(customerRepository){}
    bool ReserveBook(string customerId, string bookId);
    bool IssueBook(string customerId, string bookId);
};

class BookReturnService {
    BookRepository* bookRepository;
    CustomerRepository* customerRepository;

public:
    BookReturnService(BookRepository* bookRepository, CustomerRepository* customerRepository) : bookRepository(bookRepository), customerRepository(customerRepository){}
    int CalculateFine(string bookId, int itemNumber);
    int ReturnBook(string bookId, int itemNumber);
};

class BarCodeScanner {

};

class BarcodeScanService {
    BarCodeScanner* barCodeScanner;
public:
    BarcodeScanService(BarCodeScanner* barCodeScanner) : barCodeScanner(barCodeScanner){}
    BookItem* ScanBookItem();
};