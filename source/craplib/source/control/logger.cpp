#include "control/logger.h"

namespace crap 
{
	//IntrusiveList logger_list(offsetof(base_logger,logger_list_node));
	intrusive_list<base_logger> intr_logger_list;
}