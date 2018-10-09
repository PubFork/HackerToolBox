#!/usr/bin/env python

"""
(c) Immunity, Inc. 2004-2007


U{Immunity Inc.<http://www.immunityinc.com>}

List all pycommands with its descriptions in log window

"""

DESC="""List PyCommands"""

import immlib
import glob


def main(args):
    imm=immlib.Debugger()
    which=glob.glob("./PyCommands/*.py")
    imm.Log("List of available PyCommands")
    for file in which:
        command=file.split("\\")[1].split(".")[0]
        imm.Log("* %s" % command)
    imm.Log("",focus=1)
    return "Command executed"
        
    
    
    