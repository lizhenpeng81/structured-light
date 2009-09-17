#include "FloodFillDecoder.h"

void FloodFillDecoder::unwrapPhase() {
	toProcess.clear();
	int center = (getHeight() * getWidth()) / 2 + getWidth() / 2;
	toProcess.push_back(center);
	ready[center] = false;

	while (!toProcess.empty()) {
    int i = toProcess.front();
    toProcess.pop_front();
    float sourcePhase = phase[i];

    int x = i % width;
    int y = i / width;
    if (y > 0) // up
      unwrapPhase(i - width, sourcePhase);
    if (y < height - 1) // down
      unwrapPhase(i + width, sourcePhase);
    if (x > 0) // left
      unwrapPhase(i - 1, sourcePhase);
    if (x < width - 1) // right
      unwrapPhase(i + 1, sourcePhase);
  }
}

void FloodFillDecoder::unwrapPhase(int target, float sourcePhase) {
	if(ready[target]) {
		float diff = phase[target] - (sourcePhase - (int) sourcePhase);
		if(diff > .5)
			diff--;
		else if(diff < -.5)
			diff++;
		phase[target] = sourcePhase + diff;

		ready[target] = false;
		toProcess.push_back(target);
	}
}
