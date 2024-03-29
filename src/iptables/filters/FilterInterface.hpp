/*******************************************************************************
 * This file is part of openWNS (open Wireless Network Simulator)
 * _____________________________________________________________________________
 *
 * Copyright (C) 2004-2007
 * Chair of Communication Networks (ComNets)
 * Kopernikusstr. 5, D-52074 Aachen, Germany
 * phone: ++49-241-80-27910,
 * fax: ++49-241-80-22242
 * email: info@openwns.org
 * www: http://www.openwns.org
 * _____________________________________________________________________________
 *
 * openWNS is free software; you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License version 2 as published by the
 * Free Software Foundation;
 *
 * openWNS is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
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
