#include "Page.h"

int Page::get_min_nonexist(vector<int> vect) {
	int min_nonexistent = 1;

	if (vect.size() != 0)
	{
		for (int i = 0; i < *max_element(vect.begin(), vect.end()) + 2; i++)
		{
			if (vect.end() == find(vect.begin(), vect.end(), min_nonexistent))
				break;

			min_nonexistent++;
		}
	}
	return min_nonexistent;
}

