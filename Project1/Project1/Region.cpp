#include "Region.h"

/** Find the parent of a region.
  * @author CuiYuxin
  * @param Region* p
  * @return Region* */
Region* Region::FindParent(Region* p)
{
	if (p->Father != nullptr)
	{
		p->Father = FindParent(p->Father);
		return p->Father;
	}
	else return p;
}
