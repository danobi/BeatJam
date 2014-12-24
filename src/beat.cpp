#include "beat.h"

Beat::Beat()
{
	// get the image from the res.xml file
	_gameResources.loadXML("res.xml");
	setResAnim(_gameResources.getResAnim("circle"));

	// anchor is the "center" of the object
	setAnchor(Vector2(.5f,.5f));
}
