/******************************************************************************
 * ProjModule (Short Description)                                             *
 * __________________________________________________________________________ *
 *                                                                            *
 * Copyright (C) 2005                                                         *
 * Lehrstuhl fuer Kommunikationsnetze (ComNets)                               *
 * Kopernikusstr. 16, D-52074 Aachen, Germany                                 *
 * phone: ++49-241-80-27910 (phone), fax: ++49-241-80-22242                   *
 * email: wns@comnetsrwth-aachen.de, www: http://wns.comnets.rwth-aachen.de/  *
 ******************************************************************************/

#ifndef IP_IPMODULE_HPP
#define IP_IPMODULE_HPP

#include <WNS/module/Module.hpp>
#include <WNS/logger/Logger.hpp>

#include <list>

namespace ip
{
	namespace node { namespace component { namespace ipv4 { class Component;}}}

         /**
	 * @brief IP Module implementation.
	 *
	 * \pyco{ip.IP.IP}
	 */
	class IPModule :
		public wns::module::Module<IPModule>
	{
	public:
		IPModule(const wns::pyconfig::View& _pyConfigView);
		virtual ~IPModule();

		virtual void configure();
		virtual void startUp();
		virtual void shutDown();

	private:
		wns::logger::Logger log;
	};
}

#endif // NOT defined IP_IPMODULE_HPP


