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

#include <IP/Resolver.hpp>
#include <IP/VirtualDHCP.hpp>

using namespace ip::resolver;

STATIC_FACTORY_REGISTER_WITH_CREATOR(
	FixedAddressResolver,
	ResolverInterface,
	"ip.resolver.fixed",
	wns::PyConfigViewCreator);

STATIC_FACTORY_REGISTER_WITH_CREATOR(
	VirtualDHCPResolver,
	ResolverInterface,
	"ip.resolver.vdhcp",
	wns::PyConfigViewCreator);

FixedAddressResolver::FixedAddressResolver(const wns::pyconfig::View& _pyco):
  address(_pyco.get<std::string>("address")),
  subnetMask(_pyco.get<std::string>("subnetMask"))
{
}

void
FixedAddressResolver::resolve()
{
}

wns::service::nl::Address
FixedAddressResolver::getAddress()
{
	return address;
}

wns::service::nl::Address
FixedAddressResolver::getSubnetMask()
{
	return subnetMask;
}

VirtualDHCPResolver::VirtualDHCPResolver(const wns::pyconfig::View& _pyco)
{
  zone = _pyco.get<std::string>("vdhcpZone");
}

void
VirtualDHCPResolver::resolve()
{
	DHCPAck dhcpAck = TheDHCPService::Instance().getZoneManager(zone)->request();
	address = dhcpAck.address;
	subnetMask = dhcpAck.subnetMask;
}

wns::service::nl::Address
VirtualDHCPResolver::getAddress()
{
	return address;
}

wns::service::nl::Address
VirtualDHCPResolver::getSubnetMask()
{
	return subnetMask;;
}
