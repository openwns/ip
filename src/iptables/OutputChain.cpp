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

#include <IP/iptables/OutputChain.hpp>

using namespace ip::iptables;

STATIC_FACTORY_REGISTER_WITH_CREATOR(
	OutputChain,
	wns::ldk::FunctionalUnit,
	"ip.iptables.outputchain",
	wns::ldk::FUNConfigCreator);


OutputChain::OutputChain(wns::ldk::fun::FUN* fun, const wns::pyconfig::View& _pyco):
	Chain(fun, _pyco),
	wns::Cloneable<OutputChain>()
{
}

