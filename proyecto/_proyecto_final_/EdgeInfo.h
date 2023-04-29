#ifndef _EDGEINFO_H
#define _EDGEINFO_H

#include <vector>

// ******************************************************************************************************************************
// Clase EdgeInfo: Construir un objeto de tipo informativo que almacenará los indices donde participa en las parejas de aristas
// Atributos:
//         - index
//         - vector donde participa respecto al indice en AdjList
// *******************************************************************************************************************************
class EdgeInfo {
  private:
    int index;
    std::vector<int> positions;
  public:
    EdgeInfo();  //constructor
    EdgeInfo(int _index);
    ~EdgeInfo(); //destructor

  // friend class declaration
  // clase amiga puede acceder a las partes privadas
  friend class Graph;
};

#endif // _EDGEINFO_H
