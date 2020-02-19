#include "current_date_time.pb.h"

#include <cstring>
#include <iostream>

int main() {

    protobuftest::CurrentDateTime::Date date;
    date.set_day(11);
    date.set_month(9);
    date.set_year(2001);
    date.set_weekday("Monday");


    uint8_t memory[1024] {};

    date.SerializeToArray(memory, sizeof(memory));

    protobuftest::CurrentDateTime::Date date2;
    date2.ParseFromArray(memory, sizeof(memory));
    std::cout << date2.weekday() << std::endl;

    return 0;
}
