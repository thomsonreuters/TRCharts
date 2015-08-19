[#ftl]
${copyright}
${autogenNote}

#include <Foundation/Foundation.h>

#include <memory>

namespace ${objcSupportNamespace}
{
	/*typedef NSString __strong * StrongStringPtr;

	typedef NSArray __strong * StrongArrayPtr;

	typedef id __strong StrongAnyPtr;*/

	void markQueue(dispatch_queue_t queue);

	void unmarkQueue(dispatch_queue_t queue);

	bool isQueueMarked(void);

	void enableQueueVerification(bool yes);

	void verifyCurrentQueue(void);
}