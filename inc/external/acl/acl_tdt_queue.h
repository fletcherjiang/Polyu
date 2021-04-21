/**
* @file acl_tdt_queue.h
*
* Copyright (C) Huawei Technologies Co., Ltd. 2020-2021. All Rights Reserved.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#ifndef INC_EXTERNAL_ACL_ACL_TDT_QUEUE_H_
#define INC_EXTERNAL_ACL_ACL_TDT_QUEUE_H_

#include "acl/acl_base.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ACL_TDT_QUEUE_PERMISSION_MANAGE 1
#define ACL_TDT_QUEUE_PERMISSION_DEQUEUE 2
#define ACL_TDT_QUEUE_PERMISSION_ENQUEUE 4

typedef void *acltdtBuf;
typedef struct tagMemQueueAttr acltdtQueueAttr;
typedef struct acltdtQueueRouteList acltdtQueueRouteList;
typedef struct acltdtQueueRouteQueryInfo acltdtQueueRouteQueryInfo;
typedef struct acltdtQueueRoute acltdtQueueRoute;

enum acltdtQueueAttrType {
    ACL_TDT_QUEUE_NAME_PTR = 0,
    ACL_TDT_QUEUE_DEPTH_UINT32
};

enum acltdtQueueRouteParamType {
    ACL_TDT_QUEUE_ROUTE_SRC_UINT32 = 0,
    ACL_TDT_QUEUE_ROUTE_DST_UINT32,
    ACL_TDT_QUEUE_ROUTE_STATUS_INT32
};

enum acltdtQueueRouteQueryMode {
    ACL_TDT_QUEUE_ROUTE_QUERY_SRC = 0,
    ACL_TDT_QUEUE_ROUTE_QUERY_DST,
    ACL_TDT_QUEUE_ROUTE_QUERY_SRC_AND_DST
};

enum acltdtQueueRouteQueryInfoParamType {
    ACL_TDT_QUEUE_ROUTE_QUERY_MODE_ENUM = 0,
    ACL_TDT_QUEUE_ROUTE_QUERY_SRC_ID_UINT32,
    ACL_TDT_QUEUE_ROUTE_QUERY_DST_ID_UINT32
};

/**
 * @ingroup AscendCL
 * @brief create queue
 *
 * @param attr [IN] pointer to the queue attr
 * @param qid [OUT] pointer to the qid
 *
 * @retval ACL_SUCCESS  The function is successfully executed.
 * @retval OtherValues Failure
 */
ACL_FUNC_VISIBILITY aclError acltdtCreateQueue(const acltdtQueueAttr *attr, uint32_t *qid);

/**
 * @ingroup AscendCL
 * @brief destroy queue
 *
 * @param qid [IN] qid which to be destroyed
 *
 * @retval ACL_SUCCESS  The function is successfully executed.
 * @retval OtherValues Failure
 */
ACL_FUNC_VISIBILITY aclError acltdtDestroyQueue(uint32_t qid);

/**
 * @ingroup AscendCL
 * @brief enqueue function
 *
 * @param qid [IN] qid 
 * @param buf [IN] acltdtBuf
 * @param timeout [IN] timeout
 *
 * @retval ACL_SUCCESS  The function is successfully executed.
 * @retval OtherValues Failure
 */
ACL_FUNC_VISIBILITY aclError acltdtEnqueue(uint32_t qid, acltdtBuf buf, int32_t timeout);

/**
 * @ingroup AscendCL
 * @brief dequeue function
 *
 * @param qid [IN] qid 
 * @param buf [OUT] pointer to the acltdtBuf
 * @param timeout [IN] timeout
 *
 * @retval ACL_SUCCESS  The function is successfully executed.
 * @retval OtherValues Failure
 */
ACL_FUNC_VISIBILITY aclError acltdtDequeue(uint32_t qid, acltdtBuf *buf, int32_t timeout);

/**
 * @ingroup AscendCL
 * @brief grant queue to other process
 *
 * @param qid [IN] qid 
 * @param pid [IN] pid of dst process
 * @param permission [IN] permission of queue
 * @param timeout [IN] timeout
 *
 * @retval ACL_SUCCESS  The function is successfully executed.
 * @retval OtherValues Failure
 */
ACL_FUNC_VISIBILITY aclError acltdtGrantQueue(uint32_t qid, int32_t pid, uint32_t permission, int32_t timeout);

/**
 * @ingroup AscendCL
 * @brief attach queue in current process
 *
 * @param qid [IN] qid 
 * @param timeout [IN] timeout
 * @param permission [OUT] permission of queue
 *
 * @retval ACL_SUCCESS  The function is successfully executed.
 * @retval OtherValues Failure
 */
