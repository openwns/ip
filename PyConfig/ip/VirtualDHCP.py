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

class VirtualDHCP(Component):

    nameInComponentFactory = "ip.VDHCP"

    subnetIdentifier = None

    startAddress = None

    endAddress = None

    subnetMask = None

    unbindDelay = None

    logger = None

    def __init__(self, node, subnetIdentifier, startAddress, endAddress, subnetMask, unbindDelay = 60):
        super(VirtualDHCP, self).__init__(node, subnetIdentifier)
        self.subnetIdentifier = subnetIdentifier
        self.subnetMask = subnetMask
        self.startAddress = startAddress
        self.endAddress = endAddress
        self.unbindDelay = unbindDelay
        self.logger = Logger(self.subnetIdentifier, True, node.logger)

class VirtualDHCPServer(Node):
    def __init__(self, name, subnetIdentifier, startAddress, endAddress, subnetMask):
        super(VirtualDHCPServer, self).__init__(name)
        vdhcp = VirtualDHCP(self, subnetIdentifier, startAddress, endAddress, subnetMask)
