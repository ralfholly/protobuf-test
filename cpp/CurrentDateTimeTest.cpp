#include "current_date_time.pb.h"

#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>

void buildMessage(protobuftest::CurrentDateTimeMessage* msg) {
    msg->set_title("A simple test");
    msg->set_counter(42);
    protobuftest::CurrentDateTimeMessage::Date* date = msg->mutable_date();
    date->set_day(11);
    date->set_month(9);
    date->set_year(2001);
    date->set_weekday("Monday");
    protobuftest::CurrentDateTimeMessage::Time* time = msg->mutable_time();
    time->set_hours(1);
    time->set_minutes(2);
    time->set_seconds(3);
}

bool storeMessage(const protobuftest::CurrentDateTimeMessage* msg, const char* fname) {
    std::ofstream serializingStream(fname, std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);
    return msg->SerializeToOstream(&serializingStream);
}

bool loadMessage(protobuftest::CurrentDateTimeMessage* msg, const char* fname) {
    std::ifstream serializingStream(fname, std::ofstream::binary);
    return msg->ParseFromIstream(&serializingStream);
}

void printMessage(const protobuftest::CurrentDateTimeMessage* msg) {
    auto originalFlags{ std::cout.flags() };

    std::cout << "Received a message:" << std::endl;
    std::cout << "\tTitle: " << msg->title() << std::endl;
    std::cout << "\tCounter: " << msg->counter() << std::endl;
    if (msg->has_date()) {
        const protobuftest::CurrentDateTimeMessage::Date& date = msg->date();
        std::cout << "\t" << date.weekday() << ", " << date.year() << "-" << std::setw(2) << std::setfill('0') <<
            date.month() << "-" << date.day() << std::endl;
    } else {
        std::cout << "No date element found!" << std::endl;
    }
    if (msg->has_time()) {
        const protobuftest::CurrentDateTimeMessage::Time& time = msg->time();
        std::cout << "\t" << time.hours() << ":" << time.minutes() << ":" << time.seconds() << std::endl;
    } else {
        std::cout << "No time element found!" << std::endl;
    }
    std::cout.flags(originalFlags);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Please provide a filename!" << std::endl;
        exit(1);
    }
    const char* fname = argv[1];

    std::ifstream f(fname);
    if (!f.good()) {
        std::cout << "Creating current date/time entry" << std::endl;
        protobuftest::CurrentDateTimeMessage msg;
        buildMessage(&msg);
        storeMessage(&msg, fname);
    }
    protobuftest::CurrentDateTimeMessage msg2;
    if (loadMessage(&msg2, fname)) {
        printMessage(&msg2);
    } else {
        std::cerr << "Failed to load message!" << std::endl;
    }

    return 0;
}
