#ifndef PASSENGER_H
#define PASSENGER_H

class Passenger {
public:
    Passenger(int f, int w) :go_floor(f), wait_time(w), this_time(0) {}
    Passenger() {}

    Passenger &operator=(Passenger &t);

    int go_floor;
    int wait_time;
    int this_time;
};

Passenger &Passenger::operator=(Passenger &t) {
    if (this != &t) {
        this->go_floor = t.go_floor;
        this->wait_time = t.wait_time;
        this->this_time = t.this_time;
    }
    return *this;
}

#endif // PASSENGER_H
