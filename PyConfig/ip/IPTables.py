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
import wns.PyConfig
from Logger import Logger

class Chain(wns.PyConfig.Sealed):

    logger = None

    rules = None

    def __init__(self, name, parentLogger=None):
        self.logger = Logger(name, True, parentLogger)
        self.rules = []

    def addRule(self, filter, target, ruleTag):
        filter.setLogger(self.logger)
        target.setLogger(self.logger)
        self.rules.append(Rule(filter, target, ruleTag))

class OutputChain(Chain):
    __plugin__ = "ip.iptables.outputchain"

    def __init__(self, parentLogger=None):
        Chain.__init__(self, "OutputChain", parentLogger)

class InputChain(Chain):
    __plugin__ = "ip.iptables.inputchain"

    def __init__(self, parentLogger=None):
        Chain.__init__(self, "InputChain", parentLogger)

class ForwardChain(Chain):
    __plugin__ = "ip.iptables.forwardchain"

    def __init__(self, parentLogger=None):
        Chain.__init__(self, "ForwardChain", parentLogger)

class PreroutingChain(Chain):
    __plugin__ = "ip.iptables.preroutingchain"

    def __init__(self, parentLogger=None) :
        Chain.__init__(self, "PreroutingChain", parentLogger)

class PostroutingChain(Chain):
    __plugin__ = "ip.iptables.postroutingchain"

    def __init__(self, parentLogger=None):
        Chain.__init__(self, "PostroutingChain", parentLogger)

class Rule:

    def __init__(self, filter, target, ruleTag):
        self.filter = filter
        self.target = target
        self.ruleTag = ruleTag

class SourceDestinationFilter:

    __plugin__ = "sourceDestinationFilter"

    def __init__(self, source, sourceMask, destination, destinationMask):
        self.source = source
        self.sourceMask = sourceMask
        self.destination = destination
        self.destinationMask = destinationMask

    def setLogger(self, parentlogger):
        pass

class AcceptsAllFilter:

    __plugin__ = "acceptsAllFilter"

    def __init__(self):
        pass

    def setLogger(self, parentLogger):
        self.logger = Logger("AcceptsAllFilter", True, parentLogger)


class LoggingTarget:

    __plugin__ = "loggingTarget"

    def __init__(self):
        pass

    def setLogger(self, parentLogger=None):
        self.logger = Logger("LoggingTarget", True, parentLogger)

class DLLFlowIDTarget:

    __plugin__ = "dllFlowIDTarget"

    def __init__(self):
        pass

    def setLogger(self, parentLogger=None):
        self.logger = Logger("DLLFlowIDTarget", True, parentLogger)
