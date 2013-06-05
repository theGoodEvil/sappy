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

#include "app.h"

using namespace Sifteo;

namespace sappy {

App* App::instance = 0;

App::App() {
  ASSERT(instance == 0 && "You can only create one App instance");
  instance = this;

  Events::cubeConnect.set(&App::onCubeConnect, this);
  Events::cubeDisconnect.set(&App::onCubeDisconnect, this);
  Events::cubeRefresh.set(&App::onCubeRefresh, this);
  Events::cubeTouch.set(&App::onCubeTouch, this);

  Events::neighborAdd.set(&App::onNeighborAdd, this);
  Events::neighborRemove.set(&App::onNeighborRemove, this);
}

App* App::getInstance() {
  return instance;
}

void App::run() {
  for(CubeID cid : CubeSet::connected()) {
    onCubeConnect(cid);
  }
  
  for (;;) {
    System::paint();

    timeStep.next();
    onLoop(timeStep.delta());

    for(Cube& cube : cubes) {
      cube.update();
    }
  }
}

Cube& App::getCube(unsigned cid) {
  ASSERT(cid < CUBE_ALLOCATION);
  return cubes[cid];
}

void App::onCubeConnect(unsigned cid) {
  cubes[cid].connect(cid);
}

void App::onCubeDisconnect(unsigned cid) {
  cubes[cid].disconnect();
}

void App::onCubeRefresh(unsigned cid) {
  cubes[cid].refresh();
}

void App::onCubeTouch(unsigned cid) {
  cubes[cid].touch();
}

void App::onNeighborAdd(unsigned cube0, unsigned side0, unsigned cube1, unsigned side1) {
  cubes[cube0].neighborAdd((Side)side0, cube1, (Side)side1);
}

void App::onNeighborRemove(unsigned cube0, unsigned side0, unsigned cube1, unsigned side1) {
  cubes[cube0].neighborRemove((Side)side0, cube1, (Side)side1);
}

}
