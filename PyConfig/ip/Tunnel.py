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

import wns
from wns.Node import Component
from Logger import Logger

class TunnelExitComponent(Component):
    """The TunnelExitComponent configures the endpoint of a tunnel. As such the
    tunnel exit component is both an nl::DataHandler for IP encapsulated packets
    and a dll::Notfication service. Encapsulated packets received on via the
    nl::DataHandler are decapsulated on re-incject into the IP Layer via the
    dll::Notification service.
    """

    nameInComponentFactory = "ip.tunnelExit"
    """The name within the C++ Static Factory for Components"""

    logger = None
    """ Logger instance """

    ipNotification = None
    """ Name of the ipNotification service """

    dllNotification = "ip.__internal__.TunnelExitComponentNotification"
    """ Name of the dllNotification service """

    def __init__(self, _node, _name, ipNotification):
        """ Initializes the TunnelExitComponent
        @param _node : The parent node of this component
        @type  _node : L{wns.Node.Node}
        @param _name : The components name
        @type  _name : string
        @param ipNotification : Name of the ipNotification service
        @type  ipNotification : string
        """
        super(TunnelExitComponent, self).__init__(_node, _name)
        self.logger = Logger("TUN", True, _node.logger)
        self.ipNotification = ipNotification
        self.dllNotification = "ip.__internal__.TunnelExitComponentNotification"

class TunnelEntryComponent(Component):

    nameInComponentFactory = "ip.tunnelEntry"

    logger = None

    tunnelEntryAddress = None

    tunnelExitAddress = None

    dataTransmission = None

    ipService = None

    def __init__(self, _node, _name, tunnelEntryAddress, tunnelExitAddress, ipService):
        super(TunnelEntryComponent, self).__init__(_node, _name)
        self.logger = Logger("TUN", True, _node.logger)
        self.dataTransmission = "tun" + str(_name)
        self.tunnelEntryAddress = tunnelEntryAddress
        self.tunnelExitAddress = tunnelExitAddress
        self.ipService = ipService

