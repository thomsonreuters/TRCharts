[#ftl]
${copyright}
${autogenNote}

#import <${objcFilePrefix}Support/Common.hh>
#import <dispatch/dispatch.h>

namespace
{
	const int * const queueKey = new int(0);
	int * const queueValue = new int(0);
	bool queueVerificationEnabled = false;
}

void ${objcSupportNamespace}::markQueue(dispatch_queue_t queue)
{
	dispatch_queue_set_specific(queue, queueKey, queueValue, nullptr);
}

void ${objcSupportNamespace}::unmarkQueue(dispatch_queue_t queue)
{
	dispatch_queue_set_specific(queue, queueKey, nullptr, nullptr);
}

bool ${objcSupportNamespace}::isQueueMarked(void)
{
	return (dispatch_get_specific(queueKey) == queueValue);
}

void ${objcSupportNamespace}::enableQueueVerification(bool yes)
{
	queueVerificationEnabled = yes;
}

void ${objcSupportNamespace}::verifyCurrentQueue(void)
{
	if(queueVerificationEnabled) {
		assert(isQueueMarked() && "Not on marked queue");
	}
}