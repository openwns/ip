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

#ifndef IP_IPTABLES_FILTERS_SOURCEDESTINATIONFILTER_HPP
#define IP_IPTABLES_FILTERS_SOURCEDESTINATIONFILTER_HPP

#include <IP/iptables/filters/FilterInterface.hpp>

#include <WNS/service/nl/Address.hpp>

namespace ip { namespace iptables { namespace filters {

	class SourceDestinationFilter:
		public FilterInterface
	{
	public:
		SourceDestinationFilter(const wns::pyconfig::View& _pyco);

		SourceDestinationFilter(wns::service::nl::Address _source,
								wns::service::nl::Address _sourceMask,
								wns::service::nl::Address _destination,
								wns::service::nl::Address _destinationMask);

        virtual bool
        fires(const IPCommand*);

		virtual bool
        fires(const IPCommand*, const wns::service::tl::IUDPHeader*);

        virtual bool
        fires(const IPCommand*, const wns::service::tl::ITCPHeader*);

		bool
		operator ==(const SourceDestinationFilter& other) const;

	private:
		wns::service::nl::Address source;
		wns::service::nl::Address sourceMask;
		wns::service::nl::Address destination;
		wns::service::nl::Address destinationMask;
	};
} // filters
} // iptables
} // ip
#endif //IP_IPTABLES_FILTERS_SOURCEDESTINATIONFILTER_HPP
