#include <sstream>

#include "abstract.hpp"

using namespace std;

string AbstractMask::mask_filename (const string &folder, const string &default_name, const std::vector<std::string> names, int name_index, unsigned int image_index)
{
	string basename;
	if (names.size () > 0)
		basename = names [name_index] + ".png";
	else {
		int size = snprintf (nullptr, 0, default_name.c_str (), image_index);
		if (size < 0)
			return "ERROR";
		vector<char> buffer (size + 1); // note +1 for null terminator
		snprintf (&buffer [0], buffer.size(), default_name.c_str (), image_index);
		basename = string (buffer.begin (), buffer.end ());
	}
	return folder + "/" + basename;
}

string AbstractMask::roi_properties_filename (unsigned int mask_index)
{
	ostringstream result;
	result << "roi-" << mask_index << ".properties";
	return result.str ();
}
