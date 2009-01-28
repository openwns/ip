/******************************************************************************
 * IPModule   Internet Protocol Implementation                                *
 * __________________________________________________________________________ *
 *                                                                            *
 * Copyright (C) 2004-2006                                                    *
 * Chair of Communication Networks (ComNets)                                  *
 * Kopernikusstr. 16, D-52074 Aachen, Germany                                 *
 * phone: ++49-241-80-27910 (phone), fax: ++49-241-80-22242                   *
 * email: wns@comnets.rwth-aachen.de                                          *
 * www: http://wns.comnets.rwth-aachen.de                                     *
 ******************************************************************************/

#ifndef IP_TESTS_DLLSTUB_HPP
#define IP_TESTS_DLLSTUB_HPP

#include <WNS/service/dll/DataTransmission.hpp>
#include <WNS/service/dll/Handler.hpp>
#include <WNS/node/component/Component.hpp>

namespace ip  { namespace tests  {

	class DLLStub :
		public virtual wns::service::dll::UnicastDataTransmission
	{
	public:

		DLLStub() {};

		virtual
		~DLLStub() {};

		virtual void
		sendData(
			const wns::service::dll::UnicastAddress&,
			const wns::osi::PDUPtr&,
			wns::service::dll::protocolNumber /*protocol*/) {};

		virtual wns::service::dll::UnicastAddress
		getMACAddress() const { return wns::service::dll::UnicastAddress(); }
	};
} // tests
} // ip
#endif //IP_TESTS_DLLSTUB_HPP
