#pragma once
#include <memory>
#include <list>
#include <map>

#include <glm/glm.hpp>

class Scenegl;

class Object {
public:
  Object() = default;
  Object(const Object&) = default;
  Object(Object&&) = default;
  virtual ~Object() = default;

  virtual bool update(Scenegl &scene, float dt) = 0;
  virtual void render(Scenegl &scene) = 0;
  virtual void onClick(Scenegl &scene) {};

  glm::vec3 position{0,0,0};
  glm::vec3 rotation{0,0,0};
  glm::vec3 scale{1,1,1};
  glm::mat4 modelMatrix{1};

protected:
  void generateModelMatrix();
};

