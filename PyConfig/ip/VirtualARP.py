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

from Logger import Logger
from wns.Node import Node
from wns.Node import Component

class VirtualARP(Component):

    nameInComponentFactory = "ip.VARP"

    subnetIdentifier = None

    resolveDelay = 0.0

    logger = None

    def __init__(self, node, subnetIdentifier, resolveDelay):
        super(VirtualARP, self).__init__(node, subnetIdentifier)
        self.subnetIdentifier = subnetIdentifier
        self.resolveDelay = resolveDelay
        self.logger = Logger(self.subnetIdentifier, True, node.logger)

class VirtualARPServer(Node):
    def __init__(self, name, subnetIdentifier, resolveDelay=0.0):
        super(VirtualARPServer, self).__init__(name)
        varp = VirtualARP(self, subnetIdentifier, resolveDelay)
