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

#ifndef IP_RESOLVER_HPP
#define IP_RESOLVER_HPP

#include <WNS/StaticFactory.hpp>
#include <WNS/service/nl/Address.hpp>
#include <WNS/PyConfigViewCreator.hpp>

namespace ip { namespace resolver {

	class ResolverInterface
	{
	public:
	  virtual
	  ~ResolverInterface() {};

	  virtual void
	  resolve() = 0;

	  virtual wns::service::nl::Address
	  getAddress() = 0;

	  virtual wns::service::nl::Address
	  getSubnetMask() = 0;
	};

	typedef wns::PyConfigViewCreator<ResolverInterface, ResolverInterface> Creator;

	typedef	wns::StaticFactory<resolver::Creator> Factory;

    /**
     * @brief Resolves to a static address
     *
     * \pyco{ip.AddressResolver.FixedAddressResolver}
     */
	class FixedAddressResolver:
		public ResolverInterface
	{

	public:
	  FixedAddressResolver(const wns::pyconfig::View& _pyco);

	  virtual void
	  resolve();

	  virtual wns::service::nl::Address
	  getAddress();

	  virtual wns::service::nl::Address
	  getSubnetMask();

	private:
	  wns::service::nl::Address address;
	  wns::service::nl::Address subnetMask;

	};

    /**
     * @brief Uses DHCP to resolve addresses
     *
     * \pyco{ip.AddressResolver.VirtualDHCPResolver}
     */
	class VirtualDHCPResolver:
		public ResolverInterface
	{

	public:
	  VirtualDHCPResolver(const wns::pyconfig::View& _pyco);

	  virtual void
	  resolve();

	  virtual wns::service::nl::Address
	  getAddress();

	  virtual wns::service::nl::Address
	  getSubnetMask();

	private:
	  wns::service::nl::Address address;
	  wns::service::nl::Address subnetMask;

	  std::string zone;
	};

}// resolver
}// ip
#endif // IP_RESOLVER_HPP
