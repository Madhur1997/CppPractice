#include<iostream>
#include<vector>
#include<queue>

using namespace std;

/* Functional requirements: 
1. Issue/Return/Reserve a book.
2. Calculate fine on return.
3. Send notification if a book is out of due date.
4. Search a book.
5. Search a customer.
6. Bar code scan a book -> shows all book information.
7. Bar code scan a user card -> shows all user information.
*/

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
    string houseNumber;
    string street;
    string city;
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
    bool searchCustomerReservation(Customer* customer);
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
    static BookRepository* getInstance();
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
    static CustomerRepository* getInstance();
    void registerCustomer();
    void removeCustomer();
    void updateCustomer();
    void searchCustomer();
};

/*
Run as a cron job(background thread) every day
Whenever a book item goes out of due date, issue a notification to the customer.
Uses book lending service to calculate fine.
*/
class BookNotificationService {
    BookLendingService* bookLendingService;
    BookRepository* bookRepository;
    thread dueDateNotificationThread;
public:
    BookNotificationService(BookLendingService* bookLendingService, BookRepository* bookRepository) : bookLendingService(bookLendingService), bookRepository(bookRepository) {
        dueDateNotificationThread = thread(&BookNotificationService::BookOutOfDueDateNotification, this);
    }

    void BookOutOfDueDateNotification();
    void BookInInventoryNotification();
};

class BookLendingService {
    BookRepository* bookRepository;
    CustomerRepository* customerRepository;

public:
    BookLendingService(BookRepository* bookRepository, CustomerRepository* customerRepository) : bookRepository(bookRepository), customerRepository(customerRepository){}
    bool ReserveBook(string customerId, string bookId);
    bool IssueBook(string customerId, string bookId);
    int CalculateFine(string bookId, int itemNumber);
    int ReturnBook(string bookId, int itemNumber);
};

/*
Barcode scan service is invoked when a book/customer card is scanned using the scanner. 
It fetches the book/customer information from the database and displays it on the screen.
The byte array scans to integer/long and then fetches the book/customer information from the database.
*/
class BarcodeScanService {
    static BarcodeScanService* instance;
    BookRepository* bookRepository_;
    BarcodeScanService() = default;
    BarcodeScanService(const BarcodeScanService& b) = delete;
    BarcodeScanService(BookRepository* bookRepository) : bookRepository_(bookRepository) {}
public:
    static BarcodeScanService* getInstance(BookRepository* bookRepository);
    BookItem* ScanBookItem(int bookId, int bookItemNumber);
    Customer* ScanCustomerCard(int customerId);
};