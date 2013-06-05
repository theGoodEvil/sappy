////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2013 the Good Evil GmbH
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#include "cube.h"
#include "scene.h"

using namespace Sifteo;

namespace sappy {

Cube::Cube()
: nextAction(IDLE) {
}

Scene* Cube::getScene() {
  return scene;
}

void Cube::setScene(Scene* scene) {
  this->scene = scene;

  if (nextAction == IDLE) {
    nextAction = PAINT;
  }
}

void Cube::setLoaderConfig(AssetLoader* loader, AssetConfiguration<1>* config) {
  this->loader = loader;
  this->config = config;

  this->nextAction = LOAD;
}

void Cube::connect(CubeID id) {
  LOG("Cube::connect (cube %d)\n", (int)id);

  this->id = id;
  vbuf.attach(id);
  vbuf.initMode(BG0_ROM);

  loader->start(*config, CubeSet(id));
}

void Cube::disconnect() {
  LOG("Cube::disconnect (cube %d)\n", (int)id);

  this->id = CubeID();
  this->nextAction = IDLE;
}

void Cube::refresh() {
  LOG("Cube::refresh (cube %d)\n", (int)id);

  if (id.isDefined()) {
    this->nextAction = PAINT;
  }
}

void Cube::touch() {
  scene->onTouch(id, vbuf);
}

void Cube::neighborAdd(Side side, CubeID otherCube, Side otherSide) {
  scene->onNeighborAdd(side, otherCube, otherSide, id, vbuf);
}

void Cube::neighborRemove(Side side, CubeID otherCube, Side otherSide) {
  scene->onNeighborRemove(side, otherCube, otherSide, id, vbuf);
}


void Cube::update() {
  if (id.isDefined()) {
    switch (nextAction) {
      case LOAD:
        if (scene->load(loader, id, vbuf)) nextAction = PAINT;
        break;
      case PAINT:
        scene->onPaint(id, vbuf);
        nextAction = IDLE;
        break;
      case IDLE:
        scene->onIdle(id, vbuf);
        break;
    }
  }
}

}
