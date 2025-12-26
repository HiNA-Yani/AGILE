#!/usr/bin/env python3
'''
 * The structure of this file is inspired by the Cebinae project:
 *   https://github.com/eniac/Cebinae
 *
 * All implementation in this file is original unless otherwise stated.
'''
import os, sys, time
sys.path.append(os.path.dirname(os.path.realpath(__file__))+"/libs")

from mgr import *
m = Manager("fsmmf")


def main():
    commonStart()
    m.disconnect()

def commonStart():
    # bring up ports and add forwarding paths
    m.port_up(144, "100G", "NONE") 
    m.port_up(156, "100G", "NONE") 
    m.port_up(128, "100G", "NONE") 
    add_path_through_bottleneck(0x1070fd69b290, 144)
    add_path_through_bottleneck(0x1070fd699470, 156)
    add_path_through_bottleneck(0x1070fdc40f08, 128)
    add_path_through_bottleneck(0xe8ebd3a72da2, 128)


def add_path_through_bottleneck(dstmac, dstport):
    m.addExactEntry("tiForward", ["hdr.ethernet.dst_addr"], [dstmac], 'aiSetEgress', {"egr_port":dstport})


if __name__ == '__main__':
    main()
