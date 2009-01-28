##############################################################################
# IPModule   Internet Protocol Implementation                                #
# __________________________________________________________________________ #
#                                                                            #
# Copyright (C) 2005                                                         #
# Lehrstuhl fuer Kommunikationsnetze (ComNets)                               #
# Kopernikusstr. 16, D-52074 Aachen, Germany                                 #
# phone: ++49-241-80-27910 (phone), fax: ++49-241-80-22242                   #
# email: wns@comnetsrwth-aachen.de, www: http://wns.comnets.rwth-aachen.de/  #
##############################################################################

import IPTables
from ip.Tunnel import TunnelExitComponent, TunnelEntryComponent
from ip.AddressResolver import FixedAddressResolver, VirtualDHCPResolver

import wns
import wns.FlowSeparator
import wns.Buffer
import wns.Group
import wns.Tools
import wns.FUN

from wns.Node import Component
from Logger import Logger


class RoutingTableEntry:
    netaddress = None

    netmask = None

    gateway = None

    dllName = None

    def __init__(self, _netAddress, _netmask, _gateway, _dllName):
        self.netaddress = _netAddress
        self.netmask = _netmask
        self.gateway = _gateway
        self.dllName = _dllName

class DLLListEntry:

    name = None

    addressResolver = None

    arpZone = None

    dllDataTransmission = None

    dllNotification = None

    pointToPoint = None

    traceEnabled  = None

    def __init__(self, _name, _addressResolver, _arpZone, _pointToPoint, _dllDataTransmission, _dllNotification, _traceEnabled = False):
        self.name = _name
        self.addressResolver = _addressResolver
        self.arpZone = _arpZone
        self.dllDataTransmission = _dllDataTransmission
        self.dllNotification = _dllNotification
        self.pointToPoint = _pointToPoint
        self.traceEnabled = _traceEnabled

class LinkHandler:

    type = "wns.ldk.SimpleLinkHandler"

    isAcceptingLogger = None
    sendDataLogger = None
    wakeupLogger = None
    onDataLogger = None

    traceCompoundJourney = True

    def __init__(self, parentLogger = None):
        self.isAcceptingLogger = wns.Logger.Logger("WNS", "LinkHandler", True, parentLogger)
        self.sendDataLogger = wns.Logger.Logger("WNS", "LinkHandler", True, parentLogger)
        self.wakeupLogger = wns.Logger.Logger("WNS", "LinkHandler", True, parentLogger)
        self.onDataLogger = wns.Logger.Logger("WNS", "LinkHandler", True, parentLogger)