ACL_FUNC_VISIBILITY aclError acltdtAttachQueue(uint32_t qid, int32_t timeout, uint32_t *permission);

/**
 * @ingroup AscendCL
 * @brief bind queue routes
 *
 * @param qRouteList [IN|OUT] pointer to the route list
 *
 * @retval ACL_SUCCESS  The function is successfully executed.
 * @retval OtherValues Failure
 */
ACL_FUNC_VISIBILITY aclError acltdtBindQueueRoutes(acltdtQueueRouteList *qRouteList);

/**
 * @ingroup AscendCL
 * @brief unbind queue routes
 *
 * @param qRouteList [IN|OUT] pointer to the route list
 *
 * @retval ACL_SUCCESS  The function is successfully executed.
 * @retval OtherValues Failure
 */
ACL_FUNC_VISIBILITY aclError acltdtUnbindQueueRoutes(acltdtQueueRouteList *qRouteList);

/**
 * @ingroup AscendCL
 * @brief query queue routes according to query mode
 * 
 * @param queryInfo [IN] pointer to the queue route query info
 * @param qRouteList [IN|OUT] pointer to the route list
 *
 * @retval ACL_SUCCESS  The function is successfully executed.
 * @retval OtherValues Failure
 */
ACL_FUNC_VISIBILITY aclError acltdtQueryQueueRoutes(const acltdtQueueRouteQueryInfo *queryInfo,
                                                    acltdtQueueRouteList *qRouteList);

/**
 * @ingroup AscendCL
 * @brief alloc acltdtBuf
 * 
 * @param size [IN] alloc buf size
 * @param buf [OUT] pointer to the acltdtBuf
 *
 * @retval ACL_SUCCESS  The function is successfully executed.
 * @retval OtherValues Failure
 */
ACL_FUNC_VISIBILITY aclError acltdtAllocBuf(size_t size, acltdtBuf *buf);

/**
 * @ingroup AscendCL
 * @brief free acltdtBuf
 * 
 * @param buf [IN] pointer to the acltdtBuf
 *
 * @retval ACL_SUCCESS  The function is successfully executed.
 * @retval OtherValues Failure
 */
ACL_FUNC_VISIBILITY aclError acltdtFreeBuf(acltdtBuf buf);

/**
 * @ingroup AscendCL
 * @brief get data buf address
 * 
 * @param buf [IN] acltdtBuf
 * @param dataPtr [OUT] pointer to the data ptr
 * @param size [OUT] pointer to the size
 *
 * @retval ACL_SUCCESS  The function is successfully executed.
 * @retval OtherValues Failure
 */
ACL_FUNC_VISIBILITY aclError acltdtGetBufData(const acltdtBuf buf, void **dataPtr, size_t *size);

/**
 * @ingroup AscendCL
 * @brief Create the queue attr
 *
 *
 * @retval null for failed
 * @retval OtherValues success
 */
ACL_FUNC_VISIBILITY acltdtQueueAttr *acltdtCreateQueueAttr();

/**
 * @ingroup AscendCL
 * @brief Destroy the queue attr
 *
 * @param attr [IN]  pointer to the queue attr
 *
 * @retval ACL_SUCCESS  The function is successfully executed.
 * @retval OtherValues Failure
 *
 */
ACL_FUNC_VISIBILITY aclError acltdtDestroyQueueAttr(const acltdtQueueAttr *attr);

/**
 * @ingroup AscendCL
 * @brief Set parameter for queue attr
 *
 * @param attr [IN|OUT] pointer to the queue attr
 * @param type [IN]    parameter type
 * @param len [IN]       parameter length
 * @param param [IN]        pointer to parameter value
 *
 * @retval ACL_SUCCESS for success, other for failure
 */
ACL_FUNC_VISIBILITY aclError acltdtSetQueueAttr(acltdtQueueAttr *attr,
                                                acltdtQueueAttrType type,
                                                size_t len,
                                                const void *param);

/**
 * @ingroup AscendCL
 *
 * @brief Get parameter for queue attr.
 *
 * @param attr [IN]   pointer to the queue attr
 * @param type [IN]     parameter type
 * @param len [IN]        parameter length
 * @param paramRetSize [OUT] pointer to parameter real length
 * @param param [OUT]        pointer to parameter value
 *
 * @retval ACL_SUCCESS for success, other for failure
 */
ACL_FUNC_VISIBILITY aclError acltdtGetQueueAttr(const acltdtQueueAttr *attr,
                                                acltdtQueueAttrType type,
                                                size_t len,
                                                size_t *paramRetSize,
                                                void *param);

