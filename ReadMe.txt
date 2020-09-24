/*******************************************************************************
 * Copyright (C) 2020 ASH WARE, Inc.
 *******************************************************************************/

This is release 1.00 of the MIL-STD-1553 eTPU Drivers.

This package contains the driver eTPU source code and host layer driver source code 
comprising a MIL-STD-1553/1760 message processor.


Tools Used
==========
ASH WARE eTPU2+ DevTool, Version 2.72D
ASH WARE System DevTool, Version 2.72D
ASH WARE ETEC eTPU C Compiler Toolkit, version 2.62D


Package Contents
================
The main directory structure of the package is as follows:
.                  - contains the top-level test scripts, and the eTPU software project.
.\BC_etpu_test     - standalone eTPU simulation tests for BC eTPU driver software
.\BC_host_test     - system simulation tests for BC driver software (eTPU and host API code)
.\common_test      - simulation test artifacts common across multiple test areas
.\demo_SIM         - contains a System DevTool demo that exercises all 3 terminal types
                     on a simulated MPC5777C
.\doc              - all documentation for the drivers
.\etpu_code        - eTPU software and build output (auto-generated host API code)
.\host_code        - host API code for the drivers
.\MT_etpu_test     - standalone eTPU simulation tests for MT eTPU driver software
.\MT_host_test     - system simulation tests for MT driver software (eTPU and host API code)
.\RT_etpu_test     - standalone eTPU simulation tests for RT eTPU driver software
.\RT_host_test     - system simulation tests for RT driver software (eTPU and host API code)
.\RX_TX_etpu_test  - standalone eTPU simulation tests for low-level RX/TX eTPU code


eTPU Code Size
=========
Compile and see etpu_ab_set.map or etpu_ab_set_ana.html for details.


Change History
==============
Release 1.00 : (2020-May-01) initial release of drivers to public under MIT license
