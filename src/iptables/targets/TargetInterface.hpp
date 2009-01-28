/******************************************************************************
 * IPModule   Internet Protocol Implementation                                *
 * __________________________________________________________________________ *
 *                                                                            *
 * Copyright (C) 2005                                                         *
 * Lehrstuhl fuer Kommunikationsnetze (ComNets)                               *
 * Kopernikusstr. 16, D-52074 Aachen, Germany                                 *
 * phone: ++49-241-80-27910 (phone), fax: ++49-241-80-22242                   *
 * email: wns@comnetsrwth-aachen.de, www: http://wns.comnets.rwth-aachen.de/  *
 ******************************************************************************/

#ifndef IP_IPTABLES_TARGETS_TARGETINTERFACE_HPP
#define IP_IPTABLES_TARGETS_TARGETINTERFACE_HPP

#include <WNS/service/tl/TCPHeader.hpp>
#include <WNS/service/tl/UDPHeader.hpp>

namespace ip { namespace iptables { namespace targets {

    enum TargetResult {
        DROP = 1,
        ACCEPT = 2,
        CONT = 3
    };

    class TargetInterface
    {
    public:

        virtual
        ~TargetInterface() {};

        virtual TargetResult
        mangle(IPCommand*) = 0;

        virtual TargetResult
        mangle(IPCommand*, wns::service::tl::ITCPHeader*) = 0;

        virtual TargetResult
        mangle(IPCommand*, wns::service::tl::IUDPHeader*) = 0;
    };

    typedef wns::PyConfigViewCreator<TargetInterface, TargetInterface> TargetInterfaceCreator;

    typedef wns::StaticFactory<TargetInterfaceCreator> TargetInterfaceFactory;

} // targets
} // iptables
} // ip
#endif // IP_IPTABLES_TARGETS_TARGETINTERFACE_HPP
