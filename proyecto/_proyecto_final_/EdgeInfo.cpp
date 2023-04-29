#include "EdgeInfo.h"

EdgeInfo::EdgeInfo() {
  index = -1;
  positions.clear();
}

EdgeInfo::EdgeInfo(int _index) {
  index = _index;
  positions.clear();
}

EdgeInfo::~EdgeInfo() {
  index = -1;
  positions.clear();
}
