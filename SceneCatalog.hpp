#ifndef SCENECATALOG_HPP
#define SCENECATALOG_hpp

#include "Scene.hpp"
#include <vector>

class SceneCatalog : public std::vector<SceneBuilder> {
    public:
        SceneCatalog(const std::vector<SceneBuilder> &__x);

        static SceneCatalog builtinScenes;


};

#endif