#ifndef ABSTRACTMANAGER_HPP
#define ABSTRACTMANAGER_HPP

#include <string>

class AbstractManager
{
protected:
	AbstractManager (std::string label):
	   label (label)
	{}
	virtual ~AbstractManager () {}
public:
	const std::string label;
	virtual void setup_components (int width, int height) = 0;
	virtual void update_number_components (int width, int height) = 0;
	virtual void create_mask_files (const std::string &folder, int width, int height, bool use_default_names) = 0;
	virtual void create_property_files (const std::string &folder) = 0;
};

#endif // ABSTRACTMANAGER_HPP
