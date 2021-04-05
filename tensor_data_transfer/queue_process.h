/**
* @file queue_processor.h
*
* Copyright (C) Huawei Technologies Co., Ltd. 2019-2020. All Rights Reserved.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/
#ifndef QUEUE_PROCESSOR_H
#define QUEUE_PROCESSOR_H

#include <mutex>
#include <memory>
#include <map>
#include "queue.h"
#include "mmpa/mmpa_api.h"

namespace acl {

typedef struct QueueDataMutex {
    std::mutex muForEnqueue;
    std::mutex muForDequeue;
} QueueDataMutex;

enum PID_QUERY_TYPE {
    CP_PID,
    QS_PID
};

using QueueDataMutexPtr = std::shared_ptr<QueueDataMutex>;

class QueueProcessor
{
public:
    virtual aclError acltdtCreateQueue(const acltdtQueueAttr *attr, uint32_t *queueId);

    virtual aclError acltdtDestroyQueue(uint32_t queueId);

    virtual aclError acltdtEnqueueBuf(uint32_t queueId, acltdtBuf buf, int32_t timeout);

    virtual aclError acltdtDequeueBuf(uint32_t queueId, acltdtBuf *buf, int32_t timeout);

    virtual aclError acltdtGrantQueue(uint32_t queueId, int32_t pid, uint32_t flag, int32_t timeout);

    virtual aclError acltdtAttachQueue(uint32_t queueId, int32_t timeout, uint32_t *flag);

    virtual aclError acltdtBindQueueRoutes(acltdtQueueRouteList *qRouteList);

    virtual aclError acltdtUnbindQueueRoutes(acltdtQueueRouteList *qRouteList);

    virtual aclError acltdtQueryQueueRoutes(const acltdtQueueRouteQueryInfo *queryInfo,
                                                        acltdtQueueRouteList *qRouteList);

    virtual aclError acltdtAllocBuf(size_t size, acltdtBuf *buf);

    virtual aclError acltdtFreeBuf(acltdtBuf buf);

    virtual aclError acltdtGetBufData(const acltdtBuf buf, void **dataPtr, size_t *size);

    aclError SendBindUnbindMsg(acltdtQueueRouteList *qRouteList,
                                               int32_t devieId,
                                               bool isBind,
                                               bool isMbuffAlloc,
                                               rtEschedEventSummary_t &eventSum,
                                               rtEschedEventReply_t &ack);

    aclError SendConnectQsMsg(int32_t devieId, rtEschedEventSummary_t &eventSum, rtEschedEventReply_t &ack);
    aclError GetDstInfo(int32_t deviceId, PID_QUERY_TYPE type, pid_t &dstPid);
    bool HasQueuePermission(rtMemQueueShareAttr_t &permission);
    aclError GetQueuePermission(int32_t deviceId, uint32_t qid, rtMemQueueShareAttr_t &permission);
    aclError GetQueueRouteNum(const acltdtQueueRouteQueryInfo *queryInfo,
                                                          int32_t deviceId,
                                                          rtEschedEventSummary_t &eventSum,
                                                          rtEschedEventReply_t &ack);

    aclError QueryQueueRoutes(const acltdtQueueRouteQueryInfo *queryInfo,
                                              int32_t deviceId,
                                              bool isMbufAlloc,
                                              size_t routeNum,
                                              rtEschedEventSummary_t &eventSum,
                                              rtEschedEventReply_t &ack,
                                              acltdtQueueRouteList *qRouteList);
    QueueProcessor() = default;
    ~QueueProcessor() = default;

    // not allow copy constructor and assignment operators
    QueueProcessor(const QueueProcessor &) = delete;

    QueueProcessor &operator=(const QueueProcessor &) = delete;

    QueueProcessor(QueueProcessor &&) = delete;

    QueueProcessor &&operator=(QueueProcessor &&) = delete;

protected:
    std::recursive_mutex muForQueueCtrl;
    std::mutex mu_;
    std::map<uint32_t, QueueDataMutexPtr> muForQueue_;
    bool isQsInit_ = false;
    uint32_t qsContactId_ = 0;

private:
};

}



#endif // QUEUE_PROCESS_H