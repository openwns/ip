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

import wns.Logger

class Logger(wns.Logger.Logger):
    def __init__(self, name, enabled, parent = None, **kw):
        super(Logger, self).__init__("IP", name, enabled, parent, **kw)
        wns.Logger.globalRegistry.addLogger("IP", self)
