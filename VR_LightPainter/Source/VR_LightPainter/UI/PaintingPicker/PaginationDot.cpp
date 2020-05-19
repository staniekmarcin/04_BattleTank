


#include "PaginationDot.h"

void UPaginationDot::SetActive(bool bActive)
{
	DotImage->SetOpacity(bActive ? 1 : DisabledOpacity);

}
