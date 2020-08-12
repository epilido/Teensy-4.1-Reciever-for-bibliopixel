
namespace CMDTYPE
{
	enum CMDTYPE
	{
		SETUP_DATA = 1,
		PIXEL_DATA = 2,
		BRIGHTNESS = 3,
		GETID      = 4,
		SETID      = 5,
		GETVER	   = 6
	};
}

namespace RETURN_CODES
{
	enum RETURN_CODES
	{
		SUCCESS = 255,
		REBOOT = 42,
		ERROR = 0,
		ERROR_SIZE = 1,
		ERROR_UNSUPPORTED = 2,
		ERROR_PIXEL_COUNT = 3,
		ERROR_BAD_CMD = 4,
	};
}
