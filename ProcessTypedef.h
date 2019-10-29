namespace Process {
	typedef enum state_t {
		NEW = 0,
		READY = 1,
		RUN = 2,
		WAIT = 3,
		EXIT = 4,
	} state;

	typedef enum script_t {
		CALCULATE = 0,
		I_0 = 1,
		YIELD = 2,
		OUT = 3,
	} script;
}