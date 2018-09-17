/*
 * Copyright (C) 2018  Christian Berger
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "cluon-complete.hpp"
#include "opendlv-standard-message-set.hpp"
#include <iostream>

// We will use chrono and thread to sleep for a while.
#include <chrono>
#include <thread>

int main(int argc, char **argv) {
    // We create an OD4Session that allows us to send data to a UDP multicast
    // session. We are using group number 253 and hence, all applications
    // belonging to the same group can receive message sent to it.
    cluon::OD4Session od4{253};

    while (od4.isRunning()) {
        // Now, we define a callback lambda that is invoked when a new message of
        // type opendlv::logic::sensation::Geolocation is received. All messages in an OD4Session are wrapped
        // into a cluon::data::Envelope that contains further information like
        // sent and received time stamp (cf. here: https://github.com/chrberger/libcluon/blob/master/libcluon/resources/cluonDataStructures.odvd#L23-L30)
        // Our lambda will hence be called being handed over the cluon::data::Envelope
        // that contains MyMessage.
        auto onMyMessage1 = [](cluon::data::Envelope &&env){
            // Now, we unpack the cluon::data::Envelope to get our message.
            opendlv::logic::sensation::Geolocation msg = cluon::extractMessage<opendlv::logic::sensation::Geolocation>(std::move(env));
            std::cout << "latitude = " << msg.latitude() << ", longitude = " << msg.longitude() << std::endl;
        };

        // Finally, we register our lambda for the message identifier for MyMessage.
        od4.dataTrigger(opendlv::logic::sensation::Geolocation::ID(), onMyMessage1);

        // Let's wait for 10s to receive messages.
        //using namespace std::chrono_literals;
        //std::this_thread::sleep_for(10s);
    }

    return 0;
}
