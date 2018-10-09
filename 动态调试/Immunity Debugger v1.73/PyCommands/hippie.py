#!/usr/bin/env python

"""
(c) Immunity, Inc. 2004-2007


U{Immunity Inc.<http://www.immunityinc.com>}

"""

DESC="""Syscall Fuzzer"""

import immlib
import immutils
import getopt

# We need to find this specific place
def getRet(imm, allocaddr, max_opcodes = 300):
    addr = allocaddr

    for a in range(0, max_opcodes):
        op = imm.disasmForward( addr )
        if op.isRet():
            if op.getImmConst() == 0xc:
                op = imm.disasmBackward( addr, 3)                   
                return op.getAddress()
        addr = op.getAddress()

    return 0x0

def usage( imm ):
    imm.Log("!hippie -[o|s|d|p|c]    InjectHook on Allocate/Free Heap", focus=1)
    #imm.Log("-n Name       Tag Name ")
    imm.Log("-o            Enable Hook")
    imm.Log("-s            Show Hook results")
    imm.Log("-d            Delete Hooks")
    imm.Log("-p            Pause Hook")
    imm.Log("-C            Clear Hook")
    imm.Log("-c            Continue Hook")    
    imm.Log("-h            Filter by Heap")    
    imm.Log("-a            Filter by Chunk Address")    
    
SWITCH   = 1
SHOW     = 2
DELETE   = 3
PAUSE    = 4
CONTINUE = 5
CLEAR = 6

def showresult(imm, a, rtlallocate, extra = ""):
    if a[0] == rtlallocate:
        imm.Log("RtlAllocateHeap(0x%08x, 0x%08x, 0x%08x) <- 0x%08x %s" % ( a[1][0], a[1][1], a[1][2], a[1][3], extra), address = a[1][3]  )
    else:
        imm.Log("RtlFreeHeap(0x%08x, 0x%08x, 0x%08x) %s" % (a[1][0], a[1][1], a[1][2], extra)  )

    
def main(args):
    imm          = immlib.Debugger()
    
    try:
        opts, argo = getopt.getopt(args, "osdpch:a:C")
    except getopt.GetoptError:
        usage(imm)          
        return "Wrong Argument (Check Log Window)"

    FlagCmd    = 0
    heap = None
    chunkaddress = None
    
    for o,a in opts:
        if o == '-o':
            FlagCmd = SWITCH
        elif o == '-s':
            FlagCmd = SHOW
        elif o == '-d':     
            FlagCmd = DELETE            
        elif o == '-p':
            FlagCmd = PAUSE             
        elif o == '-c':
            FlagCmd = CONTINUE
        elif o == '-C':
            FlagCmd = CLEAR
        elif o == '-h':
            heap = int(a, 16)
        elif o == '-a':
            chunkaddress = int(a, 16)
            
    Name = "hippiehook"
    

    if FlagCmd == SWITCH:
        if imm.getKnowledge(Name):
            usage(imm)
            return "Cannot set Hooks:  Hooks are already set"
        imm.Pause()
        rtlfree      = imm.getAddress("ntdll.RtlFreeHeap")
        allocate     = imm.getAddress("ntdll.RtlAllocateHeap")
        # We need to hook on the the ret point of RtlAllocateHeap so we can
        #  get the result of the allocation.
        mod = imm.getModule("ntdll.dll")
        if not mod.isAnalysed():
            imm.analyseCode( mod.getCodebase() )        
        imm.Log("oOoo: 0x%08x" % allocate)
        rtlallocate  = getRet(imm, allocate, 1000) 
        imm.addKnowledge("FuncNames",  ( rtlallocate, rtlfree ) )

        imm.Log("0x%08x 0x%08x (0x%08x)" % (rtlallocate, rtlfree, allocate))
        
        fast = immlib.STDCALLFastLogHook( imm )
        imm.Log("Logging on Free  0x%08x" % rtlfree)
        fast.logFunction( rtlfree, 3 )

        imm.Log("Logging on Alloc 0x%08x" % rtlallocate)
        fast.logFunction( rtlallocate, 0)
        fast.logBaseDisplacement( "EBP",    8)
        fast.logBaseDisplacement( "EBP",  0xC)
        fast.logBaseDisplacement( "EBP", 0x10)
        fast.logRegister( "EAX" )
        
        # Manual Way to do it
        #fast = immlib.FastLogHook( imm ) 
        #imm.Log("Logging on 0x%08x" % rtlallocate)
        #fast.logFunction( rtlallocate )
        #fast.logBaseDisplacement("ESP", 4)
        #fast.logBaseDisplacement("ESP", 8)
        #fast.logBaseDisplacement("ESP", 12)
        #fast.logRegister("EAX")

        #fast.logFunction( rtlfree )
        #imm.Log("Logging on 0x%08x" % rtlfree)
        #fast.logBaseDisplacement("ESP", 4)
        #fast.logBaseDisplacement("ESP", 8)
        #fast.logBaseDisplacement("ESP", 12)
        
        fast.Hook()
        imm.addKnowledge(Name, fast, force_add = 1)

    elif FlagCmd == DELETE:
        fast = imm.getKnowledge( Name )
        if not fast:
            return "Couldn't find the name tag" 
        fast.unHook()
        imm.forgetKnowledge( Name )     
        return "Hook removed: %s" % Name        

    elif FlagCmd == CLEAR:
        fast = imm.getKnowledge(Name)
        if not fast:
            return "Couldn't find the name tag"
        fast.Clear()
        return "Hook has been clear"
        
    elif FlagCmd == SHOW:
        fast = imm.getKnowledge(Name)
        if not fast:
            return "Couldn't find the name tag"

        rtlallocate, rtlfree = imm.getKnowledge("FuncNames")
        ret = fast.getAllLog()
        NDX = {rtlallocate: 3, rtlfree: 2} 
        for a in ret:
            extra = ""
            if heap:
                if heap == a[1][0]:
                    if chunkaddress:
                       if a[1][ NDX[ a[0] ] ] == chunkaddress:
                           extra = "<---- * FOUND *"
                    showresult(imm, a, rtlallocate, extra)
                   #else:
                   #        showresult(imm, a, rtlallocate)                        
            else:
                if chunkaddress:
                    if a[1][ NDX[ a[0] ] ] == chunkaddress:
                        extra = "<---- * FOUND *"
                    
                showresult(imm, a, rtlallocate, extra)
                #else:
                #        showresult(imm, a, rtlallocate)
                
        imm.Log("=" * 0x2f)                    
        return "Traced %d functions" % len(ret)

    elif FlagCmd == PAUSE:
        fast = imm.getKnowledge(Name)
        if not fast:
            return "Couldn't find the name tag"
        if not fast.Pause():
            return "Error: not been able to pause %s hook " % Name
        imm.addKnowledge(Name, fast, force_add = 1)
        return "Hook %s paused" % Name

    elif FlagCmd == CONTINUE:
        fast = imm.getKnowledge(Name)
        if not fast:
            return "Couldn't find the name tag"
        if not fast.Continue():
            return "Error: not been able to continue %s hook " % Name
        imm.addKnowledge(Name, fast, force_add = 1)
        return "Hook %s continued" % Name

    return "Done"
