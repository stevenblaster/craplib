#include "control/logger.h"

namespace crap 
{
	IntrusiveList logger_list(offsetof(base_logger,logger_list_node));
	//Reserve
}