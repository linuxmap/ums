/***********************************************************************
        Copyright (c) 2002 RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Ltd.. No part of this document may be reproduced in any
form whatsoever without written prior approval by RADVISION Ltd..

RADVISION Ltd. reserve the right to revise this publication and make
changes without obligation to notify any person of such revisions or
changes.
***********************************************************************/


/*
  psynTreeDb

  Syntax tree database access
  Provides internal functions to access the syntax database generated by the
  ASN.1 compiler.
 */

#ifndef _PSYNTREE_DB_H
#define _PSYNTREE_DB_H

#include "psyntree.h"
#include "psyntreeDef.h"

#ifdef __cplusplus
extern "C" {
#endif



/************************************************************************
 * stGetChildByIndex
 * purpose: Get a child node of a parent node by its index
 * input  : hSyn            - Syntax information
 *          parentNodeId    - Parent's node ID
 *          index           - Index of the child (1-based)
 * output : nodeData        - Data pointer of the child node
 *                            Can be set to NULL
 * return : Pointer to use with stGetBrother on success,
 *          NULL on error
 ************************************************************************/
RvUint32* stGetChildByIndex(
    IN  HPST        hSyn,
    IN  int         parentNodeId,
    IN  int         index,
    OUT RvUint32**  nodeData);


/************************************************************************
 * stGetChildByIndexUnbounded
 * purpose: Get a child node of a parent node by its index, without
 *          checking the numOfChilds value. Done instead of fixing the
 *          H.450 ASN.
 * input  : hSyn            - Syntax information
 *          parentNodeId    - Parent's node ID
 *          index           - Index of the child (1-based)
 * output : nodeData        - Data pointer of the child node
 *                            Can be set to NULL
 * return : Pointer to use with stGetBrother on success,
 *          NULL on error
 ************************************************************************/
RvUint32* stGetChildByIndexUnbounded(
    IN  HPST        hSyn,
    IN  int         parentNodeId,
    IN  int         index,
    OUT RvUint32**  nodeData);


/************************************************************************
 * stGetBrother
 * purpose: Get the brother of a node to the right. The responsibility
 *          not to ask for a non-existant brother is on the caller.
 * input  : hSyn            - Syntax information
 *          nodePtr         - Node pointer to which we want the brother
 * output : nodeData        - Data pointer of the brother node
 *                            Can be set to NULL
 * return : Pointer to use (responsibly) in subsequent calls to
 *          stGetBrother()
 ************************************************************************/
RvUint32* stGetBrother(
    IN  HPST        hSyn,
    IN  RvUint32*   nodePtr,
    OUT RvUint32**  nodeData);


int stGetFirstValueNode(
    IN  HPST        hSyn,
    IN  int         parentNodeId);


#define stGetNextValueNode(hSyn,lastNodeId) stGetFirstValueNode(hSyn,lastNodeId)


/************************************************************************
 * stGetNodeDataByNodeId
 * purpose: Get the data pointer of a node by its node ID
 * input  : hSyn        - Syntax information
 *          nodeId      - Node ID
 * output : none
 * return : Data pointer of node information on success
 *          NULL on failure
 ************************************************************************/
RvUint32* stGetNodeDataByNodeId(IN HPST hSyn, IN int nodeId);


/************************************************************************
 * stGetNameByNameId
 * purpose: Get the name string by the name ID
 * input  : hSyn        - Syntax information
 *          nameId      - Name ID of the field
 * output : length      - Length on name in bytes
 *                        Can be set to NULL
 * return : Name of field on success
 *          NULL on failure
 ************************************************************************/
char* stGetNameByNameId(
    IN  HPST        hSyn,
    IN  int         nameId,
    OUT int*        length);


/************************************************************************
 * stGetNodeIdByName
 * purpose: Get the node ID of a type by the type's name string
 * input  : hSyn        - Syntax information
 *          name        - String name
 * return : Type's node ID on success
 *          Negative value on failure
 ************************************************************************/
int stGetNodeIdByName(IN HPST hSyn, IN char *name);


/************************************************************************
 * stGetNameIdByName
 * purpose: Get the name ID for a given name string
 * input  : hSyn        - Syntax information
 *          name        - String name
 * return : Name ID on success
 *          Negative value on failure
 ************************************************************************/
int stGetNameIdByName(IN HPST hSyn, IN char *name);


/************************************************************************
 * stGetNodeIdByNameId
 * purpose: Get the node ID of a type by the type's name ID
 * input  : hSyn        - Syntax information
 *          nameId      - String name's ID
 * return : Type's node ID on success
 *          Negative value on failure
 ************************************************************************/
int stGetNodeIdByNameId(IN HPST hSyn, IN int nameId);


/************************************************************************
 * stGetNameIdByNodeId
 * purpose: Get the name ID of a type by the type's node ID
 * input  : hSyn        - Syntax information
 *          nodeId      - Node ID
 * return : Type's name ID on success
 *          Negative value on failure
 ************************************************************************/
int stGetNameIdByNodeId(IN HPST hSyn, IN int nodeId);


/************************************************************************
 * stGetNameByNodeId
 * purpose: Get the name string of a type by the type's node ID
 * input  : hSyn        - Syntax information
 *          nodeId      - Node ID
 * return : Name string of node on success
 *          NULL on failure
 ************************************************************************/
char* stGetNameByNodeId(IN HPST hSyn, IN int nodeId);


/************************************************************************
 * stGetChildByNodeAndFieldName
 * purpose: Get a child's node ID by its parent's node ID and the child's
 *          name id.
 * input  : hSyn            - Syntax information
 *          parentNodeId    - Parent's node ID
 *          numFields       - Number of fields in the parent
 *          childNameId     - Name ID of the searched child
 * output : childNodeId     - Node ID of the child
 * return : Child's index on success (1-based)
 *          Negative value on failure
 ************************************************************************/
int stGetChildByNodeAndFieldName(
    IN  HPST    hSyn,
    IN  int     parentNodeId,
    IN  int     numFields,
    IN  int     childNameId,
    OUT int*    childNodeId);




#ifdef __cplusplus
}
#endif

#endif  /* _PSYNTREE_DB_H */