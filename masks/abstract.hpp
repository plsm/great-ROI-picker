#ifndef ABSTRACTROI_H
#define ABSTRACTROI_H

#include <string>
#include <vector>

class AbstractMask
{
protected:
	AbstractMask () {}
	virtual ~AbstractMask () {}
	static std::string mask_filename (const std::string &folder, const std::string &default_name, const std::vector<std::string> names, int name_index, unsigned int image_index);
	static std::string roi_properties_filename (unsigned int mask_index);
public:
	/**
	 * @brief save_masks Creates png files that represent the regions of interest
	 * that the user selected. These png files are masks that are used to select
	 * pixels that belong to a particular region of interest. dsad
	 *
	 * @param folder Folder where the ROI files are created
	 * @param width Width in pixels of the image
	 * @param height Height in pixels of the image
	 * @param names Vector with mask names to be used. If empty default names are used.
	 */
	virtual unsigned int save_masks (const std::string &folder, int width, int height, const std::vector<std::string> names, unsigned int image_index) const = 0;
	/**
	 * @brief save_properties Saves the properties of the regions of interest that
	 * the user selected to a file name roi.properties.
	 *
	 * @param folder The folder where the file named roi.properties is saved.
	 * @param index The index of this mask.
	 */
	virtual void save_properties (const std::string &folder, unsigned int index) const = 0;
#define LOCK_PROPERTY(GRAPHICS, FIELD) \
	(this->GRAPHICS == NULL ? this->FIELD : this->GRAPHICS->FIELD)
};

#endif // ABSTRACTROI_H
