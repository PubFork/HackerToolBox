#!/usr/bin/env python

"""
(c) Immunity, Inc. 2004-2007


U{Immunity Inc.<http://www.immunityinc.com>}

modptr
"""
__VERSION__ = '1.0'

DESC="""!modptr Patch all Function Pointers and detect when they triggered """


import immlib
import immutils
import libdatatype
import getopt
from immlib import AccessViolationHook

INDEXER    = 0xb4000000
INDEX_MASK = 0xFF000000
FNDX_MASK  = 0x00FFFFFF

def usage(imm):
    imm.Log("!modptr   Patch all Function Pointers and detect when they triggered")
    imm.Log("!modptr   address")
    imm.Log("  [Note: it will patch all the function pointer on the memory pages of the given address]")
    return "Usage: !modptr ADDRESS"

# Access Violation Hook class
class FunctionTriggeredHook(AccessViolationHook):
    def __init__( self, fn_ptr):
        AccessViolationHook.__init__( self )
        #self.threadid = threadid
        self.fn_ptr = fn_ptr
        
    # The objective of this Hook is to listen on every Access Violation until we
    #  found the access violation we force by patching every function pointer. 
    # Recognise what pointer is and show it on Log Window
    def run(self, regs):
        imm  = immlib.Debugger()
        
        eip  = regs['EIP']
        # Checking if we are on the correct Access Violation
        if ( eip & INDEX_MASK ) != INDEXER:
            return ""
        fndx = eip & FNDX_MASK
        if fndx >= len( self.fn_ptr ) :
            return ""
        
        obj  = self.fn_ptr[ fndx ] # it shouldn't be out of index
        
        # Print info and Unhook
        imm.Log("Found a pointer at 0x%08x that triggers: " % obj.address,  address = obj.address, focus =1 )
        imm.Log("   %s: %s" % ( obj.name, obj.Print() ), address = obj.address)

        imm.setReg("EIP", int(obj.data) )
        imm.Run()
        #self.UnHook()
        
def main(args):
    imm          = immlib.Debugger()
    if not args:
        return usage(imm)

    exclude = []
    address = 0
    try:
        opts, argo = getopt.getopt(args, "a:x:")
    except getopt.GetoptError:
        usage(imm)
        return "Wrong Argument (Check Log Window)"

    for o,a in opts:
        if o == '-a':
            address = int( a, 16 )
        elif o == '-f':
            exclude.append( int( a, 16 ) )

    page         = imm.getMemoryPagebyAddress( address )

    if not page:
        return "Failed to grab Memory Page, wrong addres: 0x%08x" % address

    addr   = page.getBaseAddress()
    mem    = imm.readMemory( page.getBaseAddress(), page.getSize() )
    ndx    = INDEXER    
    fn_ptr = []
    
    # Discovering Function Pointers
    dt     = libdatatype.DataTypes( imm )
    ret    = dt.Discover( mem, addr, what = 'pointers' )
    if ret:
        for obj in ret: 
            if obj.isFunctionPointer() and obj.address not in exclude:
                # Writing a dword that would make the Function Pointer crash on AV
                #  and later we will identify on our AV Hook
                imm.Log( "Modifying: 0x%08x" % obj.address )
                imm.writeLong( obj.address, ndx )
                ndx    += 1
                fn_ptr.append( obj )

        hook = FunctionTriggeredHook( fn_ptr )
        hook.add( "modptr_%08x" % addr )
        return "Hooking on %d Functions" % len( fn_ptr )
    else:
        return "No Function pointers found on the page of 0x%08x" % address
            
            
