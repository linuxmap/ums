/* This file was generated by RADVISION ASN.1 Compiler */
/* This is a compilation of : asn_messages\systemConfig.asn, asn_messages\h450config.asn */
/* Command line : ..\asn1\compiler\asn.exe asn_messages\systemConfig.asn asn_messages\h450config.asn -o asn_objects\commonasn -p _common  */

/***********************************************************************
Filename   : asn_objects\commonasn.h
Description: ASN.1 Generated definitions file
************************************************************************
        Copyright (c) 2002 RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Ltd.. No part of this document may be reproduced in any
form whatsoever without written prior approval by RADVISION Ltd..

RADVISION Ltd. reserve the right to revise this publication and make
changes changes without obligation to notify any person of such
revisions or changes.
***********************************************************************/

#ifndef _asn_messages_systemConfig_ASN_H
#define _asn_messages_systemConfig_ASN_H

#ifdef __cplusplus
extern "C" {
#endif

unsigned char* commonasnGetSyntax(void);

#ifdef __cplusplus
#define __ENUM enum
#define __NAME1 _common
#define __NAME2 
#else
#define __ENUM typedef enum
#define __NAME1 
#define __NAME2 _common
#endif

#if 1
__ENUM __NAME1 {
  _common_CCConfig = 0,
  _common_CDConfig = 10,
  _common_CHConfig = 20,
  _common_CIConfig = 30,
  _common_CMNConfig = 40,
  _common_COConfig = 51,
  _common_CPConfig = 61,
  _common_CTConfig = 71,
  _common_CWConfig = 81,
  _common_H450SystemConfiguration = 91,
  _common_MWIConfig = 116,
  _common_SystemConfiguration = 127,
  _common_TransportAddress = 148,
  _common_allocations = 166,
  _common_allocations_5 = 179,
  _common_allocations_57 = 194,
  _common_c_default_cipl = 210,
  _common_c_default_cipl_105 = 226,
  _common_callPropertyMode = 246,
  _common_callPropertyMode_28 = 264,
  _common_canRetainService = 285,
  _common_canRetainService_95 = 303,
  _common_cct1 = 324,
  _common_cct1_92 = 330,
  _common_cct2Busy = 339,
  _common_cct2Busy_93 = 349,
  _common_cct2NoResponse = 362,
  _common_cct2NoResponse_94 = 378,
  _common_cdt1 = 397,
  _common_cdt2 = 403,
  _common_cdt3 = 409,
  _common_cdt4 = 415,
  _common_cdt5 = 421,
  _common_chanDescs = 427,
  _common_channels = 438,
  _common_checkParamLength = 448,
  _common_cht1 = 466,
  _common_cht2 = 472,
  _common_cicl = 478,
  _common_cidAssociate = 484,
  _common_cipl = 498,
  _common_cit1 = 504,
  _common_cit2 = 510,
  _common_cit3 = 516,
  _common_cit4 = 522,
  _common_cit5 = 528,
  _common_cit6 = 534,
  _common_classReference = 540,
  _common_cmnt = 556,
  _common_cmnt_107 = 562,
  _common_constrainingField = 572,
  _common_containerOfObjectSets = 591,
  _common_containerOfObjects = 614,
  _common_containerOfTypes = 634,
  _common_containerOfValues = 652,
  _common_copySingleMessages = 671,
  _common_cpt1 = 691,
  _common_cpt10 = 697,
  _common_cpt2 = 704,
  _common_cpt3 = 710,
  _common_cpt4 = 716,
  _common_cpt5 = 722,
  _common_cpt6 = 728,
  _common_cpt7 = 734,
  _common_cpt8 = 740,
  _common_cpt9 = 746,
  _common_ctt1 = 752,
  _common_ctt2 = 758,
  _common_ctt3 = 764,
  _common_ctt4 = 770,
  _common_defaultScopeId = 776,
  _common_defaultScopeId_25 = 792,
  _common_deleteSingleMessages = 811,
  _common_delimiter = 833,
  _common_delimiter_4 = 844,
  _common_doNotUseProperty = 857,
  _common_fieldOfClassReference = 875,
  _common_fieldOfEnumerated = 898,
  _common_fieldOfObjectReference = 917,
  _common_fieldReference = 941,
  _common_fullProperty = 957,
  _common_imports = 971,
  _common_importsArray = 980,
  _common_indicateCalling = 994,
  _common_interval = 1011,
  _common_ip = 1021,
  _common_ip6Address = 1025,
  _common_ip6Address_51 = 1037,
  _common_ipAddress = 1052,
  _common_ipAddress_36 = 1063,
  _common_ipSourceRoute = 1077,
  _common_ipSourceRoute_39 = 1092,
  _common_ipxAddress = 1110,
  _common_ipxAddress_47 = 1122,
  _common_localAddress = 1137,
  _common_localIPAddress = 1151,
  _common_loose = 1167,
  _common_manualStart = 1174,
  _common_maxBuffSize = 1187,
  _common_maxBuffSize_17 = 1200,
  _common_maxCalls = 1216,
  _common_maxChannels = 1226,
  _common_maxMultiHomedAddresses = 1239,
  _common_maxMultiHomedAddresses_19 = 1263,
  _common_maxPoolSizeInKB = 1290,
  _common_maxPoolSizeInKB_18 = 1307,
  _common_maxProcs = 1327,
  _common_maxRasInTransactions = 1337,
  _common_maxRasOutTransactions = 1359,
  _common_maxServices = 1382,
  _common_maxServices_65 = 1395,
  _common_messages = 1411,
  _common_module = 1421,
  _common_mwit1 = 1429,
  _common_mwit2 = 1436,
  _common_nameChans = 1443,
  _common_netBios = 1454,
  _common_netBios_54 = 1463,
  _common_netnum = 1475,
  _common_netnum_49 = 1483,
  _common_node = 1494,
  _common_node_48 = 1500,
  _common_nsap = 1509,
  _common_nsap_55 = 1515,
  _common_objectArray = 1524,
  _common_objectReference = 1537,
  _common_objectSetArray = 1554,
  _common_objectSetElement = 1570,
  _common_objectSetReference = 1588,
  _common_pdlName = 1608,
  _common_pdlName_56 = 1617,
  _common_port = 1629,
  _common_portFrom = 1635,
  _common_portTo = 1645,
  _common_port_50 = 1653,
  _common_protocols = 1662,
  _common_route = 1673,
  _common_route_42 = 1680,
  _common_routing = 1690,
  _common_routing_44 = 1699,
  _common_silentMonitorInd = 1711,
  _common_silentMonitorInd_106 = 1729,
  _common_strict = 1751,
  _common_tcw = 1759,
  _common_tpktChans = 1764,
  _common_tpktNoBuffers = 1775,
  _common_typeArray = 1790,
  _common_typeFromConstraint = 1801,
  _common_typeReference = 1821,
  _common_udpChans = 1836,
  _common_valueNode = 1846,
  _common_valueTree = 1857,
  _common_values = 1868,
  _common_vtNodeCount = 1876,
  _common_vtPoolSize = 1889,
  _common_watchdog = 1901,
  _common_watchdog_33 = 1911,
  _common_withSyntaxElement = 1924} __NAME2;
#else

  __ENUM __NAME1 {
  _common_CCConfig = 0,
  _common_CDConfig = 10,
  _common_CHConfig = 20,
  _common_CIConfig = 30,
  _common_COConfig = 40,
  _common_CPConfig = 50,
  _common_CTConfig = 60,
  _common_CWConfig = 70,
  _common_H450SystemConfiguration = 80,
  _common_MWIConfig = 105,
  _common_SystemConfiguration = 116,
  _common_allocations = 137,
  _common_allocations_32 = 150,
  _common_allocations_5 = 166,
  _common_c_default_cipl = 181,
  _common_c_default_cipl_79 = 197,
  _common_callPropertyMode = 216,
  _common_callPropertyMode_26 = 234,
  _common_cct1 = 255,
  _common_cct1_67 = 261,
  _common_cct2Busy = 270,
  _common_cct2Busy_68 = 280,
  _common_cdt1 = 293,
  _common_cdt2 = 299,
  _common_cdt3 = 305,
  _common_cdt4 = 311,
  _common_cdt5 = 317,
  _common_chanDescs = 323,
  _common_channels = 334,
  _common_cht1 = 344,
  _common_cht2 = 350,
  _common_cicl = 356,
  _common_cidAssociate = 362,
  _common_cipl = 376,
  _common_cit1 = 382,
  _common_cit2 = 388,
  _common_cit3 = 394,
  _common_cit4 = 400,
  _common_cit5 = 406,
  _common_cit6 = 412,
  _common_cit6_76 = 418,
  _common_classReference = 427,
  _common_constrainingField = 443,
  _common_containerOfObjectSets = 462,
  _common_containerOfObjects = 485,
  _common_containerOfTypes = 505,
  _common_containerOfValues = 523,
  _common_copySingleMessages = 542,
  _common_cpt1 = 562,
  _common_cpt10 = 568,
  _common_cpt2 = 575,
  _common_cpt3 = 581,
  _common_cpt4 = 587,
  _common_cpt5 = 593,
  _common_cpt6 = 599,
  _common_cpt7 = 605,
  _common_cpt8 = 611,
  _common_cpt9 = 617,
  _common_ctt1 = 623,
  _common_ctt2 = 629,
  _common_ctt2NoResponse = 635,
  _common_ctt2NoResponse_69 = 651,
  _common_ctt3 = 670,
  _common_ctt4 = 676,
  _common_deleteSingleMessages = 682,
  _common_delimiter = 704,
  _common_delimiter_4 = 715,
  _common_doNotUseProperty = 728,
  _common_fieldOfClassReference = 746,
  _common_fieldOfEnumerated = 769,
  _common_fieldOfObjectReference = 788,
  _common_fieldReference = 812,
  _common_fullProperty = 828,
  _common_imports = 842,
  _common_importsArray = 851,
  _common_indicateCalling = 865,
  _common_localIPAddress = 882,
  _common_localIPAddress_23 = 898,
  _common_manualStart = 917,
  _common_maxBuffSize = 930,
  _common_maxBuffSize_17 = 943,
  _common_maxCalls = 959,
  _common_maxChannels = 969,
  _common_maxPoolSizeInKB = 982,
  _common_maxPoolSizeInKB_18 = 999,
  _common_maxProcs = 1019,
  _common_maxRasInTransactions = 1029,
  _common_maxRasOutTransactions = 1051,
  _common_maxServices = 1074,
  _common_maxServices_40 = 1087,
  _common_messages = 1103,
  _common_module = 1113,
  _common_mwit1 = 1121,
  _common_mwit2 = 1128,
  _common_nameChans = 1135,
  _common_objectArray = 1146,
  _common_objectReference = 1159,
  _common_objectSetArray = 1176,
  _common_objectSetElement = 1192,
  _common_objectSetReference = 1210,
  _common_pdlName = 1230,
  _common_pdlName_31 = 1239,
  _common_portFrom = 1251,
  _common_portTo = 1261,
  _common_protocols = 1269,
  _common_silentMonitorInd = 1280,
  _common_silentMonitorInd_80 = 1298,
  _common_tcw = 1319,
  _common_tpktChans = 1324,
  _common_tpktNoBuffers = 1335,
  _common_typeArray = 1350,
  _common_typeFromConstraint = 1361,
  _common_typeReference = 1381,
  _common_udpChans = 1396,
  _common_valueNode = 1406,
  _common_valueTree = 1417,
  _common_values = 1428,
  _common_vtNodeCount = 1436,
  _common_vtPoolSize = 1449,
  _common_withSyntaxElement = 1461} __NAME2;

#endif

#undef __NAME1
#undef __NAME2
#undef __ENUM

#define _common(a) _common_##a,
#define __common(a) _common_##a

#ifdef __cplusplus
}
#endif

#endif