class IPv4Component(Component):

    nameInComponentFactory = "ip.IPv4"

    linkHandler = None

    dataTransmission = None

    notification = None

    dns = None

    sourceDomainName = None

    domainName = None

    dnsZone = None

    dataLinkLayers = None

    neighbourCache = None

    node = None

    fun = None

    ipHeader = None

    upperConvergence = None

    outputChain = None

    inputChain = None

    forwarding = None

    forwardChain = None

    routing = None

    postroutingChain = None

    preroutingChain = None

    synchronizer = None

    outputBuffers = None

    lowerConvergence = None

    endToEndProbe = None

    hopProbe = None

    windowedEndToEndProbe = None

    windowedHopProbe = None

    logger = None

    tunnelExitNotification = None

    tunnelExit = None

    tunnelEntries = None

    def __init__(self, _node, _name, _domainName, probeWindow = 0.5, useDllFlowIDRule = False):
        super(IPv4Component, self).__init__(_node, _name)
        self.configureProbingFUs(probeWindow)
        self.domainName = _domainName
        self.dataTransmission = "ip.dataTransmission"
        self.notification = "ip.notification"
        self.dns = "ip.dns"
        self.dnsZone = "ip.DEFAULT.GLOBAL"
        self.dataLinkLayers = []
        self.logger = Logger("IP", True, _node.logger)
        self.linkHandler = LinkHandler(self.logger)
        self.neighbourCache = []
        self.node = _node

        self.fun = wns.FUN.FUN()

        outputBuffer = wns.Buffer.Dropping(size=100, sizeUnit = 'PDU')

        creator = wns.FlowSeparator.Config('flowSeparatorPrototype', outputBuffer)
        ifNotFoundStrategy = wns.FlowSeparator.CreateOnFirstCompound(creator)

        outputBuffers= wns.FlowSeparator.FlowSeparator(FlowIDBuilder(),
                                                       ifNotFoundStrategy)



        self.ipHeader = wns.FUN.Node("ip.ipHeader", IPHeader(parentLogger=self.logger))
        self.upperConvergence = wns.FUN.Node("IP.upperConvergence", UpperConvergence(parentLogger=self.logger))
        self.outputChain = wns.FUN.Node("outputChain", IPTables.OutputChain(parentLogger = self.logger))
        self.inputChain = wns.FUN.Node("inputChain", IPTables.InputChain(parentLogger = self.logger))
        self.forwarding = wns.FUN.Node("IP.forwarding", Forwarding(parentLogger=self.logger))
        self.forwardChain = wns.FUN.Node("forwardChain", IPTables.ForwardChain(parentLogger = self.logger))
        self.routing = wns.FUN.Node("IP.routing", Routing(parentLogger=self.logger))
        self.postroutingChain = wns.FUN.Node("postroutingChain", IPTables.PostroutingChain(parentLogger = self.logger))

        tempStringList = []
        tempStringList = _domainName.split(".")

        self.preroutingChain = wns.FUN.Node("preroutingChain", IPTables.PreroutingChain(parentLogger = self.logger))

        self.synchronizer = wns.FUN.Node("synchronizer", wns.Tools.Synchronizer())
        self.outputBuffers = wns.FUN.Node("outputBuffers", OutputBuffers(parentLogger=self.logger))
        self.lowerConvergence = wns.FUN.Node("IP.lowerConvergence", LowerConvergence(parentLogger=self.logger))

        filter = IPTables.SourceDestinationFilter("0.0.0.0", "0.0.0.0","0.0.0.0", "0.0.0.0")
        target = IPTables.LoggingTarget()

        acceptsAllFilter = IPTables.AcceptsAllFilter()
        dllFlowIDTarget = IPTables.DLLFlowIDTarget()

        self.outputChain.config.addRule(filter, IPTables.LoggingTarget(), 0)
        self.inputChain.config.addRule(filter, IPTables.LoggingTarget(), 0)
        self.forwardChain.config.addRule(filter, IPTables.LoggingTarget(), 0)
        self.preroutingChain.config.addRule(filter, IPTables.LoggingTarget(), 0)

        if(useDllFlowIDRule):
            self.preroutingChain.config.addRule(acceptsAllFilter, dllFlowIDTarget, 99999)

        self.postroutingChain.config.addRule(filter, IPTables.LoggingTarget(), 0)

        self.fun.add(self.ipHeader)
        self.fun.add(self.upperConvergence)
        self.fun.add(self.outputChain)
        self.fun.add(self.inputChain)
        self.fun.add(self.endToEndProbe)
        self.fun.add(self.windowedEndToEndProbe)
        self.fun.add(self.forwarding)
        self.fun.add(self.forwardChain)
        self.fun.add(self.hopProbe)
        self.fun.add(self.windowedHopProbe)
        self.fun.add(self.routing)
        self.fun.add(self.postroutingChain)
        self.fun.add(self.preroutingChain)
        self.fun.add(self.synchronizer)
        self.fun.add(self.outputBuffers)
        self.fun.add(self.lowerConvergence)

        self.upperConvergence.connect(self.outputChain)
        self.outputChain.connect(self.inputChain)
        self.inputChain.connect(self.endToEndProbe)
        self.endToEndProbe.connect(self.windowedEndToEndProbe)
        self.windowedEndToEndProbe.connect(self.forwarding)
        self.forwarding.connect(self.forwardChain)
        self.forwardChain.connect(self.hopProbe)
        self.hopProbe.connect(self.windowedHopProbe)
        self.windowedHopProbe.connect(self.routing)
        self.routing.connect(self.postroutingChain)
        self.postroutingChain.connect(self.preroutingChain)
        self.preroutingChain.connect(self.synchronizer)
        self.synchronizer.connect(self.outputBuffers)
        self.outputBuffers.connect(self.lowerConvergence)

        self.tunnelExit = None
        self.tunnelEntries = []

    def configureProbingFUs(self, probeWindow) :
        probe = wns.Probe.Packet("hopProbe", "ip.hop", parentLogger=self.logger, moduleName='IP')
        probe.incomingThroughputProbeName = None
        self.hopProbe = wns.FUN.Node("hopProbe", probe)

        probe = wns.Probe.Packet("e2eProbe", "ip.endToEnd", parentLogger=self.logger, moduleName='IP')
        probe.incomingThroughputProbeName = None
        self.endToEndProbe = wns.FUN.Node("endToEndProbe", probe)

        probe = wns.Probe.Window("windowedHopProbe", "ip.hop", windowSize = probeWindow, parentLogger=self.logger, moduleName='IP')
        self.windowedHopProbe = wns.FUN.Node("windowedHopProbe", probe)

        probe = wns.Probe.Window("windowedE2EProbe", "ip.endToEnd", windowSize = probeWindow, parentLogger=self.logger, moduleName='IP')
        self.windowedEndToEndProbe = wns.FUN.Node("windowedEndToEndProbe", probe)

    def addDLL(self, _name, _addressResolver, _arpZone, _pointToPoint, _dllDataTransmission, _dllNotification):
        self.dataLinkLayers.append(DLLListEntry(_name, _addressResolver, _arpZone, _pointToPoint, _dllDataTransmission, _dllNotification))

    def addRoute(self, _netAddress, _netmask, _gateway, _dllName):
        self.routing.config.addRoute(_netAddress, _netmask, _gateway, _dllName)

    def clearRoutingTable(self):
        self.routing.config.routingTable = []

    def addTunnel(self, _dllName, _tunnelEntryAddress, _tunnelExitAddress):
        if (self.tunnelExit == None):
            self.tunnelExit = TunnelExitComponent(self.node, "TUN-IN", self.notification)

        tunnelEntry = TunnelEntryComponent(self.node,
                                           "TUN-OUT",
                                           _tunnelEntryAddress,
                                           _tunnelExitAddress,
                                           self.dataTransmission)

        self.tunnelEntries.append(tunnelEntry)

        self.addDLL(_name = _dllName,
                    _addressResolver = FixedAddressResolver(_tunnelEntryAddress, "255.255.255.255"),
                    _arpZone = "tunnel",
                    _pointToPoint = True,
                    _dllDataTransmission = tunnelEntry.dataTransmission,
                    _dllNotification = self.tunnelExit.dllNotification)

    def enableTrace(self):
        for dll in self.dataLinkLayers:
            dll.traceEnabled = True