/**
 * @ingroup AscendCL
 * @brief Create the queue route
 *
 * @param srcId [IN]   src id of queue route
 * @param dstId [IN]   dst id of queue route
 * 
 * @retval null for failed
 * @retval OtherValues success
 */
ACL_FUNC_VISIBILITY acltdtQueueRoute* acltdtCreateQueueRoute(uint32_t srcId, uint32_t dstId);

/**
 * @ingroup AscendCL
 * @brief Destroy the queue attr
 *
 * @param route [IN]  pointer to the queue route
 *
 * @retval ACL_SUCCESS  The function is successfully executed.
 * @retval OtherValues Failure
 *
 */
ACL_FUNC_VISIBILITY aclError acltdtDestroyQueueRoute(const acltdtQueueRoute *route);

/**
 * @ingroup AscendCL
 *
 * @brief Get parameter for queue route.
 *
 * @param route [IN]   pointer to the queue route
 * @param type [IN]     parameter type
 * @param len [IN]        parameter length
 * @param paramRetSize [OUT] pointer to parameter real length
 * @param param [OUT]        pointer to parameter value
 *
 * @retval ACL_SUCCESS for success, other for failure
 */
ACL_FUNC_VISIBILITY aclError acltdtGetQueueRouteParam(const acltdtQueueRoute *route,
                                                      acltdtQueueRouteParamType type,
                                                      size_t len,
                                                      size_t *paramRetSize,
                                                      void *param);

/**
 * @ingroup AscendCL
 * @brief Create the queue route list
 * 
 * @retval null for failed
 * @retval OtherValues success
 */
ACL_FUNC_VISIBILITY acltdtQueueRouteList* acltdtCreateQueueRouteList();

/**
 * @ingroup AscendCL
 * @brief Destroy the queue route list
 *
 * @param routeList [IN]  pointer to the queue route list
 *
 * @retval ACL_SUCCESS  The function is successfully executed.
 * @retval OtherValues Failure
 *
 */
ACL_FUNC_VISIBILITY aclError acltdtDestroyQueueRouteList(const acltdtQueueRouteList *routeList);

/**
 * @ingroup AscendCL
 * @brief add queue route to the route list
 *
 * @param routeList [IN|OUT]  pointer to the queue route list
 * @param route [IN]  pointer to the queue route
 *
 * @retval ACL_SUCCESS  The function is successfully executed.
 * @retval OtherValues Failure
 *
 */
ACL_FUNC_VISIBILITY aclError acltdtAddQueueRoute(acltdtQueueRouteList *routeList, const acltdtQueueRoute *route);

/**
 * @ingroup AscendCL
 * @brief get queue route from route list
 *
 * @param routeList [IN]  pointer to the queue route list
 * @param index [IN]  index of queue route in route list
 * @param route [IN|OUT]  pointer to the queue route
 *
 * @retval ACL_SUCCESS  The function is successfully executed.
 * @retval OtherValues Failure
 *
 */
ACL_FUNC_VISIBILITY aclError acltdtGetQueueRoute(const acltdtQueueRouteList *routeList,
                                                 size_t index,
                                                 acltdtQueueRoute *route);

/**
 * @ingroup AscendCL
 * @brief Create the queue route query info
 * 
 * @retval null for failed
 * @retval OtherValues success
 */
ACL_FUNC_VISIBILITY  acltdtQueueRouteQueryInfo* acltdtCreateQueueRouteQueryInfo();

/**
 * @ingroup AscendCL
 * @brief Destroy the queue route query info
 *
 * @param info [IN]  pointer to the queue route info
 *
 * @retval ACL_SUCCESS  The function is successfully executed.
 * @retval OtherValues Failure
 *
 */
ACL_FUNC_VISIBILITY aclError acltdtDestroyQueueRouteQueryInfo(const acltdtQueueRouteQueryInfo *info);

/**
 * @ingroup AscendCL
 * @brief Set parameter for queue route info
 *
 * @param attr [IN|OUT] pointer to the queue route info
 * @param type [IN]    parameter type
 * @param len [IN]       parameter length
 * @param param [IN]        pointer to parameter value
 *
 * @retval ACL_SUCCESS for success, other for failure
 */
ACL_FUNC_VISIBILITY aclError acltdtSetQueueRouteQueryInfo(acltdtQueueRouteQueryInfo *param,
                                                          acltdtQueueRouteQueryInfoParamType type,
                                                          size_t len,
                                                          const void *value);


#ifdef __cplusplus
}
#endif

#endif //INC_EXTERNAL_ACL_ACL_TDT_QUEUE_H_