#include <iostream>
#include "message.h"

int main() {
    custom::message msg;
    msg.readfile();
    msg.writetoconsole();
    msg.compress();
    return 0;
}
