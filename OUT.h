#include "ProcessScript.h"
#include <string>

namespace Process {
	class OUT : public ProcessScript {
	public:
		OUT() { ProcessScript(); }
		void print_message();
	private:
		std::string message;
	};
}