class IPHeader(wns.PyConfig.Sealed):

    __plugin__ = "ip.ipHeader"

    headerSize = 20*8

    logger = None

    def __init__(self, parentLogger=None):
        self.logger = Logger("IPHeader", True, parentLogger)

class UpperConvergence(wns.PyConfig.Sealed):

    __plugin__ = "ip.upperConvergence"

    sourceAddress = None

    logger = None

    def __init__(self, parentLogger=None):
        self.logger = Logger("UpperConvergence", True, parentLogger)

class Forwarding(wns.FUN.FunctionalUnit):

    __plugin__ = "ip.forwarding"

    isForwarding = False

    ttl = None

    logger = None

    commandName = None

    def __init__(self, parentLogger=None):
        super(Forwarding, self).__init__("forwarding")

        self.isForwarding = False

        self.ttl = 255

        self.logger = Logger("Forwarding", True, parentLogger)

class ARPResolver(wns.FUN.FunctionalUnit):

    __plugin__ = "ip.arpresolver"

    logger = None

    arpZone = None

    def __init__(self, arpZone, parentLogger=None):
        super(ARPResolver, self).__init__("arpresolver")

        self.logger = Logger("ARPResolver", True, parentLogger)

        self.arpZone = arpZone


class Routing(wns.PyConfig.Sealed):

    __plugin__ = "ip.routing"

    routingTable = None

    logger = None

    def __init__(self, parentLogger=None):
        self.routingTable = []

        self.logger = Logger("Routing", True, parentLogger)

    def addRoute(self, _destination, _netmask, _gateway, _dllName):
        self.routingTable.append(RoutingTableEntry(_destination, _netmask, _gateway, _dllName))


class FlowIDBuilder(wns.PyConfig.Sealed):
    __plugin__ = 'ip.outputBuffersFlowIDBuilder'

class OutputBuffers(wns.FlowSeparator.FlowSeparator):

    group = None

    def __init__(self, parentLogger):
        subFUN = wns.FUN.FUN()
        outputBuffer = wns.FUN.Node('outputBuffer',
                                         wns.Buffer.Dropping(size=100,
                                                             sizeUnit = 'PDU'))

        arpResolver = wns.FUN.Node('arpResolver',
                                   ARPResolver("TBD_arpZone", parentLogger=parentLogger))

        subFUN.add(outputBuffer)
        subFUN.add(arpResolver)

        outputBuffer.connect(arpResolver)

        self.group = wns.Group.Group(subFUN, 'outputBuffer', 'arpResolver')

        creator = wns.FlowSeparator.Config('flowSeparatorPrototype', self.group)
        ifNotFoundStrategy = wns.FlowSeparator.CreateOnFirstCompound(creator)

        super(OutputBuffers, self).__init__(FlowIDBuilder(),
                                             ifNotFoundStrategy,
					     parentLogger=parentLogger)

class LowerConvergence(wns.PyConfig.Sealed):

    __plugin__ = "ip.lowerConvergence"

    logger = None

    def __init__(self, parentLogger=None):
        self.logger = Logger("LowerConvergence", True, parentLogger)

class DLLDropIn(Component):
    nameInComponentFactory = "ip.node.component.ipv4.tests.DLL"
    def __init__(self, _node, _name):
        super(DLLDropIn, self).__init__(_node, _name)

