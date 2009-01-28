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

#include <IP/iptables/PreroutingChain.hpp>

using namespace ip::iptables;

STATIC_FACTORY_REGISTER_WITH_CREATOR(
	PreroutingChain,
	wns::ldk::FunctionalUnit,
	"ip.iptables.preroutingchain",
	wns::ldk::FUNConfigCreator);


PreroutingChain::PreroutingChain(wns::ldk::fun::FUN* fun, const wns::pyconfig::View& _pyco):
	Chain(fun, _pyco),
	wns::Cloneable<PreroutingChain>(),
	fun(fun),
	log(_pyco.get("logger"))
{
}

void
PreroutingChain::onFUNCreated()
{
	assure(fun, "FUN not set!" );
	postroutingChain = fun->findFriend<ip::iptables::IRuleControl*>("postroutingChain");
	assure(postroutingChain, "PostroutingChain not found!");

	if(hasRules(99999))
	{
		dllFlowIDTarget = dynamic_cast<ip::iptables::targets::DLLFlowIDTarget*>(getRule(99999).getTarget());
		assure(dllFlowIDTarget, "Target not set");
		dllFlowIDTarget->setRuleController(postroutingChain);
	}
	Chain::onFUNCreated();
}
