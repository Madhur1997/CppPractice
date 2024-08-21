#include<bits/stdc++.h>

using namespace std;

/* FR:
    1. Search hotels by location and type.
    2. Search rooms within a hotel.
    3. Book Rooms in a hotel.
    4. View/Cancel user bookings.
    5. Admin can add Hotels/Rooms/Room availabilities.
*/

class Address {
    string addr1;
    string addr2;
    string city;
    string state;
    string country;
    int pincode;
};

enum HotelType {
    Star1,
    Star2,
    Star3,
    Star4,
    Star5
};

enum RoomType {
    Deluxe,
    Luxury,
    Suite
};

enum RoomStatus {
    Maintenance,
    Booked,
    Available
};

class RoomUnit {
    int roomId;
    RoomType roomType;
    // Date to status mapping.
    unordered_map<string, RoomStatus> roomStatusByDate;
};

class Room {
    int hotelId;
    RoomType roomType;
    string description;
    int beds;
    int count;
    list<RoomUnit> roomUnits;
};

class RoomDTO {
    int hotelId;
    RoomType roomType;
    string description;
    int beds;
    int count;
};

class Hotel {
    int id;
    string name;
    list<Room> rooms;
    Address address;
    HotelType hotelType;
};

class GuestDetails {
    string name;
    int age;
};

class GuestReservation {
    RoomType roomType;
    vector<GuestDetails> guestDetails;
};

class Booking {
    int id;
    string user;
    string checkIn;
    string checkOut;
    int numGuests;
    vector<GuestReservation> guestReservations;
    int hotelId;
};

class User {
    int id;
    string name;
    list<Booking> bookings;
};

class ISearchService {
public:
    virtual list<Hotel> searchHotelsByTypeAndCity(HotelType hotelType, string city)=0;
    virtual list<RoomDTO> searchRoomsByHotel(int hotelId)=0;
    virtual list<RoomDTO> searchRoomsByHotelRoomType()=0;
    virtual list<Booking> listBookingsByUser()=0;
};

class SearchService : public ISearchService {
    list<Hotel> hotels;
    list<User> users;
public:
    virtual list<Hotel> searchHotelsByTypeAndCity(HotelType hotelType, string city) override {} 
    virtual list<RoomDTO> searchRoomsByHotel(int hotelId) override {}
    virtual list<RoomDTO> searchRoomsByHotelRoomType() override {}
    virtual list<Booking> listBookingsByUser() override {}
};

class BookingService {

public:
    Booking bookRooms(int hotelId, vector<GuestReservation> guestReservations) {}
    bool cancelBooking(int userId, int bookingId) {}
};

class AdminService {
public:
    void addHotel(Hotel hotel) {}
    void addRoom(int hotelId, RoomType roomType) {}
    void addRoomUnit(int hotelId, RoomType roomType, int numberRooms) {}
    void addRoomAvailability(int hotelId, int roomId, RoomStatus roomStatus) {}
};