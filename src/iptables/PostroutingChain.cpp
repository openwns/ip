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

#include <IP/iptables/PostroutingChain.hpp>

using namespace ip::iptables;

STATIC_FACTORY_REGISTER_WITH_CREATOR(
	PostroutingChain,
	wns::ldk::FunctionalUnit,
	"ip.iptables.postroutingchain",
	wns::ldk::FUNConfigCreator);


PostroutingChain::PostroutingChain(wns::ldk::fun::FUN* fun, const wns::pyconfig::View& _pyco):
	Chain(fun, _pyco),
	wns::Cloneable<PostroutingChain>(),
	dllFlowIDTarget(NULL)
{
}

void
PostroutingChain::onFlowRemoved(wns::service::dll::FlowID flowID)
{
	if(hasRules(flowID))
	{
		removeRules(flowID);
	    removeFromDLLFlowIDTarget(flowID);
	}
	else
	{
		//rules are created when a packet with its Ruletag (flowID) arrive.
		//if no packet has ever arrived with this flowID there will be no Rule
		//with this RUletag (flowID)!!

		MESSAGE_BEGIN(NORMAL, log, m, "");
		m << "Warning! There are no Rules with this RuleTag: " << flowID;
		MESSAGE_END();
	}
}

void
PostroutingChain::registerDLLFlowIDTarget(targets::DLLFlowIDTarget* target)
{
	dllFlowIDTarget = target;
	assure(dllFlowIDTarget, "dllFlowIDTarget not set.");
}

void
PostroutingChain::removeFromDLLFlowIDTarget(wns::service::dll::FlowID flowID)
{
	dllFlowIDTarget->ruleErased(flowID);
}
