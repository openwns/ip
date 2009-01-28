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

#ifndef IP_IPTABLES_TARGETS_LOGGINGTARGET_HPP
#define IP_IPTABLES_TARGETS_LOGGINGTARGET_HPP

#include <IP/IPHeader.hpp>
#include <IP/iptables/targets/TargetInterface.hpp>

#include <WNS/pyconfig/View.hpp>
#include <WNS/logger/Logger.hpp>

namespace ip { namespace iptables { namespace targets {

	class LoggingTarget:
		public TargetInterface
	{
	public:

		LoggingTarget(const wns::pyconfig::View& _pyco);

		virtual
		~LoggingTarget();

        virtual TargetResult
        mangle(IPCommand*);

        virtual TargetResult
        mangle(IPCommand*, wns::service::tl::IUDPHeader*);

        virtual TargetResult
        mangle(IPCommand*, wns::service::tl::ITCPHeader*);

	private:
		wns::logger::Logger log;
	};

} // targets
} // iptables
} // ip
#endif // IP_IPTABLES_TARGETS_LOGGINGTARGET_HPP
