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

#ifndef IP_IPTABLES_FILTERS_FILTERINTERFACE_HPP
#define IP_IPTABLES_FILTERS_FILTERINTERFACE_HPP

#include <IP/IPHeader.hpp>

#include <WNS/service/tl/TCPHeader.hpp>
#include <WNS/service/tl/UDPHeader.hpp>
#include <WNS/StaticFactory.hpp>
#include <WNS/PyConfigViewCreator.hpp>

namespace ip { namespace iptables { namespace filters {

    class FilterInterface
    {
    public:

        virtual
        ~FilterInterface() {};

        virtual bool
        fires(const IPCommand*) = 0;

        virtual bool
        fires(const IPCommand*, const wns::service::tl::ITCPHeader*) = 0;

        virtual bool
        fires(const IPCommand*, const wns::service::tl::IUDPHeader*) = 0;

    };

    typedef wns::PyConfigViewCreator<FilterInterface, FilterInterface> FilterInterfaceCreator;

    typedef wns::StaticFactory<FilterInterfaceCreator> FilterInterfaceFactory;

} // filters
} // iptables
} // ip
#endif // IP_IPTABLES_FILTERS_FILTERINTERFACE_HPP
