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

class ipv4Address:
    
    address = long(0)
    
    def __init__(self, _buildFrom):
        if (type(_buildFrom)==type(long()) or (type(_buildFrom) == type(int()))):
            self.address = _buildFrom
        else:
            self.address  = long(0)
            self.address  = long(_buildFrom.split(".")[0]) << 24
            self.address += long(_buildFrom.split(".")[1]) << 16
            self.address += long(_buildFrom.split(".")[2]) << 8
            self.address += long(_buildFrom.split(".")[3])
            
    def __str__(self):
        strRepr =        str((self.address >> 24).__and__(0xFF))
        strRepr += "." + str((self.address >> 16).__and__(0xFF))
        strRepr += "." + str((self.address >> 8).__and__(0xFF))
        strRepr += "." + str((self.address).__and__(0xFF))
        return strRepr
    
    def __add__(self, added):
        return ipv4Address(self.address + int(added))
    
    def __sub__(self, subtracted):
        return ipv4Address(self.address - int(subtracted))
        
        
